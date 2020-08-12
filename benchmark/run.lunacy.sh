#!/bin/sh

NAME=lunacy32

for a in 1 2 3 4 5 6 7 ; do 
	for b in $NAME $NAME-sipHash31 $NAME-noSipHash ; do 
		echo -----------------------  
		echo $b 
		time /lunacy/$b examine-growth.lua benchmark 
		echo ----------- 
	done 
done
