#!/usr/local/bin/bash

if [ ! -f "./uls" ]; then
    make
fi

TESTS=(
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

desc_index=0
cmd_index=0

for i in "${!TESTS[@]}"
do
    if [[ $i == *"desc"* ]]; then
        ((desc_index++))
        cmd_index=$((desc_index*2))

        # Вывод описания теста
        echo "Starting test $desc_index"
        echo "${TESTS[$i]}"
    else
        ((cmd_index++))

        # Выполнение тестового сценария
        OUTPUT=$(eval "${TESTS[$i]}")

        # Проверка результата выполнения теста
        if [ "$OUTPUT" != "" ]
        then
            echo "Test failed: ${TESTS[$(($cmd_index-1))]}"
            echo "$OUTPUT"
        else
            echo "Success: ${TESTS[$(($cmd_index-1))]}"
        fi
    fi

    if [ $cmd_index -eq ${#TESTS[@]} ]
    then
        break
    fi
done

# for i in $(seq 1 ${#TESTS[@]}) # итерируем от 1 до количества элементов в массиве
# do
#     desc_key="test${i}_desc"
#     cmd_key="test${i}_cmd"

#     # Вывод описания теста
#     echo "Starting test ${TESTS[$desc_key]}..."

#     # Выполнение тестового сценария
#     OUTPUT=$(eval "${TESTS[$cmd_key]}")

#     # Проверка результата выполнения теста
#     if [ "$OUTPUT" != "" ]
#     then
#         echo "Failed:"
#         echo "$OUTPUT"
#     else
#         echo "Success"
#     fi
# done