# ИДЗ 3 Лазарев Василий Юрьевич Вариант 37

## Условие задачи
```
Задача о сельской библиотеке. В библиотеке имеется N книг, Каждая изкниг в Ki экземплярах. M читателей 
регулярно заглядывают в библиотеку, выбирая для чтения от одной до трех книг и читая их некоторое количество 
дней. Если желаемой книги нет, то читатель, взяв существующие, дожидается от библиотекаря информации об ее 
появлении и приходит в библиотеку, чтобы специально забрать ее. Возможна ситуация, когда несколько читателей
конкурируют из-за этой популярной книги. Создать многопоточное приложение, моделирующее заданный процесс.
```
Планируемая оценка: ~8

## Решение:
## Описание используемой модели параллельных вычислений
Программа написана по модели итеративного параллелизма, эта модель здесь кажется наиболее подходящей. Потоки представляют собой функции, имеющие внутри себя циклы, сами функции должны взаимодействовать друг с другом - описание работы программы абсолютно совпадает с описанием этой модели.

Входные данные есть возможность ввести с помощью:
```
1)Консоли
2)Файл input.txt
3)Аргументы командной строки
4)Рандомное заполнение
```
[input.txt](https://github.com/Lapo4kaKek/CSA_IHW4/blob/main/input.txt) - файл для ввода данных
Формат:
```
{count book}
title1
title2
...
titleN
{count user}
name1
name2
...
```
Название книги вводится без пробелов.

Пример ввода:
```
5
ПортретДорианаГрея 2
Библия 3
Матан 5
БогатыйПапа 1
Удушье 2
3
Артем
Полина
Алексей
```

Критерии на оценку 5:

В программу добавлены поясняющие комментарии
## Сценарий поведения
Сразу после заполнения библиотеки книгами, а также создания людей, библиотека начинает работу. В нее приходят люди и пытаются взять какую-то книгу (в нашем ту что пришла в голову, то есть случайную). Если книга в наличии - человек ее берет, если нет - добавляем в "лист ожидания" эту книги и спустя какое-то время этот человек попробует еще раз заполучить книгу. 

Критерии на оценку 6:
Реализован ввод данных из командной строки (в начале это тоже указано)
## Алгоритм
Алгоритм полностью идентичен описанному выше сценарию поведения, однако в роли людей выступают потоки (1 чел = 1 поток), библиотекой является map с ключом названием книги, а значение - количество экземпляров.

Программа компилируется и запускается на Macos, Windows, Linux. На Linux можно скомпилировать например так:
```
g++ prog.cpp -o prog -fsanitize=thread -lpthread
g++ -Wall -o main main.cpp
```
![](https://github.com/Lapo4kaKek/CSA_IHW4/blob/main/staic/compil.jpeg)

## Ввод из командной строки на macos из Clion: (для начала нужно перейти в Edit Configurations)
![](https://github.com/Lapo4kaKek/CSA_IHW4/blob/main/staic/programArg.png)

Ввод из командной строки на Linux:
![](https://github.com/Lapo4kaKek/CSA_IHW4/blob/main/staic/third.jpeg)
Делается командой:
```
./main "сюда подаем данные"
```
Формат в командной строке аналогичен формату ввода в файл (через пробел, количество книг -> книги -> количество людей -> люди)

Критерии на оценку 7:

В программу добавлены ввод данных из файла и вывод результатов
в файл
Ввод данных из командной строки расширен с учетом введенных
изменений. Можно задать в командной строке первым параметром "file" и тогда будет выполнено чтение из файла [input.txt](https://github.com/Lapo4kaKek/CSA_IHW4/blob/main/input.txt)

Ввод с помощью файла на macos:
![](https://github.com/Lapo4kaKek/CSA_IHW4/blob/main/staic/inputFile.png)

Проверка вывода (запустил уже с другими данными)
![](https://github.com/Lapo4kaKek/CSA_IHW4/blob/main/staic/output.png)


Ввод с помощью файла и вывод на linux:
![](https://github.com/Lapo4kaKek/CSA_IHW4/blob/main/staic/first.jpeg)

В [input](https://github.com/Lapo4kaKek/CSA_IHW4/tree/main/input) лежат дополнительные варианты ввода, в [output](https://github.com/Lapo4kaKek/CSA_IHW4/tree/main/output) соответсвующие выводы.


Критерии на оценку 8:

В программу добавлена генерация случайных данных в допустимых диапазонах.
Генерация рандомных названий книг и рандомных имен осуществляется с помощью текущего количества секунд. При использование rand() значения будут повторяться, так как это лишь "псевдослучайная" генерация.

![](https://github.com/Lapo4kaKek/CSA_IHW4/blob/main/staic/randomTrue.png)

#Запуск с рандомными параметрами:
![](https://github.com/Lapo4kaKek/CSA_IHW4/blob/main/staic/randomIn.png)

Внутри library лежат действительно случаные значения:
![](https://github.com/Lapo4kaKek/CSA_IHW4/blob/main/staic/randomLibrary.png)

Пользователи тоже снегерировались случайно:
![](https://github.com/Lapo4kaKek/CSA_IHW4/blob/main/staic/randomUsers.png)

Ввод данных из командной строки расширен с учетом введенных
изменений. Можно задать в командной строке первым параметром "random" и тогда будет выполнена случайная генерация.
![](https://github.com/Lapo4kaKek/CSA_IHW4/blob/main/staic/inputCommandRandom.jpeg)
