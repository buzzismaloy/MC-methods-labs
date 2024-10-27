# Лабораторная работа №1

## Поиск числа пи. (Поиск определенного интеграла)

1. Задаем радиус окружности `R`. Сторона квадрата, куда вписана окружность, равна диаметру окружности. (Или, в случае расчета площади четверти окружности — радиусу).

2. Задаем количество бросков:
   - 10,
   - 100,
   - 1000,
   - 10000

3. Бросаем "кости" для нахождения координат `x` и `y` так, что интервал выпадения от нуля (центр координат) до `R`.

4. По формуле уравнения окружности проверяем, попадает ли случайная точка в окружность (под кривую интеграла).

5. После выполнения всех бросков считаем отношение успешных бросков ко всем.

6. Сравниваем точность вычисления в зависимости от количества бросков.


## Для каждого числа бросков запустить пять раз.

## Проверка рандомайзера на плотность распределения:

1. Найти в открытых источниках характеристики равномерного распределения:
   - математическое ожидание,
   - дисперсия.

2. Создать проверочную выборку из 100 случайных величин.

3. Рассчитать для выборки математическое ожидание и дисперсию.

4. Сравнить полученные значения с теоретическими.


# Лабораторная работа № 2

Методом Метрополиса реализовать случайное блуждание, следуя варианту.

## Вариант 4

1. **Блуждание трехмерное одной частицы по квадратной сетке**.

2. **События**:
   - Фиксированный шаг в сторону на единицу (6 возможных направлений).
   - Вероятности шагнуть в каждую сторону равны друг другу (в сумме дают единицу).

3. Каждое новое состояние системы идентично предыдущему (т.е., α = 1).

4. **Параметры сетки**:
   - Размер 31x31x31, от 0 до 30.
   - Периодические граничные условия.

5. **Шаги расчета**: 1000 и 10000.

6. **Графическое отображение**:
   - Построить финальный график блуждания.
   - Запустить три раза и вывести на одном графике.


# Лабораторная работа № 3

Методом Метрополиса реализовать получение выборки семплов, следуя варианту.

## Вариант 4

**Получение выборки семплов**:
   - Количество образцов: 100.
   - Интервал: \([-1; 9]\).
   - Начальная точка: \( x0 = 0 \).
   - Первые 500 точек отбрасываются.

**Распределение выборки стремится к распределению Коши**

**Проверка**:
   - После выполнения расчета убедиться, что полученная выборка соответствует заданному распределению Коши.


