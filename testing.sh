#!/bin/bash

echo Testing has started!
echo
for file in examples/working/*.in; do
    echo $file
    valgrind ./build/ParaCL < $file 
    echo
done

# echo
# for file in examples/*.in; do
#     echo $file
#     valgrind ./build/ParaCL < $file
#     echo
# done

# echo "Wrong code examples testing!"
# echo
# for file in examples/wrong/*.in; do
#     echo $file
#     valgrind ./build/ParaCL < $file
#     echo
# done