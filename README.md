# OpenTTD's Steam Integration Plugin

This plugin allows OpenTTD to announce what the player is doing on Steam.

## Supported OpenTTD

- OpenTTD 14+

## Supported Platforms

- Windows (32bit, 64bit)
- Linux (x86_64)
- MacOS (i386, x86_64, arm64)

## Preparation

- Lookup the latest SDK version [here](https://partner.steamgames.com/downloads/list).
- Run `./download-sdk.sh <SDK version>`.

In case you can't execute `download-sdk.sh`, you have to do some actions manually:

- Download the latest Discord Game SDK from [here](https://partner.steamgames.com/downloads/list).
- Unpack the zip-file.
- Copy the `public/steam` folder into `src/` (so there now is a `src/steam` folder with include-files).
- Copy the `redistributable_bin` folder to `lib` (so there are now folders like `linux32` in `lib/`).
- Make a folder `lib/win32`, and move `lib/steam_api.*` to `lib/win32/`.

### Side-note

https://partner.steamgames.com/downloads/ hosts the SDKs, and sometimes allows direct downloading.
But other times, it first require authentication.
This makes access the SDK from there a bit problematic, as availability is unpredictable.
In result, the SDK is also available in the branch `sdk`, and is used by the download-script / CI.

If a new SDK is released, it would need to be added to the `sdk` branch before it is available for the CI.

## Building

This is a default CMake Project.

```bash
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$(pwd)/install ..
make
```

On MacOS, you need to add `-DCMAKE_OSX_ARCHITECTURES=[arm64|x86_64|i386]` to the `cmake` line, to select which of the targets you want to build for.

## Installation

```bash
make install
```

This creates a `lib` folder in the `install` folder of your build-dir.

In your OpenTTD folder, for example in your Documents folder, there should be a `social_integration` folder (if not, start OpenTTD once to create that folder).
Copy the content of the `lib` folder into `social_integration/steam`.

Now start OpenTTD to try out the plugin.
Start OpenTTD with `-dmisc=1` to get a bit more information about what plugins it sees and how they are loading.
