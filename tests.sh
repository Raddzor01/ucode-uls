#!/bin/bash

make

TESTS=(
    ["desc"]="Start Basic tests"
    ["desc"]="Print current directory" ["cmd"]="diff <(./uls) <(ls)"
    ["desc"]="Print root directory" ["cmd"]="diff <(./uls /) <(ls /)"
    ["desc"]="Print long listing format(-l) - Test 1" ["cmd"]="diff <(./uls -l /) <(ls -l /)"
    ["desc"]="Print long listing format(-l) - Test 2" ["cmd"]="diff <(./uls -l /dev/null) <(ls -l /dev/null)"
    ["desc"]="Print long listing format(-l) - Test 3" ["cmd"]="diff <(./uls -l /usr/bin) <(ls -l /usr/bin)"
    ["desc"]="Print link" ["cmd"]="diff <(./uls ./src) <(ls -l ./src)"
    ["desc"]="End Basic tests"
)

for i in "${!TESTS[@]}"; do
    if [[ ${TESTS[$i]} == "desc" ]]; then
        echo "${TESTS[$i+1]}"
    elif [[ ${TESTS[$i]} == "cmd" ]]; then
        OUTPUT=$(bash -c "${TESTS[$i+1]}")
        if [[ "$OUTPUT" != "" ]]; then
            echo "Test failed: ${TESTS[$i-1]}"
            echo "$OUTPUT"
        else
            echo "Test succeeded: ${TESTS[$i-1]}"
        fi
    fi
done

# for i in "${!TESTS[@]}"
# do
#     if [[ $i == *"desc"* ]]; then
#         echo "${TESTS[$i]}"
#     else
#         if [ -n "${TESTS[$i]}" ]; then
#             OUTPUT=$(bash -c "${TESTS[$i]}")
#         else
#             OUTPUT=$(./uls -a)
#         fi

#         if [ "$OUTPUT" != "" ]
#         then
#             echo "Test failed: ${TESTS[$i-1]}"
#             echo "$OUTPUT"
#         else
#             echo "Success test ${i}"
#         fi
#     fi
# done
