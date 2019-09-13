#!/bin/bash

if [ "$#" -eq 1 ]
then
	g++ -o "$1" -pthread -std=c++11 main.cpp buffer.cpp producer.cpp thread.cpp handler.cpp data.cpp
else
	echo "Usage: ./compile.sh <executable name>"
fi
