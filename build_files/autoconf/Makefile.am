AUTOMAKE_OPTIONS = foreign
SUBDIRS =  lib @samples@

doxygen_apidir=${datadir}/pircbotcpp/doc/api/html/
doxygen_api_samplesdir=${datadir}/pircbotcpp/doc/api+samples/html/

doxygen_api_DATA = @doxygen_api@
doxygen_api_samples_DATA = @doxygen_api_samples@

all: @doxygenate@

doxygenGen: doxygen

doxygen: ../../doc/doxygen/api/html/index.html \
         ../../doc/doxygen/api+samples/html/index.html

../../doc/doxygen/api/html/index.html:
	cd ../../doc/doxygen/ && doxygen Doxyfile_api

../../doc/doxygen/api+samples/html/index.html:
	cd ../../doc/doxygen/ && doxygen Doxyfile_api+samples

