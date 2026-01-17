#!/bin/bash

REP_BIN="./build/rep_main"
REQ_BIN="./build/req_main"

echo "Starting REP"
$REP_BIN &
REP_PID=$!
sleep 1

echo "Starting REQ"
$REQ_BIN

echo "Client finished. Shutting down REP server (PID: $REP_PID)"
kill $REP_PID
wait $REP_PID 2>/dev/null
