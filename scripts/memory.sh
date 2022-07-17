#! /usr/bin/bash

MEMORY="$(free -h | awk '/^Mem:/ {print $3 "/" $2}')"
echo -e "$MEMORY RAM "
