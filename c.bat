@echo off
asm8 prg.asm
if %ERRORLEVEL% NEQ 2 goto okay
pause
:okay