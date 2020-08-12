#!/bin/sh

for a in 1 2 3 4 5 6 7 ; do 
for NAME in lunacy32 lunacy64 ; do
	for b in $NAME $NAME-sipHash31 $NAME-noSipHash $NAME-halfSipHash31 ; do 
		echo -----------------------  
		echo $b 
		time /lunacy/$b examine-growth.lua benchmark 
		echo ----------- 
	done 
done
done
