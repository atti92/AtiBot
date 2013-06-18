
//pircbot includes
#include <pircbot/impl/OutputThread.h>
#include <pircbot/PircBot.h>
#include <pircbot/impl/Socket.h>
#include <pircbot/impl/Queue.h>

//boost includes
#include <boost/bind.hpp>
#include <boost/thread/xtime.hpp>

namespace pircbot
{
namespace impl
{

void OutputThread::run()
{
    m_running = true;
    while (m_running) 
	{
		boost::xtime xt;
		boost::xtime_get(&xt, boost::TIME_UTC);
		xt.sec += (m_bot.getMessageDelay() / 1000);
		m_thread->sleep(xt);
		string line = m_outQueue.next();
		if(line != "")
		{
			m_bot.sendRawLine(line.c_str());			
		} 
		else 
		{
			m_running = false;
		}
    }
}

void OutputThread::sendRawLine(const PircBot &bot, Socket &socket, string line)
{

	if(line.size() > bot.getMaxLineLength() - 2) 
	{
		line = line.substr(0, bot.getMaxLineLength() - 2);
	}
	
	try
	{
		socket.sendLine(line + "\r\n");	
		line = ">>>" + line;
		bot.log(line.c_str());	
	}
	catch(exception &)
	{
		// Silent response - just lose the line.
	}
}

void OutputThread::start()
{
	m_thread = new thread(bind(&OutputThread::run, this));
}


} //end of impl namespace
} //end of pircbot namespace 
