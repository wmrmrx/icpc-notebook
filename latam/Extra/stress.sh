#!/bin/bash

P=A
make ${P} brute gen || exit 1
for ((i = 1; ; i++)); do
	./gen >in
	./${P} <in >out
	./brute <in >out2
	if (! cmp -s out out2); then
		echo "--> entrada:"
		cat in
		echo "--> saida1:"
		cat out
		echo "--> saida2:"
		cat out2
		break
	fi
	echo $i
done
