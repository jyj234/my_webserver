#!bin/bash
cd ./build
make clean
cmake ../
make

while  [  -e "./build/http_thread" ];do 
	echo "waiting\n"
done
./build/http_thread 127.0.0.1 5000
