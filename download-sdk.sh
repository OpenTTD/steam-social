#!/bin/sh

set -e

if [ -z "${1}" ]; then
    echo "Usage: ${0} <sdk-version>"
    exit 1
fi

SDK_VERSION="${1}"

mkdir sdk
(
    cd sdk
    curl -O https://raw.githubusercontent.com/OpenTTD/steam-social/sdk/steamworks_sdk_${SDK_VERSION}.zip
    unzip -q steamworks_sdk_${SDK_VERSION}.zip
)

rm -rf src/steam
cp -R sdk/sdk/public/steam src/

rm -rf lib
cp -R sdk/sdk/redistributable_bin lib

mkdir lib/win32
mv lib/steam_api.* lib/win32/

rm -rf sdk

echo "OK - SDK downloaded."
