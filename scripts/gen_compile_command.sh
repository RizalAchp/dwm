#!/usr/bin/env bash

make --always-make --dry-run \
	| grep -wE 'clang|clang++|cc|c++|gcc|g++|.*gcc|.*g++' \
    | grep -w '\-c' \
    | jq -nR '[inputs|{directory:".", command:., file: match(" [^ ]+$").string[1:]}]' \
    > compile_commands.json
