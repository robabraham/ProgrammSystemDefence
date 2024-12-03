@echo off
:menu
cls
echo =============================
echo          МЕНЮ
echo =============================
echo 1. IPv4 and IPv6
echo 2. Traceroute
echo 3. IP-address of internet
echo 4. Encrypt
echo 5. Decrypt
echo 6. Execute
echo 7. Restore
echo 8. Cost
echo 9. Exit
echo =============================
set /p choice=Enter number: 

if "%choice%"=="1" goto ipv4_ipv6
if "%choice%"=="2" goto traceroute
if "%choice%"=="3" goto ip_address
if "%choice%"=="4" goto encrypt
if "%choice%"=="5" goto decrypt
if "%choice%"=="6" goto execute
if "%choice%"=="7" goto restore
if "%choice%"=="8" goto cost
if "%choice%"=="9" exit
goto menu

:ipv4_ipv6
cls
echo Adress IPv4 and IPv6:
ipconfig | findstr "IPv4 IPv6"
pause
goto menu

:traceroute
cls
set /p host=Enter host name: 
tracert %host%
pause
goto menu

:ip_address
cls
set /p host=Enter host name: 
nslookup %host%
pause
goto menu

:encrypt
cls
set /p input=Enter text or file path: 
certutil -encode %input% encrypted.txt
echo Encrypted data in encrypted.txt
pause
goto menu

:decrypt
cls
set /p input=Enter path to encrypted file: 
certutil -decode %input% decrypted.txt
echo Data decrypted at decrypted.txt
pause
goto menu

:execute
cls
set /p input=Enter file name for execute: 
start "" "%input%"
pause
goto menu

:restore
cls
echo Not implemented.
pause
goto menu

:cost
cls
set /p path=Enter path to file: 
for %%F in ("%path%") do set size=%%~zF
set /a cost=size*10
echo Size is: %size% byte
echo Cost: %cost% USD
pause
goto menu
