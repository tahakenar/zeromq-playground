#!/bin/bash

SUB_BIN="./build/sub_main"
PUB_BIN="./build/pub_main"

echo "Starting SUB"
$SUB_BIN &
SUB_PID=$!
sleep 1

echo "Starting PUB"
$PUB_BIN

echo "Server finished publishing. Shutting down SUB client (PID: $SUB_PID)"
kill $SUB_PID
wait $SUB_PID 2>/dev/null
