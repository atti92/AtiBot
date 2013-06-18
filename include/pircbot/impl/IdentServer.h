#ifndef PIRCBOT_IMPL_IDENTSERVER_H
#define PIRCBOT_IMPL_IDENTSERVER_H

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

//Boost includes
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>

//std includes
#include <string>


//This define is for asio to know that
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
using asio::ip::tcp;

#ifdef _WIN32
#  pragma warning(default: 4267)  	
#  pragma warning(default: 4554)
#endif


namespace pircbot
{
namespace impl
{

//Forward declerations
class PircBot;

using namespace boost;
using namespace std;

class IdentServer
{
	public:
		void run();
		IdentServer(const PircBot &bot, const string &login);

	private:
		const PircBot &m_bot;
		string m_login;
};


} //end of impl namespace
} //end of pircbot namespace 



#endif

