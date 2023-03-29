#!/bin/bash

#clear


#g++ -o tmp-unit-test ./unit/* ../loraPacketFormatter.* \
#    ../geom.* ../wsPacketFormatter.*
#./tmp-unit-test

#read -p "Press enter to run the simpleMock"

g++ -o tmp-simpleMock ./mocks/simpleMock/* ../loraPacketFormatter.* \
    ../geom.* ../wsPacketFormatter.*
./tmp-simpleMock

rm ./tmp-*

