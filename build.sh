#!/bin/sh
g++ -o flnotify -Os -I/opt/fltk/include -L/opt/fltk/lib \
-Wl,-rpath,/opt/fltk/lib -I/usr/X11R7/include \
-lfltk -fno-rtti -fno-exceptions flnotify.cxx \
-s -Wall -fomit-frame-pointer -Wextra -ffunction-sections \
-fdata-sections -Wl,-O1 -Wl,-gc-sections

strip -R .comment -R .gnu.version flnotify
