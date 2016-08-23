@echo off

rem change the line below with the serial port number for your arduino
rem include only the numeric part of the port.
set EnigmaQRPort=9

rem code from: http://stackoverflow.com/questions/4248220/how-can-i-retrieve-the-seconds-part-of-time-in-cmd

For /f "tokens=1-4 delims=/:." %%a in ("%TIME%") do (
    SET HH24=%%a
    SET MI=%%b
    SET SS=%%c
    SET FF=%%d
)

set EnigmaQRTime=i1;r2;h%HH24%;m%MI%;s%SS%;u1;p1;x
echo %EnigmaQRTime% >> com%EnigmaQRPort%:
echo %EnigmaQRTime%