Стулов Михаил Александрович

Задача 2 (заражения)

Cтандартная сборка через CMake

Написаны рандомно-генерируемые тесты (без использования фреймворков для тестов). 
Запустить их можно, если передать в аргументах командной строки "test".
Тесты проверяют, что выбранный набор вершин действительно заражает весь граф.

## infector

Прежде всего при помощи класса `Graph` считываем граф и преобразуем к списку смежности 
с нумерацией вершин от 0 до (количество вершин - 1), без петель и кратных ребер.
При помощи этого же класса в конце восстановим изначальную нумерацию вершин

Решение жадным алгоритмом.
Поддерживаем для каждой вершины количество зараженных соседей (от 0 до 2).
Так же есть условно функция `benefit(vertex)` (ее поддерживаем при помощи `std:set`) - она говорит насколько выгодно взять эту вершину, 
исходя из количества незараженных соседей(`to`) двух типов: 
у `to` нет зараженного соседа или же у `to` есть один зараженный сосед.
Какой вклад в benefit дает каждый из этих типов соседей параметризуется `static` полями класса `GraphInfector`.
Протестировать какими лучше поставить эти параметры я не успел((.

Сначала заражаем все вершины, степень которых 1 или 0. 
Далее если есть вершины, у которых хотя бы два зараженных соседа - 
обрабатываем их, и так пока не закончатся необработанные зараженные вершины. 
Когда необработанных зараженных нет - выбираем незараженную вершину с максимальным `benefit` и заражаем.

Асимптотика O(MlogM), M - число ребер
