
//pircbot includes
#include <pircbot/Colors.h>
#include <pircbot/impl/Exceptions.h>

//std includes
#include <string>
#include <cctype>
using namespace std;

namespace pircbot
{
namespace impl
{

const char *Colors::getBold() 
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x2);
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getNormal()
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0xf);
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getUnderLine() 
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x1f);
		s = 0x1f;
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getReverse()
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x16);
		s = 0x16;
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getWhite()
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x3) + string("00");
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getBlack()
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x3) + string("01");
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getDarkBlue()
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x3) + string("02");
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getDarkGreen()
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x3) + string("03");
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getRed()
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x3) + string("04");
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getBrown()
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x3) + string("05");	
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getPurple()
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x3) + string("06");
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getOlive()
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x3) + string("07");
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getYellow()
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x3) + string("08");
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getGreen()
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x3) + string("09");
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getTeal()
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x3) + string("10");
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getCyan()
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x3) + string("11");
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getBlue()
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x3) + string("12");
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getMagenta()
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x3) + string("13");
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getDarkGray()
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x3) + string("14");
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::getLightGray()
	throw(Exception &)
{
	try
	{
		static string s = string(1, 0x3) + string("15");
		return s.c_str();
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

Colors::Colors()
{

}

const char *Colors::removeColors(const char *line)
	throw(Exception &)
{
	try
	{
		string lineString(line);
		size_t length = lineString.length();
		string buffer;
		unsigned int i = 0;
		while (i < length) 
		{
			char ch = lineString.at(i);
			if (ch == 0x3) 
			{
				i++;
				// Skip "x" or "xy" (foreground color).
				if (i < length) 
				{
					ch = lineString.at(i);
					if (isdigit(ch)) 
					{
						i++;
						if (i < length) 
						{
							ch = lineString.at(i);
							if (isdigit(ch)) 
							{
								i++;
							}
						}
						// Now skip ",x" or ",xy" (background color).
						if (i < length) 
						{
							ch = lineString.at(i);
							if (ch == ',') 
							{
								i++;
								if (i < length) 
								{
									ch = lineString.at(i);
									if (isdigit(ch)) 
									{
										i++;
										if (i < length) {
											ch = lineString.at(i);
											if (isdigit(ch)) 
											{
												i++;
											}
										}
									}
									else 
									{
										// Keep the comma.
										i--;
									}
								}
								else 
								{
									// Keep the comma.
									i--;
								}
							}
						}
					}
				}
			}
			else if (ch == 0xf) 
			{
				i++;
			}
			else 
			{
				buffer += ch;
				i++;
			}
		}

		return strdup(buffer.c_str());
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

const char *Colors::removeFormatting(const char *line)
	throw(Exception &)
{
	try
	{
		string lineString(line);
		size_t length = lineString.length();
		string buffer;
	    
		for (unsigned int i = 0; i < length; i++) 
		{
			char ch = lineString.at(i);
			if (ch == 0xf || ch == 0x2 || ch == 0x1f || ch == 0x16) 
			{
				// Don't add this character.
			}
			else 
			{
				buffer += ch;
			}
		}

		return strdup(buffer.c_str());
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}

void Colors::releaseMemoryOfCharArray(const char *line)
	throw(Exception &)
{
	try
	{
		free((void *)line);
	}
	catch(Exception &e)
	{
		throw ExceptionImpl(e.what());
	}
}


} //end of pircbot namespace
} //end of impl namespace

