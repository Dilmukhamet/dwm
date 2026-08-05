#!/bin/bash

PIDFILE="/tmp/screenrecord.pid"

if [ ! -f "$PIDFILE" ]; then
  notify-send "Screen record" "No recording running"
  exit 1
fi

PID="$(cat "$PIDFILE")"

if kill -0 "$PID" 2>/dev/null; then
  kill -2 "$PID"
  wait "$PID" 2>/dev/null
  sleep 1
  rm -f "$PIDFILE"
  notify-send "Screen record" "Stopped recording"
else
  rm -f "$PIDFILE"
  notify-send "Screen record" "Recording process not found"
fi
