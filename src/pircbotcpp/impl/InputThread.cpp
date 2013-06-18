
//pirc includes
#include <pircbot/impl/InputThread.h>
#include <pircbot/impl/OutputThread.h>
#include <pircbot/impl/Socket.h>
#include <pircbot/PircBot.h>
#include <pircbot/PircBot.h>

//boost includes
#include <boost/thread/thread.hpp>
#include "boost/date_time/local_time/local_time.hpp"
#include <boost/bind.hpp>

using namespace boost::gregorian; 
using namespace boost::local_time;
using namespace boost::posix_time;

namespace pircbot
{
namespace impl
{

const unsigned int InputThread::MAX_LINE_LENGTH = 512;

void InputThread::run()
{
    try 
	{
		m_running = true;
        while (m_running) 
		{
            try 
			{
                string line;
				while ((line = m_socket.readLine()) != "") 
				{
                    try 
					{
                        m_bot.handleLine(line.c_str());
                    }
                    catch (exception &) 
					{
                        m_bot.log("### Your implementation of PircBot is faulty and you have");
                        m_bot.log("### allowed an uncaught Exception or Error to propagate in your");
                        m_bot.log("### code. It may be possible for PircBot to continue operating");
                        m_bot.log("### ");
					}
                }
                
				if (line == "") 
				{
                    // The server must have disconnected us.
                    m_running = false;
                }
            }
            catch (exception &) 
			{
                // This will happen if we haven't received anything from the server for a while.
                // So we shall send it a ping to check that we are still connected.
				// We ping it with the local time in seconds
				posix_time_zone localTime("MST-07");
				time_zone_ptr zone(&localTime);
				local_date_time ldt = local_microsec_clock::local_time(zone);
				ptime time_t_epoch(date(1970,1,1)); 
				time_duration diff = ldt.utc_time() - time_t_epoch;
				string rawLine("PING ");
				rawLine += diff.total_seconds();
				sendRawLine("PING " + diff.total_seconds());
            }
        }
    }
    catch (exception e) 
	{
        // Do nothing.
    }
    
    // If we reach this point, then we must have disconnected.
	m_socket.close();

    if (!m_disposed) 
	{
        m_bot.log("*** Disconnected.");        
        m_isConnected = false;
		m_bot.onDisconnect();
    }
}

void InputThread::dispose()
{
	m_disposed = true;
	m_running = false;
	m_socket.close();
}

void InputThread::start()
{
	m_thread.reset(new thread(bind(&InputThread::run, this)));
}

void InputThread::sendRawLine(const string &line)
{
	OutputThread::sendRawLine(m_bot, m_socket, line);
}


} //end of impl namespace
} //end of pircbot namespace 
