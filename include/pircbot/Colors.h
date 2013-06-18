#ifndef PIRCBOT_COLORS_H
#define PIRCBOT_COLORS_H

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
 * The Colors class provides several static fields and methods that you may
 * find useful when writing an IRC Bot.
 *  <p>
 * This class contains constants that are useful for formatting lines
 * sent to IRC servers.  These constants allow you to apply various
 * formatting to the lines, such as colours, boldness, underlining
 * and reverse text.
 *  <p>
 * The class contains static methods to remove colours and formatting
 * from lines of IRC text.
 *  <p>
 * Here are some examples of how to use the contants from within a
 * class that inherits PircBot;
 * 
   <pre> 
         string boldMessage(Colors::getBold());
         boldMessage += "A bold hello!";
         sendMessage(channel, boldMessage.c_str());
         <b>A bold hello!</b>

         string redMessage(Colors::getRed());
         redMessage += "Red";
         redMessage += Colors::getNormal();
         redMessage += " text";
         sendMessage("#cs", redMessage.c_str());
         <i>Red text</i> (only red would be red here)
         
         string redAndBoldMessage(Colors::getBold());
         redAndBoldMessage += Colors::getRed();
         redAndBoldMessage += "Bold and Red";
         sendMessage("#cs",redAndBoldMessage.c_str());
         <i><b>Bold and Red</b></i>(This would be red as well as bold)
    </pre>
 * 
 * Please note that some IRC channels may be configured to reject any
 * messages that use colours.  Also note that older IRC clients may be
 * unable to correctly display lines that contain colours and other
 * control characters.
 *  <p>
 * Note that this class name has been spelt in the American style in
 * order to remain consistent with the rest of the API.
 *
 * @author  Frank Hassanabad,
 *          <a href="http://pircbotcpp.sourceforge.net/">http://pircbotcpp.sourceforge.net/</a>
 * @version    1.4.4.1
 */
class PIRCBOT_EXPORT Colors {

	public:

	   /**
		* Removes all previously applied color and formatting attributes.
        *
		* @return hex code string to removes all previously applied color 
		* and formatting attributes.
		*
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getNormal() 
			throw(Exception &);

	   /**
		* Bold text.
        *
		* @return hex code string for bold text.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getBold() 
			throw(Exception &);

	   /**
		* Underlined text.
        *
		* @return hex code string for underlined text.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getUnderLine() 
			throw(Exception &);

	   /**
		* Reversed text (may be rendered as italic text in some clients).
        *
		* @return hex code string for r
		* eversed text (may be rendered as italic text in some clients).
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getReverse() 
			throw(Exception &);

	   /**
		* White coloured text.
        *
		* @return hex code string for white coloured text.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getWhite() 
			throw(Exception &);
	
	   /**
		* Black coloured text.
        *
		* @return hex code string for Black coloured text.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getBlack() 
			throw(Exception &);

	   /**
		* Dark blue coloured text.
        *
		* @return hex code string for dark blue coloured text.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getDarkBlue() 
			throw(Exception &);
	
	   /**
		* Dark green coloured text.
        *
		* @return hex code string for dark green coloured text.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getDarkGreen() 
			throw(Exception &);
	
	   /**
		* Red coloured text.
        *
		* @return hex code string for red coloured text.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getRed() 
			throw(Exception &);
	
	   /**
		* Brown coloured text.
        *
		* @return hex code string for brown coloured text.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getBrown() 
			throw(Exception &);

	   /**
		* Purple coloured text.
        *
		* @return hex code string for purple coloured text.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getPurple() 
			throw(Exception &);

	   /**
		* Olive coloured text.
        *
		* @return hex code string for olive coloured text.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getOlive() 
			throw(Exception &);

	   /**
		* Yellow coloured text.
        *
		* @return hex code string for yellow coloured text.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getYellow() 
			throw(Exception &);

	   /**
		* Green coloured text.
        *
		* @return hex code string for green coloured text.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getGreen() 
			throw(Exception &);
	
	   /**
		* Teal coloured text.
        *
		* @return hex code string for teal coloured text.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getTeal() 
			throw(Exception &);

	   /**
		* Cyan coloured text.
        *
		* @return hex code string for cyan coloured text.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getCyan() 
			throw(Exception &);

	   /**
		* Blue coloured text.
        *
		* @return hex code string for blue coloured text.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getBlue() 
			throw(Exception &);

	   /**
		* Magenta coloured text.
        *
		* @return hex code string for magenta coloured text.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getMagenta() 
			throw(Exception &);

	   /**
		* Dark gray coloured text.
        *
		* @return hex code string for dark gray coloured text.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getDarkGray() 
			throw(Exception &);

	   /**
		* Light gray coloured text.
        *
		* @return hex code string for light gray coloured text.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *getLightGray() 
			throw(Exception &);

	   /**
		* Removes all colours from a line of IRC text.
		* 
		* Note that this method allocates memory and 
		* that you will have to call 
		* Colors::releaseMemoryOfCharArray() to release
		* the memory.  DO NOT try and delete this memory
		* yourself.  Instead use Colors::releaseMemoryOfCharArray()
		* release the memory.
		* 
		* @param line the input text.
		* 
		* @return the same text, but with all colours removed.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *removeColors(const char *line) 
			throw(Exception &);


	   /**
		* Remove formatting from a line of IRC text.
		* 
		* Note that this method allocates memory and 
		* that you will have to call 
		* Colors::releaseMemoryOfCharArray() to release
		* the memory.  DO NOT try and delete this memory
		* yourself.  Instead use Colors::releaseMemoryOfCharArray()
		* release the memory.
		* 
		* @param line the input text.
		* 
		* @return the same text, but without any bold, underlining, reverse, etc.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static const char *removeFormatting(const char *line)
			throw(Exception &);

	   /**
		* Deallocates the memory of the char * that comes from 
		* Colors::removeColors() or Colors::removeFormatting.  
		* Call this to deallocate the memory.  This method 
		* ensures dll boundary safety.
		* 
		* @param line The string you retrieved through
		* a call to PircBot::removeColors() or 
		* Colors::removeFormatting that you wish to 
		* deallocate.
		*
		* @param line The string you want to deallocate.
        *
		* @throws Exception Will not directly throw an exception but if an
		* underlying method throws an exception, it will be wrapped and
		* thrown as an Exception.
		*/
		static void releaseMemoryOfCharArray(const char *line)
			throw(Exception &);
		
	private:

	   /**
		* This class should not be constructed.
		*/
		Colors();
};

} //end of impl namespace 

//expose Colors to the pircbot namespace
using pircbot::impl::Colors;

} //end of pircbot namespace


#ifdef _WIN32
#    pragma warning( disable : 4290 )
#endif

#endif

