
//pircbot includes
#include <pircbot/impl/Queue.h>
#include <pircbot/impl/Exceptions.h>

namespace pircbot
{
namespace impl
{

string Queue::next()
{
    // Block if the Queue is empty.
	recursive_mutex::scoped_lock synchronized(m_queueMutex);
    if (m_queue.size() == 0) 
	{
		cond.wait(synchronized);
    }
	
	if(m_queue.size() == 0)
	{
		throw ExceptionImpl("Internal error, Race hazard in Queue object.");
	}
	string s = m_queue.front();
	m_queue.pop();
	return s;
}

void Queue::add(const string &s) 
{
	recursive_mutex::scoped_lock synchronized(m_queueMutex);
	m_queue.push(s);
	cond.notify_one();
}


} //end of impl namespace
} //end of pircbot namespace 
