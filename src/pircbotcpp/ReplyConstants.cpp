#include <pircbot/ReplyConstants.h>

//std includes
#include <string>
using namespace std;

namespace pircbot
{
namespace impl
{

// Error Replies.
int ReplyConstants::ERR_NOSUCHNICK = 401;
int ReplyConstants::ERR_NOSUCHSERVER = 402;
int ReplyConstants::ERR_NOSUCHCHANNEL = 403;
int ReplyConstants::ERR_CANNOTSENDTOCHAN = 404;
int ReplyConstants::ERR_TOOMANYCHANNELS = 405;
int ReplyConstants::ERR_WASNOSUCHNICK = 406;
int ReplyConstants::ERR_TOOMANYTARGETS = 407;
int ReplyConstants::ERR_NOORIGIN = 409;
int ReplyConstants::ERR_NORECIPIENT = 411;
int ReplyConstants::ERR_NOTEXTTOSEND = 412;
int ReplyConstants::ERR_NOTOPLEVEL = 413;
int ReplyConstants::ERR_WILDTOPLEVEL = 414;
int ReplyConstants::ERR_UNKNOWNCOMMAND = 421;
int ReplyConstants::ERR_NOMOTD = 422;
int ReplyConstants::ERR_NOADMININFO = 423;
int ReplyConstants::ERR_FILEERROR = 424;
int ReplyConstants::ERR_NONICKNAMEGIVEN = 431;
int ReplyConstants::ERR_ERRONEUSNICKNAME = 432;
int ReplyConstants::ERR_NICKNAMEINUSE = 433;
int ReplyConstants::ERR_NICKCOLLISION = 436;
int ReplyConstants::ERR_USERNOTINCHANNEL = 441;
int ReplyConstants::ERR_NOTONCHANNEL = 442;
int ReplyConstants::ERR_USERONCHANNEL = 443;
int ReplyConstants::ERR_NOLOGIN = 444;
int ReplyConstants::ERR_SUMMONDISABLED = 445;
int ReplyConstants::ERR_USERSDISABLED = 446;
int ReplyConstants::ERR_NOTREGISTERED = 451;
int ReplyConstants::ERR_NEEDMOREPARAMS = 461;
int ReplyConstants::ERR_ALREADYREGISTRED = 462;
int ReplyConstants::ERR_NOPERMFORHOST = 463;
int ReplyConstants::ERR_PASSWDMISMATCH = 464;
int ReplyConstants::ERR_YOUREBANNEDCREEP = 465;
int ReplyConstants::ERR_KEYSET = 467;
int ReplyConstants::ERR_CHANNELISFULL = 471;
int ReplyConstants::ERR_UNKNOWNMODE = 472;
int ReplyConstants::ERR_INVITEONLYCHAN = 473;
int ReplyConstants::ERR_BANNEDFROMCHAN = 474;
int ReplyConstants::ERR_BADCHANNELKEY = 475;
int ReplyConstants::ERR_NOPRIVILEGES = 481;
int ReplyConstants::ERR_CHANOPRIVSNEEDED = 482;
int ReplyConstants::ERR_CANTKILLSERVER = 483;
int ReplyConstants::ERR_NOOPERHOST = 491;
int ReplyConstants::ERR_UMODEUNKNOWNFLAG = 501;
int ReplyConstants::ERR_USERSDONTMATCH = 502;


// Command Responses.
int ReplyConstants::RPL_TRACELINK = 200;
int ReplyConstants::RPL_TRACECONNECTING = 201;
int ReplyConstants::RPL_TRACEHANDSHAKE = 202;
int ReplyConstants::RPL_TRACEUNKNOWN = 203;
int ReplyConstants::RPL_TRACEOPERATOR = 204;
int ReplyConstants::RPL_TRACEUSER = 205;
int ReplyConstants::RPL_TRACESERVER = 206;
int ReplyConstants::RPL_TRACENEWTYPE = 208;
int ReplyConstants::RPL_STATSLINKINFO = 211;
int ReplyConstants::RPL_STATSCOMMANDS = 212;
int ReplyConstants::RPL_STATSCLINE = 213;
int ReplyConstants::RPL_STATSNLINE = 214;
int ReplyConstants::RPL_STATSILINE = 215;
int ReplyConstants::RPL_STATSKLINE = 216;
int ReplyConstants::RPL_STATSYLINE = 218;
int ReplyConstants::RPL_ENDOFSTATS = 219;
int ReplyConstants::RPL_UMODEIS = 221;
int ReplyConstants::RPL_STATSLLINE = 241;
int ReplyConstants::RPL_STATSUPTIME = 242;
int ReplyConstants::RPL_STATSOLINE = 243;
int ReplyConstants::RPL_STATSHLINE = 244;
int ReplyConstants::RPL_LUSERCLIENT = 251;
int ReplyConstants::RPL_LUSEROP = 252;
int ReplyConstants::RPL_LUSERUNKNOWN = 253;
int ReplyConstants::RPL_LUSERCHANNELS = 254;
int ReplyConstants::RPL_LUSERME = 255;
int ReplyConstants::RPL_ADMINME = 256;
int ReplyConstants::RPL_ADMINLOC1 = 257;
int ReplyConstants::RPL_ADMINLOC2 = 258;
int ReplyConstants::RPL_ADMINEMAIL = 259;
int ReplyConstants::RPL_TRACELOG = 261;
int ReplyConstants::RPL_NONE = 300;
int ReplyConstants::RPL_AWAY = 301;
int ReplyConstants::RPL_USERHOST = 302;
int ReplyConstants::RPL_ISON = 303;
int ReplyConstants::RPL_UNAWAY = 305;
int ReplyConstants::RPL_NOWAWAY = 306;
int ReplyConstants::RPL_WHOISUSER = 311;
int ReplyConstants::RPL_WHOISSERVER = 312;
int ReplyConstants::RPL_WHOISOPERATOR = 313;
int ReplyConstants::RPL_WHOWASUSER = 314;
int ReplyConstants::RPL_ENDOFWHO = 315;
int ReplyConstants::RPL_WHOISIDLE = 317;
int ReplyConstants::RPL_ENDOFWHOIS = 318;
int ReplyConstants::RPL_WHOISCHANNELS = 319;
int ReplyConstants::RPL_LISTSTART = 321;
int ReplyConstants::RPL_LIST = 322;
int ReplyConstants::RPL_LISTEND = 323;
int ReplyConstants::RPL_CHANNELMODEIS = 324;
int ReplyConstants::RPL_NOTOPIC = 331;
int ReplyConstants::RPL_TOPIC = 332;
int ReplyConstants::RPL_TOPICINFO = 333;
int ReplyConstants::RPL_INVITING = 341;
int ReplyConstants::RPL_SUMMONING = 342;
int ReplyConstants::RPL_VERSION = 351;
int ReplyConstants::RPL_WHOREPLY = 352;
int ReplyConstants::RPL_NAMREPLY = 353;
int ReplyConstants::RPL_LINKS = 364;
int ReplyConstants::RPL_ENDOFLINKS = 365;
int ReplyConstants::RPL_ENDOFNAMES = 366;
int ReplyConstants::RPL_BANLIST = 367;
int ReplyConstants::RPL_ENDOFBANLIST = 368;
int ReplyConstants::RPL_ENDOFWHOWAS = 369;
int ReplyConstants::RPL_INFO = 371;
int ReplyConstants::RPL_MOTD = 372;
int ReplyConstants::RPL_ENDOFINFO = 374;
int ReplyConstants::RPL_MOTDSTART = 375;
int ReplyConstants::RPL_ENDOFMOTD = 376;
int ReplyConstants::RPL_YOUREOPER = 381;
int ReplyConstants::RPL_REHASHING = 382;
int ReplyConstants::RPL_TIME = 391;
int ReplyConstants::RPL_USERSSTART = 392;
int ReplyConstants::RPL_USERS = 393;
int ReplyConstants::RPL_ENDOFUSERS = 394;
int ReplyConstants::RPL_NOUSERS = 395;


// Reserved Numerics.
int ReplyConstants::RPL_TRACECLASS = 209;
int ReplyConstants::RPL_STATSQLINE = 217;
int ReplyConstants::RPL_SERVICEINFO = 231;
int ReplyConstants::RPL_ENDOFSERVICES = 232;
int ReplyConstants::RPL_SERVICE = 233;
int ReplyConstants::RPL_SERVLIST = 234;
int ReplyConstants::RPL_SERVLISTEND = 235;
int ReplyConstants::RPL_WHOISCHANOP = 316;
int ReplyConstants::RPL_KILLDONE = 361;
int ReplyConstants::RPL_CLOSING = 362;
int ReplyConstants::RPL_CLOSEEND = 363;
int ReplyConstants::RPL_INFOSTART = 373;
int ReplyConstants::RPL_MYPORTIS = 384;
int ReplyConstants::ERR_YOUWILLBEBANNED = 466;
int ReplyConstants::ERR_BADCHANMASK = 476;
int ReplyConstants::ERR_NOSERVICEHOST = 492;

ReplyConstants::ReplyConstants()
	throw(Exception &)
{

}

void *ReplyConstants::operator new(size_t size)
{
	return ::operator new(size);
}

void ReplyConstants::operator delete(void* p) 
{
    ::operator delete(p);
}

ReplyConstants &ReplyConstants::operator=(const ReplyConstants &replyConstants)
{ 
	//Do not use this.  It won't work
	return *this;
}

ReplyConstants::ReplyConstants(const ReplyConstants &pircbot) 
{ 
	//Do not use this.  It won't work
}

ReplyConstants::~ReplyConstants() { }





} //end of impl namespace
} //end of pircbot namespace 
