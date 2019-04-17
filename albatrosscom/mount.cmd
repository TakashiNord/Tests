
echo on

color f1

echo %HOMEDRIVE% %HOMEPATH% 
echo %ALLUSERSPROFILE%
echo %USERPROFILE%
echo %APPDATA%

rem setlocal

:set_display
if "%DISPLAY%" == "" set DISPLAY=LOCALPC:0.0

rem net use * /delete /y

set wrk="%cd%"
set dss=z:
subst %dss% %wrk%
if NOT EXIST %dss%\ ( subst %dss% %cd% )
rem if EXIST %dss%\ ( goto normal_exit )

cd %dss%\

rem echo on

rem explorer %dss%\

rem ==============================================

