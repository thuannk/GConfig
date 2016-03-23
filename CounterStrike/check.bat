echo off
echo N|comp "C:\Program Files (x86)\Steam\userdata\91736926\730\local\cfg\autoexec.cfg" autoexec.cfg 2>nul| find "OK"
echo N|comp "C:\Program Files (x86)\Steam\userdata\91736926\730\local\cfg\custom.cfg" custom.cfg 2>nul| find "OK"
echo N|comp "C:\Program Files (x86)\Steam\userdata\91736926\730\local\cfg\video.txt" video.txt 2>nul| find "OK"
pause