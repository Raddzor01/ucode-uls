#!/usr/local/bin/bash

if [ ! -f "./uls" ]; then
    make
fi

declare -A BASIC_TESTS=(
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

echo "Starting Basic tests"

for i in $(seq 1 $((${#BASIC_TESTS[@]} / 2)))
do
    desc_key="test${i}_desc"
    cmd_key="test${i}_cmd"

    echo "Starting test $i - ${BASIC_TESTS[$desc_key]}...."

    OUTPUT=$(eval "${BASIC_TESTS[$cmd_key]}")

    if [ "$OUTPUT" != "" ]
    then
        echo "Failed test $i"
        echo "Output:"
        echo "$OUTPUT"
    else
        echo "Success test $i"
    fi
done

echo "End Basic tests"
echo "Starting Creative tests"

declare -A CREATIVE_TESTS=(
    ["test1_desc"]="Print recursive(-R) - Test 1"
    ["test1_cmd"]="diff <(./uls -R) <(ls -R)"
    ["test2_desc"]="Print recursive(-R) - Test 2"
    ["test2_cmd"]="diff <(./uls -R /dev/null) <(ls -R /dev/null)"
    ["test3_desc"]="Print recursive(-R) - Test 3"
    ["test3_cmd"]="diff <(./uls -R /usr/bin) <(ls -R /usr/bin)"
    ["test4_desc"]="Print with -a flag" 
    ["test4_cmd"]="diff <(./uls -a /) <(ls -a /)"
    ["test5_desc"]="Print with -A flag" 
    ["test5_cmd"]="diff <(./uls -A /) <(ls -A /)"
    ["test6_desc"]="Print with -Ra flags" 
    ["test6_cmd"]="diff <(./uls -Ra) <(ls -Ra)"
    ["test7_desc"]="Print with -RA flags" 
    ["test7_cmd"]="diff <(./uls -RA) <(ls -RA)"
    ["test8_desc"]="Print with -G flag" 
    ["test8_cmd"]="diff <(./uls -G /) <(ls -G /)"
    ["test9_desc"]="Print with -lh flags" 
    ["test9_cmd"]="diff <(./uls -lh /) <(ls -lh /)"
    ["test10_desc"]="Print with -le flags" 
    ["test10_cmd"]="diff <(./uls -le /) <(ls -le /)"
    ["test11_desc"]="Print with -lT flags" 
    ["test11_cmd"]="diff <(./uls -lT /) <(ls -lT /)"
    ["test12_desc"]="Print with -l@ flags" 
    ["test12_cmd"]="diff <(./uls -l@ /) <(ls -l@ /)"
    ["test13_desc"]="Print with -l@ flags" 
    ["test13_cmd"]="diff <(./uls -l@ /) <(ls -l@ /)"
    ["test14_desc"]="Print with reverse sorting flag(-r)" 
    ["test14_cmd"]="diff <(./uls -r /) <(ls -r /)"
    ["test15_desc"]="Print with time sorting flag(-t)" 
    ["test15_cmd"]="diff <(./uls -t /) <(ls -t /)"
    ["test15_desc"]="Print with ctime sorting flag(-c)" 
    ["test15_cmd"]="diff <(./uls -c /) <(ls -c /)"
    ["test16_desc"]="Print with size sorting flag(-S)" 
    ["test16_cmd"]="diff <(./uls -t /) <(ls -t /)"
    ["test17_desc"]="Print with access time sorting flag(-u)" 
    ["test17_cmd"]="diff <(./uls -u /) <(ls -u /)"
    ["test17_desc"]="Print one per line(-1)" 
    ["test17_cmd"]="diff <(./uls -1 /) <(ls -1 /)"
    ["test18_desc"]="Print by columns(-C)" 
    ["test18_cmd"]="diff <(./uls -C /) <(ls -C /)"
    ["test19_desc"]="Print with file classificator(-F)" 
    ["test19_cmd"]="diff <(./uls -F /) <(ls -F /)"
    ["test20_desc"]="Print with comma separation(-m)" 
    ["test20_cmd"]="diff <(./uls -m /) <(ls -m /)"
    ["test21_desc"]="Print with dir classificator(-p)" 
    ["test21_cmd"]="diff <(./uls -p /) <(ls -p /)"
)

for i in $(seq 1 $((${#CREATIVE_TESTS[@]} / 2)))
do
    desc_key="test${i}_desc"
    cmd_key="test${i}_cmd"

    echo "Starting test $i - ${CREATIVE_TESTS[$desc_key]}...."

    OUTPUT=$(eval "${CREATIVE_TESTS[$cmd_key]}")

    if [ "$OUTPUT" != "" ]
    then
        echo "Failed test $i"
        echo "Output:"
        echo "$OUTPUT"
    else
        echo "Success test $i"
    fi
done
