#ifndef PIRCBOT_USER_H
#define PIRCBOT_USER_H

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
//To get the PIRCBOT_EXPORT macro
#include <pircbot/exports.h>
#include <pircbot/Exceptions.h>

/* Disable Windows VC 7.x warning about 
 * it ignoring the throw specification
 */
#ifdef _WIN32
#    pragma warning ( push )
#    pragma warning( disable : 4290 )
#endif

namespace pircbot
{
namespace impl
{

//Forward declerations
class UserImpl;

/**
 * This class is used to represent a user on an IRC server.
 * Instances of this class are returned by the getUsers method
 * in the PircBot class.
 *
 * @author  Frank Hassanabad
 *          <a href="http://pircbotcpp.sourceforge.net/">http://pircbotcpp.sourceforge.net/</a>
 * @version    1.4.4.1
 */
class PIRCBOT_EXPORT User
{
	
	public:

	   /**
		* Constructs a User object with empty string 
		* for the prefix and the nick
		*/
		User()
			throw(Exception &);

	   /**
		* Constructs a User object with a known prefix and nick.
		*
		* @param prefix The status of the user, for example, "@".
		* @param nick The nick of the user.
		*/
		User(const char * const prefix, const char * const nick)
			throw(Exception &);

	   /**
		* Returns the prefix of the user. If the User object has been obtained
		* from a list of users in a channel, then this will reflect the user's
		* status in that channel.
		*
		* @return The prefix of the user. If there is no prefix, then an empty
		*         string is returned.
		*/
		virtual const char * const getPrefix() const
			throw(Exception &);

	   /**
		* Returns whether or not the user represented by this object is an
		* operator. If the User object has been obtained from a list of users
		* in a channel, then this will reflect the user's operator status in
		* that channel.
		* 
		* @return true if the user is an operator in the channel.
		*/
		virtual bool isOp() const
			throw(Exception &);

	   /**
		* Returns whether or not the user represented by this object has
		* voice. If the User object has been obtained from a list of users
		* in a channel, then this will reflect the user's voice status in
		* that channel.
		* 
		* @return true if the user has voice in the channel.
		*/
		virtual bool hasVoice() const
			throw(Exception &);


	   /**
		* Returns the nick of the user.
		* 
		* @return The user's nick.
		*/
	    virtual const char * const getNick() const
			throw(Exception &);

	   /**
		* Returns the nick of the user complete with their prefix if they
		* have one, e.g. "@Dave".
		* 
		* C++ note.  I cannot overload the "<<" without having to 
		* pull in C++ libraries.  And once I pull in an std, then 
		* there's no guarantee of dll boundary safety.
		* 
		* @return The user's prefix and nick.
		*/
	    virtual const char * const toString() const
			throw(Exception &);

	   /**
		* Returns true if the nick represented by this User object is the same
		* as the nick of the User object given as an argument.
		* A case insensitive comparison is made.
        *
		* @param rhs The right hand side reference
		* 
		* @return true if rhs is a User object with a matching lowercase nick.
		*/
		bool operator==(const User &rhs) const;

	   /**
		* Returns the result of calling the compareTo method on lowercased
		* nicks. This is useful for sorting lists of User objects.
		* 
		* @param rhs The right hand side reference
		*
		* @return the result of calling compareTo on lowercased nicks.
		*/
		bool operator<(const User &rhs) const;


	   /**
		* Returns the result of calling the compareTo method on lowercased
		* nicks. This is useful for sorting lists of User objects.
		* 
		* @param rhs The right hand side reference
        *
		* @return the result of calling compareTo on lowercased nicks.
		*/
		bool operator>(const User &rhs) const;

	   /**
		* Performs a deep copy of this object.
		*
		* @param rhs The right hand side reference
		*/
		User &operator=(const User &rhs);
		
	   /**
		* The copy constructor.
		* Performs a deep copy of the object.
		*
		* @param user The standard second reference
		*/
		User(const User &user);
		
	   /**
		* Default virtual destructor.
		* It will delete the private 
		* implementation (pimpl)
		*/
		virtual ~User();

	   /**
		* All delete's will be handled through
		* this dll.
		*
		* This is required for dll boundary safety.
		* Instead of allowing the compiler to 
		* choose if it wants to inline this 
		* we have made it so that it cannot.
		* If we let the compiler choose to 
		* inline or not inline this and the 
		* "new operator" we can run into dll
		* boundary issues.  The issue would be
		* that the compiler would inline one 
		* and not the other.  Thus, your 
		* executable with its own heap would 
		* allocate/delete and this dll would 
		* do the other.  That's a dll boundary
		* safety violation.
		* 
        * @param p The pointer to an instance
		* of this object.
		*/
        void operator delete(void* p);

	   /**
		* All new's will be handled through
		* this dll.
		*
		* This is required for dll boundary safety.
		* Instead of allowing the compiler to 
		* choose if it wants to inline this 
		* we have made it so that it cannot.
		* If we let the compiler choose to 
		* inline or not inline this and the 
		* "delete operator" we can run into dll
		* boundary issues.  The issue would be
		* that the compiler would inline one 
		* and not the other.  Thus, your 
		* executable with its own heap would 
		* allocate/delete and this dll would 
		* do the other.  That's a dll boundary
		* safety violation.
		* 
        * @param size The size to allocate 
		* an instance of this object with.
		*
		* @return An instance of this object
		*/
		void *operator new(unsigned int size);

	private:

       /**
		* The private implementation in which
		* you cannot get access to.
		*
		* This shared_ptr holds the private methods 
		* and private member variables of this class.  This 
		* makes ABI (Application Binary Interface) more
		* resilient to change. See the private implementation
		* idiom on the internet for more information about this.
		*/
		UserImpl *m_pimpl;
		friend class UserImpl;
};

} //end of impl namespace

//expose PircBot to the pircbot namespace
using pircbot::impl::User;

} //end of pircbot namespace 

#ifdef _WIN32
#    pragma warning( disable : 4290 )
#endif

#endif

