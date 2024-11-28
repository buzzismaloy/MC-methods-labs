# Оглавление

- [Лабораторная работа № 1](#лабораторная-работа-№-1)
  - [Поиск числа пи (Поиск определенного интеграла)](#поиск-числа-пи-поиск-определенного-интеграла)
    - [Алгоритм](#алгоритм)
    - [Для каждого числа бросков запустить пять раз](#для-каждого-числа-бросков-запустить-пять-раз)
    - [Проверка рандомайзера на плотность распределения](#проверка-рандомайзера-на-плотность-распределения)

- [Лабораторная работа № 2](#лабораторная-работа-№-2)
  - [Случайное блуждание методом Метрополиса](#случайное-блуждание-методом-метрополиса)
    - [Вариант 4](#вариант-4)
    - [Графическое отображение](#графическое-отображение)

- [Лабораторная работа № 3](#лабораторная-работа-№-3)
  - [Получение выборки семплов методом Метрополиса](#получение-выборки-семплов-методом-метрополиса)
    - [Вариант 4](#вариант-4-1)
    - [Проверка соответствия распределению Коши](#проверка-соответствия-распределению-кошy)

- [Лабораторная работа № 4](#лабораторная-работа-№-4)
  - [Решение задачи коммивояжера методом имитации отжига](#решение-задачи-коммивояжера-методом-имитации-отжига)
    - [Параметры задачи](#параметры-задачи)
    - [Метод и реализация](#метод-и-реализация)

- [Лабораторная работа № 5](#лабораторная-работа-№-5)
  - [Псевдо-жизнь кинетическим методом Монте-Карло](#псевдо-жизнь-кинетическим-методом-монте-карло)
    - [Алгоритмы КМК без отказов](#алгоритмы-кмк-без-отказов)
    - [Правила игры](#правила-игры)
    - [Параметры симуляции](#параметры-симуляции)

- [Лабораторная работа № 6](#лабораторная-работа-№-6)
  - [Игра «Жизнь» кинетическим методом Монте-Карло (КМК)](#игра-жизнь-кинетическим-методом-монте-карло-кмк)
    - [Алгоритмы КМК с отказами](#алгоритмы-кмк-с-отказами)
    - [Описание игры](#описание-игры)
    - [Правила обновления клеток](#правила-обновления-клеток)
    - [Реализация](#реализация)
    - [Параметры симуляции](#параметры-симуляции-1)

---

# Лабораторная работа № 1

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

---

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


---

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

---

# Лабораторная работа № 4

Методом имитации отжига решить задачу коммивояжёра.  
Дано N = 20 городов со случайно сгенерированными координатами в квадрате
10х10. x ∈ (0 ; 10), y ∈ (0 ; 10).

(Для удобства тестирования можете взять один раз сгенерированные координаты.)  
Каждый город представляется как пара координат \(x, y)\.

- **Множество состояний** \( S \): все возможные маршруты, проходящие через каждый город.

- **Целевая функция** \( E \): минимальное расстояние между городами, равное сумме евклидовых расстояний между парами городов в маршруте.  
  Поскольку задача замкнутая, добавьте в конце расстояние между последним и первым городом.

- **Функция** \( F \), генерирующая новое состояние:  
  Выбираем два произвольных города в маршруте и инвертируем путь между ними.  
  Например, если маршрут был (1, 2, 3, 4, 5, 6, 7), генератор случайных чисел выбрал города 2 и 7, тогда после процедуры получается (1, 7, 6, 5, 4, 3, 2).  
  (Используйте `flipud()` для MATLAB и Python.)

- **Функция времени**:  
  T = (0.1 * tmax) / k, где k  – номер текущей итерации.  
  Вы можете выбрать иную функцию изменения времени и сравнить результаты.

### Задаем:
- Начальную температуру tmax
- Минимальную температуру tmin
- Начальное состояние системы s0.

Помните: метод имитации отжига стохастический и не гарантирует получения оптимального решения.  
Изменяйте функцию времени, параметр tmax, и несколько раз запускайте программу, пока не получите наиболее удовлетворяющий результат.  
Для расчета может понадобиться до 1 000 000 итераций.

---

# Лабораторная работа № 5

## Псевдо-жизнь кинетическим методом Монте-Карло

### Алгоритмы КМК без отказов

**Место действия игры** — размеченная на клетки плоскость, которая может быть ограниченной или периодичной.  
Каждая клетка на этой поверхности имеет восемь соседей, окружающих её, и может находиться в двух состояниях: быть «живой» (заполненной) или «мёртвой» (пустой).  
Распределение живых клеток в начале игры называется первым поколением.  
Каждое следующее поколение рассчитывается на основе предыдущего по следующим правилам:

1. Клетка может двинуться в любом из четырех направлений с равными вероятностями \( v = 1 \);  
   (по диагонали не ходит)

2. Если у клетки \( A \) есть клетка-соседка \( B \), то клетка \( A \) может взаимодействовать с \( B \) и произвести в одну из ближайших клеток ещё одну клетку \( C \) с вероятностью \( v = 3 \). Либо клетка может двинуться в оставшиеся свободные направления с \( v = 1 \).

3. Если у клетки больше 3 соседей, она может умереть с вероятностью \( v = 2 \).

На пустых клетках ничего не происходит.

Всего в системе может произойти девять видов событий:
- Движение по четырем направлениям
- Образование новой клетки по четырем направлениям
- Смерть клетки

Игра прекращается, если на поле не останется ни одной «живой» клетки.

### Реализовать метод первой реакции

- **Время расчета:** размер сетки^2  
- **Размер сетки:** 20×20  
- **Первое поколение:** четыре клетки с координатами (5, 5), (15, 5), (5, 15), (15, 15)  
- **Четный вариант:** ограниченная сетка

---

# Лабораторная работа № 6

## Игра «Жизнь» кинетическим методом Монте-Карло (КМК)
### Алгоритмы КМК с отказами

### Описание игры
Игровое поле представляет собой размеченную на клетки плоскость, которая может быть:
- безграничной,
- ограниченной,
- замкнутой.

Каждая клетка на этом поле имеет восемь соседей, окружающих её, и может находиться в двух состояниях:
- **"живая"** (заполненная клетка),
- **"мёртвая"** (пустая клетка).

Начальное распределение живых клеток называется **первым поколением**. Каждое последующее поколение рассчитывается на основе предыдущего с помощью определённых правил.

### Правила обновления клеток
1. **Движение клетки**  
   Клетка может двигаться в любом из четырех направлений (вверх, вниз, влево, вправо) с равными вероятностями, \(v = 1\). Движение по диагонали запрещено.

2. **Размножение**  
   Если у клетки \(A\) есть соседка \(B\), то клетка \(A\) может взаимодействовать с \(B\) и создать ещё одну клетку \(C\) в одном из ближайших свободных мест с вероятностью \(v = 3\). Если направление занято, клетка движется в другие доступные направления с вероятностью \(v = 1\).

3. **Смерть**  
   Если у клетки более трех соседей, она может умереть с вероятностью \(v = 2\).

На пустых клетках никаких событий не происходит.

### Возможные события
Всего в системе может произойти девять типов событий:
- Движение клетки в одном из четырех направлений.
- Создание новой клетки в одном из четырех направлений.
- Смерть клетки при наличии более трёх соседей.

Игра прекращается, если на поле не остаётся ни одной "живой" клетки.

### Реализация
Реализация должна включать метод случайного выбора и линейного поиска события.

### Параметры симуляции
- **Время расчета:** \(10 * (размер сетки^2)
- **Размер сетки:** 20x20
- **Первое поколение**: четыре клетки с координатами (5,5), (15,5), (5,15), (15,15).

---
