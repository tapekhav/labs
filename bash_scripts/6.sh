#! /bin/bash

> new.txt # создание нового регулярного файла
echo "Создан новый регулярный файл:\n" > result.txt # запись вывода в результирующий файл
od -tc new.txt >> result.txt # отслеживание состояния new.txt

echo "abc\nASDA\nzxcaaaaaaa" >> new.txt 
echo "Файл был изменён(добавлен текст):\n" >> result.txt # запись вывода в результирующий файл
od -tc new.txt >> result.txt  # отслеживание состояния new.txt

echo "abc\nASDA" > new.txt
echo "Файл был изменён(удалена часть текста):\n" >> result.txt # запись вывода в результирующий файл
od -tc new.txt >> result.txt  # отслеживание состояния new.txt
