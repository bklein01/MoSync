@echo off

IF EXIST setdirs.bat GOTO STD
@echo Error: setdirs.bat missing
GOTO END
:STD

call setdirs.bat

echo Clearing directories...

REM call cleardir %TARGETDIR%\src
REM call cleardir %TARGETDIR%\classes
REM call cleardir %TARGETDIR%\tmpclasses

call cleardir build

echo Preprocessing...
@REM echo on

call process ../../shared BigPhatError 1
call process ../../shared Binary 2
call process ../../shared BinaryInterface 3
call process ../../shared Core 4
call process ../../shared LimitedLengthInputStream 5
call process ../../shared LittleEndianDataInputStream 6
call process ../../shared ThreadPool 7
call process ../../shared UBin 8
call process ../../shared RefByteArrayOutputStream 9
call process ../../shared Tilemap 10
REM call process ../../shared Tileset 11
call process ../../shared ImageCache 12
call process ../../shared MAPanicReport 13

call process src MoSync 14
call process src MoSyncView 15
call process src Syscall 16

:END
