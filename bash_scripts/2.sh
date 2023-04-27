#! /bin/sh

if [ $# -lt 1 ] # сравнение количества введенных аргументов с 1
then
echo $0: error: File not specified # если они не были введены,
else                               # то файл не специализирован
filename=$1 # в переменную filename записываем первый введенны аргумент
# вывод inode поданного файла
inode=`ls -i $filename | cut -d ' ' -f 1 | tr -d " "` 
# поиск файлов по inode
tmp=`ls -lRi /home/vladimir/OS | grep $inode`
fi

# вывод найденных файлов
echo $tmp
