#!/bin/bash

#PI_NUMBER=3.14159
file_input="output.txt" #название файла из которого берем данные
file_output="accuracy.txt" #название файла в который выводим результат

declare -A pi_sums #объявляет под именем pi_sums ассоциативный массив
declare -A pi_counts #объявляет под именем pi_counts ассоциативный массив

calculate_avg () { #тут и так все понятно, имхо
for throw in "${!pi_sums[@]}"
do
	sum=${pi_sums[$throw]}
	count=${pi_counts[$throw]}

	avg=$(bc <<< "scale=5; $sum / $count")
	echo "Number of throws: $throw, average estimate of pi: $avg" # >> "$file_output"
done | sort -r >> "$file_output" #прежде чем вывести в файл, передаем наши данные в утилиту sort
				 #с ключом -r который ответственен за сортировку в обратном порядке после чего результат выводим в файл
}

current_throws=0
while read -r line #читаем файл
do
	if [[ $line == "Number of throws:"*  ]] #и так все понятно
	then
		current_throws=$(echo $line | awk '{print $4}') #с помощью утилиты awk получаем количество бросков, которое является 4-м аргументом в строке
		pi_sums[$current_throws]=0 #все просто
		pi_count[$current_throws]=0 #все просто
	fi

	if [[ $line == "the estimate of pi number:"* ]] #все понятно
	then
		pi_val=$(echo $line | awk '{print $6}') #с помощью утилиты получаем оценку числа пи, которая является 6 аргументом в строке
		pi_sums[$current_throws]=$(bc <<< "${pi_sums[$current_throws]} + $pi_val") #все просто
		pi_counts[$current_throws]=$(( ${pi_counts[$current_throws]} + 1 )) #все просто
	fi
done < "$file_input" #считываем из файла

calculate_avg
