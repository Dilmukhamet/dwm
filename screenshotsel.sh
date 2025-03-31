#!/bin/sh
mkdir -p ~/Documents/screenshots && scrot ~/Documents/screenshots/%m-%d-%Y-%H%M%S.png --select --line mode=edge
