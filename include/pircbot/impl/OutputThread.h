#ifndef PIRCBOT_IMPL_OUTPUTTHREAD_H
#define PIRCBOT_IMPL_OUTPUTTHREAD_H

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
#include <iostream>

//boost includes
#include <boost/thread/thread.hpp>

namespace pircbot
{
namespace impl
{

using namespace std;
using namespace boost;

//Forward declerations
class PircBot;
class Queue;
class Socket;

/**
 * A Thread which is responsible for sending messages to the IRC server.
 * Messages are obtained from the outgoing message queue and sent
 * immediately if possible.  If there is a flood of messages, then to
 * avoid getting kicked from a channel, we put a small delay between
 * each one.
 */
class OutputThread
{
	public:

	   /**
		* Constructs an OutputThread for the underlying PircBot.  All messages
		* sent to the IRC server are sent by this OutputThread to avoid hammering
		* the server.  Messages are sent immediately if possible.  If there are
		* multiple messages queued, then there is a delay imposed.
		* 
		* @param bot The underlying PircBot instance.
		* @param outQueue The Queue from which we will obtain our messages.
		*/
		OutputThread(const PircBot &bot, Queue &outQueue)
			: m_bot(bot), 
			  m_outQueue(outQueue),
			  m_thread(0),
			  m_running(false)
		{ }

	   /**
		* This method starts the Thread consuming from the outgoing message
		* Queue and sending lines to the server.
		*/
		void run();

		/**
		 * Starts this thread running
		 */
		void start();		

		/**
         * A static method to write a line to a BufferedOutputStream and then pass
		 * the line to the log method of the supplied PircBot instance.
		 * 
		 * @param bot The underlying PircBot instance.
		 * @param line The line to be written. "\r\n" is appended to the end.
		 */
		 static void sendRawLine(const PircBot &bot, Socket &socket, string line);
		
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

		void dispose()
		{
			m_running = false;
		}

		~OutputThread()
		{
			dispose();
		}

	private:
		const PircBot &m_bot;
		Queue &m_outQueue;
		thread *m_thread;
		bool m_running;
};

} //end of impl namespace
} //end of pircbot namespace 


#endif

