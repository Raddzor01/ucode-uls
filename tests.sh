#!/bin/bash

TEST1=$(diff <(./uls) <(ls))

if [ "TEST1" != ""]
then
    echo "Test 1 failed - (print current dir)"
    echo "$DIFF"
else
    echo "Success test 1"
fi
