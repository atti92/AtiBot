#ifndef PIRCBOT_IMPL_QUEUE_H
#define PIRCBOT_IMPL_QUEUE_H

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
#include <queue>
#include <string>

//boost includes
#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>

namespace pircbot
{
namespace impl
{

using namespace std;
using namespace boost;

class Queue
{
	public:

    /**
     * Adds string to the end of the Queue.
     *
     * @param s The string to be added to the Queue.
     */
    void add(const string &s); 
	
		
    /**
     * Returns the string at the front of the Queue.  This
     * string is then removed from the Queue.  If the Queue
     * is empty, then this method shall block until there
     * is an string in the Queue to return.
     *
     * @return The next item from the front of the queue.
     */
	string next();

	/**
     * Returns true if the Queue is not empty.  If another
     * Thread empties the Queue before <b>next()</b> is
     * called, then the call to <b>next()</b> shall block
     * until the Queue has been populated again.
     *
     * @return True only if the Queue not empty.
     */
    bool hasNext() const {
        return (this->size() != 0);
    }

	/**
     * Clears the contents of the Queue.
     */
    void clear() 
	{
		recursive_mutex::scoped_lock synchronized(m_queueMutex);
		
		//What an inefficient way to do this.
		//queue needs a clear method
		while(!m_queue.empty())
		{
			m_queue.pop();
		}
    }

    /**
     * Returns the size of the Queue.
     *
     * @return The current size of the queue.
     */
	size_t size() const {
        return m_queue.size();
    }

	private:
		/**
		 * The internal queue
		 * representation
		 */
		queue<string> m_queue;
		
		/**
		 * Mutext for the queue
		 */
		recursive_mutex m_queueMutex;

		/**
		 * Condition to do wait()
		 * and notify() on 
		 * m_queue
		 */
		condition cond;


};

} //end of impl namespace
} //end of pircbot namespace 


#endif
