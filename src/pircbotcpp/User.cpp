
//pirc bot includes
#include <pircbot/User.h>
#include <pircbot/impl/Exceptions.h>

//std includes
#include <string>
using namespace std;

//boost includes
#include <boost/algorithm/string.hpp>
using namespace boost;

namespace pircbot
{
namespace impl
{

class UserImpl
{
	public:
		UserImpl(string prefix, string nick)
			: m_prefix(prefix), 
			  m_nick(nick), 
			  m_lowerNick(to_lower_copy(nick))
		{
			
		}
		string m_prefix;
		string m_nick;
		string m_lowerNick;
};

User::User(const char * const prefix, const char * const nick) 
	throw(Exception &)
	: m_pimpl(new UserImpl(prefix, nick))
{

}

User::User()
	throw(Exception &)
	: m_pimpl(new UserImpl("", ""))
{

}

const char * const User::getPrefix() const
	throw(Exception &)
{
	try
	{
		return m_pimpl->m_prefix.c_str();
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

bool User::isOp() const
	throw(Exception &)
{
	try
	{
		return m_pimpl->m_prefix.find_first_of('@') != string::npos;
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

bool User::hasVoice() const
	throw(Exception &)
{
	try
	{
		return m_pimpl->m_prefix.find_first_of('+') != string::npos;
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char * const User::getNick() const
	throw(Exception &)
{
	try
	{
		return m_pimpl->m_nick.c_str();
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char * const User::toString() const
	throw(Exception &)
{
	try
	{
		return string(m_pimpl->m_prefix + m_pimpl->m_nick).c_str();
	}
	catch(exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}


bool User::operator==(const User &rhs) const
{
	return this->m_pimpl->m_lowerNick == rhs.m_pimpl->m_lowerNick;
}

bool User::operator<(const User &rhs) const
{
	return this->m_pimpl->m_nick < rhs.m_pimpl->m_nick;
}
bool User::operator>(const User &rhs) const
{
	return this->m_pimpl->m_nick > rhs.m_pimpl->m_nick;

}

User &User::operator=(const User &rhs)
{
	this->m_pimpl->m_nick = rhs.m_pimpl->m_nick;
	this->m_pimpl->m_prefix = rhs.m_pimpl->m_prefix;
	this->m_pimpl->m_lowerNick = rhs.m_pimpl->m_lowerNick;
	return *this;
}

User::User(const User &user)
{
	m_pimpl = new UserImpl(user.m_pimpl->m_prefix, user.m_pimpl->m_nick);
}

User::~User()
{
	delete(m_pimpl);
}


void *User::operator new(size_t size)
{
	return ::operator new(size);
}

void User::operator delete(void* p) 
{
    ::operator delete(p);
}



} //end of impl namespace
} //end of pircbot namespace 
