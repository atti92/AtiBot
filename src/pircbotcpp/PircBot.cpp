
//This define is for pircbot to know that
//yes I am a Windows XP machine
#ifdef _WIN32
#define _WIN32_WINNT 0x0501
#endif

//pircbot includes
#include <pircbot/PircBot.h>
#include <pircbot/impl/OutputThread.h>
#include <pircbot/impl/InputThread.h>
#include <pircbot/impl/Socket.h>
#include <pircbot/impl/Queue.h>
#include <pircbot/User.h>
#include <pircbot/impl/Exceptions.h>
#include <pircbot/impl/IdentServer.h>
#include <pircbot/Colors.h>

//std includes
#include <string>
#include <map>
using namespace std;

//boost includes
//Disable warnings with the boost library
#ifdef _WIN32
#  pragma warning(disable:4267)
#endif

#include <boost/thread/recursive_mutex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "boost/date_time/local_time/local_time.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
using namespace boost;
using namespace boost::posix_time;
using namespace boost::gregorian; 
using namespace boost::local_time;

#ifdef _WIN32
#  pragma warning(default: 4267)  	
#endif


//asio includes
//Disable warnings with the asio library
#ifdef _WIN32
#  pragma warning(push)	
#  pragma warning(disable:4267)
#  pragma warning(disable:4554)
#endif

#include <asio.hpp>
using asio::ip::tcp;

#ifdef _WIN32
#  pragma warning(default: 4267)  	
#  pragma warning(default: 4554)
#endif

/* Disable Windows VC 7.x warning about 
 * it ignoring the throw specification
 */
#ifdef _WIN32
#    pragma warning( disable : 4290 )
#endif


namespace pircbot
{
namespace impl
{


class PircBotImpl 
{
	public:
		PircBotImpl(PircBot &bot)
			: m_verbose(false),
			  m_name("PircBotcpp"),
			  m_nick("PircBotcpp"),
			  m_login("PircBotcpp"),
			  m_version("PircBotcpp " + string(VERSION) + " C++ IRC Bot - http://pircbotcpp.sourceforge.net/"),
			  m_autoNickChange(false),
			  m_messageDelay(1000),
			  m_tokenDelimters(" \t\n\r\f"),
			  m_bot(bot),
			  m_finger("You ought to be arrested for fingering a bot!"),
			  m_channelPrefixes("#&+!")
		{
		}
		string m_server;
		int m_port;
		string m_password;

		//Mutex for this class
		recursive_mutex m_this;

		//Mutex for m_channels;
		recursive_mutex m_channelsMutex;
		map<string, map<User, User> > m_channels;
		asio::io_service io_service;


		// Outgoing message stuff.
	    Queue m_outQueue;
		int m_messageDelay;
	
		// Default settings for the PircBot.
        bool m_autoNickChange;
		bool m_verbose;
        string m_name;
		string m_nick;
		string m_login;
		string m_version;
		string m_finger; 
		string m_channelPrefixes;

		//Connection stuff
		shared_ptr<InputThread> m_inputThread;
		shared_ptr<OutputThread> m_outputThread;
		
		//Tokenizer information
		char_separator<char> m_tokenDelimters;
		PircBot &m_bot;
		map<string, string> m_topics;
		
		//1 to 1 with the sockets
		Socket m_socket;
		shared_ptr<IdentServer> m_identServer;

	   /**
        * The definitive version number of this release of PircBot.
        * (Note: Change this before automatically building releases)
        */
        static const char *VERSION;
		
		static const int OP_ADD;
		static const int OP_REMOVE;
		static const int VOICE_ADD;
		static const int VOICE_REMOVE;

       /**
		* Sets the internal nick of the bot.  This is only to be called by the
		* PircBot class in response to notification of nick changes that apply
		* to us.
		* 
		* @param nick The new nick.
		*/
		void setNick(string nick) 
		{
			m_nick = nick;
		}

	   /**
		* This method is called by the PircBot when a numeric response
		* is received from the IRC server.  We use this method to
		* allow PircBot to process various responses from the server
		* before then passing them on to the onServerResponse method.
		*  <p>
		* Note that this method is private and should not appear in any
		* of the javadoc generated documenation.
		* 
		* @param code The three-digit numerical code for the response.
		* @param response The full response from the IRC server.
		*/
	    void processServerResponse(const int &code, const string &response) 
		{
			if (code == ReplyConstants::RPL_LIST) 
			{
				// This is a bit of information about a channel.
				size_t firstSpace = response.find(' ');
				size_t secondSpace = response.find(' ', firstSpace + 1);
				size_t thirdSpace = response.find(' ', secondSpace + 1);
				size_t colon = response.find(':');
				string channel = response.substr(firstSpace + 1, secondSpace - (firstSpace + 1));
				int userCount = 0;
				try 
				{
					userCount = lexical_cast<int>(response.substr(secondSpace + 1, thirdSpace - (secondSpace + 1)));
				}
				catch (bad_lexical_cast &) 
				{
					// Stick with the value of zero.
				}
				string topic = response.substr(colon + 1);
				m_bot.onChannelInfo(channel.c_str(), userCount, topic.c_str());
			}
			else if (code == ReplyConstants::RPL_TOPIC) 
			{
				// This is topic information about a channel we've just joined.
				size_t firstSpace = response.find(' ');
				size_t secondSpace = response.find(' ', firstSpace + 1);
				size_t colon = response.find(':');
				string channel = response.substr(firstSpace + 1, secondSpace - (firstSpace + 1));
				string topic = response.substr(colon + 1);
	            
				m_topics.insert(pair<string, string>(channel, topic));
	            
				// For backwards compatibility only - this onTopic method is deprecated.
				m_bot.onTopic(channel.c_str(), topic.c_str());
			}
			else if (code == ReplyConstants::RPL_TOPICINFO) 
			{
				typedef tokenizer<char_separator<char> > tokenizer;
				tokenizer tokens(response, m_tokenDelimters);
				tokenizer::iterator tok_iter = tokens.begin();
				
				if(tok_iter == tokens.end())
				{
					m_bot.onServerResponse(code, response.c_str());
					return;
				}
				string channel = *tok_iter;
				++tok_iter;

				if(tok_iter == tokens.end())
				{
					m_bot.onServerResponse(code, response.c_str());
					return;
				}
				string setBy = *tok_iter;
				++tok_iter;
				
				long date = 0;
				try 
				{
					if(tok_iter == tokens.end())
					{
						m_bot.onServerResponse(code, response.c_str());
						return;
					}
					date = (lexical_cast<int>(*tok_iter)) * 1000;
				}
				catch (bad_lexical_cast e) {
					// Stick with the default value of zero.
				}
	            
				typedef map<string,string> mapString;
				mapString::iterator it;
				it = m_topics.find(channel);
				if(it != m_topics.end())
				{
					string topic = it->second;
					m_topics.erase(channel);
					m_bot.onTopic(channel.c_str(), topic.c_str(), setBy.c_str(), date, false);
				}
			}
			else if (code == ReplyConstants::RPL_NAMREPLY) 
			{
				// This is a list of nicks in a channel that we've just joined.
				size_t channelEndIndex = response.find(" :");
				size_t i = response.rfind(' ', channelEndIndex - 1) + 1;
				string channel = response.substr(i, channelEndIndex - i);
	            
				typedef tokenizer<char_separator<char> > tokenizer;
				tokenizer tokens(response.substr(response.find(" :") + 2), m_tokenDelimters);
				tokenizer::iterator tok_iter = tokens.begin();

				while (tok_iter != tokens.end()) 
				{
					string nick = *tok_iter;
					string prefix = "";
					if (starts_with(nick, "@"))
					{
						// User is an operator in this channel.
						prefix = "@";
					}
					else if (starts_with(nick, "+"))
					{
						// User is voiced in this channel.
						prefix = "+";
					}
					else if (starts_with(nick, "."))
					{
						// Some wibbly status I've never seen before...
						prefix = ".";
					}
					nick = nick.substr(prefix.length());
					addUser(channel, User(prefix.c_str(), nick.c_str()));
					++tok_iter;
				}
			}
			else if (code == ReplyConstants::RPL_ENDOFNAMES) 
			{
				// This is the end of a NAMES list, so we know that we've got
				// the full list of users in the channel that we just joined.
				size_t i = response.find(' ') + 1;
				size_t j = response.find(" :");
				string channel = response.substr(i, j - i);
				unsigned int sizeOfArray;
				User *users = m_bot.getUsers(channel.c_str(), sizeOfArray);
				m_bot.onUserList(channel.c_str(), users, sizeOfArray);
			}

			m_bot.onServerResponse(code, response.c_str());
		}

	   /**
		* Add a user to the specified channel in our memory.
		* Overwrite the existing entry if it exists.
		*/
		void addUser(string channel, const User &user) 
		{

			to_lower(channel);
			recursive_mutex::scoped_lock synchronized(m_channelsMutex);
			map<User, User> users;
			users.insert(pair<User, User>(user, user));
			m_channels.insert(pair<string, map<User, User> >(channel, users));
		}
		
	   /**
		* Remove a user from the specified channel in our memory.
		*/
        User removeUser(string channel, string nick) 
		{
			to_lower(channel);
			User user("", nick.c_str());
			recursive_mutex::scoped_lock synchronized(m_channelsMutex);
			map<string, map<User, User> >::iterator it = m_channels.find(channel);
		    User returnUser;
			if(it != m_channels.end())
			{
				map<User, User>::iterator mit;
				mit = it->second.find(user);
				if(mit != it->second.end())
				{
					returnUser = mit->second;
					it->second.erase(user);
				}
			}

			return returnUser;
		}

	   /**
		* Remove a user from all channels in our memory.
		*/
		void removeUser(string nick) 
		{
			recursive_mutex::scoped_lock synchronized(m_channelsMutex);
			map<string, map<User, User> >::iterator it = m_channels.begin();
			while(it != m_channels.end())
			{
				removeUser(it->first, nick);
				++it;
			}
		}


	   /**
		* Rename a user if they appear in any of the channels we know about.
		*/
		void renameUser(string oldNick, string newNick) 
		{
			recursive_mutex::scoped_lock synchronized(m_channelsMutex);
			map<string, map<User, User> >::iterator it = m_channels.begin();
			while(it != m_channels.end())
			{
				string channel = it->first;
				User user = removeUser(channel, oldNick);
				if(user.getNick() != "" && user.getPrefix() != "")
				{
					User newUser(user.getPrefix(), newNick.c_str());
					addUser(channel, user);
				}
			}
		}

	   /**
		* Removes an entire channel from our memory of users.
		*/
		void removeChannel(string channel) 
		{
			to_lower(channel);
			recursive_mutex::scoped_lock synchronized(m_channelsMutex);
			m_channels.erase(channel);
		}

	   /**
		* Removes all channels from our memory of users.
		*/
		void removeAllChannels() 
		{
			recursive_mutex::scoped_lock synchronized(m_channelsMutex);
			m_channels.clear();
		}

	   /**
		* Called when the mode of a channel is set.  We process this in
		* order to call the appropriate onOp, onDeop, etc method before
		* finally calling the override-able onMode method.
		*  <p>
		* Note that this method is private and is not intended to appear
		* in the javadoc generated documentation.
		*
		* @param target The channel or nick that the mode operation applies to.
		* @param sourceNick The nick of the user that set the mode.
		* @param sourceLogin The login of the user that set the mode.
		* @param sourceHostname The hostname of the user that set the mode.
		* @param mode  The mode that has been set.
		*/
		void processMode(string target, string sourceNick, 
			             string sourceLogin, string sourceHostname, 
						 string mode) 
		{
	        
			if (m_channelPrefixes.find(target.at(0) >= 0))
			{
				// The mode of a channel is being changed.
				string channel(target);
				typedef tokenizer<char_separator<char> > tokenizer;
				tokenizer tokens(mode, m_tokenDelimters);
				tokenizer::iterator tok_iter = tokens.begin();
				vector<string> params;
				int t = 0;
				while (tok_iter != tokens.end()) 
				{
					params.push_back(*tok_iter);
					++tok_iter;
				}
	            
				char pn = ' ';
				int p = 1;
	     
				// All of this is very large and ugly, but it's the only way of providing
				// what the users want :-/
				for (unsigned int i = 0; i < params.at(0).length(); i++) 
				{
					char atPos = params.at(0).at(i);
	     
					if (atPos == '+' || atPos == '-') 
					{
						pn = atPos;
					}
					else if (atPos == 'o') 
					{
						if (pn == '+') 
						{
							updateUser(channel, OP_ADD, params.at(p));
							m_bot.onOp(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), params.at(p).c_str());
						}
						else 
						{
							updateUser(channel, OP_REMOVE, params.at(p));
							m_bot.onDeop(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), params.at(p).c_str());
						}

						p++;
					}
					else if (atPos == 'v') 
					{
						if (pn == '+') 
						{
							updateUser(channel, VOICE_ADD, params.at(p));
							m_bot.onVoice(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), params.at(p).c_str());
						}
						else 
						{
							updateUser(channel, VOICE_REMOVE, params.at(p));
							m_bot.onDeVoice(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), params.at(p).c_str());
						}

						p++; 
					
					}
					else if (atPos == 'k') 
					{
						if (pn == '+') 
						{
							m_bot.onSetChannelKey(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), params.at(p).c_str());
						}
						else 
						{
							m_bot.onRemoveChannelKey(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), params.at(p).c_str());
						}
						
						p++;
					
					}
					else if (atPos == 'l') 
					{
						if (pn == '+') 
						{
							int i = 0;
							try
							{
								int i = lexical_cast<int>(params.at(p));
							}
							catch(bad_lexical_cast &)
							{
								//let i stay at zero
							}
							m_bot.onSetChannelLimit(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), i);
							p++;
						}
						else 
						{
							m_bot.onRemoveChannelLimit(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str());
						}
					}
					else if (atPos == 'b') 
					{
						if (pn == '+') 
						{
							m_bot.onSetChannelBan(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), params.at(p).c_str());
						}
						else 
						{
							m_bot.onRemoveChannelBan(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), params.at(p).c_str());
						}
						p++;
					}
					else if (atPos == 't') 
					{
						if (pn == '+') 
						{
							m_bot.onSetTopicProtection(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str());
						}
						else 
						{
							m_bot.onRemoveTopicProtection(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str());
						}
					}
					else if (atPos == 'n') 
					{
						if (pn == '+') 
						{
							m_bot.onSetNoExternalMessages(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str());
						}
						else 
						{
							m_bot.onRemoveNoExternalMessages(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str());
						}
					}
					else if (atPos == 'i') 
					{
						if (pn == '+') 
						{
							m_bot.onSetInviteOnly(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str());
						}
						else 
						{
							m_bot.onRemoveInviteOnly(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str());
						}
					}
					else if (atPos == 'm') 
					{
						if (pn == '+') 
						{
							m_bot.onSetModerated(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str());
						}
						else 
						{
							m_bot.onRemoveModerated(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str());
						}
					}
					else if (atPos == 'p') 
					{
						if (pn == '+') 
						{
							m_bot.onSetPrivate(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str());
						}
						else 
						{
							m_bot.onRemovePrivate(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str());
						}
					}
					else if (atPos == 's') 
					{
						if (pn == '+') 
						{
							m_bot.onSetSecret(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str());
						}
						else 
						{
							m_bot.onRemoveSecret(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str());
						}
					}
				}
	        
				m_bot.onMode(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), mode.c_str());
			}
			else 
			{
				// The mode of a user is being changed.
				string nick(target);
				m_bot.onUserMode(nick.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), mode.c_str());
			}
		}


		void updateUser(string channel, int userMode, string nick) 
		{
			to_lower(channel);
			recursive_mutex::scoped_lock synchronized(m_channelsMutex);
			map<string, map<User, User> >::iterator it = m_channels.find(channel);
            User newUser;
            if (it != m_channels.end()) 
			{
				map<User, User>::iterator iit = it->second.begin();
                while(iit != it->second.end()) 
				{
					User userObj = iit->second;
					++iit;
					
					string left = to_lower_copy(string(userObj.getNick()));
					string right = to_lower_copy(nick);
                    if (left == right) 
					{
                        if (userMode == OP_ADD) 
						{
                            if (userObj.hasVoice()) 
							{
                                newUser = User("@+", nick.c_str());
                            }
                            else 
							{
                                newUser = User("@", nick.c_str());
                            }
                        }
                        else if (userMode == OP_REMOVE) 
						{
                            if(userObj.hasVoice()) 
							{
                                newUser = User("+", nick.c_str());
                            }
                            else 
							{
                                newUser = User("", nick.c_str());
                            }
                        }
                        else if (userMode == VOICE_ADD) 
						{
                            if(userObj.isOp()) 
							{
                                newUser = User("@+", nick.c_str());
                            }
                            else 
							{
                                newUser = User("+", nick.c_str());
                            }
                        }
                        else if (userMode == VOICE_REMOVE) 
						{
                            if(userObj.isOp()) 
							{
                                newUser = User("@", nick.c_str());
                            }
                            else 
							{
                                newUser = User("", nick.c_str());
                            }
                        }
                    }
                }
            }

            if (newUser.getNick() != "" || newUser.getPrefix() != "") 
			{
				it->second.insert(pair<User, User>(newUser, newUser));
            }
            else 
			{
                // just in case ...
				it->second.insert(pair<User, User>(User("", nick.c_str()), User("", nick.c_str())));
            }
        }
};


const char *PircBotImpl::VERSION = "1.4.4.1";
const int PircBotImpl::OP_ADD = 1;
const int PircBotImpl::OP_REMOVE = 2;
const int PircBotImpl::VOICE_ADD = 3;
const int PircBotImpl::VOICE_REMOVE = 4;




PircBot::PircBot()
	throw(Exception &)
	: m_pimpl(new PircBotImpl(*this))
{
}

void PircBot::connect(const char * const hostname, const unsigned int &port, const char * const password)
			throw(IOException &, IrcException &, NickAlreadyInUseException &, Exception &)
{
	try
	{
		recursive_mutex::scoped_lock synchronized(m_pimpl->m_this);

		m_pimpl->m_server = hostname;
        m_pimpl->m_port = port;
		if(password != 0)
		{
	        m_pimpl->m_password = password;
		}
		if (isConnected()) 
		{
			throw IOExceptionImpl("The PircBot is already connected to an IRC server.  Disconnect first.");
        }

        // Don't clear the outqueue - there might be something important in it!

		// Clear everything we may have know about channels.
        m_pimpl->removeAllChannels();
		m_pimpl->m_socket.setPort(m_pimpl->m_port);
		m_pimpl->m_socket.setHost(m_pimpl->m_server);
		m_pimpl->m_socket.connect();
        log("*** Connected to server.");
        
		// Attempt to join the server.
        if (m_pimpl->m_password != "") {
			OutputThread::sendRawLine(*this, m_pimpl->m_socket, string("PASS ") + m_pimpl->m_password);
        }

		string nick = getName();
		OutputThread::sendRawLine(*this, m_pimpl->m_socket, "NICK " + nick);
		OutputThread::sendRawLine(*this, m_pimpl->m_socket, string("USER ") + getLogin() + string(" 8 * :") + getVersion());		

		m_pimpl->m_inputThread.reset(new InputThread(*this, m_pimpl->m_socket));

        // Read stuff back from the server to see if we connected.
        int tries = 1;
		string line;
		line = m_pimpl->m_socket.readLine();
		while((line = m_pimpl->m_socket.readLine()) != "")
		{
			handleLine(line.c_str());
			stringstream streamLine;
			streamLine << line;
			string word1;
			string code;
			streamLine >> word1;
			streamLine >> code;
			
			if(code != "") 
			{
				if(code == "004")
				{
					// We're connected to the server.
					break;
				}
                else if (code == "433") 
				{
                    if (m_pimpl->m_autoNickChange) 
					{
                        tries++;
                        nick = getName() + tries;
						OutputThread::sendRawLine(*this, m_pimpl->m_socket, "NICK " + nick);
                    }
                    else 
					{
                        m_pimpl->m_socket.close();
						throw NickAlreadyInUseExceptionImpl(line.c_str());
                    }
                }
                else if (starts_with(code, "5") || starts_with(code, "4"))
				{
                    m_pimpl->m_socket.close();
					string msg("Could not log into the IRC server: ");
					msg += line;
                    throw IrcExceptionImpl(msg.c_str());
                }
			}
            m_pimpl->setNick(nick);
		}
        log("*** Logged onto server.");

		// This makes the socket timeout on read operations after 5 minutes.
		// Maybe in some future version I will let the user change this at runtime.
		asio::socket_base::linger option(true, 300);
		///@todo once this bug is fixed uncomment the following below
		//			s.get_option(option);

        // Now start the InputThread to read all other lines from the server.
        m_pimpl->m_inputThread->start();

		// Now start the outputThread that will be used to send all messages.
		if(m_pimpl->m_outputThread == 0)
		{
			m_pimpl->m_outputThread.reset(new OutputThread(*this, m_pimpl->m_outQueue));
			m_pimpl->m_outputThread->start();
		}
		onConnect();
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::log(const char * const line) const
	throw(Exception &)
{
	try
	{
		if (m_pimpl->m_verbose) 
		{
			ptime t(second_clock::local_time());
			cout << to_simple_string(t) << " " << line << endl; 
		}
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *PircBot::getName() const
	throw(Exception &)
{
	try
	{
		return m_pimpl->m_name.c_str();
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *PircBot::getLogin() const
	throw(Exception &)
{
	try
	{
		return m_pimpl->m_login.c_str();
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *PircBot::getVersion() const
	throw(Exception &)
{
	try
	{
		return m_pimpl->m_version.c_str();
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::handleLine(const char * const line)
	throw(Exception &)
{
	try
	{

		log(line);
		string stringLine(line);
		//Remove the newline that's attached to the line
		erase_all(stringLine, "\n");
		erase_all(stringLine, "\r");

		// Check for server pings.
		if(starts_with(stringLine, "PING "))
		{
			// Respond to the ping and return immediately.
			onServerPing(stringLine.substr(5).c_str());
			return;
		}

		string sourceNick = "";
		string sourceLogin = "";
		string sourceHostname = "";

		typedef tokenizer<char_separator<char> > tokenizer;
		tokenizer tokens(stringLine, m_pimpl->m_tokenDelimters);
		tokenizer::iterator tok_iter = tokens.begin();
		
		if(tok_iter == tokens.end())
		{
			return;
		}

		string senderInfo = *tok_iter;
		++tok_iter;

		if(tok_iter == tokens.end())
		{
			return;
		}

		string command = *tok_iter;
		string target;
		++tok_iter;

		size_t exclamation = senderInfo.find("!");
		size_t at = senderInfo.find("@");

		if (starts_with(senderInfo, ":"))
		{
			if (exclamation > 0 && at > 0 && exclamation < at) 
			{
				sourceNick = senderInfo.substr(1, exclamation - 1);
				sourceLogin = senderInfo.substr(exclamation + 1, at - (exclamation + 1));
				sourceHostname = senderInfo.substr(at + 1);
			}
			else 
			{
				if (tok_iter != tokens.end()) 
				{
					string token = command;
					int code = -1;
					try
					{
						code = lexical_cast<int>(token);
					}
					catch(bad_lexical_cast &)
					{
						// Keep the existing value.
					}

					if (code != -1) 
					{
						string errorStr = token;
						size_t i = stringLine.find(errorStr, senderInfo.length()) + 4;
						string response = stringLine.substr(i, stringLine.length() - i);
						m_pimpl->processServerResponse(code, response);
						// Return from the method.
						return;
					}
					else 
					{
						// This is not a server response.
						// It must be a nick without login and hostname.
						// (or maybe a NOTICE or suchlike from the server)
						sourceNick = senderInfo;
						target = token;
					}
				}
				else 
				{
					// We don't know what this line means.
					onUnknown(line);
					// Return from the method;
					return;
				}
			}
		}
		to_upper(command);
		
		if (starts_with(sourceNick, ":"))
		{
			sourceNick = sourceNick.substr(1);
		}
		
		if (target == "") 
		{
			if(tok_iter != tokens.end())
			{
				target = *tok_iter;
				++tok_iter;
			}
		}
		
		if (starts_with(target, ":"))
		{
			target = target.substr(1);
		}
		
		char ascii = 0x1;
		string asciiString;
		asciiString += ascii;
		// Check for CTCP requests.
		if ((command == "PRIVMSG") && 
			(stringLine.find(":" + asciiString) != string::npos) && 
			ends_with(stringLine, asciiString))
		{
			size_t i = stringLine.find(":" + asciiString) + 2;
			string request = stringLine.substr(i, stringLine.length() - 1 - i);
			if (request == "VERSION") 
			{
				// VERSION request
				onVersion(sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), target.c_str());
			}
			else if (starts_with(request, "ACTION "))
			{
				// ACTION request
				onAction(sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), target.c_str(), request.substr(7).c_str());
			}
			else if (starts_with(request, "PING ")) 
			{
					// PING request
					onPing(sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), target.c_str(), request.substr(5).c_str());
			}
			else if (request == "TIME") 
			{
				// TIME request
				onTime(sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), target.c_str());
			}
			else if (request == "FINGER")
			{
				// FINGER request
				onFinger(sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), target.c_str());
			}
			else 
			{
				tokenizer tokens2(request);
				tokenizer::iterator tok_iter2 = tokens2.begin();
				if((tok_iter2 != tokens2.end()) && (*tok_iter2 == "DCC"))
				{
					///@todo uncomment this once dcc manager is written
					//bool success = m_pimpl->m_dccManager.processRequest(sourceNick, sourceLogin, sourceHostname, request);
				}
				else
				{
					// An unknown CTCP message - ignore it.
					onUnknown(line);
				}
			}
		}
		else if (command == "PRIVMSG" && m_pimpl->m_channelPrefixes.find(target.at(0)) >= 0)
		{
			// This is a normal message to a channel.
			onMessage(target.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), stringLine.substr(stringLine.find(" :") + 2).c_str());

		}
		else if (command == "PRIVMSG")
		{
			// This is a private message to us.
			onPrivateMessage(sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), stringLine.substr(stringLine.find(" :") + 2).c_str());
		}
		else if (command == "JOIN")
		{
			// Someone is joining a channel.
			string channel = target;
			this->m_pimpl->addUser(channel, User("", sourceNick.c_str()));
			onJoin(channel.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str());
		}
		else if (command == "PART")
		{
			// Someone is parting from a channel.
			m_pimpl->removeUser(target, sourceNick);
			if(sourceNick == getNick())
			{
				m_pimpl->removeChannel(target);
			}
			onPart(target.c_str(), sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str());
		}
		else if (command == "NICK")
		{
			// Somebody is changing their nick.
			string newNick = target;
			m_pimpl->renameUser(sourceNick, newNick);
			if(sourceNick == getNick())
			{
				// Update our nick if it was us that changed nick.
				m_pimpl->setNick(newNick);
			}
			onNickChange(sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), newNick.c_str());
		}
		else if (command == "NOTICE")
		{
			// Someone is sending a notice.
			onNotice(sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), target.c_str(), stringLine.substr(stringLine.find(" :") + 2).c_str());
		}
		else if (command == "QUIT")
		{
			// Someone has quit from the IRC server.
			if(sourceNick == getNick())
			{
				m_pimpl->removeAllChannels();
			}
			else
			{
				m_pimpl->removeUser(sourceNick);
			}
			onQuit(sourceNick.c_str(), sourceLogin.c_str(), sourceHostname.c_str(), stringLine.substr(stringLine.find(" :") + 2).c_str());
		}
		else if (command == "KICK")
		{
			// Somebody has been kicked from a channel.
			string recipient;
			if(tok_iter != tokens.end())
			{
				recipient = *tok_iter;
				++tok_iter;
				if(recipient == getNick())
				{
					m_pimpl->removeChannel(target);
				}
				m_pimpl->removeUser(target, recipient);
			}
			
			onKick(target.c_str(), sourceNick.c_str(), sourceLogin.c_str(), 
				sourceHostname.c_str(), recipient.c_str(), stringLine.substr(stringLine.find(" :") + 2).c_str());
		}
		else if (command == "MODE")
		{

			// Somebody is changing the mode on a channel or user.
			string mode = stringLine.substr(stringLine.find(target, 2) + target.length() + 1);
			if(starts_with(mode, ":"))
			{
				mode = mode.substr(1);
			}
			m_pimpl->processMode(target, sourceNick, sourceLogin, sourceHostname, mode);
		}
		else if (command == "TOPIC")
		{
			posix_time_zone localTime("MST-07");
			time_zone_ptr zone(&localTime);
			local_date_time ldt = local_microsec_clock::local_time(zone);
			ptime time_t_epoch(date(1970,1,1)); 
			time_duration diff = ldt.utc_time() - time_t_epoch;
			int date = diff.total_milliseconds();
			onTopic(target.c_str(), stringLine.substr(stringLine.find(" :") + 2).c_str(), sourceNick.c_str(), date, true);
		}
		else if (command == "INVITE")
		{
			// Somebody is inviting somebody else into a channel.
			onInvite(target.c_str(), sourceNick.c_str(), sourceLogin.c_str(), 
					sourceHostname.c_str(), stringLine.substr(stringLine.find(" :") + 2).c_str());
		}
		else 
		{
			// If we reach this point, then we've found something that the PircBot
			// Doesn't currently deal with.
			onUnknown(line);
		}
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::onServerPing(const char * const response)
	throw(Exception &)
{
	try
	{
		string temp("PONG ");
		temp += response;
		sendRawLine(temp.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::sendRawLine(const char * const line) const
	throw(Exception &)
{
	try
	{
		recursive_mutex::scoped_lock synchronized(m_pimpl->m_this);
		if(isConnected() && m_pimpl->m_inputThread.get() != 0)
		{
			m_pimpl->m_inputThread->sendRawLine(line);
		}
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

bool PircBot::isConnected() const
	throw(Exception &)
{
	try
	{
		recursive_mutex::scoped_lock synchronized(m_pimpl->m_this);
		return ((m_pimpl->m_inputThread.get() != 0) && (m_pimpl->m_inputThread->isConnected()));
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::onConnect()
	throw(Exception &)
{

}

void PircBot::join() const
	throw(Exception &)
{
	try
	{
		//Join to all the boost threads that are active.
		//Once they all unblock this method can then 
		//return.
		m_pimpl->m_outputThread->join();
		m_pimpl->m_inputThread->join();
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

unsigned int PircBot::getMaxLineLength() const
	throw(Exception &)
{
	try
	{
		return InputThread::MAX_LINE_LENGTH;
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::setMessageDelay(const unsigned int &delay)
	throw(Exception &)
{
	try
	{
		m_pimpl->m_messageDelay = delay;
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

unsigned int PircBot::getMessageDelay() const
	throw(Exception &)
{
	try
	{
		return m_pimpl->m_messageDelay;
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::joinChannel(const char * const channel) const 
	throw(Exception &)
{
	try
	{
		string joinLine("JOIN ");
		joinLine += channel;
		this->sendRawLine(joinLine.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::setVerbose(const bool &verbose)
	throw(Exception &)
{
	try
	{
		m_pimpl->m_verbose = verbose;
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::onMessage(const char * const channel, 
						const char * const sender, 
						const char * const login, 
						const char * const hostname, 
						const char * const message)
	throw(Exception &)
{

}

void PircBot::sendMessage(const char * const target, 
						  const char * const message) const
	throw(Exception &)
{
	try
	{
		string outQueueMsg("PRIVMSG ");
		outQueueMsg += target;
		outQueueMsg += " :";
		outQueueMsg += message;
		m_pimpl->m_outQueue.add(outQueueMsg);
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}


void PircBot::setName(const char * const name)
	throw(Exception &)
{
	try
	{
		m_pimpl->m_name = name;
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}


void PircBot::onChannelInfo(const char * const channel, const int &userCount, const char * const topic)
	throw(Exception &)
{

}

void PircBot::onTopic(const char * const channel, const char * const topic)
	throw(Exception &)
{

}

void PircBot::onTopic(const char * const channel, 
                      const char * const topic, 
                      const char * const setBy, 
                      long date, bool changed)
	throw(Exception &)
{ }

User* PircBot::getUsers(const char * const channel, unsigned int &arraySize) const
	throw(Exception &)
{
	try
	{
		string channelString(channel);
		to_lower(channelString);
		arraySize = 0;
		User *userArray = 0;
		recursive_mutex::scoped_lock synchronized(m_pimpl->m_channelsMutex);
		map<string, map<User, User> >::iterator it = m_pimpl->m_channels.find(channelString);
		if(it != m_pimpl->m_channels.end())
		{
			userArray = new User[it->second.size()];
			arraySize = it->second.size();
			typedef map<User, User>::iterator MI;
			int i = 0;
			for(MI elements = it->second.begin(); elements != it->second.end(); ++elements, ++i)
			{
				userArray[i] = elements->second;
			}
		}
		return userArray;
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::releaseMemoryOfUserArray(User *userArray)
	throw(Exception &)
{
	try
	{
		delete[] userArray;
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::onUserList(const char * const channel, User* users, int usersArraySize)
	throw(Exception &)
{

}

void PircBot::onServerResponse(const int &code, const char * const response)
	throw(Exception &)
{

}

void PircBot::onUnknown(const char * const line)
	throw(Exception &)
{
        // And then there were none :)
}

void PircBot::onVersion(const char * const sourceNick, 
                        const char * const sourceLogin, 
                        const char * const sourceHostname, 
                        const char * const target)
	throw(Exception &)
{
	try
	{
		string onVersion("NOTICE ");
		onVersion += sourceNick;
		onVersion += ":";
		onVersion += 0x1;
		onVersion += "VERSION ";
		onVersion += m_pimpl->m_version;
		onVersion += 0x1;
		sendRawLine(onVersion.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::onAction(const char * const sender, 
                       const char * const login, 
                       const char * const hostname, 
                       const char * const target, 
                       const char * const action)
	throw(Exception &)
{

}

void PircBot::onPing(const char * const sourceNick, 
                     const char * const sourceLogin, 
                     const char * const sourceHostname, 
                     const char * const target, 
                     const char * const pingValue)
	throw(Exception &)
{
	try
	{
		string rawLine("NOTICE");
		rawLine += sourceNick;
		rawLine += ":";
		rawLine += 0x1;
		rawLine += "PING ";
		rawLine += pingValue;
		rawLine += 0x1;
		sendRawLine(rawLine.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::onTime(const char * const sourceNick, 
                     const char * const sourceLogin, 
                     const char * const sourceHostname, 
                     const char * const target)
	throw(Exception &)
{
	try
	{
		ptime t(second_clock::local_time());
		string rawLine("NOTICE ");
		rawLine += sourceNick;
		rawLine += 0x1;
		rawLine += "TIME ";
		rawLine += to_simple_string(t);
		rawLine += 0x1;
		sendRawLine(rawLine.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::onFinger(const char * const sourceNick, 
                       const char * const sourceLogin, 
                       const char * const sourceHostname, 
                       const char * const target)
	throw(Exception &)
{
	try
	{
		string rawLine("NOTICE ");
		rawLine += sourceNick;
		rawLine += 0x1;
		rawLine += "FINGER ";
		rawLine += m_pimpl->m_finger;
		rawLine += 0x1;
		sendRawLine(rawLine.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::onPrivateMessage(const char * const sender, 
                               const char * const login, 
                               const char * const hostname, 
                               const char * const message)
	throw(Exception &)
{

}

void PircBot::onJoin(const char * const channel, 
                     const char * const sender, 
                     const char * const login, 
                     const char * const hostname)
	throw(Exception &)
{

}

const char *PircBot::getNick() 
	throw(Exception &)
{
	try
	{
		return m_pimpl->m_nick.c_str();
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::onPart(const char * const channel, 
                     const char * const sender, 
                     const char * const login, 
                     const char * const hostname)
	throw(Exception &)
{

}


void PircBot::onNickChange(const char * const oldNick, 
                           const char * const login, 
                           const char * const hostname, 
                           const char * const newNick)
	throw(Exception &)
{

}

void PircBot::onNotice(const char * const sourceNick, 
					   const char * const sourceLogin, 
					   const char * const sourceHostname, 
					   const char * const target, 
					   const char * const notice)
	throw(Exception &)
{

}

void PircBot::onQuit(const char * const sourceNick, 
					 const char * const sourceLogin, 
					 const char * const sourceHostname, 
					 const char * const reason)
	throw(Exception &)
{

}

void PircBot::onKick(const char * const channel, 
			         const char * const kickerNick, 
					 const char * const kickerLogin, 
					 const char * const kickerHostname, 
					 const char * const recipientNick, 
					 const char * const reason)
	throw(Exception &)
{

}

void PircBot::onInvite(const char * const targetNick, 
		               const char * const sourceNick, 
				       const char * const sourceLogin, 
				       const char * const sourceHostname, 
				       const char * const channel)    
	throw(Exception &)
{ } 

void PircBot::onOp(const char * const channel, 
			       const char * const sourceNick, 
				   const char * const sourceLogin, 
				   const char * const sourceHostname, 
				   const char * const recipient)
	throw(Exception &)
{ } 

void PircBot::onDeop(const char * const channel, 
			         const char * const sourceNick, 
					 const char * const sourceLogin, 
					 const char * const sourceHostname, 
					 const char * const recipient)
	throw(Exception &)
{ } 

void PircBot::onVoice(const char * const channel, 
			          const char * const sourceNick, 
					  const char * const sourceLogin, 
					  const char * const sourceHostname, 
					  const char * const recipient)
	throw(Exception &)
{ } 

void PircBot::onDeVoice(const char * const channel, 
			            const char * const sourceNick, 
					    const char * const sourceLogin, 
					    const char * const sourceHostname, 
					    const char * const recipient)
	throw(Exception &)
{ }

void PircBot::onSetChannelKey(const char * const channel, 
			                  const char * const sourceNick, 
							  const char * const sourceLogin, 
							  const char * const sourceHostname, 
							  const char * const key)
	throw(Exception &)
{ } 

void PircBot::onRemoveChannelKey(const char * const channel, 
			                     const char * const sourceNick, 
								 const char * const sourceLogin, 
								 const char * const sourceHostname, 
								 const char * const key)
	throw(Exception &)
{} 

void PircBot::onSetChannelLimit(const char * const channel, 
		                        const char * const sourceNick, 
						        const char * const sourceLogin, 
						        const char * const sourceHostname, 
						        const int &limit)
	throw(Exception &)
{ }

void PircBot::onRemoveChannelLimit(const char * const channel, 
		                           const char * const sourceNick, 
						           const char * const sourceLogin, 
						           const char * const sourceHostname)
	throw(Exception &)
{ }

void PircBot::onSetChannelBan(const char * const channel, 
                              const char * const sourceNick, 
							  const char * const sourceLogin, 
							  const char * const sourceHostname, 
							  const char * const hostmask)
	throw(Exception &)
{ }

void PircBot::onRemoveChannelBan(const char * const channel, 
			                     const char * const sourceNick, 
								 const char * const sourceLogin, 
								 const char * const sourceHostname, 
								 const char * const hostmask)
	throw(Exception &)
{ }

void PircBot::onSetTopicProtection(const char * const channel, 
			                       const char * const sourceNick, 
								   const char * const sourceLogin, 
								   const char * const sourceHostname)
	throw(Exception &)
{ }

void PircBot::onRemoveTopicProtection(const char * const channel, 
			                          const char * const sourceNick, 
									  const char * const sourceLogin, 
									  const char * const sourceHostname)
	throw(Exception &)
{ }

void PircBot::onSetNoExternalMessages(const char * const channel, 
			                          const char * const sourceNick, 
									  const char * const sourceLogin, 
									  const char * const sourceHostname)
	throw(Exception &)
{ }

void PircBot::onRemoveNoExternalMessages(const char * const channel, 
			                             const char * const sourceNick, 
										 const char * const sourceLogin, 
										 const char * const sourceHostname)
	throw(Exception &)
{ }

void PircBot::onSetInviteOnly(const char * const channel, 
			                  const char * const sourceNick, 
						      const char * const sourceLogin, 
							  const char * const sourceHostname)
	throw(Exception &)
{ }

void PircBot::onRemoveInviteOnly(const char * const channel, 
			                     const char * const sourceNick, 
								 const char * const sourceLogin, 
								 const char * const sourceHostname)
	throw(Exception &)
{ }

void PircBot::onSetModerated(const char * const channel, 
			                 const char * const sourceNick, 
							 const char * const sourceLogin, 
							 const char * const sourceHostname)
	throw(Exception &)
{ }

void PircBot::onRemoveModerated(const char * const channel, 
			                    const char * const sourceNick, 
								const char * const sourceLogin, 
								const char * const sourceHostname)
	throw(Exception &)
{ }

void PircBot::onSetPrivate(const char * const channel, 
			               const char * const sourceNick, 
						   const char * const sourceLogin, 
						   const char * const sourceHostname)
	throw(Exception &)
{ }

void PircBot::onRemovePrivate(const char * const channel, 
			                  const char * const sourceNick, 
						      const char * const sourceLogin, 
							  const char * const sourceHostname)
	throw(Exception &)
{ }

void PircBot::onSetSecret(const char * const channel, 
			              const char * const sourceNick, 
						  const char * const sourceLogin, 
						  const char * const sourceHostname)
	throw(Exception &)
{ }

void PircBot::onRemoveSecret(const char * const channel, 
			                 const char * const sourceNick, 
							 const char * const sourceLogin, 
							 const char * const sourceHostname)
	throw(Exception &)
{ }

void PircBot::onMode(const char * const channel, 
			         const char * const sourceNick, 
					 const char * const sourceLogin, 
					 const char * const sourceHostname, 
					 const char * const mode)
	throw(Exception &)
{ }

void PircBot::onUserMode(const char * const targetNick, 
			             const char * const sourceNick, 
						 const char * const sourceLogin, 
						 const char * const sourceHostname, 
						 const char * const mode)
	throw(Exception &)
{ }

void PircBot::connect(const char * const hostname)
	throw(IOException &, IrcException &, NickAlreadyInUseException &, Exception &)
{
	try
	{
		recursive_mutex::scoped_lock synchronized(m_pimpl->m_this);
		connect(hostname, 6667, "");
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::connect(const char * const hostname, 
		              const unsigned int &port)
			throw(IOException &, IrcException &, NickAlreadyInUseException &, Exception &)

{
	try
	{
		recursive_mutex::scoped_lock synchronized(m_pimpl->m_this);
		connect(hostname, port, "");
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::reconnect() 
	throw(IOException &, IrcException &, NickAlreadyInUseException &, Exception &)

{
	try
	{
		recursive_mutex::scoped_lock synchronized(m_pimpl->m_this);
		string server(getServer());
		if(server.empty() || server == "")
		{
			throw IrcExceptionImpl("Cannot reconnect to an IRC server because we were never connected to one previously!");
		}
		connect(getServer(), getPort(), getPassword());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}

}

void PircBot::disconnect() const
	throw(Exception &)
{
	try
	{
		recursive_mutex::scoped_lock synchronized(m_pimpl->m_this);
		quitServer();
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::setAutoNickChange(bool autoNickChange)
	throw(Exception &)
{
	try
	{
		m_pimpl->m_autoNickChange = autoNickChange;
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::startIdentServer() const
	throw(Exception &)
{
	try
	{
		m_pimpl->m_identServer.reset(new IdentServer(*this, getLogin()));
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
	
}


void PircBot::joinChannel(const char * const channel, 
			              const char * const key) const
	throw(Exception &)
{
	try
	{
		string str(channel);
		str += " ";
		str += key;
		joinChannel(str.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}

}

void PircBot::partChannel(const char * const channel) const
	throw(Exception &)
{
	try
	{
		string msg("PART ");
		msg += channel;
        sendRawLine(msg.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::partChannel(const char * const channel, 
                          const char * const reason) const
	throw(Exception &)
{
	try
	{
		string msg("PART ");
		msg += channel;
		msg += " :";
		msg += reason;
		sendRawLine(msg.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::quitServer() const
	throw(Exception &)
{
	try
	{
		quitServer("");
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}


void PircBot::quitServer(const char * const reason) const
	throw(Exception &)
{
	try
	{
		string msg("QUIT :");
		msg += reason;
        sendRawLine(msg.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::sendRawLineViaQueue(const char * const line) const
	throw(Exception &)
{
	try
	{
		recursive_mutex::scoped_lock synchronized(m_pimpl->m_this);
		string stringLine(line);
		if(stringLine.empty() || stringLine == "")
		{
			throw ExceptionImpl("Cannot send null messages to server");
		}
		if(isConnected())
		{
			m_pimpl->m_outQueue.add(stringLine);
		}
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::sendAction(const char * const target, 
			             const char * const action) const
	throw(Exception &)
{
	try
	{
		string msg("ACTION ");
		msg += action;
		sendCTCPCommand(target, msg.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::sendNotice(const char * const target, 
                         const char * const notice) const
	throw(Exception &)
{
	try
	{
		string msg("NOTICE ");
		msg += target;
		msg += " :";
		msg += notice;
        m_pimpl->m_outQueue.add(msg);
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::sendCTCPCommand(const char * const target, 
                              const char * const command) const
	throw(Exception &)
{
	try
	{
		string msg("PRIVMSG ");
		msg += target;
		msg += " :";
		msg += 0x1;
		msg += command;
		msg += 0x1;
		m_pimpl->m_outQueue.add(msg);
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::changeNick(const char * const newNick) const
	throw(Exception &)
{
	try
	{
		string msg("NICK ");
		msg += newNick;
		sendRawLine(msg.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::setMode(const char * const channel, 
             const char * const mode) const
	throw(Exception &)
{
	try
	{
		string msg("MODE ");
		msg += channel;
		msg += " ";
		msg += mode;
        sendRawLine(msg.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::sendInvite(const char * const nick, 
                         const char * const channel) const
	throw(Exception &)
{

	try
	{
		string msg("INVITE ");
		msg += nick;
		msg += " :";
		msg += channel;
        sendRawLine(msg.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::ban(const char * const channel, 
                  const char * const hostmask) const
	throw(Exception &)
{
	try
	{
		string msg("MODE ");
		msg += channel;
		msg += " +b ";
		msg += hostmask;
        sendRawLine(msg.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::unBan(const char * const channel, 
                    const char * const hostmask) const 
	throw(Exception &)
{
	try
	{
		string msg("MODE ");
		msg += channel;
		msg += " -b ";
		msg += hostmask;
        sendRawLine(msg.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::op(const char * const channel, 
			     const char * const nick) const
	throw(Exception &)
{
	try
	{
		string msg ("+o ");
		msg += nick;
        setMode(channel, msg.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::deOp(const char * const channel, 
                   const char * const nick) const
	throw(Exception &)
{
	try
	{
		string msg("-o ");
		msg += nick;
        setMode(channel, msg.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::voice(const char * const channel, 
			        const char * const nick) const
	throw(Exception &)
{
	try
	{
		string msg("+v ");
		msg += nick;
        setMode(channel, msg.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::deVoice(const char * const channel, 
                      const char * const nick) const
	throw(Exception &)
{
	try
	{
		string msg("-v ");
		msg += nick;
        setMode(channel, msg.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::setTopic(const char * const channel, 
                       const char * const topic) const
	throw(Exception &)
{
	try
	{
		string msg("TOPIC ");
		msg += channel;
		msg += " :";
		msg += topic;
        sendRawLine(msg.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::kick(const char * const channel, 
			       const char * const nick) const
	throw(Exception &)
{
	try
	{
        kick(channel, nick, "");
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::kick(const char * const channel, 
			       const char * const nick, 
				   const char * const reason) const
	throw(Exception &)
{
	try
	{
		string msg("KICK ");
		msg += channel;
		msg += " ";
		msg += nick;
		msg += " :";
		msg += reason;
        sendRawLine(msg.c_str());
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::listChannels() const 
	throw(Exception &)
{
	try
	{
        listChannels("");
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::listChannels(const char * const parameters) const
    throw(Exception &)
{
	try
	{
		string parametersString(parameters);
        if (parametersString == "") 
		{
            sendRawLine("LIST");
        }
        else 
		{
			string msg("LIST ");
			msg += parameters;
            sendRawLine(msg.c_str());
        }
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::onDisconnect() 
	throw(Exception &)
{ 

}

void PircBot::setVersion(const char * const version)
	throw(Exception &)
{
	try
	{
		m_pimpl->m_version = version;
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::setFinger(const char * const finger) 
	throw(Exception &)
{
	try
	{
		m_pimpl->m_finger = finger;
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *PircBot::getFinger() const 
	throw(Exception &)
{
	try
	{
		return m_pimpl->m_finger.c_str();
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::setLogin(const char * const login)
	throw(Exception &)
{
	try
	{
		m_pimpl->m_login = login;
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}

}

unsigned int PircBot::getOutgoingQueueSize() const
	throw(Exception &)
{
	try
	{
        return m_pimpl->m_outQueue.size();
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *PircBot::getServer() const
	throw(Exception &)
{
	try
	{
		return m_pimpl->m_server.c_str();
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

unsigned int PircBot::getPort() const
	throw(Exception &)
{
	try
	{
        return m_pimpl->m_port;
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *PircBot::getPassword() const
	throw(Exception &)
{
	try
	{
        return m_pimpl->m_password.c_str();
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::releaseMemoryOfCharArray(const char **array, const unsigned int size)
	throw(Exception &)
{
	try
	{
		for(unsigned int i = 0; i < size; ++i) 
		{
			free((void *)array[i]);
		}

		delete[] array;
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char** PircBot::getChannels(int &sizeOfArray) const
	throw(Exception &)
{
	try
	{
		const char **channels;
		recursive_mutex::scoped_lock synchronized(m_pimpl->m_channelsMutex);
		sizeOfArray = m_pimpl->m_channels.size();
		channels = new const char*[m_pimpl->m_channels.size()];
		map<string, map<User, User> >::iterator it = m_pimpl->m_channels.begin();
		for(unsigned int i = 0; i < m_pimpl->m_channels.size(); ++i)
		{
			channels[i] = strdup(it->first.c_str());
			++it;
		}
		
		return channels;
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void PircBot::dispose()
	throw(Exception &)
{
	try
	{
		m_pimpl->m_outputThread->dispose();
		m_pimpl->m_inputThread->dispose();
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}


void *PircBot::operator new(size_t size)
{
	return ::operator new(size);
}

void PircBot::operator delete(void* p) 
{
    ::operator delete(p);
}

PircBot &PircBot::operator=(const PircBot &pircBot)
{ 
	//Do not use this.  It won't work
	return *this;

}

PircBot::PircBot(const PircBot &pircbot) 
{ 
	//Do not use this.  It won't work
}

PircBot::~PircBot() 
{ 
	dispose();
	delete m_pimpl;
}


} //end of impl namespace
} //end of pircbot namespace 
