#ifndef PIRCBOT_PIRCBOT_H
#define PIRCBOT_PIRCBOT_H

/*
 * pircbotcpp, C++ port of the pircbot Java version
 * A IRC C++ software development kit. An Object 
 * Oriented client framework which lets you 
 * write quick and easy C++ IRC bots
 *
 * Copyright (C) 2006 Frank Hassanabad 
 * http://pircbotcpp.sourceforge.net/
 *
 * Java version 
 * Copyright Paul James Mutton, 2001-2004, http://www.jibble.org/
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */


//pircbot includes
//To get the PIRCBOT_EXPORT macro
#include <pircbot/exports.h>
#include <pircbot/ReplyConstants.h>
#include <pircbot/Exceptions.h>

/* Disable Windows VC 7.x warning about 
 * it ignoring the throw specification
 */
#ifdef _WIN32
#    pragma warning ( push )
#    pragma warning( disable : 4290 )
#endif

namespace pircbot
{
namespace impl
{

/**
 * The private implementation in which
 * you cannot get access to.
 *
 * This class holds the private methods
 * and private attributes of this class.  This 
 * makes ABI (Application Binary Interface) more
 * resilient to change. See the private implementation
 * idiom on the internet for more information about this.
 */
class PircBotImpl;

//Forward decleration
class User;

/**
 * PircBotcpp is a C++ framework for writing IRC bots quickly and easily.
 *  <p>
 * It provides an event-driven architecture to handle common IRC
 * events, flood protection, DCC support, ident support, and more.
 * The comprehensive logfile format is suitable for use with pisg to generate
 * channel statistics.
 *  <p>
 * Methods of the PircBot class can be called to send events to the IRC server
 * that it connects to.  For example, calling the sendMessage method will
 * send a message to a channel or user on the IRC server.  Multiple servers
 * can be supported using multiple instances of PircBot.
 *  <p>
 * To perform an action when the PircBot receives a normal message from the IRC
 * server, you would override the onMessage method defined in the PircBot
 * class.  All on<i>XYZ</i> methods in the PircBot class are automatically called
 * when the event <i>XYZ</i> happens, so you would override these if you wish
 * to do something when it does happen.
 *  <p>
 * Some event methods, such as onPing, should only really perform a specific
 * function (i.e. respond to a PING from the server).  For your convenience, such
 * methods are already correctly implemented in the PircBot and should not
 * normally need to be overridden.  Please read the full documentation for each
 * method to see which ones are already implemented by the PircBot class.
 *  <p>
 * Please visit the PircBot homepage at
 * <a href="http://pircbotcpp.sourceforge.net/">http://pircbotcpp.sourceforge.net/</a>
 * for full revision history, a beginners guide to creating your first PircBot
 * and a list of some existing C++ IRC bots and clients that use the PircBotcpp
 * framework.
 * 
 * @author  Frank Mehri Hassanabad,
 * @version    1.4.4.1
 */
class PIRCBOT_EXPORT PircBot : public ReplyConstants
{
	public:

       /**
		* Constructs a PircBot with the default settings.  Your own constructors
		* in classes which extend the PircBot abstract class should be responsible
		* for changing the default settings if required.
		*
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		PircBot()
			throw(Exception &);

	   /**
		* Attempt to connect to the specified IRC server.
		* The onConnect method is called upon success.
		*
		* @param hostname The hostname of the server to connect to.
		* 
		* @throws IOException if it was not possible to connect to the server.
		* @throws IrcException if the server would not let us join it.
		* @throws NickAlreadyInUseException if our nick is already in use on the server.
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void connect(const char * const hostname) 
			throw(IOException &, IrcException &, NickAlreadyInUseException &, Exception &);

	   /**
		* Attempt to connect to the specified IRC server and port number.
		* The onConnect method is called upon success.
		*
		* @param hostname The hostname of the server to connect to.
		* @param port The port number to connect to on the server.
		* 
		* @throws IOException if it was not possible to connect to the server.
		* @throws IrcException if the server would not let us join it.
		* @throws NickAlreadyInUseException if our nick is already in use on the server.
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void connect(const char * const hostname, 
		                     const unsigned int &port)
			throw(IOException &, IrcException &, NickAlreadyInUseException &, Exception &);

	   /**
		* Attempt to connect to the specified IRC server using the supplied
		* password.
		* The onConnect method is called upon success.
		*
		* @param hostname The hostname of the server to connect to.
		* @param port The port number to connect to on the server.
		* @param password The password to use to join the server.
		*
		* @throws IOException if it was not possible to connect to the server.
		* @throws IrcException if the server would not let us join it.
		* @throws NickAlreadyInUseException if our nick is already in use on the server.
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void connect(const char * const hostname, 
			                 const unsigned int &port, 
							 const char * const password)
			throw(IOException &, IrcException &, NickAlreadyInUseException &, Exception &);

	   /**
		* Reconnects to the IRC server that we were previously connected to.
		* If necessary, the appropriate port number and password will be used.
		* This method will throw an IrcException if we have never connected
		* to an IRC server previously.
		* 
		* @throws IOException if it was not possible to connect to the server.
		* @throws IrcException if the server would not let us join it.
		* @throws NickAlreadyInUseException if our nick is already in use on the server.
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void reconnect()
			throw(IOException &, IrcException &, NickAlreadyInUseException &, Exception &);


	   /**
		* This method disconnects from the server cleanly by calling the
		* quitServer() method.  Providing the PircBot was connected to an
		* IRC server, the onDisconnect() will be called as soon as the
		* disconnection is made by the server.
		*
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*
		* @see #quitServer() quitServer
		* @see #quitServer(const char * const reason) const quitServer
		*/
		virtual void disconnect() const
			throw(Exception &);

	   /**
		* When you connect to a server and your nick is already in use and
		* this is set to true, a new nick will be automatically chosen.
		* This is done by adding numbers to the end of the nick until an
		* available nick is found.
		*
		* @param autoNickChange Set to true if you want automatic nick changes
		*                       during connection.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void setAutoNickChange(bool autoNickChange) 
			throw(Exception &);

	   /**
		* Starts an ident server (Identification Protocol Server, RFC 1413).
		*  <p>
		* Most IRC servers attempt to contact the ident server on connecting
		* hosts in order to determine the user's identity.  A few IRC servers
		* will not allow you to connect unless this information is provided.
		*  <p>
		* So when a PircBot is run on a machine that does not run an ident server,
		* it may be necessary to call this method to start one up.
		*  <p>
		* Calling this method starts up an ident server which will respond with
		* the login provided by calling getLogin() and then shut down immediately.
		* It will also be shut down if it has not been contacted within 60 seconds
		* of creation.
		*  <p>
		* If you require an ident response, then the correct procedure is to start
		* the ident server and then connect to the IRC server.  The IRC server may
		* then contact the ident server to get the information it needs.
		*  <p>
		* The ident server will fail to start if there is already an ident server
		* running on port 113, or if you are running as an unprivileged user who
		* is unable to create a server socket on that port number.
		*  <p>
		* If it is essential for you to use an ident server when connecting to an
		* IRC server, then make sure that port 113 on your machine is visible to
		* the IRC server so that it may contact the ident server.
		*
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void startIdentServer() const
			throw(Exception &);

	   /**
		* Joins a channel.
		* 
		* @param channel The name of the channel to join (eg "#cs").
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void joinChannel(const char * const channel) const
			throw(Exception &);

	   /**
		* Joins a channel with a key.
		* 
		* @param channel The name of the channel to join (eg "#cs").
		* @param key The key that will be used to join the channel.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
	    virtual void joinChannel(const char * const channel, 
			                     const char * const key) const
			throw(Exception &); 

	   /**
		* Parts a channel.
		*
		* @param channel The name of the channel to leave.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void partChannel(const char * const channel) const
			throw(Exception &);

	   /**
		* Parts a channel, giving a reason.
		*
		* @param channel The name of the channel to leave.
		* @param reason  The reason for parting the channel.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void partChannel(const char * const channel, 
			                     const char * const reason) const
			throw(Exception &);

	   /**
		* Quits from the IRC server.
		* Providing we are actually connected to an IRC server, the
		* onDisconnect() method will be called as soon as the IRC server
		* disconnects us.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void quitServer() const
			throw(Exception &);

	   /**
		* Quits from the IRC server with a reason.
		* Providing we are actually connected to an IRC server, the
		* onDisconnect() method will be called as soon as the IRC server
		* disconnects us.
		*
		* @param reason The reason for quitting the server.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void quitServer(const char * const reason) const
			throw(Exception &);

	   /**
		* Sends a raw line to the IRC server as soon as possible, bypassing the
		* outgoing message queue.
		*
		* @param line The raw line to send to the IRC server.
		*/
		virtual void sendRawLine(const char * const line) const
			throw(Exception &);

	   /**
		* Sends a raw line through the outgoing message queue.
		* 
		* @param line The raw line to send to the IRC server.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void sendRawLineViaQueue(const char * const line) const
			throw(Exception &);
		
	   /**
		* Sends a message to a channel or a private message to a user.  These
		* messages are added to the outgoing message queue and sent at the
		* earliest possible opportunity.
		*  <p>
		* Some examples: -
		*  <pre>    // Send the message "Hello!" to the channel #cs.
		*    sendMessage("#cs", "Hello!");
		*    
		*    // Send a private message to Paul that says "Hi".
		*    sendMessage("Paul", "Hi");</pre>
		*  
		* You may optionally apply colours, boldness, underlining, etc to
		* the message by using the <code>Colors</code> class.
		*
		* @param target The name of the channel or user nick to send to.
		* @param message The message to send.
		* 
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*
		* @see Colors
		*/
		virtual void sendMessage(const char * const target, 
			                     const char * const message) const
			throw(Exception &);

	   /**
		* Sends an action to the channel or to a user.
		*
		* @param target The name of the channel or user nick to send to.
		* @param action The action to send.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		* 
		* @see Colors
		*/
		virtual void sendAction(const char * const target, 
			                    const char * const action) const
			throw(Exception &);

	   /**
		* Sends a notice to the channel or to a user.
		*
		* @param target The name of the channel or user nick to send to.
		* @param notice The notice to send.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void sendNotice(const char * const target, 
			                    const char * const notice) const
			throw(Exception &);

	   /**
		* Sends a CTCP command to a channel or user.  (Client to client protocol).
		* Examples of such commands are "PING <number>", "FINGER", "VERSION", etc.
		* For example, if you wish to request the version of a user called "Dave",
		* then you would call <code>sendCTCPCommand("Dave", "VERSION");</code>.
		* The type of response to such commands is largely dependant on the target
		* client software.
		* 
		* @param target The name of the channel or user to send the CTCP message to.
		* @param command The CTCP command to send.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
	    virtual void sendCTCPCommand(const char * const target, 
			                         const char * const command) const
			throw(Exception &);


	   /**
		* Attempt to change the current nick (nickname) of the bot when it
		* is connected to an IRC server.
		* After confirmation of a successful nick change, the getNick method
		* will return the new nick.
		*
		* @param newNick The new nick to use.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void changeNick(const char * const newNick) const
			throw(Exception &);
		
	   /**
		* Set the mode of a channel.
		* This method attempts to set the mode of a channel.  This
		* may require the bot to have operator status on the channel.
		* For example, if the bot has operator status, we can grant
		* operator status to "Dave" on the #cs channel
		* by calling setMode("#cs", "+o Dave");
		* An alternative way of doing this would be to use the op method.
		* 
		* @param channel The channel on which to perform the mode change.
		* @param mode    The new mode to apply to the channel.  This may include
		*                zero or more arguments if necessary.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		* 
		* @see #op(const char * const channel, const char * const nick) const op
		*/
		virtual void setMode(const char * const channel, 
			                 const char * const mode) const
			throw(Exception &);

	   /**
		* Sends an invitation to join a channel.  Some channels can be marked
		* as "invite-only", so it may be useful to allow a bot to invite people
		* into it.
		* 
		* @param nick    The nick of the user to invite
		* @param channel The channel you are inviting the user to join.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void sendInvite(const char * const nick, 
			                    const char * const channel) const
			throw(Exception &);

	   /**
		* Bans a user from a channel.  An example of a valid hostmask is
		* "*!*compu@*.18hp.net".  This may be used in conjunction with the
		* kick method to permanently remove a user from a channel.
		* Successful use of this method may require the bot to have operator
		* status itself.
		* 
		* @param channel The channel to ban the user from.
		* @param hostmask A hostmask representing the user we're banning.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void ban(const char * const channel, 
			             const char * const hostmask) const
			throw(Exception &);

	   /**
		* Unbans a user from a channel.  An example of a valid hostmask is
		* "*!*compu@*.18hp.net".
		* Successful use of this method may require the bot to have operator
		* status itself.
		* 
		* @param channel The channel to unban the user from.
		* @param hostmask A hostmask representing the user we're unbanning.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void unBan(const char * const channel, 
			               const char * const hostmask) const 
			throw(Exception &);

	   /**
		* Grants operator privilidges to a user on a channel.
		* Successful use of this method may require the bot to have operator
		* status itself.
		* 
		* @param channel The channel we're opping the user on.
		* @param nick The nick of the user we are opping.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void op(const char * const channel, 
			            const char * const nick) const
			throw(Exception &);

	   /**
		* Removes operator privilidges from a user on a channel.
		* Successful use of this method may require the bot to have operator
		* status itself.
		* 
		* @param channel The channel we're deopping the user on.
		* @param nick The nick of the user we are deopping.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void deOp(const char * const channel, 
			              const char * const nick) const
			throw(Exception &);
	    
	   /**
		* Grants voice privilidges to a user on a channel.
		* Successful use of this method may require the bot to have operator
		* status itself.
		* 
		* @param channel The channel we're voicing the user on.
		* @param nick The nick of the user we are voicing.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void voice(const char * const channel, 
			               const char * const nick) const
			throw(Exception &);

	   /**
		* Removes voice privilidges from a user on a channel.
		* Successful use of this method may require the bot to have operator
		* status itself.
		* 
		* @param channel The channel we're devoicing the user on.
		* @param nick The nick of the user we are devoicing.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void deVoice(const char * const channel, 
			                 const char * const nick) const
			throw(Exception &);

	   /**
		* Set the topic for a channel.
		* This method attempts to set the topic of a channel.  This
		* may require the bot to have operator status if the topic
		* is protected.
		* 
		* @param channel The channel on which to perform the mode change.
		* @param topic   The new topic for the channel.
		* 
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void setTopic(const char * const channel, 
		                      const char * const topic) const
			throw(Exception &);

	   /**
		* Kicks a user from a channel.
		* This method attempts to kick a user from a channel and
		* may require the bot to have operator status in the channel.
		* 
		* @param channel The channel to kick the user from.
		* @param nick    The nick of the user to kick.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void kick(const char * const channel, 
			              const char * const nick) const
			throw(Exception &);

	   /**
		* Kicks a user from a channel, giving a reason.
		* This method attempts to kick a user from a channel and
		* may require the bot to have operator status in the channel.
		* 
		* @param channel The channel to kick the user from.
		* @param nick    The nick of the user to kick.
		* @param reason  A description of the reason for kicking a user.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void kick(const char * const channel, 
			              const char * const nick, 
						  const char * const reason) const
			throw(Exception &);
	    
	   /**
		* Issues a request for a list of all channels on the IRC server.
		* When the PircBot receives information for each channel, it will
		* call the onChannelInfo method, which you will need to override
		* if you want it to do anything useful.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		* 
		* @see #onChannelInfo(const char * const channel, const int &userCount, const char * const topic) onChannelInfo
		*/
		virtual void listChannels() const 
			throw(Exception &);

	   /**
		* Issues a request for a list of all channels on the IRC server.
		* When the PircBot receives information for each channel, it will
		* call the onChannelInfo method, which you will need to override
		* if you want it to do anything useful.
		*  <p>
		* Some IRC servers support certain parameters for LIST requests.
		* One example is a parameter of ">10" to list only those channels
		* that have more than 10 users in them.  Whether these parameters
		* are supported or not will depend on the IRC server software.
		* 
		* @param parameters The parameters to supply when requesting the
		*                   list.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		* 
		* @see #onChannelInfo(const char * const channel, const int &userCount, const char * const topic) onChannelInfo
		*/
		virtual void listChannels(const char * const parameters) const
    		throw(Exception &);

	   /**
		* Sends a file to another user.  Resuming is supported.
		* The other user must be able to connect directly to your bot to be
		* able to receive the file.
		*  <p>
		* You may throttle the speed of this file transfer by calling the
		* setPacketDelay method on the DccFileTransfer that is returned.
		*  <p>
		* This method may not be overridden.
		* 
		* @param file The file to send.
		* @param nick The user to whom the file is to be sent.
		* @param timeout The number of milliseconds to wait for the recipient to
		*                acccept the file (we recommend about 120000).
		* 
		* @return The DccFileTransfer that can be used to monitor this transfer.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		* 
		* @see DccFileTransfer
		* 
		*/
		///@todo write this when DccFileTransfer class is written
		//public void DccFileTransfer dccSendFile(File file, string nick, int timeout);
		//	DccFileTransfer transfer = new DccFileTransfer(this, _dccManager, file, nick, timeout);
		//	transfer.doSend(true);
		//	return transfer;
		//}


	   /**
		* Receives a file that is being sent to us by a DCC SEND request.
		* Please use the onIncomingFileTransfer method to receive files.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		* 
		* @deprecated As of PircBot 1.2.0, use {@link #onIncomingFileTransfer(DccFileTransfer)}
		*/
		///@todo write this when DccFileTransfer class is written
		//protected final void dccReceiveFile(File file, long address, int port, int size) {
        //throw new RuntimeException("dccReceiveFile is deprecated, please use sendFile");
        //}

	   /**
		* Attempts to establish a DCC CHAT session with a client.  This method
		* issues the connection request to the client and then waits for the
		* client to respond.  If the connection is successfully made, then a
		* DccChat object is returned by this method.  If the connection is not
		* made within the time limit specified by the timeout value, then null
		* is returned.
		*  <p>
		* It is <b>strongly recommended</b> that you call this method within a new
		* Thread, as it may take a long time to return.
		*  <p>
		* This method may not be overridden.
		* 
		* @param nick The nick of the user we are trying to establish a chat with.
		* @param timeout The number of milliseconds to wait for the recipient to
		*                accept the chat connection (we recommend about 120000).
		* 
		* @return a DccChat object that can be used to send and recieve lines of
		*         text.  Returns <b>null</b> if the connection could not be made.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		* 
		* @see DccChat
		*/
		///@todo write this when DccFileTransfer class is written
		//public final DccChat dccSendChatRequest(string nick, int timeout) {


	   /**
		* Attempts to accept a DCC CHAT request by a client.
		* Please use the onIncomingChatRequest method to receive files.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		* 
		* @deprecated As of PircBot 1.2.0, use {@link #onIncomingChatRequest(DccChat)}
		*/
		///@todo write this when DccChat class is written.
		//protected final DccChat dccAcceptChatRequest(string sourceNick, long address, int port) {
		//	throw new RuntimeException("dccAcceptChatRequest is deprecated, please use onIncomingChatRequest");
		//}

	   /**
		* Adds a line to the log.  This log is currently output to the standard
		* output and is in the correct format for use by tools such as pisg, the
		* Perl IRC Statistics Generator.  You may override this method if you wish
		* to do something else with log entries.
		* Each line in the log begins with a number which
		* represents the logging time This timestamp and the following log entry 
		* are separated by a single space character, " ".  Outgoing messages are 
		* distinguishable by a log entry that has ">>>" immediately following the 
		* space character after the timestamp.  DCC events use "+++" and warnings 
		* about unhandled
		* Exceptions and Errors use "###".
		*  <p>
		* This implementation of the method will only cause log entries to be
		* output if the PircBot has had its verbose mode turned on by calling
		* setVerbose(true);
		* 
		* @param line The line to add to the log.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void log(const char * const line) const
			throw(Exception &);

	   /**
		* This method handles events when any line of text arrives from the server,
		* then calling the appropriate method in the PircBot.  This method is
		* protected and only called by the InputThread for this instance.
		*  <p>
		* This method may not be overridden!
		*
		* This method was protected in Java but it's public here
		* so it can be accessed in InputThread
		* 
		* @param line The raw line of text from the server.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void handleLine(const char * const line)
			throw(Exception &);

	protected:

	   /**
		* This method is called once the PircBot has successfully connected to
		* the IRC server.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onConnect()
			throw(Exception &);

	public:

	   /**
		* This method carries out the actions to be performed when the PircBot
		* gets disconnected.  This may happen if the PircBot quits from the
		* server, or if the connection is unexpectedly lost.
		*  <p>
		* Disconnection from the IRC server is detected immediately if either
		* we or the server close the connection normally. If the connection to
		* the server is lost, but neither we nor the server have explicitly closed
		* the connection, then it may take a few minutes to detect (this is
		* commonly referred to as a "ping timeout").
		*  <p>
		* If you wish to get your IRC bot to automatically rejoin a server after
		* the connection has been lost, then this is probably the ideal method to
		* override to implement such functionality.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		*
		* This was protected in the Java version but I had to make it public
		* in the C++ version since other classes were calling this method
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onDisconnect() 
			throw(Exception &); 

	protected:

		//Written, this is part of the pimpl in the PircBot.cpp class
	    //void processServerResponse(const int &code, const string &response) 

	   /**
		* This method is called when we receive a numeric response from the
		* IRC server.
		*  <p> 
		* Numerics in the range from 001 to 099 are used for client-server
		* connections only and should never travel between servers.  Replies
		* generated in response to commands are found in the range from 200
		* to 399.  Error replies are found in the range from 400 to 599.
		*  <p>
		* For example, we can use this method to discover the topic of a
		* channel when we join it.  If we join the channel #test which
		* has a topic of &quot;I am King of Test&quot; then the response
		* will be &quot;<code>PircBot #test :I Am King of Test</code>&quot;
		* with a code of 332 to signify that this is a topic.
		* (This is just an example - note that overriding the
		* <code>onTopic</code> method is an easier way of finding the
		* topic for a channel). Check the IRC RFC for the full list of other
		* command response codes.
		*  <p>
		* PircBot implements the interface ReplyConstants, which contains
		* contstants that you may find useful here.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param code The three-digit numerical code for the response.
		* @param response The full response from the IRC server.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		* 
		* @see ReplyConstants
		*/
		virtual void onServerResponse(const int &code, 
			                          const char * const response)
			throw(Exception &);

	   /**
		* This method is called when we receive a user list from the server
		* after joining a channel.
		*
		* DO NOT try and delete the User pointer.  Instead 
		* to deallocate call releaseMemoryOfUserArray().  This is to
		* keep everything dll boundary safe.
		*
		*  <p>
		* Shortly after joining a channel, the IRC server sends a list of all
		* users in that channel. The PircBot collects this information and
		* calls this method as soon as it has the full list.
		*  <p>
		* To obtain the nick of each user in the channel, call the getNick()
		* method on each User object in the array.
		*  <p>
		* At a later time, you may call the getUsers method to obtain an
		* up to date list of the users in the channel.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The name of the channel.
		* @param users An array of User objects belonging to this channel.
		* @param usersArraySize The size of the users array
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		* 
		* @see User
		*/
		virtual void onUserList(const char * const channel, 
			                    User* users, int usersArraySize)
			throw(Exception &);

	   /**
		* This method is called whenever a message is sent to a channel.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		*
		* @param channel The channel to which the message was sent.
		* @param sender The nick of the person who sent the message.
		* @param login The login of the person who sent the message.
		* @param hostname The hostname of the person who sent the message.
		* @param message The actual message sent to the channel.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onMessage(const char * const channel, 
			                   const char * const sender, 
					           const char * const login, 
					           const char * const hostname, 
					           const char * const message)
			throw(Exception &);

       /**
		* This method is called whenever a private message is sent to the PircBot.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		*
		* @param sender The nick of the person who sent the private message.
		* @param login The login of the person who sent the private message.
		* @param hostname The hostname of the person who sent the private message.
		* @param message The actual message.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onPrivateMessage(const char * const sender, 
			                          const char * const login, 
							          const char * const hostname, 
							          const char * const message)
			throw(Exception &);

		/**
		* This method is called whenever an ACTION is sent from a user.  E.g.
		* such events generated by typing "/me goes shopping" in most IRC clients.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param sender The nick of the user that sent the action.
		* @param login The login of the user that sent the action.
		* @param hostname The hostname of the user that sent the action.
		* @param target The target of the action, be it a channel or our nick.
		* @param action The action carried out by the user.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
	    virtual void onAction(const char * const sender, 
					          const char * const login, 
					          const char * const hostname, 
					          const char * const target, 
					          const char * const action)
			throw(Exception &);

	   /**
		* This method is called whenever we receive a notice.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param sourceNick The nick of the user that sent the notice.
		* @param sourceLogin The login of the user that sent the notice.
		* @param sourceHostname The hostname of the user that sent the notice.
		* @param target The target of the notice, be it our nick or a channel name.
		* @param notice The notice message.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onNotice(const char * const sourceNick, 
					          const char * const sourceLogin, 
					          const char * const sourceHostname, 
					          const char * const target, 
					          const char * const notice)
			throw(Exception &);

	   /**
		* This method is called whenever someone (possibly us) joins a channel
		* which we are on.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		*
		* @param channel The channel which somebody joined.
		* @param sender The nick of the user who joined the channel.
		* @param login The login of the user who joined the channel.
		* @param hostname The hostname of the user who joined the channel.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
        virtual void onJoin(const char * const channel, 
			                const char * const sender, 
					        const char * const login, 
					        const char * const hostname)
			throw(Exception &);

	   /**
		* This method is called whenever someone (possibly us) parts a channel
		* which we are on.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		*
		* @param channel The channel which somebody parted from.
		* @param sender The nick of the user who parted from the channel.
		* @param login The login of the user who parted from the channel.
		* @param hostname The hostname of the user who parted from the channel.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onPart(const char * const channel, 
                            const char * const sender, 
					        const char * const login, 
					        const char * const hostname)
			throw(Exception &);

	   /**
		* This method is called whenever someone (possibly us) changes nick on any
		* of the channels that we are on.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		*
		* @param oldNick The old nick.
		* @param login The login of the user.
		* @param hostname The hostname of the user.
		* @param newNick The new nick.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onNickChange(const char * const oldNick, 
			                      const char * const login, 
						          const char * const hostname, 
						          const char * const newNick)
			throw(Exception &);

	   /**
		* This method is called whenever someone (possibly us) is kicked from
		* any of the channels that we are in.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel from which the recipient was kicked.
		* @param kickerNick The nick of the user who performed the kick.
		* @param kickerLogin The login of the user who performed the kick.
		* @param kickerHostname The hostname of the user who performed the kick.
		* @param recipientNick The unfortunate recipient of the kick.
		* @param reason The reason given by the user who performed the kick.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onKick(const char * const channel, 
			                const char * const kickerNick, 
					        const char * const kickerLogin, 
					        const char * const kickerHostname, 
					        const char * const recipientNick, 
					        const char * const reason)
			throw(Exception &);

	   /**
		* This method is called whenever someone (possibly us) quits from the
		* server.  We will only observe this if the user was in one of the
		* channels to which we are connected.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param sourceNick The nick of the user that quit from the server.
		* @param sourceLogin The login of the user that quit from the server.
		* @param sourceHostname The hostname of the user that quit from the server.
		* @param reason The reason given for quitting the server.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onQuit(const char * const sourceNick, 
					        const char * const sourceLogin, 
					        const char * const sourceHostname, 
					        const char * const reason)
			throw(Exception &);

       /**
		* This method is called whenever a user sets the topic, or when
		* PircBot joins a new channel and discovers its topic.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		*
		* @param channel The channel that the topic belongs to.
		* @param topic The topic for the channel.
		* 
		* @deprecated As of 1.2.0, replaced by 
		    {@link #onTopic(const char * const channel, const char * const topic, const char * const setBy, long date, bool changed)}
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onTopic(const char * const channel, 
			                 const char * const topic)
			 throw(Exception &);

	   /**
		* This method is called whenever a user sets the topic, or when
		* PircBot joins a new channel and discovers its topic.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		*
		* @param channel The channel that the topic belongs to.
		* @param topic The topic for the channel.
		* @param setBy The nick of the user that set the topic.
		* @param date When the topic was set (milliseconds since the epoch).
		* @param changed True if the topic has just been changed, false if
		*                the topic was already there.
		* 
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onTopic(const char * const channel, 
				             const char * const topic, 
                             const char * const setBy, 
                             long date, bool changed)
			throw(Exception &);

	   /**
		* After calling the listChannels() method in PircBot, the server
		* will start to send us information about each channel on the
		* server.  You may override this method in order to receive the
		* information about each channel as soon as it is received.
		*  <p>
		* Note that certain channels, such as those marked as hidden,
		* may not appear in channel listings.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The name of the channel.
		* @param userCount The number of users visible in this channel.
		* @param topic The topic for this channel.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		* 
		* @see #listChannels() listChannels
		*/
		virtual void onChannelInfo(const char * const channel, 
			                       const int &userCount, 
								   const char * const topic)
			throw(Exception &);

	private:
		//This is in the pimpl inside of PircBot.cpp
		//void processMode(string target, string sourceNick, 
		//	             string sourceLogin, string sourceHostname, 
		//				 string mode) 
	protected:

	   /**
		* Called when the mode of a channel is set.
		*  <p>
		* You may find it more convenient to decode the meaning of the mode
		* string by overriding the onOp, onDeOp, onVoice, onDeVoice,
		* onChannelKey, onDeChannelKey, onChannelLimit, onDeChannelLimit,
		* onChannelBan or onDeChannelBan methods as appropriate.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		*
		* @param channel The channel that the mode operation applies to.
		* @param sourceNick The nick of the user that set the mode.
		* @param sourceLogin The login of the user that set the mode.
		* @param sourceHostname The hostname of the user that set the mode.
		* @param mode The mode that has been set.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onMode(const char * const channel, 
			                const char * const sourceNick, 
							const char * const sourceLogin, 
							const char * const sourceHostname, 
							const char * const mode)
			throw(Exception &);

	   /**
		* Called when the mode of a user is set.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param targetNick The nick that the mode operation applies to.
		* @param sourceNick The nick of the user that set the mode.
		* @param sourceLogin The login of the user that set the mode.
		* @param sourceHostname The hostname of the user that set the mode.
		* @param mode The mode that has been set.
		* 
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
        virtual void onUserMode(const char * const targetNick, 
			                    const char * const sourceNick, 
								const char * const sourceLogin, 
								const char * const sourceHostname, 
								const char * const mode)
			throw(Exception &);

	   /**
		* Called when a user (possibly us) gets granted operator status for a channel.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
		* @param recipient The nick of the user that got 'opped'.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onOp(const char * const channel, 
			              const char * const sourceNick, 
				          const char * const sourceLogin, 
				          const char * const sourceHostname, 
				          const char * const recipient)
			throw(Exception &);

	   /**
		* Called when a user (possibly us) gets operator status taken away.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
		* @param recipient The nick of the user that got 'deopped'.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
        virtual void onDeop(const char * const channel, 
			                const char * const sourceNick, 
					        const char * const sourceLogin, 
					        const char * const sourceHostname, 
					        const char * const recipient)
			throw(Exception &);

	   /**
		* Called when a user (possibly us) gets voice status granted in a channel.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
		* @param recipient The nick of the user that got 'voiced'.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
        virtual void onVoice(const char * const channel, 
			                 const char * const sourceNick, 
					         const char * const sourceLogin, 
					         const char * const sourceHostname, 
					         const char * const recipient)
			throw(Exception &);

	   /**
		* Called when a user (possibly us) gets voice status removed.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
		* @param recipient The nick of the user that got 'devoiced'.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onDeVoice(const char * const channel, 
			                   const char * const sourceNick, 
					           const char * const sourceLogin, 
					           const char * const sourceHostname, 
					           const char * const recipient)
			throw(Exception &);

	   /**
		* Called when a channel key is set.  When the channel key has been set,
		* other users may only join that channel if they know the key.  Channel keys
		* are sometimes referred to as passwords.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
		* @param key The new key for the channel.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
        virtual void onSetChannelKey(const char * const channel, 
			                         const char * const sourceNick, 
							         const char * const sourceLogin, 
							         const char * const sourceHostname, 
							         const char * const key)
			throw(Exception &);

	   /**
		* Called when a channel key is removed.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
		* @param key The key that was in use before the channel key was removed.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onRemoveChannelKey(const char * const channel, 
			                            const char * const sourceNick, 
								        const char * const sourceLogin, 
								        const char * const sourceHostname, 
								        const char * const key)
			throw(Exception &);

	   /**
		* Called when a user limit is set for a channel.  The number of users in
		* the channel cannot exceed this limit.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
		* @param limit The maximum number of users that may be in this channel at the same time.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
	    virtual void onSetChannelLimit(const char * const channel, 
		                               const char * const sourceNick, 
						               const char * const sourceLogin, 
						               const char * const sourceHostname, 
						               const int &limit)
			throw(Exception &);

	   /**
		* Called when the user limit is removed for a channel.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onRemoveChannelLimit(const char * const channel, 
										  const char * const sourceNick, 
										  const char * const sourceLogin, 
										  const char * const sourceHostname)
			throw(Exception &);

	   /**
		* Called when a user (possibly us) gets banned from a channel.  Being
		* banned from a channel prevents any user with a matching hostmask from
		* joining the channel.  For this reason, most bans are usually directly
		* followed by the user being kicked :-)
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
		* @param hostmask The hostmask of the user that has been banned.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onSetChannelBan(const char * const channel, 
			                         const char * const sourceNick, 
									 const char * const sourceLogin, 
									 const char * const sourceHostname, 
									 const char * const hostmask)
			throw(Exception &);

	   /**
		* Called when a hostmask ban is removed from a channel.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
		* @param hostmask
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onRemoveChannelBan(const char * const channel, 
			                            const char * const sourceNick, 
										const char * const sourceLogin, 
										const char * const sourceHostname, 
										const char * const hostmask)
			throw(Exception &);

	   /**
		* Called when topic protection is enabled for a channel.  Topic protection
		* means that only operators in a channel may change the topic.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onSetTopicProtection(const char * const channel, 
			                              const char * const sourceNick, 
										  const char * const sourceLogin, 
										  const char * const sourceHostname)
			throw(Exception &);

	   /**
		* Called when topic protection is removed for a channel.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onRemoveTopicProtection(const char * const channel, 
			                                 const char * const sourceNick, 
											 const char * const sourceLogin, 
											 const char * const sourceHostname)
			throw(Exception &);

	   /**
		* Called when a channel is set to only allow messages from users that
		* are in the channel.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onSetNoExternalMessages(const char * const channel, 
			                                 const char * const sourceNick, 
											 const char * const sourceLogin, 
											 const char * const sourceHostname)
			throw(Exception &);
        
	   /**
		* Called when a channel is set to allow messages from any user, even
		* if they are not actually in the channel.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onRemoveNoExternalMessages(const char * const channel, 
			                                    const char * const sourceNick, 
												const char * const sourceLogin, 
												const char * const sourceHostname)
			throw(Exception &);
	    	    
	   /**
		* Called when a channel is set to 'invite only' mode.  A user may only
		* join the channel if they are invited by someone who is already in the
		* channel.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onSetInviteOnly(const char * const channel, 
			                         const char * const sourceNick, 
									 const char * const sourceLogin, 
									 const char * const sourceHostname)
			throw(Exception &);
	    	    
	   /**
		* Called when a channel has 'invite only' removed.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onRemoveInviteOnly(const char * const channel, 
			                            const char * const sourceNick, 
										const char * const sourceLogin, 
										const char * const sourceHostname)
			throw(Exception &);
	    	    
	   /**
		* Called when a channel is set to 'moderated' mode.  If a channel is
		* moderated, then only users who have been 'voiced' or 'opped' may speak
		* or change their nicks.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onSetModerated(const char * const channel, 
			                        const char * const sourceNick, 
									const char * const sourceLogin, 
									const char * const sourceHostname)
			throw(Exception &);
	    	    
	   /**
		* Called when a channel has moderated mode removed.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onRemoveModerated(const char * const channel, 
			                           const char * const sourceNick, 
									   const char * const sourceLogin, 
									   const char * const sourceHostname)
			throw(Exception &);
	    	    
	   /**
		* Called when a channel is marked as being in private mode.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onSetPrivate(const char * const channel, 
			                      const char * const sourceNick, 
								  const char * const sourceLogin, 
								  const char * const sourceHostname)
			throw(Exception &);
	    	    
	   /**
		* Called when a channel is marked as not being in private mode.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onRemovePrivate(const char * const channel, 
			                         const char * const sourceNick, 
									 const char * const sourceLogin, 
									 const char * const sourceHostname)
			throw(Exception &);
	    	    
	   /**
		* Called when a channel is set to be in 'secret' mode.  Such channels
		* typically do not appear on a server's channel listing.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onSetSecret(const char * const channel, 
			                     const char * const sourceNick, 
								 const char * const sourceLogin, 
								 const char * const sourceHostname)
			throw(Exception &);	    
	    
	   /**
		* Called when a channel has 'secret' mode removed.
		*  <p>
		* This is a type of mode change and is also passed to the onMode
		* method in the PircBot class.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param channel The channel in which the mode change took place.
		* @param sourceNick The nick of the user that performed the mode change.
		* @param sourceLogin The login of the user that performed the mode change.
		* @param sourceHostname The hostname of the user that performed the mode change.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onRemoveSecret(const char * const channel, 
			                        const char * const sourceNick, 
									const char * const sourceLogin, 
									const char * const sourceHostname)
			throw(Exception &);

	   /**
		* Called when we are invited to a channel by a user.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param targetNick The nick of the user being invited - should be us!
		* @param sourceNick The nick of the user that sent the invitation.
		* @param sourceLogin The login of the user that sent the invitation.
		* @param sourceHostname The hostname of the user that sent the invitation.
		* @param channel The channel that we're being invited to.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
       virtual void onInvite(const char * const targetNick, 
		                     const char * const sourceNick, 
					         const char * const sourceLogin, 
					         const char * const sourceHostname, 
					         const char * const channel)
			throw(Exception &);

	   /**
		* This method used to be called when a DCC SEND request was sent to the PircBot.
		* Please use the onIncomingFileTransfer method to receive files, as it
		* has better functionality and supports resuming.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		* 
		* @deprecated As of PircBot 1.2.0, use {@link #onIncomingFileTransfer(DccFileTransfer)}
		*/
	    ///@todo write this when Dcc classes are done
		//protected void onDccSendRequest(string sourceNick, string sourceLogin, string sourceHostname, string filename, long address, int port, int size) {}
	    
	    
	   /**
		* This method used to be called when a DCC CHAT request was sent to the PircBot.
		* Please use the onIncomingChatRequest method to accept chats, as it
		* has better functionality.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		* 
		* @deprecated As of PircBot 1.2.0, use {@link #onIncomingChatRequest(DccChat)}
		*/
		///@todo write this when Dcc classes are done
		//protected void onDccChatRequest(string sourceNick, string sourceLogin, string sourceHostname, long address, int port) {}
	    
	    
	   /**
		* This method is called whenever a DCC SEND request is sent to the PircBot.
		* This means that a client has requested to send a file to us.
		* This abstract implementation performs no action, which means that all
		* DCC SEND requests will be ignored by default. If you wish to receive
		* the file, then you may override this method and call the receive method
		* on the DccFileTransfer object, which connects to the sender and downloads
		* the file.
		*  <p>
		* Example:
		* <pre> public void onIncomingFileTransfer(DccFileTransfer transfer) {
		*     // Use the suggested file name.
		*     File file = transfer.getFile();
		*     // Receive the transfer and save it to the file, allowing resuming.
		*     transfer.receive(file, true);
		* }</pre>
		*  <p>
		* <b>Warning:</b> Receiving an incoming file transfer will cause a file
		* to be written to disk. Please ensure that you make adequate security
		* checks so that this file does not overwrite anything important!
		*  <p>
		* Each time a file is received, it happens within a new Thread
		* in order to allow multiple files to be downloaded by the PircBot
		* at the same time. 
		*  <p>
		* If you allow resuming and the file already partly exists, it will
		* be appended to instead of overwritten.  If resuming is not enabled,
		* the file will be overwritten if it already exists.
		*  <p>
		* You can throttle the speed of the transfer by calling the setPacketDelay
		* method on the DccFileTransfer object, either before you receive the
		* file or at any moment during the transfer.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		*
		* @param transfer The DcccFileTransfer that you may accept.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		* 
		* @see DccFileTransfer
		* 
		*/
		///@todo write this when Dcc classes are done
		//protected void onIncomingFileTransfer(DccFileTransfer transfer) {}
	    
	    
	   /**
		* This method gets called when a DccFileTransfer has finished.
		* If there was a problem, the Exception will say what went wrong.
		* If the file was sent successfully, the Exception will be null.
		*  <p>
		* Both incoming and outgoing file transfers are passed to this method.
		* You can determine the type by calling the isIncoming or isOutgoing
		* methods on the DccFileTransfer object.
		*
		* @param transfer The DccFileTransfer that has finished.
		* @param e null if the file was transfered successfully, otherwise this
		*          will report what went wrong.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		* 
		* @see DccFileTransfer
		* 
		*/
		///@todo write this when Dcc classes are done
		//protected void onFileTransferFinished(DccFileTransfer transfer, Exception e) {
	    
	    
	   /**
		* This method will be called whenever a DCC Chat request is received.
		* This means that a client has requested to chat to us directly rather
		* than via the IRC server. This is useful for sending many lines of text
		* to and from the bot without having to worry about flooding the server
		* or any operators of the server being able to "spy" on what is being
		* said. This abstract implementation performs no action, which means
		* that all DCC CHAT requests will be ignored by default.
		*  <p>
		* If you wish to accept the connection, then you may override this
		* method and call the accept() method on the DccChat object, which
		* connects to the sender of the chat request and allows lines to be
		* sent to and from the bot.
		*  <p>
		* Your bot must be able to connect directly to the user that sent the
		* request.
		*  <p>
		* Example: 
		* <pre> public void onIncomingChatRequest(DccChat chat) {
		*     try {
		*         // Accept all chat, whoever it's from.
		*         chat.accept();
		*         chat.sendLine("Hello");
		*         const char *response = chat.readLine();
		*         chat.close();
		*     }
		*     catch (IOException e) {}
		* }</pre>
		* 
		* Each time this method is called, it is called from within a new Thread
		* so that multiple DCC CHAT sessions can run concurrently.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		*
		* @param chat A DccChat object that represents the incoming chat request.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		* 
		* @see DccChat
		* 
		*/
		///@todo write this when dcc classes are done
		//protected void onIncomingChatRequest(DccChat chat) {}

	   /**
		* This method is called whenever we receive a VERSION request.
		* This abstract implementation responds with the PircBot's _version string,
		* so if you override this method, be sure to either mimic its functionality
		* or to call PircBot::onVersion(...);
		* 
		* @param sourceNick The nick of the user that sent the VERSION request.
		* @param sourceLogin The login of the user that sent the VERSION request.
		* @param sourceHostname The hostname of the user that sent the VERSION request.
		* @param target The target of the VERSION request, be it our nick or a channel name.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onVersion(const char * const sourceNick, 
                               const char * const sourceLogin, 
                               const char * const sourceHostname, 
                               const char * const target)
			throw(Exception &);

	   /**
		* This method is called whenever we receive a PING request from another
		* user.
		*  <p>
		* This abstract implementation responds correctly, so if you override this
		* method, be sure to either mimic its functionality or to call
		* PircBot::onPing(...);
		* 
		* @param sourceNick The nick of the user that sent the PING request.
		* @param sourceLogin The login of the user that sent the PING request.
		* @param sourceHostname The hostname of the user that sent the PING request.
		* @param target The target of the PING request, be it our nick or a channel name.
		* @param pingValue The value that was supplied as an argument to the PING command.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onPing(const char * const sourceNick, 
			                const char * const sourceLogin, 
					        const char * const sourceHostname, 
					        const char * const target, 
					        const char * const pingValue)
			throw(Exception &);

	   /**
		* The actions to perform when a PING request comes from the server.
		*  <p>
		* This sends back a correct response, so if you override this method,
		* be sure to either mimic its functionality or to call
		* PircBot::onServerPing(response);
		*
		* @param response The response that should be given back in your PONG.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onServerPing(const char * const response)
			throw(Exception &);

	   /**
		* This method is called whenever we receive a TIME request.
		*  <p>
		* This abstract implementation responds correctly, so if you override this
		* method, be sure to either mimic its functionality or to call
		* PircBot::onTime(...);
		* 
		* @param sourceNick The nick of the user that sent the TIME request.
		* @param sourceLogin The login of the user that sent the TIME request.
		* @param sourceHostname The hostname of the user that sent the TIME request.
		* @param target The target of the TIME request, be it our nick or a channel name.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onTime(const char * const sourceNick, 
			                const char * const sourceLogin, 
					        const char * const sourceHostname, 
					        const char * const target)
			throw(Exception &);

	   /**
		* This method is called whenever we receive a FINGER request.
		*  <p>
		* This abstract implementation responds correctly, so if you override this
		* method, be sure to either mimic its functionality or to call
		* PircBot::onFinger(...);
		* 
		* @param sourceNick The nick of the user that sent the FINGER request.
		* @param sourceLogin The login of the user that sent the FINGER request.
		* @param sourceHostname The hostname of the user that sent the FINGER request.
		* @param target The target of the FINGER request, be it our nick or a channel name.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onFinger(const char * const sourceNick, 
			                  const char * const sourceLogin, 
					          const char * const sourceHostname, 
					          const char * const target)
			throw(Exception &);

	   /**
		* This method is called whenever we receive a line from the server that
		* the PircBot has not been programmed to recognise.
		*  <p>
		* The implementation of this method in the PircBot abstract class
		* performs no actions and may be overridden as required.
		* 
		* @param line The raw line that was received from the server.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void onUnknown(const char * const line)
			throw(Exception &);
		
	public:

	   /**
		* Sets the verbose mode. If verbose mode is set to true, then log entries
		* will be printed to the standard output. The default value is false and
		* will result in no output. For general development, we strongly recommend
		* setting the verbose mode to true.
		*
		* @param verbose true if verbose mode is to be used.  Default is false.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void setVerbose(const bool &verbose)
			throw(Exception &);

	protected:

	   /**
		* Sets the name of the bot, which will be used as its nick when it
		* tries to join an IRC server.  This should be set before joining
		* any servers, otherwise the default nick will be used.  You would
		* typically call this method from the constructor of the class that
		* extends PircBot.
		*  <p>
		* The changeNick method should be used if you wish to change your nick
		* when you are connected to a server.
		*
		* @param name The new name of the Bot.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void setName(const char * const name)
			throw(Exception &);
		
	private:

		//This is written in PircBot.cpp in the pimpl
		//void setNick(string nick) 

	protected:
	   /**
		* Sets the internal login of the Bot.  This should be set before joining
		* any servers.
		*
		* @param login The new login of the Bot.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void setLogin(const char * const login)
			throw(Exception &);

	   /**
		* Sets the internal version of the Bot.  This should be set before joining
		* any servers.
		*
		* @param version The new version of the Bot.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void setVersion(const char * const version)
			throw(Exception &);

	   /**
		* Sets the interal finger message.  This should be set before joining
		* any servers.
		*
		* @param finger The new finger message for the Bot.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void setFinger(const char * const finger) 
			throw(Exception &);

	public:

	   /**
		* Gets the name of the PircBot. This is the name that will be used as
		* as a nick when we try to join servers.
		*
		* @return The name of the PircBot.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual const char *getName() const
			throw(Exception &); 

	   /**
		* Returns the current nick of the bot. Note that if you have just changed
		* your nick, this method will still return the old nick until confirmation
		* of the nick change is received from the server.
		*  <p>
		* The nick returned by this method is maintained only by the PircBot
		* class and is guaranteed to be correct in the context of the IRC server.
		*
		* @return The current nick of the bot.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual const char *getNick()
			throw(Exception &);

	   /**
		* Gets the internal login of the PircBot.
		*
		* @return The login of the PircBot.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual const char *getLogin() const
			throw(Exception &);

	   /**
		* Gets the internal version of the PircBot.
		*
		* @return The version of the PircBot.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual const char *getVersion() const
			throw(Exception &);

	   /**
		* Gets the internal finger message of the PircBot.
		*
		* @return The finger message of the PircBot.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual const char *getFinger() const 
			throw(Exception &);

	   /**
		* Returns whether or not the PircBot is currently connected to a server.
		* The result of this method should only act as a rough guide,
		* as the result may not be valid by the time you act upon it.
		*
		* @return True if and only if the PircBot is currently connected to a server.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual bool isConnected() const
			throw(Exception &);

	   /**
		* Sets the number of milliseconds to delay between consecutive
		* messages when there are multiple messages waiting in the
		* outgoing message queue.  This has a default value of 1000ms.
		* It is a good idea to stick to this default value, as it will
		* prevent your bot from spamming servers and facing the subsequent
		* wrath!  However, if you do need to change this delay value (<b>not
		* recommended</b>), then this is the method to use.
		*
		* @param delay The number of milliseconds between each outgoing message.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void setMessageDelay(const unsigned int &delay)
			throw(Exception &);
		
	   /**
		* Returns the number of milliseconds that will be used to separate
		* consecutive messages to the server from the outgoing message queue.
		*
		* @return Number of milliseconds.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual unsigned int getMessageDelay() const
			throw(Exception &);

	   /**
		* Gets the maximum length of any line that is sent via the IRC protocol.
		* The IRC RFC specifies that line lengths, including the trailing \r\n
		* must not exceed 512 bytes.  Hence, there is currently no option to
		* change this value in PircBot.  All lines greater than this length
		* will be truncated before being sent to the IRC server.
		* 
		* @return The maximum line length (currently fixed at 512)
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual unsigned int getMaxLineLength() const
			throw(Exception &);

	   /**
		* Gets the number of lines currently waiting in the outgoing message Queue.
		* If this returns 0, then the Queue is empty and any new message is likely
		* to be sent to the IRC server immediately.
		*
		* @return The number of lines in the outgoing message Queue.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual unsigned int getOutgoingQueueSize() const
			throw(Exception &);

	   /**
		* Returns the name of the last IRC server the PircBot tried to connect to.
		* This does not imply that the connection attempt to the server was
		* successful (we suggest you look at the onConnect method).
		* A value of null is returned if the PircBot has never tried to connect
		* to a server.
		* 
		* @return The name of the last machine we tried to connect to. Returns
		*         null if no connection attempts have ever been made.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		const char *getServer() const
			throw(Exception &);

	   /**
		* Returns the port number of the last IRC server that the PircBot tried
		* to connect to.
		* This does not imply that the connection attempt to the server was
		* successful (we suggest you look at the onConnect method).
		* A value of -1 is returned if the PircBot has never tried to connect
		* to a server.
		* 
		* @return The port number of the last IRC server we connected to.
		*         Returns -1 if no connection attempts have ever been made.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		unsigned int getPort() const
			throw(Exception &);

	   /**
		* Returns the last password that we used when connecting to an IRC server.
		* This does not imply that the connection attempt to the server was
		* successful (we suggest you look at the onConnect method).
		* A value of null is returned if the PircBot has never tried to connect
		* to a server using a password.
		* 
		* @return The last password that we used when connecting to an IRC server.
		*         Returns null if we have not previously connected using a password.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
        const char *getPassword() const
			throw(Exception &);

		//This method will never be written
		//public int[] longToIp(long address)
		
		//This method will never be written
		//public long ipToLong(byte[] address)

		//This method will never be written
		//public void setEncoding(string charset) throws UnsupportedEncodingException 
		
		//This method will never be written
		//public string getEncoding() {
			
		//This method will never be written
	    //public InetAddress getInetAddress() {

	   /**
		* Sets the InetAddress to be used when sending DCC chat or file transfers.
		* This can be very useful when you are running a bot on a machine which
		* is behind a firewall and you need to tell receiving clients to connect
		* to a NAT/router, which then forwards the connection.
		* 
		* @param dccInetAddress The new InetAddress, or null to use the default.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		///@todo write this or not?
		/*
		public void setDccInetAddress(InetAddress dccInetAddress) {
			_dccInetAddress = dccInetAddress;
		}
		*/
    
	   /**
		* Returns the InetAddress used when sending DCC chat or file transfers.
		* If this is null, the default InetAddress will be used.
		* 
		* @return The current DCC InetAddress, or null if left as default.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		///@todo write this or not?
	/*
		public InetAddress getDccInetAddress() {
			return _dccInetAddress;
		}
    */
    
		/**
		* Returns the set of port numbers to be used when sending a DCC chat
		* or file transfer. This is useful when you are behind a firewall and
		* need to set up port forwarding. The array of port numbers is traversed
		* in sequence until a free port is found to listen on. A DCC tranfer will
		* fail if all ports are already in use.
		* If set to null, <i>any</i> free port number will be used. 
		* 
		* @return An array of port numbers that PircBot can use to send DCC
		*         transfers, or null if any port is allowed.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
	    ///@todo write this or not?
	    /*
		public int[] getDccPorts() {
			if (_dccPorts == null || _dccPorts.length == 0) {
				return null;
			}
			// Clone the array to prevent external modification.
			return (int[]) _dccPorts.clone();
		}
	    */
    
	   /**
		* Sets the choice of port numbers that can be used when sending a DCC chat
		* or file transfer. This is useful when you are behind a firewall and
		* need to set up port forwarding. The array of port numbers is traversed
		* in sequence until a free port is found to listen on. A DCC tranfer will
		* fail if all ports are already in use.
		* If set to null, <i>any</i> free port number will be used. 
		* 
		* @param ports The set of port numbers that PircBot may use for DCC
		*              transfers, or null to let it use any free port (default).
		*
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
	    ///@todo write this or not?
	    /*
		public void setDccPorts(int[] ports) {
			if (ports == null || ports.length == 0) {
				_dccPorts = null;
			}
			else {
				// Clone the array to prevent external modification.
				_dccPorts = (int[]) ports.clone();
			}
		}    
		*/
		
		//This method will never be written.
	    //public boolean equals(Object o)
		
		//This method will never be written.
		//public int hashCode()

		//This method will never be written.
		//public string toString()

	   /**
		* Returns an array of all users in the specified channel.
		* DO NOT try and delete this pointer yourself.  Instead 
		* to deallocate call releaseMemoryOfUserArray().  This is to
		* keep everything dll boundary safe.
		* 
		*  <p>
		* There are some important things to note about this method:-
		* <ul>
		*  <li>This method may not return a full list of users if you call it
		*      before the complete nick list has arrived from the IRC server.
		*  </li>
		*  <li>If you wish to find out which users are in a channel as soon
		*      as you join it, then you should override the onUserList method
		*      instead of calling this method, as the onUserList method is only
		*      called as soon as the full user list has been received.
		*  </li>
		*  <li>This method will return immediately, as it does not require any
		*      interaction with the IRC server.
		*  </li>
		*  <li>The bot must be in a channel to be able to know which users are
		*      in it.
		*  </li>
		* </ul>
		* 
		* @param channel The name of the channel to list.
		*
		* @param arraySize The size of the array will be returned to you.
		* 
		* @return An array of User objects. This array is NULL/0 if we are not
		*         in the channel.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		* 
		* @see #onUserList(const char * const channel, User* users, int usersArraySize) onUserList
		*/
		virtual User* getUsers(const char * const channel, 
			                   unsigned int &arraySize) const
			throw(Exception &);

	   /**
		* Returns an array of all channels that we are in.  Note that if you
		* call this method immediately after joining a new channel, the new
		* channel may not appear in this array as it is not possible to tell
		* if the join was successful until a response is received from the
		* IRC server.
		*
		* Release the memory through releaseMemoryOfCharArray.  DO NOT
		* try and release the memory yourself.  Let releaseMemoryOfCharArray
		* handle the release of the memory.
		* 
		* @param sizeOfArray The size of the array 
		*
		* @return A string array containing the names of all channels that we
		*         are in.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual const char** getChannels(int &sizeOfArray) const
			throw(Exception &);

	   /**
		* Disposes of all thread resources used by this PircBot. This may be
		* useful when writing bots or clients that use multiple servers (and
		* therefore multiple PircBot instances) or when integrating a PircBot
		* with an existing program.
		*  <p>
		* Each PircBot runs its own threads for dispatching messages from its
		* outgoing message queue and receiving messages from the server.
		* Calling dispose() ensures that these threads are
		* stopped, thus freeing up system resources.
		*  <p>
		* Once a PircBot object has been disposed, it should not be used again.
		* Attempting to use a PircBot that has been disposed may result in
		* unpredictable behaviour.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void dispose()
			throw(Exception &);
		
	private:
		//This is written in pircbot.cpp file in the pimpl
		//void addUser(string channel, const User &user)
        //User removeUser(string channel, string nick) 
		//void removeUser(string nick) 
		//void renameUser(string oldNick, string newNick) 
		//void removeChannel(string channel) 
		//void removeAllChannels() 
		//void updateUser(string channel, int userMode, string nick) 

	public:

	   /**
		* Block until all internal threads are done 
		* processing.  Call this at the bottom of your
		* main() if you want pircbot to continue 
		* processing without terminating your main.
		* 
		* You can also call this if you have a mulithreaded
		* program and you want just one thread to block 
		* with irc processing.
		* 
		* To terminate the internal threads, call the 
		* PircBot::dispose() method.  This will cause 
		* pircbot to shut down its threads for this 
		* join() to become unblocked.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		virtual void join() const
			throw(Exception &);
		

	   /**
		* Deallocates the memory of a userArray.  Call 
		* to deallocate memory of a userArray such as in 
		* the call of PircBot::getUsers().  This method 
		* ensures dll boundary safety. DO NOT try and 
		* delete the memory of userArray yourself.  Use
		* this method instead.
		* 
		* @param userArray the array you retrieved through
		* a call to PircBot::getUsers() that you wish to 
		* deallocate.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
	    */
		static void releaseMemoryOfUserArray(User *userArray)
			throw(Exception &);
		
	   /**
		* Deallocates the memory of the array that comes from 
		* PircBot::getChannels().  Call this to deallocate 
		* the memory.  This method ensures dll boundary safety.
		* DO NOT try and delete the memory of array yourself.
		* Use this method instead.
		* 
		* @param array The array you retrieved through
		* a call to PircBot::getChannels() that you wish to 
		* deallocate.
		*
		* @param size The size of the array.  If you pass in an 
		* invalid size expect your program to crash.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static void releaseMemoryOfCharArray(const char **array, const unsigned int size)
			throw(Exception &);

	   /**
		* All delete's will be handled through
		* this dll.
		*
		* This is required for dll boundary safety.
		* Instead of allowing the compiler to 
		* choose if it wants to inline this 
		* we have made it so that it cannot.
		* If we let the compiler choose to 
		* inline or not inline this and the 
		* "new operator" we can run into dll
		* boundary issues.  The issue would be
		* that the compiler would inline one 
		* and not the other.  Thus, your 
		* executable with its own heap would 
		* allocate/delete and this dll would 
		* do the other.  That's a dll boundary
		* safety violation.
		* 
        * @param p The pointer to an instance
		* of this object.
	    */
        void operator delete(void* p);

	   /**
		* All new's will be handled through
		* this dll.
		*
		* This is required for dll boundary safety.
		* Instead of allowing the compiler to 
		* choose if it wants to inline this 
		* we have made it so that it cannot.
		* If we let the compiler choose to 
		* inline or not inline this and the 
		* "delete operator" we can run into dll
		* boundary issues.  The issue would be
		* that the compiler would inline one 
		* and not the other.  Thus, your 
		* executable with its own heap would 
		* allocate/delete and this dll would 
		* do the other.  That's a dll boundary
		* safety violation.
		* 
        * @param size The size to allocate 
		* an instance of this object with.
		*
		* @return An instance of this object
		*/
		void *operator new(unsigned int size);
		
	   /**
		* Default virtual destructor.
		* It will disconnect you from the 
		* server call PircBot::dispose()
		* and delete the private 
		* implementation (pimpl)
		*/
		virtual ~PircBot();

	private: 

	   /**
		* The assignment operator.
		* For now, I am not allowing a copy to be made.  
		*
		* @param pircbot The standard second reference.
		*/
		PircBot &operator=(const PircBot &pircbot);

	   /**
		* The copy constructor.
		* For now, I am not allowing this to be invoked. 
		*
		* \param pircbot The standard second reference
		*/
		PircBot(const PircBot &pircbot);

	   /**
		* The private implementation in which
		* you cannot get access to.
		*
		* This shared_ptr holds the private methods 
		* and private member variables of this class.  This 
		* makes ABI (Application Binary Interface) more
		* resilient to change. See the private implementation
		* idiom on the internet for more information about this.
		*/
		PircBotImpl *m_pimpl;
		friend class PircBotImpl;
};


} //end of impl namespace

//expose PircBot to the pircbot namespace
using pircbot::impl::PircBot;

} //end of pircbot namespace 

#ifdef _WIN32
#    pragma warning( disable : 4290 )
#endif

#endif

