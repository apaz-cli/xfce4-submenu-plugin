#!/bin/sh

clang src/xfce4-submenu-plugin.c \
        $(pkg-config --cflags --libs gtk+-2.0) \
        $(pkg-config --cflags --libs libxfce4util-1.0) \
        $(pkg-config --cflags --libs libxfce4panel-1.0) \
        $(pkg-config --cflags --libs libxfce4panel-2.0) \
        $(pkg-config --cflags --libs libxfce4ui-1) \
        -fsanitize=address -g -Wall -Wextra \
        -Ofast -march=native \
        # -o xfce4-submenu-plugin \
        