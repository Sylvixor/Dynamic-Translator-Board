# README #

This README would normally document whatever steps are necessary to get your application up and running.
### ###

### Dependancies ###

Check the 2 dependancies files in the repo.


### How to compile & run ###

*Use the buildscript.sh to generate the build files from CMakelists.txt, do this after any changes to CMakeLists.txt
*Use sudo ./build_run to compile and run the program.

### How to add new sensor to software ###

In the folder main/files, the "sensorModules.json" file holds the config for all sensormodules.
Add in a new section in the json, with unique number as the key, and fill in the  settings.
*Not all settings are still used, but are still there for backwards compatibility with older software.