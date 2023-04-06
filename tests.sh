#!/usr/local/bin/bash

if [ ! -f "./uls" ]; then
    make
fi

declare -A TESTS=(
    ["test1_desc"]="Print current directory"
    ["test1_cmd"]="diff <(./uls) <(ls)"
    ["test2_desc"]="Print root directory" 
    ["test2_cmd"]="diff <(./uls /) <(ls /)"
    ["test3_desc"]="Print long listing format(-l) - Test 1" 
    ["test3_cmd"]="diff <(./uls -l /) <(ls -l /)"
    ["test4_desc"]="Print long listing format(-l) - Test 2" 
    ["test4_cmd"]="diff <(./uls -l /dev/null) <(ls -l /dev/null)"
    ["test5_desc"]="Print long listing format(-l) - Test 3" 
    ["test5_cmd"]="diff <(./uls -l /usr/bin) <(ls -l /usr/bin)"
    ["test6_desc"]="Print link" 
    ["test6_cmd"]="diff <(./uls ./src) <(ls ./src)"
)

for i in $(seq 1 ${#TESTS[@]} / 2) # итерируем от 1 до количества элементов в массиве
do
    desc_key="test${i}_desc"
    cmd_key="test${i}_cmd"

    echo "Starting test ${TESTS[$desc_key]}..."

    OUTPUT=$(eval "${TESTS[$cmd_key]}")

    if [ "$OUTPUT" != "" ]
    then
        echo "Failed:"
        echo "$OUTPUT"
    else
        echo "Success"
    fi
done