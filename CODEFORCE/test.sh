#!/bin/bash
if [ -f v1.cum ]; then rm v1.cum; fi
if [ -f v2.cum ]; then rm v2.cum; fi
for ((i=0; i<10; i++))
do 
echo $i
./gendata >D4.in 
./my.out <D4.in >v1.out
./watashi.out <D4.in >v2.out
cat v1.out >>v1.cum
cat v2.out >> v2.cum
if diff v1.out v2.out
then 
    echo "PASS"
else
    break
fi
done

