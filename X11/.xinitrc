#!/bin/sh

if [ -f "$HOME/.config/x11/xprofile" ]; then
	. "$HOME/.config}/x11/xprofile"
else
	. "$HOME/.xprofile"
fi

exec dwm
