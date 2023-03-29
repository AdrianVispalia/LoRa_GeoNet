#!/bin/bash

#clear


g++ -o tmp-unit-test ./unit/* ../loraPacketFormatter.* \
    ../geom.* ../wsPacketFormatter.*
./tmp-unit-test

read -p "Press enter to end the tests"

rm ./tmp-*

