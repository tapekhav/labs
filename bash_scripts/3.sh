#! /bin/sh

filename=$1 # считывается имя файла
ls -lRa / | grep $filename | grep ^l > symlinks.txt # поиск символических ссылок
echo -n "total " >> symlinks.txt 
wc -l symlinks.txt | cut -c 1 >> symlinks.txt # вывод количества ссылок

com=`cat symlinks.txt` 

echo $com # вывод результата в консоль
