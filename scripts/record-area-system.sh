#!/bin/bash

mkdir -p "$HOME/Documents/screenrecords"
PIDFILE="/tmp/screenrecord.pid"

if [ -f "$PIDFILE" ] && kill -0 "$(cat "$PIDFILE")" 2>/dev/null; then
  notify-send "Screen record" "Recording already running"
  exit 1
fi

read -r X Y W H < <(slop -f "%x %y %w %h")
W=$((W / 2 * 2))
H=$((H / 2 * 2))

OUT="$HOME/Documents/screenrecords/$(date +%m-%d-%Y-%H:%M:%S)-system.mp4"

ffmpeg \
  -f x11grab \
  -video_size "${W}x${H}" \
  -framerate 30 \
  -i "$DISPLAY+$X,$Y" \
  -f pulse \
  -i "alsa_output.pci-0000_36_00.6.analog-stereo.monitor" \
  -c:v libx264 \
  -preset veryfast \
  -crf 18 \
  -c:a aac \
  -b:a 128k \
  -pix_fmt yuv420p \
  "$OUT" &

echo $! > "$PIDFILE"
notify-send "Screen record" "Started system audio recording"
