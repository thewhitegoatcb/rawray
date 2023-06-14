# RawRay

RawRay is a Stingray engine plugin that enables the execution of external Lua scripts before the game boots, without modifying game bundle files.

## Features
* Integrates [LFS](https://github.com/lunarmodules/luafilesystem)
* `rr.msgbox(msg, title)` function to display popup messages
* `rr.raw_dofile(path)` function to execute Lua files outside of the bundle
* `rr.openlibs()` function to reload libraries (used by the overrider)
* Offers an independent logging library with `rr.log_info(msg)`, `rr.log_warning(msg)`, `rr.log_error(msg)`, and `rr.log_debug(msg)` functions

## Provided Addons
* Overrider

Allows overriding bundled compiled files with uncompiled Lua files on disk.

__Usage:__ Place the file you want to override in the overrides folder.

__Lua API changes:__ `require`, `dofile`, and `loadfile` now accept a path with a prefix of `@` or `#`, where:
  * `@` - forces loading the original file
  * `#` - forces loading the override file (even if it doesn't exist)
  * (no prefix) - checks if an override exists, executes it if found, or proceeds with the bundled version

An example of an override can be seen in [boot.lua](rawray_lua/rawray/overrides/scripts/boot_init.lua).

## Configuration
The configuration can be found in [config.lua](rawray_lua/rawray/config.lua).

## Installation
To install RawRay

1. Extract the [Installation files](https://github.com/thewhitegoatcb/rawray/releases/latest) into the game's root directory, in example of a typical installation:
```
C:/Program Files (x86)/Steam/steamapps/common/Warhammer Vermintide 2/rawray
```
2. Run `_RawRay_Plugin_Install.bat` **OR** copy `rawray/plugins/rawray.dll` into `binaries/plugins/rawray.dll` and `binaries_dx12/plugins/rawray.dll`
## Supported Games
* Warhammer: Vermintide 2 (Modded Realm only)
