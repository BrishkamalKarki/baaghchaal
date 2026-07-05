#!/usr/bin/env pwsh

# ./commander.ps1 or ./commander.ps1 -D for debug mode
# ./commander.ps1 -R for the release mode
# -C at last for the initial build file setup

#DEFAULT - DEBUG MODE
$BUILD_DIR="build_wn"
$SUB_BUILD_DIR="build_debug"
$PATH_NINJA="$PWD/tools"

if ($env:Path -notlike "*$PATH_NINJA*"){
    $env:Path += ";$PATH_NINJA"
}

if (($args.Count -ge 1 -and $args[0] -eq "-C") -or ($args.Count -ge 1 -and $args[1] -eq "-C")){
    cmake --preset "debug-windows"
    Write-Host "re-builded the bebug dude" -ForegroundColor Blue
}

if (($args.Count -ge 1 -and $args[0] -eq "-C") -or ($args.Count -ge 1 -and $args[1] -eq "-C")){
    cmake --preset "release-windows"
    Write-Host "re-builded the release dude" -ForegroundColor Blue
}


if ($args.Count -ge 1 -and $args[0] -eq "-R"){
    $SUB_BUILD_DIR="build_release"
    cmake --build "$BUILD_DIR/$SUB_BUILD_DIR"
     Write-Host "re-compiled the code dude" -ForegroundColor Yellow
    Write-Host "running in release mode in windows" -ForegroundColor Green 
    & "./build_wn/build_release/BaaghChaal.exe" 
}
else{
    cmake --build "$BUILD_DIR/$SUB_BUILD_DIR"
    Write-Host "re-compiled the code dude" -ForegroundColor Yellow
    Write-Host "running in debug mode in windows" -ForegroundColor Green
    & "./build_wn/build_debug/BaaghChaal.exe"
}