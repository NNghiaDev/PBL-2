@echo off
echo ========================================================
echo   Running Hospital Management System (HMS) - Dear ImGui
echo ========================================================
if exist "build\HMS.exe" (
    start "" "build\HMS.exe"
) else (
    echo [Error] build\HMS.exe not found! Please build the project with CMake first.
    pause
)
