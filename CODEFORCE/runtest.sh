#!/bin/bash
# 1. the script accepts xxx.cpp
# 2. compiles: g++ -o mybin xxx.cpp
# 3. look for xxx{1,2,3,...}.in
#    run mybin and obtain my.out
# 4. it then compares my.out against xxx{1,2,3,...}.out
if [[ $# != 1 ]]
then
    echo "usage: ./runtest mycode.cpp"
    exit 1
fi
bin=mybin
g++ -o $bin $1
pre=`basename $1 .cpp`
for i in $pre*.in
do
    post=`basename $i .in`
    echo -n "## " $i $post.out
    ./$bin <$i >my.out
    if ! diff $post.out my.out>/dev/null;
    then
        echo
        echo "Testcase FAILED" $i
        echo -n "Expect:   "; cat $post.out
        echo -n "Received: "; cat my.out
        exit 1
    fi
    echo " PASSED"
done
