#!/bin/sh
g++ -o flnotify -Os -I/usr/local/include/FL -L/usr/local/lib \
-Wl,-rpath,/usr/local/lib -I/usr/local/include \
-lfltk -march=i486 -mtune=i686 -fno-rtti -fno-exceptions flnotify.cxx \
-s -Wall -fomit-frame-pointer -Wextra -ffunction-sections \
-fdata-sections -Wl,-O1 -Wl,-gc-sections

sstrip -R .comment -R .gnu.version flnotify
