#ifndef PIRCBOT_IMPL_SOCKET_H
#define PIRCBOT_IMPL_SOCKET_H

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

//This define is for pircbot to know that
//yes I am a Windows XP machine
#ifdef _WIN32
#define _WIN32_WINNT 0x0501
#endif

//asio includes
//Disable warnings with the asio library
#ifdef _WIN32
#  pragma warning(push)	
#  pragma warning(disable:4267)
#  pragma warning(disable:4554)
#endif

#include <asio.hpp>

//Reenable warnings to their default value
#ifdef _WIN32
#  pragma warning(default: 4267)  	
#  pragma warning(default: 4554)
#endif

//Boost includes
#include <boost/thread/recursive_mutex.hpp>
#include <boost/shared_ptr.hpp>

//std includes
#include <string>
#include <iostream>

namespace pircbot
{
namespace impl
{

using asio::ip::tcp;
using namespace boost;
using namespace std;

/**
 * Wrapped up as a socket for 
 * easier java to c++ translation
 * 
 */
class Socket 
{
	public:
		
		recursive_mutex &getMutex()
		{
			return m_this;
		}

		void setHost(const string &host)
		{
			m_host = host;
		}

		void setPort(const int &port)
		{
			m_port = port;
		}

		void sendLine(const string &line)
		{
			m_outputStream << line;
			size_t count = asio::write(*m_socket, m_asioOutputStream);
		}

		string readLine()
		{
			std::string line;
			try
			{
				size_t count = asio::read_until(*m_socket, m_asioInputStream, boost::regex("\r\n"));
				std::getline(m_inputStream, line); 
			}
			catch(Exception &)
			{
				//If Exception just return an empty line
			}

			return line;
		}

		void close()
		{
			m_socket->close();
		}

		void connect()
		{
			ostringstream portString;
			portString << m_port;
			tcp::resolver::query query(m_host, portString.str());
			tcp::resolver::iterator iterator = m_resolver.resolve(query);
			m_socket->connect(*iterator);
		}


		Socket() 
			: m_resolver(m_io_service),
			  m_outputStream(&m_asioOutputStream),
		      m_inputStream(&m_asioInputStream)
		{ 
			m_socket.reset(new tcp::socket(m_io_service));
		}

	private:
		shared_ptr<tcp::socket> m_socket;
		recursive_mutex m_this;
		asio::io_service m_io_service;
		tcp::resolver m_resolver;
		int m_port;
		string m_host;
		asio::streambuf m_asioInputStream;
		asio::streambuf m_asioOutputStream;

		istream m_inputStream;
		ostream m_outputStream;
};


} //end of impl namespace
} //end of pircbot namespace 

#endif
