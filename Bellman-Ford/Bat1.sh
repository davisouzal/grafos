#!/bin/bash

bf=./bf.bin

echo "Testando algoritmo de Bellman-Ford"
for i in instances/*.dat
do
	echo -e "\e[33mInstância $i\e[0m";
	$bf -f $i > temp;

	j=$(basename $i);
	diff -w temp ./sp/$j > result ;
	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m"
	else
		echo -e "\e[31mErro\e[0m";
	fi
	rm temp;

done
