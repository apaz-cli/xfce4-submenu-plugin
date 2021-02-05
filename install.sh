#!/bin/sh
sudo mkdir /usr/libexec/xfce4
sudo mkdir /usr/libexec/xfce4/panel-plugins

sudo cp xfce4-submenu-plugin.desktop      /usr/share/xfce4/panel-plugins/xfce4-submenu-plugin.desktop
sudo cp a.out                             /usr/libexec/xfce4/panel-plugins/xfce4-submenu-plugin