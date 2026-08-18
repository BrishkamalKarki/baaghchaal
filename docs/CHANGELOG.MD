## Changelog

All notable changes to this project will be documented in this file.

The format is based on Keep a Changelog  
and this project adheres to Semantic Versioning.

---

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

---

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

--- 

### [3 Bishesh Khatri] - 2026-07-12

### Added
- Added button ui, the button now shows up and is defined under button.hpp. 
- Added cirulcar button ui, defined under circular_button.hpp. 
- Added GoogleSans-VariableFont_GRAD,opsz,wght.ttf font inside the assets folder.

### Fixed
- Intercepted SDL_EVENT_MOUSE_BUTTON_DOWN in GameSession and used SDL_RenderCoordinatesFromWindow to convert raw window coordinates into logical coordinates, fixing the button hit-box misalignment.

---

### [4 Brishkamal Karki] - 2026-07-26

### Added
- Updated the system archetecture:
  - scenes to be put in seperate folder - game_scenes
  - all the audio, fonts and textures will be in game_managers
  - board position configuration and the system configuration to be placed as a seperate folder - game_config
- Added font_manager, texture_manager, board_config, theme_config, system_config, engine, game_state, event_manager

### Description
Updated the Event managers to seperate file where the events are checked. Reconfigured the system file archetecture. Added the texture manager and updated the font manager. Partially added the board scence where a baagh can move in the board and the valid moves around a point are seen. Partially made the engine - that can now give the valid positions to move and to change the position. This has been only implemented on the baagh texture. Added the circular button such that texture can be rendered on it.

### Changed
  nothing


### Fixed
  nothing

---

### [5 Brishkamal Karki] - 2026-07-30

### Added
- Added the most of the ui part in the board scene
- Added different variants of fonts
- Added the logic part of putting the goat, moving the baagh and the goat along with eating the goat
### Description
Added the rounded rects in the board scece for the configuration info display, baagh and goat info display, timer display, turn display. U can now play it in a 2 player mode roughly.

### Changed
  nothing


### Fixed
  nothing

---


### [6 Brishkamal Karki] - 2026-08-18

### Added
- Added the prebuilt `libraries/` folder (SDL3 + support libraries) so the game builds without vcpkg or internet
- Added `CMakePresets.json` with 4 presets (debug/release for Linux and Windows)
- Added `docs/SETUP_AND_RELEASE.md` (setup, troubleshooting, slimming, GitHub release guide)
- Added Requirements and Troubleshooting sections to `README.md`

### Description
  Big cleanup round: the game now builds fully offline from one `CMakeLists.txt`,
  and the repo was slimmed down so it fits comfortably on GitHub.

### Changed
- Rewrote `CMakeLists.txt` — one file for both platforms (Windows uses the MSVC `.lib` libraries, Linux links the `.a` files with `--start-group` / `--end-group`)
- Rewrote `commander.sh` — only simple flags now (`-R` for release, `-C` to force re-configure)
- Improved `commander.ps1` — adds bundled `tools/ninja.exe` to PATH and copies the SDL3 DLLs next to the `.exe`
- Slimmed `libraries/` from 210 MB to 86 MB (kept only the libraries the game actually links)
- Slimmed `assets/` from 50 MB to 10 MB (kept only the fonts, sounds and sprites the game loads)
- Updated `.gitignore` (build folders no longer tracked)
- Deleted junk files (old `build/`, root `CMakeCache.txt`, `CMakeFiles/`, `Makefile`)
- Moved `proposal.pdf` and the game-flow image into `docs/`

### Fixed
- Fixed the pause button crash (empty timer text caused a NULL texture and a segfault)

  Note: the startup screen, the result screen (including its main menu) and the
  settings screen were not made by me — they were built by my teammates.
  Known issue: playing again after visiting the main menu still crashes the game;
  the cause is found and the fix is ready, but not applied yet.