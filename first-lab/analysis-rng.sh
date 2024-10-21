#!/bin/bash

RAND_MAX=32767 #уже было

generate_hundred_numbers () { #генерируем 100 чисел от 0 до 1
	for i in {1..100} 
	do
		echo $( bc <<< "scale=5; $RANDOM / $RAND_MAX" )
	done
}

calc_stats () {
	local numbers=("$@") #записываем все значения переданные в функцию в массив
	local sum=0
	local sum_sq=0
	local len=${#numbers[@]} #размер массива

	for i in "${numbers[@]}"
	do
		sum=$(bc <<< "$sum + $i")
		sum_sq=$(bc <<< "$sum_sq + $i^2")
	done	

	avg=$(bc <<< "scale=5; $sum / $len")#мат ожидание
	disp=$(bc <<< "scale=5; ($sum_sq / $len) - ($avg^2)")#дисперсия

	echo -e "Math expectation: $avg\nDispersion: $disp" >> result-analysis.txt
}


numbers=($(generate_hundred_numbers)) #генерируем 100 чисел записывая их в массив
calc_stats "${numbers[@]}" #вызываем функцию передавая туда все значения из массива 
