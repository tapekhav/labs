#!/bin/bash

types='- c d l s b p' # все типы файлов
for i in $types # цикл по всем типам
do     
    echo $i # вывод некоторого типа
    file_search=`ls -lR $1 | grep ^$i | head -1` # поиск файла некоторого типа и вывод первого попавшегося
	if [[ -n $file_search ]] # если строка не пустая
	then
        cmd=`ls -lR $1 | grep ^$i | head -1 | cut -b 53-1000` 
		echo "$file_search -- `pwd`/$cmd" # вывод полного пути файла
	else
		echo "notfound" # если строка с файлом пустая
	fi
done
