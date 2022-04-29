# Задача 3_1
Реализовать ***очередь с динамическим зацикленным буфером***, обрабатывающую команды push* и pop*.
## Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.

Каждая команда задаётся как 2 целых числа: a b.

- a = 2 - pop front
- a = 3 - push back

Команда добавления элемента 3 задана с неотрицательным параметром b.

Для очереди используются команды 2 и 3.

Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”. 
## Формат выходных данных.
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

------
**Требования:** Очередь должна быть реализована в виде класса.
|  in   |  out  |
| :---: | :---: |
|   3   |  YES  |
| 3 44  |
| 3 50  |
| 2 44  |
|   2   |  YES  |
| 2 -1  |
| 3 10  |
|   2   |  NO   |
| 3 44  |
| 2 66  |
