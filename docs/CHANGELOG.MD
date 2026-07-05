## Changelog

All notable changes to this project will be documented in this file.

The format is based on Keep a Changelog  
and this project adheres to Semantic Versioning.

### [1 Brishkamal Karki] - 2026-07-05

### Added
- Folders: inital game archetecture folders setup (still incomplete)
- Initial project architecture and the makefile for the compilation of the project
- SDL3, SDL3_image, SDL3_ttf, SDL3_mixer set up for Windows and Linux  
- Build script (`commander.ps1` / `commander.sh`) with organized output and logs

### Description
Set up SDL3 + extensions and the CMake build system for easy compilation on Windows and Linux.

In linux, run the file - commander.sh<br>
To make a new build folder,
```
./commander.sh -C 
```
To run the app + recompile:<br>
Debug:
```
./commander.sh or ./commander.sh -D
```
Release:
```
./commander.sh -R
```
In windows, run the file - commander.ps1<br>
To make a new build folder,
```
./commander.ps1 -C 
```
To run the app + recompile:<br>
Debug:
```
./commander.ps1 or ./commander.ps1 -D
```
Release:
```
./commander.ps1 -R
```

### Changed
  nothing


### Fixed
  nothing