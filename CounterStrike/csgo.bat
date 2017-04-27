:: Replace autoexec and video.txt
xcopy /V /Y /R autoexec.cfg "C:\Program Files (x86)\Steam\userdata\91736926\730\local\cfg\autoexec.cfg"
:: xcopy /V /Y /R video.txt "C:\Program Files (x86)\Steam\userdata\91736926\730\local\cfg\video.txt"

:: Delete old config
del /F "C:\Program Files (x86)\Steam\userdata\91736926\730\local\cfg\config.cfg"

:: Create new config with content is "exec autoexec"
echo exec autoexec > "C:\Program Files (x86)\Steam\userdata\91736926\730\local\cfg\config.cfg"

:: Check script
pause

:: Start game
start steam://rungameid/730