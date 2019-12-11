#!/bin/bash

CXX="g++"

for s in src/*.cpp; do
  ${CXX} -Iinclude/ -c -o src/$(basename ${s} .cpp).o ${s}
done

for s in client server; do
  ${CXX} -o bin/${s} src/tcp-${s}.o src/udp-${s}.o src/${s}.o
done
