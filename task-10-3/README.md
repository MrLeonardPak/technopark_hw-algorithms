# Задача 10
## В дерево
Постройте B-дерево минимального порядка t и выведите его по слоям.
В качестве ключа используются числа, лежащие в диапазоне 0..232 -1

**Требования:** 
B-дерево должно быть реализовано в виде шаблонного класса.
Решение должно поддерживать передачу функции сравнения снаружи.




**Формат входных данных**

Сначала вводится минимальный порядок дерева t.
Затем вводятся элементы дерева.

**Формат выходных данных**

Программа должна вывести B-дерево по слоям. Каждый слой на новой строке, элементы должны выводится в том порядке, в котором они лежат в узлах.

|          in           |         out         |
| :-------------------: | :-----------------: |
| 2 0 1 2 3 4 5 6 7 8 9 | 3 1 5 7 0 2 4 6 8 9 |
| 4 0 1 2 3 4 5 6 7 8 9 | 3 0 1 2 4 5 6 7 8 9 |
