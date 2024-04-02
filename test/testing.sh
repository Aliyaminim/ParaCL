#!/bin/bash

echo -e "\e[1mTesting has started!\e[0m"
echo

echo -e "\e[1mTesting well-formed paracl program\e[0m"
echo
for file in well_formed/*.in; do
    echo $filez
    ../build/ParaCL $file < well_formed/input/${file:12:-3}.inp > well_formed/output/${file:12:-3}.outp
    diff well_formed/correct/${file:12:-3}.corr well_formed/output/${file:12:-3}.outp
    if [ $? = 0 ]
    then
        echo "Correct answer"
    else
        echo "Incorrect answer"
    fi
    echo
done

for file in ./*.in; do
    echo $file
    ../build/ParaCL $file
    echo
done

echo -e "\e[1mTesting ill-formed paracl program\e[0m"
echo
for file in ill_formed/*.in; do
    echo $file
    ../build/ParaCL $file
    echo
done