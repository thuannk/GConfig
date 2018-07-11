@echo off
SET CFOLDER="C:\Program Files (x86)\Steam\userdata\867981618\730\local\cfg"
choice /C 12 /M "Press 1 to delete config.cfg. Press 2 to clear all cfg folder."
if errorlevel 255 goto end
if errorlevel 2 goto 2
if errorlevel 1 goto 1
if errorlevel 0 goto end
:1
echo Deleting config.cfg
del /F %CFOLDER%\config.cfg
goto end

:2
echo Clearing cfg folder
rd /S /Q %CFOLDER%
mkdir %CFOLDER%
goto end

:end
echo Done!
pause