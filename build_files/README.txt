This directory has each build system capable of building pircbotcpp.

See the [doc] directory for instructions on how to build with these.

[autoconf]
The autoconf and automake scripts to build the source code 
underneath Linux.

[vs7_dll] 
The solution in here is for building pircbotcpp on Windows 
using Visual Studio 2003 (7.x).  Use this solution to just 
build the pircbotcpp dll (pircbotcpp-mt.dll)

[vs7_build_bin_dist]
This contains a batch file to automate building a pircbotcpp
distribution automatically.  Use this if you have the prerequists
of Boost and Doxygen installed, and the enviornment 
variables setup and you just want a one click build.

[vs7_dll_all]
This is what I use for building pircbotcpp dll and the samples.