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

key=0
for i in "${!TESTS[@]}"
do
    if [[ $i == *"desc" ]]; then
        # Вывод описания теста
        echo "Starting test $key"
        echo "${TESTS[$i]}"
    else
        # Выполнение тестового сценария
        OUTPUT=$(eval "${TESTS[$i]}")

        # Проверка результата выполнения теста
        if [ "$OUTPUT" != "" ]
        then
            echo "Test failed: ${TESTS[$i-1]}"
            echo "$OUTPUT"
        else
            echo "Success: $key"
        fi
        ((key++))
    fi
done