#!/bin/bash

VENT_BIN="./build/ventilator_main"
WORKER_BIN="./build/worker_main"
SINK_BIN="./build/sink_main"

echo "Starting SINK"
$SINK_BIN &
SINK_PID=$!
sleep 1

echo "Starting 2 WORKER instances"
$WORKER_BIN &
WORKER_1_PID=$!
$WORKER_BIN &
WORKER_2_PID=$!
sleep 1

echo "Starting VENTILATOR"
$VENT_BIN

echo "Server finished publishing. Shutting down sink and workers (PIDs: $WORKER_1_PID, $WORKER_2_PID, $SINK_PID)"
kill $WORKER_1_PID $WORKER_2_PID $SINK_PID
wait $WORKER_1_PID $WORKER_2_PID $SINK_PID 2>/dev/null
