#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
UE_HOME="/Users/Shared/Epic Games/UE_5.8"
shopt -s nullglob
PLUGIN_FILES=("$SCRIPT_DIR"/*.uplugin)
shopt -u nullglob

if [ "${#PLUGIN_FILES[@]}" -eq 0 ]; then
    echo "Error: No .uplugin file found in: $SCRIPT_DIR" >&2
    exit 1
elif [ "${#PLUGIN_FILES[@]}" -gt 1 ]; then
    echo "Error: Multiple .uplugin files found in: $SCRIPT_DIR" >&2
    exit 1
fi

PLUGIN_FILE="${PLUGIN_FILES[0]}"

"$UE_HOME/Engine/Build/BatchFiles/RunUAT.sh" \
BuildPlugin \
-Plugin="$PLUGIN_FILE" \
-Package="$SCRIPT_DIR/Build" \
-Rocket || exit $?

/usr/bin/plutil -replace EnabledByDefault -bool true -r \
    "$SCRIPT_DIR/Build/${PLUGIN_FILE##*/}"