#!/bin/bash

#clear


g++ -o tmp-unit-test ./unit/* ../src/loraPacketFormatter.* \
    ../src/geom.* ../src/wsPacketFormatter.*
./tmp-unit-test

read -p "Press enter to end the tests"

rm ./tmp-*

