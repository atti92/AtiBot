#ifndef PIRCBOT_REPLYCONSTANTS_H
#define PIRCBOT_REPLYCONSTANTS_H

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

/**
 * This interface contains the values of all numeric replies specified
 * in section 6 of RFC 1459.  Refer to RFC 1459 for further information.
 *  <p>
 * If you override the onServerResponse method in the PircBot class,
 * you may find these constants useful when comparing the numeric
 * value of a given code.
 * 
 * @author  Frank Hassanabad,
 *          <a href="http://pircbotcpp.sourceforge.net/">http://pircbotcpp.sourceforge.net/</a>
 * @version    1.4.4.1
 */
class PIRCBOT_EXPORT ReplyConstants
{
	public:

		// Error Replies.

		/**
		 * "<nickname> :No such nick/channel"
		 * 
		 * Used to indicate the nickname parameter supplied to a
         * command is currently unused.
		 */
		static int ERR_NOSUCHNICK;

		/**
		 * "<server name> :No such server"
		 *
		 * Used to indicate the server name given currently
         * doesn't exist
		 */
		static int ERR_NOSUCHSERVER;

		/**
		 * "<channel name> :No such channel"
		 * 
		 * Used to indicate the given channel name is invalid.
		 */
		static int ERR_NOSUCHCHANNEL;

		/**
		 * "<channel name> :Cannot send to channel"
		 * 
		 * Sent to a user who is either (a) not on a channel
         * which is mode +n or (b) not a chanop (or mode +v) on
         * a channel which has mode +m set and is trying to send
         * a PRIVMSG message to that channel
		 */
		static int ERR_CANNOTSENDTOCHAN;

		/**
		 * "<channel name> :You have joined too many channels"
		 * 
		 * Sent to a user when they have joined the maximum
         * number of allowed channels and they try to join
         * another channel
		 */
		static int ERR_TOOMANYCHANNELS;

		/**
		 * "<nickname> :There was no such nickname"
		 * 
		 * Returned by WHOWAS to indicate there is no history
         * information for that nickname.
		 */
		static int ERR_WASNOSUCHNICK;

		/**
		 * "<target> :Duplicate recipients. No message delivered"
		 * 
		 * Returned to a client which is attempting to send a
         * PRIVMSG/NOTICE using the user@host destination format
         * and for a user@host which has several occurrences.
		 */
		static int ERR_TOOMANYTARGETS;

		/**
		 * ":No origin specified"
		 *
		 * PING or PONG message missing the originator parameter
         * which is required since these commands must work
         * without valid prefixes.
		 */
		static int ERR_NOORIGIN;

		/**
		 * ":No recipient given (<command>)"
		 */
		static int ERR_NORECIPIENT;

		/**
		 * ":No text to send"
		 */
		static int ERR_NOTEXTTOSEND;

		/**
		 *  "<mask> :No toplevel domain specified"
		 */
		static int ERR_NOTOPLEVEL;

		/**
		 * "<mask> :Wildcard in toplevel domain"
		 */
		static int ERR_WILDTOPLEVEL;

		/**
		 * "<command> :Unknown command"
		 *
		 * Returned to a registered client to indicate that the
         *command sent is unknown by the server.
		 */
		static int ERR_UNKNOWNCOMMAND;

		/**
		 * ":MOTD File is missing"
		 * 
		 * Server's MOTD file could not be opened by the server.
		 */
		static int ERR_NOMOTD;

		/**
		 * "<server> :No administrative info available"
		 *
		 * Returned by a server in response to an ADMIN message
         * when there is an error in finding the appropriate
         * information.
		 */
		static int ERR_NOADMININFO;

		/**
		 * ":File error doing <file op> on <file>"
		 *
		 * Generic error message used to report a failed file
         * operation during the processing of a message.
		 */
		static int ERR_FILEERROR;

		/**
		 * ":No nickname given"
		 *
		 * Returned when a nickname parameter expected for a
         * command and isn't found.
		 */
		static int ERR_NONICKNAMEGIVEN;

		/**
		 * "<nick> :Erroneus nickname"
		 * 
		 * Returned after receiving a NICK message which contains
         * characters which do not fall in the defined set.  See
         * section x.x.x for details on valid nicknames.
		 */
		static int ERR_ERRONEUSNICKNAME;

		/**
		 * "<nick> :Nickname is already in use"
		 * 
		 * Returned when a NICK message is processed that results
         * in an attempt to change to a currently existing
         * nickname.
		 */
		static int ERR_NICKNAMEINUSE;

		/**
		 * "<nick> :Nickname collision KILL"
         * Returned by a server to a client when it detects a
         * nickname collision (registered of a NICK that
         * already exists by another server).
		 */
		static int ERR_NICKCOLLISION;

		/**
		 * "<nick> <channel> :They aren't on that channel"
         * Returned by the server to indicate that the target
         * user of the command is not on the given channel.
		 */
		static int ERR_USERNOTINCHANNEL;

		/**
		 * "<channel> :You're not on that channel"
		 * 
         * Returned by the server whenever a client tries to
         * perform a channel effecting command for which the
         * client isn't a member.		 
		 */
		static int ERR_NOTONCHANNEL;

		/**
		 * "<user> <channel> :is already on channel"
		 *
         * Returned when a client tries to invite a user to a
		 * channel they are already on.		 
		 */
		static int ERR_USERONCHANNEL;

		/**
		 * "<user> :User not logged in"
		 *
		 * Returned by the summon after a SUMMON command for a
         * user was unable to be performed since they were not
         * logged in.
		 */
		static int ERR_NOLOGIN;

		/**
		 * ":SUMMON has been disabled"
		 * 
		 * Returned as a response to the SUMMON command.  Must be
         * returned by any server which does not implement it.
		 */
		static int ERR_SUMMONDISABLED;

		/**
		 * ":USERS has been disabled"
		 * 
		 * Returned as a response to the USERS command.  Must be
         * returned by any server which does not implement it.
		 */
		static int ERR_USERSDISABLED;

		/**
		 *  ":You have not registered"
		 *
		 * Returned by the server to indicate that the client
         * must be registered before the server will allow it
         * to be parsed in detail.
		 */
		static int ERR_NOTREGISTERED;

		/**
		 * "<command> :Not enough parameters"
		 *
		 * Returned by the server by numerous commands to
         * indicate to the client that it didn't supply enough
         * parameters.
		 */
		static int ERR_NEEDMOREPARAMS;

		/**
		 * ":You may not reregister"
		 *
         * Returned by the server to any link which tries to
         * change part of the registered details (such as
         * password or user details from second USER message).		 
		 */
		static int ERR_ALREADYREGISTRED;

		/**
		 * ":Your host isn't among the privileged"
		 *
         * Returned to a client which attempts to register with
         * a server which does not been setup to allow
         * connections from the host the attempted connection
         * is tried.		 
		 */
		static int ERR_NOPERMFORHOST;

		/** 
		 * ":Password incorrect"
		 *
		 * Returned to indicate a failed attempt at registering
         * a connection for which a password was required and
         * was either not given or incorrect. 
		 */
		static int ERR_PASSWDMISMATCH;

		/**
		 * ":You are banned from this server"
		 *
		 * Returned after an attempt to connect and register
         * yourself with a server which has been setup to
         * explicitly deny connections to you. 
		 */
		static int ERR_YOUREBANNEDCREEP;

		/**
		 * "<channel> :Channel key already set"
		 */
		static int ERR_KEYSET;

		/**
		 * "<channel> :Cannot join channel (+l)"
		 */
		static int ERR_CHANNELISFULL;

		/**
		 * "<char> :is unknown mode char to me"
		 */
		static int ERR_UNKNOWNMODE;

		/**
		 * "<channel> :Cannot join channel (+i)"
		 */
		static int ERR_INVITEONLYCHAN;

		/**
		 * "<channel> :Cannot join channel (+b)"
		 */
		static int ERR_BANNEDFROMCHAN;

		/**
		 * "<channel> :Cannot join channel (+k)"
		 */
		static int ERR_BADCHANNELKEY;

		/**
		 * ":Permission Denied- You're not an IRC operator"
		 * 
         * Any command requiring operator privileges to operate
         * must return this error to indicate the attempt was
         * unsuccessful.		 
		 */
		static int ERR_NOPRIVILEGES;

		/**
		 * "<channel> :You're not channel operator"
		 * Any command requiring 'chanop' privileges (such as
         * MODE messages) must return this error if the client
         * making the attempt is not a chanop on the specified
         * channel.
		 */
		static int ERR_CHANOPRIVSNEEDED;

		/**
		 * ":You cant kill a server!"
		 * 
		 * Any attempts to use the KILL command on a server
         * are to be refused and this error returned directly
         * to the client.
		 */
		static int ERR_CANTKILLSERVER;

		/**
		 * ":No O-lines for your host"
		 *
		 * If a client sends an OPER message and the server has
         * not been configured to allow connections from the
         * client's host as an operator, this error must be
         * returned.
		 */
		static int ERR_NOOPERHOST;

		/**
		 * ":Unknown MODE flag"
		 * 
		 * Returned by the server to indicate that a MODE
         * message was sent with a nickname parameter and that
         * the a mode flag sent was not recognized.
		 */
		static int ERR_UMODEUNKNOWNFLAG;

		/**
		 * ":Cant change mode for other users"
		 * 
         * Error sent to any user trying to view or change the
         * user mode for a user other than themselves.
		 */
		static int ERR_USERSDONTMATCH;
	    
	    
		// Command Responses.

		/**
		 * "Link <version & debug level> <destination> <next server>"
		 */
		static int RPL_TRACELINK;

		/**
		 * "Try. <class> <server>"
		 */
		static int RPL_TRACECONNECTING;

		/**
		 * "H.S. <class> <server>"
		 */
		static int RPL_TRACEHANDSHAKE;

		/**
		 * "???? <class> [<client IP address in dot form>]"
		 */
		static int RPL_TRACEUNKNOWN;

		/**
		 * "Oper <class> <nick>"
		 */
		static int RPL_TRACEOPERATOR;

		/**
		 * "User <class> <nick>"
		 */
		static int RPL_TRACEUSER;

		/**
		 * "Serv <class> <int>S <int>C <server> <nick!user|*!*>@<host|server>"
		 */
		static int RPL_TRACESERVER;

		/**
		 * "<newtype> 0 <client name>"
		 */
		static int RPL_TRACENEWTYPE;

		/**
		 * "<linkname> <sendq> <sent messages> <sent bytes> <received messages> <received bytes> <time open>"
		 */
		static int RPL_STATSLINKINFO;

		/**
		 * "<command> <count>"
		 */
		static int RPL_STATSCOMMANDS;

		/**
		 * "C <host> * <name> <port> <class>"  
		 */
		static int RPL_STATSCLINE;

		/**
		 * "N <host> * <name> <port> <class>"
		 */
		static int RPL_STATSNLINE;

		/**
		 * "I <host> * <host> <port> <class>"
		 */
		static int RPL_STATSILINE;

		/**
		 * "K <host> * <username> <port> <class>"
		 */
		static int RPL_STATSKLINE;

		/**
		 * "Y <class> <ping frequency> <connect frequency> <max sendq>"
		 */
		static int RPL_STATSYLINE;

		/**
		 * "<stats letter> :End of /STATS report"
		 */
		static int RPL_ENDOFSTATS;

		/**
		 * "<user mode string>"
		 *
         * To answer a query about a client's own mode,
         * RPL_UMODEIS is sent back.
		 */
		static int RPL_UMODEIS;

		/**
		 * "L <hostmask> * <servername> <maxdepth>"
		 */
		static int RPL_STATSLLINE;

		/**
		 * ":Server Up %d days %d:%02d:%02d"
		 */
		static int RPL_STATSUPTIME;

		/**
		 * "O <hostmask> * <name>"
		 */
		static int RPL_STATSOLINE;

		/**
		 * "H <hostmask> * <servername>"
		 */
		static int RPL_STATSHLINE;

		/**
		 * ":There are <integer> users and <integer> invisible on <integer> servers"
		 */
		static int RPL_LUSERCLIENT;

		/**
		 * "<integer> :operator(s) online"
		 */
		static int RPL_LUSEROP;

		/**
		 * "<integer> :unknown connection(s)"
		 */
		static int RPL_LUSERUNKNOWN;

		/**
		 * "<integer> :channels formed"
		 */
		static int RPL_LUSERCHANNELS;

		/**
		 * ":I have <integer> clients and <integer> servers"
		 *
		 * In processing an LUSERS message, the server
         * sends a set of replies from RPL_LUSERCLIENT,
         * RPL_LUSEROP, RPL_USERUNKNOWN,
         * RPL_LUSERCHANNELS and RPL_LUSERME.  When
         * replying, a server must send back
         * RPL_LUSERCLIENT and RPL_LUSERME.  The other
         * replies are only sent back if a non-zero count
         * is found for them.
		 */
		static int RPL_LUSERME;

		/**
		 * "<server> :Administrative info"
		 */
		static int RPL_ADMINME;

		/**
		 * ":<admin info>"
		 */
		static int RPL_ADMINLOC1;

		/**
		 * ":<admin info>"
		 */
		static int RPL_ADMINLOC2;

		/**
		 * ":<admin info>"
		 *
		 * When replying to an ADMIN message, a server
         * is expected to use replies RLP_ADMINME
         * through to RPL_ADMINEMAIL and provide a text
         * message with each.  For RPL_ADMINLOC1 a
         * description of what city, state and country
         * the server is in is expected, followed by
         * details of the university and department
         * (RPL_ADMINLOC2) and finally the administrative
         * contact for the server (an email address here
         * is required) in RPL_ADMINEMAIL.
		 */
		static int RPL_ADMINEMAIL;

		/**
		 * "File <logfile> <debug level>"
		 *
         * The RPL_TRACE* are all returned by the server in
         * response to the TRACE message.  How many are
         * returned is dependent on the the TRACE message and
         * whether it was sent by an operator or not.  There
         * is no predefined order for which occurs first.
         * Replies RPL_TRACEUNKNOWN, RPL_TRACECONNECTING and
         * RPL_TRACEHANDSHAKE are all used for connections
         * which have not been fully established and are either
         * unknown, still attempting to connect or in the
         * process of completing the 'server handshake'.
         * RPL_TRACELINK is sent by any server which handles
         * a TRACE message and has to pass it on to another
         * server.  The list of RPL_TRACELINKs sent in
         * response to a TRACE command traversing the IRC
         * network should reflect the actual connectivity of
         * the servers themselves along that path.
         * RPL_TRACENEWTYPE is to be used for any connection
         * which does not fit in the other categories but is
         * being displayed anyway.
		 */
		static int RPL_TRACELOG;

		/**
		 * Dummy reply number. Not used.
		 */
		static int RPL_NONE;

		/**
		 * "<nick> :<away message>"
		 */
		static int RPL_AWAY;

		/**
		 * ":[<reply>{<space><reply>}]"
		 * 
		 * Reply format used by USERHOST to list replies to
         * the query list.  The reply string is composed as
         * follows:
         *
         * <reply> ::= <nick>['*'] '=' <'+'|'-'><hostname>
         *
         * The '*' indicates whether the client has registered
         * as an Operator.  The '-' or '+' characters represent
         * whether the client has set an AWAY message or not
         * respectively.
		 */
		static int RPL_USERHOST;

		/**
		 * ":[<nick> {<space><nick>}]"
		 * 
		 * Reply format used by ISON to list replies to the
         * query list.
		 */
		static int RPL_ISON;

		/**
		 * ":You are no longer marked as being away"
		 */
		static int RPL_UNAWAY;

		/**
		 * ":You have been marked as being away"
		 *
		 * These replies are used with the AWAY command (if
         * allowed).  RPL_AWAY is sent to any client sending a
         * PRIVMSG to a client which is away.  RPL_AWAY is only
         * sent by the server to which the client is connected.
         * Replies RPL_UNAWAY and RPL_NOWAWAY are sent when the
         * client removes and sets an AWAY message.
		 */
		static int RPL_NOWAWAY;

		/**
		 * "<nick> <user> <host> * :<real name>"
		 */
		static int RPL_WHOISUSER;

		/**
		 * "<nick> <server> :<server info>"
		 */
		static int RPL_WHOISSERVER;

		/**
		 * "<nick> :is an IRC operator"
		 */
		static int RPL_WHOISOPERATOR;

		/**
		 * "<nick> <user> <host> * :<real name>"
		 */
		static int RPL_WHOWASUSER;

		/**
		 * "<name> :End of /WHO list"
		 *
		 * The RPL_WHOREPLY and RPL_ENDOFWHO pair are used
         * to answer a WHO message.  The RPL_WHOREPLY is only
         * sent if there is an appropriate match to the WHO
         * query.  If there is a list of parameters supplied
         * with a WHO message, a RPL_ENDOFWHO must be sent
         * after processing each list item with <name> being
         * the item.
		 */
		static int RPL_ENDOFWHO;

		/**
		 * "<nick> <integer> :seconds idle"
		 */
		static int RPL_WHOISIDLE;

		/**
		 * "<nick> :End of /WHOIS list"
		 */
		static int RPL_ENDOFWHOIS;

		/**
		 * "<nick> :{[@|+]<channel><space>}"
		 *
		 * Replies 311 - 313, 317 - 319 are all replies
         * generated in response to a WHOIS message.  Given that
         * there are enough parameters present, the answering
         * server must either formulate a reply out of the above
         * numerics (if the query nick is found) or return an
         * error reply.  The '*' in RPL_WHOISUSER is there as
         * the literal character and not as a wild card.  For
         * each reply set, only RPL_WHOISCHANNELS may appear
         * more than once (for long lists of channel names).
         * The '@' and '+' characters next to the channel name
         * indicate whether a client is a channel operator or
         * has been granted permission to speak on a moderated
         * channel.  The RPL_ENDOFWHOIS reply is used to mark
         * the end of processing a WHOIS message.
		 */
		static int RPL_WHOISCHANNELS;

		/**
		 * "Channel :Users  Name"
		 */
		static int RPL_LISTSTART;

		/**
		 * "<channel> <# visible> :<topic>"
		 */
		static int RPL_LIST;

		/**
		 * ":End of /LIST"
		 *
		 * Replies RPL_LISTSTART, RPL_LIST, RPL_LISTEND mark
         * the start, actual replies with data and end of the
         * server's response to a LIST command.  If there are
         * no channels available to return, only the start
         * and end reply must be sent. 
		 */
		static int RPL_LISTEND;

		/**
		 * "<channel> <mode> <mode params>"
		 */
		static int RPL_CHANNELMODEIS;

		/**
		 * "<channel> :No topic is set"
		 */
		static int RPL_NOTOPIC;

		/**
		 * "<channel> :<topic>"
		 *
		 * When sending a TOPIC message to determine the
         * channel topic, one of two replies is sent.  If
         * the topic is set, RPL_TOPIC is sent back else
         * RPL_NOTOPIC.
		 */
		static int RPL_TOPIC;

		/**
		 * See RFC For this one
		 */
		static int RPL_TOPICINFO;

		/**
		 * "<channel> <nick>"
		 *
		 * Returned by the server to indicate that the
         * attempted INVITE message was successful and is
         * being passed onto the end client.
		 */
		static int RPL_INVITING;

		/**
		 * "<user> :Summoning user to IRC"
		 *
		 * Returned by a server answering a SUMMON message to
         * indicate that it is summoning that user.
		 */
		static int RPL_SUMMONING;

		/**
		 * "<version>.<debuglevel> <server> :<comments>"
		 * 
		 * Reply by the server showing its version details.
         * The <version> is the version of the software being
         * used (including any patchlevel revisions) and the
         * <debuglevel> is used to indicate if the server is
         * running in "debug mode".
         * The "comments" field may contain any comments about
         * the version or further version details.
		 */
		static int RPL_VERSION;

		/**
		 * "<channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real name>"
		 */
		static int RPL_WHOREPLY;

		/**
		 * "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]"
		 */
		static int RPL_NAMREPLY;

		/**
		 * "<mask> <server> :<hopcount> <server info>"
		 */
		static int RPL_LINKS;

		/**
		 * "<mask> :End of /LINKS list"
		 *
		 * In replying to the LINKS message, a server must send
         * replies back using the RPL_LINKS numeric and mark the
         * end of the list using an RPL_ENDOFLINKS reply.
		 */
		static int RPL_ENDOFLINKS;

		/**
		 * "<channel> :End of /NAMES list"
         * To reply to a NAMES message, a reply pair consisting
         * of RPL_NAMREPLY and RPL_ENDOFNAMES is sent by the
         * server back to the client.  If there is no channel
         * found as in the query, then only RPL_ENDOFNAMES is
         * returned.  The exception to this is when a NAMES
         * message is sent with no parameters and all visible
         * channels and contents are sent back in a series of
         * RPL_NAMEREPLY messages with a RPL_ENDOFNAMES to mark
         * the end.
		 */
		static int RPL_ENDOFNAMES;

		/**
		 * "<channel> <banid>"
		 */
		static int RPL_BANLIST;

		/**
		 * "<channel> :End of channel ban list"
		 *
		 * When listing the active 'bans' for a given channel,
         * a server is required to send the list back using the
         * RPL_BANLIST and RPL_ENDOFBANLIST messages.  A separate
         * RPL_BANLIST is sent for each active banid.  After the
         * banids have been listed (or if none present) a
         * RPL_ENDOFBANLIST must be sent. 
		 */
		static int RPL_ENDOFBANLIST;

		/**
		 * "<nick> :End of WHOWAS"
		 *
		 * When replying to a WHOWAS message, a server must use
         * the replies RPL_WHOWASUSER, RPL_WHOISSERVER or
         * ERR_WASNOSUCHNICK for each nickname in the presented
         * list.  At the end of all reply batches, there must
         * be RPL_ENDOFWHOWAS (even if there was only one reply
         * and it was an error).
		 */
		static int RPL_ENDOFWHOWAS;

		/**
		 * ":<string>"
		 */
		static int RPL_INFO;

		/**
		 * ":- <text>"
		 */
		static int RPL_MOTD;

		/**
		 * ":End of /INFO list"
		 *
		 * A server responding to an INFO message is required to
         * send all its 'info' in a series of RPL_INFO messages
         * with a RPL_ENDOFINFO reply to indicate the end of the
         * replies.
		 */
		static int RPL_ENDOFINFO;

		/**
		 * ":- <server> Message of the day - "
		 */
		static int RPL_MOTDSTART;

		/**
		 * ":End of /MOTD command"
		 *
		 * When responding to the MOTD message and the MOTD file
         * is found, the file is displayed line by line, with
         * each line no longer than 80 characters, using
         * RPL_MOTD format replies.  These should be surrounded
         * by a RPL_MOTDSTART (before the RPL_MOTDs) and an
         * RPL_ENDOFMOTD (after).
		 */
		static int RPL_ENDOFMOTD;

		/**
		 * ":You are now an IRC operator"
		 *
		 * RPL_YOUREOPER is sent back to a client which has
         * just successfully issued an OPER message and gained
         * operator status.
		 */
		static int RPL_YOUREOPER;

		/**
		 * "<config file> :Rehashing"
		 *
		 * If the REHASH option is used and an operator sends
         * a REHASH message, an RPL_REHASHING is sent back to
         * the operator.
		 */
		static int RPL_REHASHING;

		/**
		 * "<server> :<string showing server's local time>"
		 *
		 * When replying to the TIME message, a server must send
         * the reply using the RPL_TIME format above.  The string
         * showing the time need only contain the correct day and
         * time there.  There is no further requirement for the
         * time string.
		 */
		static int RPL_TIME;

		/**
		 * ":UserID   Terminal  Host"
		 */
		static int RPL_USERSSTART;

		/**
		 * ":%-8s %-9s %-8s"
		 */
		static int RPL_USERS;

		/**
		 * ":End of users"
		 */
		static int RPL_ENDOFUSERS;

		/**
		 * ":Nobody logged in"
		 */
		static int RPL_NOUSERS;
	    
	    
		// Reserved Numerics.

		/**
		 * Reserved Numerics, see RFC for this
		 */
		static int RPL_TRACECLASS;

		/**
		 * Reserved Numerics, see RFC for this
		 */
		static int RPL_STATSQLINE;

		/**
		 * Reserved Numerics, see RFC for this
		 */
		static int RPL_SERVICEINFO;

		/**
		 * Reserved Numerics, see RFC for this
		 */
		static int RPL_ENDOFSERVICES;

		/**
		 * Reserved Numerics, see RFC for this
		 */
		static int RPL_SERVICE;

		/**
		 * Reserved Numerics, see RFC for this
		 */
		static int RPL_SERVLIST;

		/**
		 * Reserved Numerics, see RFC for this
		 */
		static int RPL_SERVLISTEND;

		/**
		 * Reserved Numerics, see RFC for this
		 */
		static int RPL_WHOISCHANOP;

		/**
		 * Reserved Numerics, see RFC for this
		 */
		static int RPL_KILLDONE;

		/**
		 * Reserved Numerics, see RFC for this
		 */
		static int RPL_CLOSING;

		/**
		 * Reserved Numerics, see RFC for this
		 */
		static int RPL_CLOSEEND;

		/**
		 * Reserved Numerics, see RFC for this
		 */
		static int RPL_INFOSTART;

		/**
		 * Reserved Numerics, see RFC for this
		 */
		static int RPL_MYPORTIS;

		/**
		 * Reserved Numerics, see RFC for this
		 */
		static int ERR_YOUWILLBEBANNED;

		/**
		 * Reserved Numerics, see RFC for this
		 */
		static int ERR_BADCHANMASK;

		/**
		 * Reserved Numerics, see RFC for this
		 */
		static int ERR_NOSERVICEHOST;

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

		/**
		 * Default virtual destructor.
		 */
		virtual ~ReplyConstants();

		/**
		 * Default constructor
		 */
		ReplyConstants()
			throw(Exception &);

	private: 

		/**
		 * The assignment operator.
		 * For now, I am not allowing a copy to be made.  
		 *
		 * @param replyConstants The standard second reference.
		 */
		ReplyConstants &operator=(const ReplyConstants &replyConstants);

		/**
		 * The copy constructor.
		 * For now, I am not allowing this to be invoked. 
		 *
		 * @param replyConstants The standard second reference
		 */
		ReplyConstants(const ReplyConstants &replyConstants);

};


} //end of impl namespace

//expose PircBot to the pircbot namespace
using pircbot::impl::ReplyConstants;

#ifdef _WIN32
#    pragma warning( disable : 4290 )
#endif

} //end of pircbot namespace 


#endif

