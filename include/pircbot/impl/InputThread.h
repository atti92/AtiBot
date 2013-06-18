#ifndef PIRCBOT_IMPL_INPUTTHREAD_H
#define PIRCBOT_IMPL_INPUTTHREAD_H

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

//std includes
#include <string>

//Boost includes
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>

namespace pircbot
{
namespace impl
{

using namespace boost;
using namespace std;

//Forward declerations
class PircBot;
class Socket;

class InputThread
{
	public:
		static const unsigned int MAX_LINE_LENGTH;

		InputThread(PircBot &bot, Socket &socket)
			: m_bot(bot),
			  m_isConnected(true),
			  m_disposed(false),
			  m_socket(socket),
			  m_running(false)
		{}

  	   /**
		* Sends a raw line to the IRC server as soon as possible, bypassing the
		* outgoing message queue.
		*
		* @param line The raw line to send to the IRC server.
		*/
		void sendRawLine(const string &line);

	   /**
		* Returns true if this InputThread is connected to an IRC server.
		* The result of this method should only act as a rough guide,
		* as the result may not be valid by the time you act upon it.
		* 
		* @return True if still connected.
		*/
		bool isConnected() const {
			return m_isConnected;
		}
		
	   /**
		* Called to start this Thread reading lines from the IRC server.
		* When a line is read, this method calls the handleLine method
		* in the PircBot, which may subsequently call an 'onXxx' method
		* in the PircBot subclass.  If any subclass of Throwable (i.e.
		* any Exception or Error) is thrown by your method, then this
		* method will ignore it.  It is probable that the PircBot may still 
		* be functioning normally after such a problem, but the existance 
		* of any uncaught exceptions in your code is something you should 
		* really fix.
		*/
		void run();

		/**
		 * Closes the socket without 
		 * onDisconnect being called subsequently.
		 */
		void dispose();

		/**
		 * Starts this thread running
		 */
		void start();		

		 /**
		  * Causes whichever thread calls this 
		  * method to block until this thread
		  * is finished.
		  */
		 void join()
		 {
			if(m_thread != 0)
			{
				m_thread->join();
			}
		 }

		~InputThread()
		{
			dispose();
		}

	private:
		PircBot &m_bot;
		bool m_isConnected;
		bool m_disposed;
		shared_ptr<thread> m_thread;
		Socket &m_socket;
		bool m_running;


};


} //end of impl namespace
} //end of pircbot namespace 

#endif

