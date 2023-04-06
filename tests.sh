#!/usr/local/bin/bash

if [ ! -f "./uls" ]; then
    make
fi

declare -A TESTS=(
    ["desc"]="Print current directory" 
    ["cmd"]="diff <(./uls) <(ls)"
    ["desc"]="Print root directory"
    ["cmd"]="diff <(./uls /) <(ls /)"
    ["desc"]="Print long listing format(-l) - Test 1"
    ["cmd"]="diff <(./uls -l /) <(ls -l /)"
    ["desc"]="Print long listing format(-l) - Test 2" 
    ["cmd"]="diff <(./uls -l /dev/null) <(ls -l /dev/null)"
    ["desc"]="Print long listing format(-l) - Test 3" 
    ["cmd"]="diff <(./uls -l /usr/bin) <(ls -l /usr/bin)"
    ["desc"]="Print link" ["cmd"]="diff <(./uls ./src) <(ls ./src)"
)

key = 0
for i in "${!TESTS[@]}"
do
    if [[ $i == *"desc"* ]]; then
        echo "${TESTS[$i]}"
    else
        echo "Starting test $key"
        OUTPUT=$(eval "${TESTS[$i]}")

        # Проверка результата выполнения теста
        if [ "$OUTPUT" != "" ]
        then
            echo "Test failed: ${TESTS[$i]}"
            echo "$OUTPUT"
        else
            echo "Success: ${TESTS[$i]}"
        fi
        ((key++))
    fi
done