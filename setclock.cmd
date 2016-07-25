@echo off

set EnigmaQRPort=9

rem code from: http://stackoverflow.com/questions/4248220/how-can-i-retrieve-the-seconds-part-of-time-in-cmd

For /f "tokens=1-4 delims=/:." %%a in ("%TIME%") do (
    SET HH24=%%a
    SET MI=%%b
    SET SS=%%c
    SET FF=%%d
)

set EnigmaQRTime=h%HH24%;m%MI%;s%SS%;u1;x
echo %EnigmaQRTime% >> com%EnigmaQRPort%:
echo %EnigmaQRTime%
