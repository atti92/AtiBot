//pircbot includes
#include <pircbot/all.h>
using namespace pircbot;

//std includes
#include <string>
#include <iostream>
using namespace std;

/**
 * Our custom bot, 
 * called HackBotcpp.
 *
 * Inherit from PircBot
 * and implement the methods
 * you need to utilize.
 */
class HackBotcpp : public PircBot
{
	public:
		
		/**
		 * Default constructor
		 * in which we set the name
		 * of our bot.
		 */
		HackBotcpp()
		{
			this->setName("AtiBot");
		}
		
		/**
		 * We override the onMessage here 
		 * so that we responde to someone 
		 * saying "time".  
		 *
		 * @param channel The channel to which the message was sent.
		 * @param sender The nick of the person who sent the message.
		 * @param login The login of the person who sent the message.
		 * @param hostname The hostname of the person who sent the message.
		 * @param message The actual message sent to the channel.
		 * 
 		 * @throws Exception Inherit from Exception and throw any type
		 * of exception you would like.
		 */
		void onMessage(const char * const channel, 
					const char * const sender, 
					const char * const login, 
					const char * const hostname, 
					const char * const message)
		   throw(Exception &)	
		{
			//The message that someone from the server said.
			string messageString(message);

			//Create a string of the sender of the message from 
			//the sender *char
			string senderString(sender);
			
			//Look to see if the message string is equal to time
			if(messageString == "time")
			{
				//Create our time string and sppend the name
				//of the person asking for the time to it.
				string time = "Time for you to get a watch";
				senderString += ": The time is now ";
				senderString += time;

				//Okay, so send to the channel our message
				sendMessage(channel, senderString.c_str()); 
			}
		}
};

/**
 * Our standard C++ main
 */
int main(int argc, char* argv[])
{
	try
	{
		//Create new instance of our custom bot
		PircBot *p = new HackBotcpp;
		
		//We want verbose messages turned on.
		p->setVerbose(true);

		//Connect to our irc server
		p->connect("irc.starsonata.com", 7777);

		//Join our channel
		p->joinChannel("#chatbot");

		//Wait until all the threads are destroyed 
		//before letting main exit.
		p->join();
	}
	catch(Exception &e)
	{
		//Error, so let's print it and exit 1
		cout << e.what() << endl;
		return 1;
	}

	//No errors, so we return with 0
	return 0;
}

