#!/bin/sh

echo    $(pkg-config --cflags --libs gtk+-2.0) \
        $(pkg-config --cflags --libs libxfce4panel-1.0) \
        $(pkg-config --cflags --libs libxfce4panel-2.0) \
        $(pkg-config --cflags --libs libxfce4ui-1) \
        $(pkg-config --cflags --libs libxfce4util-1.0) | sed 's/ / \n/g' | sort -u

echo "-Ofast"
echo "-march=native"
echo "-fsanitize=address"
echo "-g"