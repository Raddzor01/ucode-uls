#!/bin/bash

TEST=$(diff <(./uls) <(ls))

if [ "$TEST" != ""]
then
    echo "Test 1 failed - (print current directory)"
    echo "$TEST"
else
    echo "Success test 1"
fi

TEST=$(diff <(./uls /) <(ls) /)

if [ "$TEST" != ""]
then
    echo "Test 2 failed - (print root directory)"
    echo "$TEST"
else
    echo "Success test 2"
fi