
//pircbot includes

//pircbot includes
#include <pircbot/impl/IdentServer.h>
#include <pircbot/PircBot.h>

//boost includes
#include <boost/bind.hpp>


namespace pircbot
{
namespace impl
{

IdentServer::IdentServer(const PircBot &bot, const string &login)
	: m_bot(bot),
	  m_login(login)
{
	
	thread thread(bind(&IdentServer::run, this));
}

void IdentServer::run()
{
	try
	{
		asio::io_service io_service;
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 113));
		tcp::socket socket(io_service);

		asio::socket_base::linger option(true, 60);
		///@todo once this bug is fixed uncomment the following below
		//m_socket.get_option(option);
		acceptor.accept(socket);
		
		//input stream
		asio::streambuf asioInputStream;
		istream inputStream(&asioInputStream);

		//output stream
		asio::streambuf asioOutputStream;
		ostream outputStream(&asioOutputStream);

		try
		{
			string line;
			size_t count = asio::read_until(socket, asioInputStream, boost::regex("\r\n"));
			std::getline(inputStream, line); 
			string msg("*** Ident request received: " + line);
            m_bot.log(msg.c_str());
			line = line + " : USERID : UNIX : " + m_login;
			outputStream << line;
			size_t count2 = asio::write(socket, asioOutputStream);
			msg = "*** Ident reply sent: " + line;
			m_bot.log(msg.c_str());
			socket.close();
		}
		catch(Exception &)
		{
            // We're not really concerned with what went wrong, are we?
		}
	}
	catch(Exception &)
	{
		m_bot.log("*** Could not start the ident server on port 113.");
		return;
	}



}


} //end of impl namespace
} //end of pircbot namespace 
