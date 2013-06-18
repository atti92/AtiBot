If you have the binary distribution you should see 
several files here.  If you have the source distribution 
you will see several files here if the build builds 
correctly.

[pircbotcpp-mt.dll] or [pircbotcpp-mt.so]
               
               This is the built dll or shared object in which
               all the executables above rely on.  This is the 
               pircbotcpp core engine.  When you build programs
               you link to this dll or shared object.  
			   
			   Under Linux this will be in [/usr/lib]



[pircbotcpp-mt.lib] 
               
               This is only on Windows.  Use this to link your
               applications to that are going to be using the
               pircbotcpp-mt.dll for developing applications against
               the pircbotcpp api.  See your Visual Studio 7.1
               guide on linking against libs for using dll's for
               further information.


               
[simple.exe] or [simple]

               This is built from the sample at 
               [src\samples\simple] This is a bare bones 
               simple console example.  In a few lines of code 
               it shows how to use the pircbotcpp engine 
               in your C++ code.  Run this to start up a 
               console session connected to the pircbotcpp 
			   engine.
			   
			   Under Linux this will be in 
			   [/usr/bin] 
			   
			   

[msvcr71.dll]  

               This is the Visual Studio 7.1 dll that is used
               by all executables and dlls here since they are 
               built using Visual Studio 7.1.  This only exists
               on Windows.

            