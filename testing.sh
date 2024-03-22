#!/bin/bash

echo -e "\e[1mTesting has started!\e[0m"
echo

echo -e "\e[1mTesting well-formed paracl program\e[0m"
echo
for file in examples/*.in; do
    echo $file
    valgrind ./build/ParaCL < $file
    echo
done


echo -e "\e[1mTesting ill-formed paracl program\e[0m"
echo
for file in examples/wrong/*.in; do
echo $file
    ./build/ParaCL < $file
    echo
done