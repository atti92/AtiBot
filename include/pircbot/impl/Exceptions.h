#ifndef PIRCBOT_IMPL_EXCEPTIONS_H
#define PIRCBOT_IMPL_EXCEPTIONS_H

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
#include <pircbot/Exceptions.h>

//std includes
#include <string>

//boost includes
#include <boost/shared_ptr.hpp>

namespace pircbot 
{
namespace impl 
{
using namespace std;
using namespace boost;

class ExceptionImpl : public Exception
{
	public: 
		ExceptionImpl(const char * const msg = "Unknown exception")
			: m_msg(msg)
		{ }

		virtual const char* what() const throw()
		{
			return m_msg.c_str();
		}	

	private:
		string m_msg;		
};

class IOExceptionImpl : public IOException
{ 
	public:
		IOExceptionImpl() 
			: m_exception(new ExceptionImpl) { }

		IOExceptionImpl(const char  * const e)
			: m_exception(new ExceptionImpl(e))
		{ }

		virtual const char* what() const throw()
		{
			return m_exception->what();
		}

	private:
		shared_ptr<Exception> m_exception;
};

class NickAlreadyInUseExceptionImpl : public NickAlreadyInUseException
{ 
	public:
		NickAlreadyInUseExceptionImpl() 
			: m_exception(new ExceptionImpl) { }

		NickAlreadyInUseExceptionImpl(const char  * const e)
			: m_exception(new ExceptionImpl(e))
		{ }

		virtual const char* what() const throw()
		{
			return m_exception->what();
		}

	private:
		shared_ptr<Exception> m_exception;
};

class IrcExceptionImpl : public IrcException
{ 
	public:
		IrcExceptionImpl() 
			: m_exception(new ExceptionImpl) { }

		IrcExceptionImpl(const char  * const e)
			: m_exception(new ExceptionImpl(e))
		{ }

		virtual const char* what() const throw()
		{
			return m_exception->what();
		}

	private:
		shared_ptr<Exception> m_exception;
};



} //end of namespace impl
} //end of namespace pircbot



#endif

