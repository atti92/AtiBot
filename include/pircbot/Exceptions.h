#ifndef PIRCBOT_EXCEPTIONS_H
#define PIRCBOT_EXCEPTIONS_H

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

//To get the REBECA_EXPORT macro
#include <pircbot/exports.h>

namespace pircbot
{
namespace impl 
{

/**
 * Base Exception class where all exceptions are 
 * derived from.  
 *
 * This mimicks the Standard Library's exception class.
 * The reason for it and not the standard library is 
 * because the Standard Library cannot be used in any of
 * pircbot's public interfaces.
 *
 * This constraint gives the users of pircbot the 
 * choice of their own Standard Library and not become
 * tied to a particular implementation of the Standard 
 * Library.
 * 
 * All Standard Library exceptions that occur inside of 
 * pircbot are caught and rewrapped inside of this 
 * Exception.  Therefore, no Standard Library exceptions
 * will be thrown outside of pircbot.
 */
class PIRCBOT_EXPORT Exception
{
	public:

		/**
		 * Get the message or jist of what occurred 
		 * when the exception was thrown.
		 *
		 * By default, if a sub class does not override
		 * this method and throw a custom message, this 
		 * will return "unknown exception" message.
		 *
		 * @return Will return the message or jist of
		 * what occured when the exception was thrown.
		 * 
		 * \exception Will not throw any
		 */
		virtual const char* what() const throw() 
		{ 
			return "unknown exception";
		}

		/**
		 * Default Empty virtual destructor.
		 */
		virtual ~Exception() { } 
};

/**
 * Signals that an I/O exception of some sort has occurred. This
 * class is the general class of exceptions produced by failed or
 * interrupted I/O operations.
 */
class PIRCBOT_EXPORT IOException : public Exception
{ 
	public:

		/**
		 * Default Empty virtual destructor.
		 */
		virtual ~IOException() { } 
};

/**
 * A NickAlreadyInUseException class.  This exception is
 * thrown when the PircBot attempts to join an IRC server
 * with a user name that is already in use.
 */
class PIRCBOT_EXPORT NickAlreadyInUseException : public Exception
{ 
	public:

		/**
		 * Default Empty virtual destructor.
		 */
		virtual ~NickAlreadyInUseException() { } 
};

/**
 * An IrcException class.
 */
class PIRCBOT_EXPORT IrcException : public Exception
{ 
	public:

		/**
		 * Default Empty virtual destructor.
		 */
		virtual ~IrcException() { } 
};



} //end of namespace impl

//expose the exception handlers to rebecca namespace
using pircbot::impl::Exception;
using pircbot::impl::IOException;
using pircbot::impl::NickAlreadyInUseException;
using pircbot::impl::IrcException;

} //end of namespace pircbot


#endif
