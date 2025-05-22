@echo off
  echo %1

  if not exist "%1" (
      echo "include not exit...building"
      mkdir "%1"
  ) else (
      echo "include exited"
  )

  git rev-parse HEAD > "%1\external.h"
  set /p versionnumber=< "%1\external.h"
  echo #ifndef VERSION_H > "%1\external.h"  
  echo #define VERSION_H >> "%1\external.h"
  echo. >> "%1\external.h"
  rem set versionnumber=<git rev-parse HEAD
  echo #define VERSION_NUMBER "%versionnumber%" >> "%1\external.h"
  echo. >> "%1\external.h"
  echo #endif // VERSION_H >> "%1\external.h"