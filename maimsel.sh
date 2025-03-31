#!/bin/sh
mkdir -p /home/dil/Documents/screenshots && maim -s | tee ~/Documents/screenshots/$(date +%m-%d-%Y-%H:%M).png | xclip -selection clipboard -t image/png
