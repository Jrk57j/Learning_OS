#!/bin/bash
#shell script that can run the c programs with different variables and counts. 
count="0"
pcount="5"
while [ $count -lt 21 ]
do
   # ./a4p1 $pcount 
   # ./a4p2 $pcount
    ./a4p3 $pcount
    count=$[$count+1]
    #pcount=$[$pcount+1]
done
