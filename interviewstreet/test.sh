for ((i=1; i<=$1; i++))
do
    python2.7 gendata.py >unlucky.in
    ./naive <unlucky.in >naive.out
    ./unlucky < unlucky.in > unlucky.out
    diff naive.out unlucky.out
done
