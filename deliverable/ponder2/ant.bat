@echo off

if exist %_ANTDIR%\bin\ant.bat goto antfound
set _ANTDIR=apache-ant-1.7.0
if exist %_ANTDIR%\bin\ant.bat goto antfound
set _ANTDIR=apache-ant-1.7.0-bin\apache-ant-1.7.0
if exist %_ANTDIR%\bin\ant.bat goto antfound

echo Extracting Ant from the binary zip file
java -jar lib\UnZip.jar -q apache-ant-1.7.0-bin.zip .
set _ANTDIR=apache-ant-1.7.0
if exist %_ANTDIR%\bin\ant.bat goto antfound

echo apache-ant-1.7.0\bin\ant.bat not found.
echo
echo Please extract apache-ant-1.7.0.zip before running this script
echo Extract it into the tutorial directory, you should be left
echo with a directory called apache-ant-1.7.0 which contains a bin directory.
echo
echo This can take a few minutes to do on Windows

goto finish

:antfound

set ANT_HOME=%CD%\%_ANTDIR%
set PATH=%ANT_HOME%\bin;%PATH%

"%ANT_HOME%\bin\ant.bat" %1 %2 %3 %4 %5 %6

:finish
