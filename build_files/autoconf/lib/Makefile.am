AUTOMAKE_OPTIONS = gnu

lib_LTLIBRARIES = libpircbot-mt.la
libpircbot_mt_la_SOURCES = ../../../src/pircbotcpp/Colors.cpp \
						   ../../../src/pircbotcpp/PircBot.cpp \
						   ../../../src/pircbotcpp/ReplyConstants.cpp \
						   ../../../src/pircbotcpp/User.cpp \
						   ../../../src/pircbotcpp/impl/IdentServer.cpp \
						   ../../../src/pircbotcpp/impl/InputThread.cpp \
						   ../../../src/pircbotcpp/impl/OutputThread.cpp \
						   ../../../src/pircbotcpp/impl/Queue.cpp \
						   ../../../src/pircbotcpp/impl/Socket.cpp

libpircbot_mt_la_LDFLAGS = -version-info 0:0:0
INCLUDES=-I../../../include

# public api directory that we're going to copy all of 
# our header files from
includeapidir=${includedir}/pircbot
includeapi_DATA = ../../../include/pircbot/*.h

