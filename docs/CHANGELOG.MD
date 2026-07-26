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

### [2 Brishkamal Karki] - 2026-07-07

### Added
- Added a rounded rectangle in `rounded_rect.hpp`
- Added texture  manager in `resource_manager.hpp`

### Description
Just made a rounded rectangle that can be fully implemented for which color, size, position and shape and size needs to be given.
Also an texture manager which need a image file to be loaded.

### Changed
  - Added the things related to rounded rectangle and the texture in `ui_manager.hpp/cpp` and `ui_layer.hpp`

### Fixed
  nothing

### [2 Bishesh Khatri] - 2026-07-12

### Added
- Added button ui, the button now shows up and is defined under button.hpp. 
- Added cirulcar button ui, defined under circular_button.hpp. 
- Added GoogleSans-VariableFont_GRAD,opsz,wght.ttf font inside the assets folder.

### Fixed
- Intercepted SDL_EVENT_MOUSE_BUTTON_DOWN in GameSession and used SDL_RenderCoordinatesFromWindow to convert raw window coordinates into logical coordinates, fixing the button hit-box misalignment.

### [4 Brishkamal Karki] - 2026-07-26

### Added
- Updated the system archetecture:
  - scenes to be put in seperate folder - game_scenes
  - all the audio, fonts and textures will be in game_managers
  - board position configuration and the system configuration to be placed as a seperate folder - game_config
- Added font_manager, texture_manager, board_config, theme_config, system_config, engine, game_state, event_manager

### Description
Updated the Event managers to seperate file where the events are checked. Reconfigured the system file archetecture. Added the texture manager and updated the font manager. Partially added the board scence where a baagh can move in the board and the valid moves around a point are seen. Partially made the engine - that can now give the valid positions to move and to change the position. This has been only implemented on the baagh texture.

### Changed
  nothing


### Fixed
  nothing
