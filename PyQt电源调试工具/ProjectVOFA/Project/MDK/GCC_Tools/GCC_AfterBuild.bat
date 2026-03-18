@echo off
:: enter .bat folder
cd %~dp0
:: 批处理所在路径
set bat_path=%0
:: 传入工程生成路径
set out_dir=%1
:: 目标文件名称
set target_name=%2

:: 对hex文件进行Patch并生成patch后的.bin和.hex
call :doFilePatch
if %errorlevel% == 1 (
    echo Failed 2: Patch failed!
    goto :EOF
)

exit /b %errorlevel%

:: Function Definiations ------------------------------------------------
:: 对文件进行Patch
:doFilePatch
Patcher.exe %out_dir%\%target_name%.hex
exit /b %errorlevel%
