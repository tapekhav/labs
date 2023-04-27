#! /bin/sh

# все типы файлов
types='f c d l s b p'
# цикл по всем типам
for i in $types
do
    tmp=`find / -type $i -ls | head -1` # команда, выводящая 
    # расширенную информацию о всех типах файлов
    echo $i: # вывод типа 
    if [[ -n $tmp ]] # если строка с данными не пустая
    then
        echo "$tmp" # вывод, если строка не пустая
    else
        echo "   notfound" # вывод, если не был найден файл
    fi

done
