#!bin/bash
killall -9 http_thread
nohup ./build/http_thread >out.log 2>&1 &
