call vendor\bin\premake\premake5.exe vs2017
PAUSE 

REM this batch will generatte the project and if everything is alright the cmd line will close, if error, it will show the error mesg and then pause.
REM @echo off
REM call vendor\bin\premake\premake5.exe vs2017
REM IF %ERRORLEVEL% NEQ 0 (
REM   PAUSE
REM )