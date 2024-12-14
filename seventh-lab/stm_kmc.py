import numpy as np
import matplotlib.pyplot as plt

def run_simulation(grid_size, tmax=1000.0, dt=0.1):
    # Внутренние параметры задачи
    k1p = 1.0  # константа скорости адсорбции СО
    k1m = 0.2  # константа скорости десорбции СО
    k2 = 0.5  # константа скорости адсорбции О2
    k3 = 1.0e5  # константа скорости реакции образования CO2 из CO и O
    k4 = 0.03  # константа скорости реакции образования CO2 из CO и Os
    k5 = 0.005  # константа скорости образования CO2 из CO и Os

    # Параметры модели
    N = grid_size ** 2  # общее число узлов решетки
    N_CO, N_O, N_Os = 0, 0, 0  # начальные условия (чистая поверхность)
    t, t_out = 0.0, 0.0  # текущее время и время следующей выдачи
    results = []  # список для хранения результатов

    # Инициализация генератора случайных чисел
    np.random.seed(12345)

    # Расчеты KMC
    while t < tmax:
        # Запись результатов
        if t >= t_out:
            results.append((t, N_CO / N, N_O / N, N_Os / N))
            t_out += dt

        NN1 = 1.0 / (N - 1)  # нормировочный фактор
        N0 = N - N_CO - N_O - N_Os  # число свободных узлов

        # Вычисление скоростей процессов
        Rate = np.array([
            k1p * N0,  # скорость адсорбции СО
            k1m * N_CO,  # скорость десорбции СО
            4 * k3 * N_CO * N_O * NN1,  # скорость реакции образования CO2 из CO и O
            4 * k5 * N_CO * N_Os * NN1,  # скорость реакции образования CO2 из CO и Os
            2 * k2 * N0 * (N0 - 1) * NN1,  # скорость адсорбции О2
            k4 * N_O  # скорость перехода O -> Os
        ])

        RSum = np.sum(Rate)  # суммарная скорость
        if RSum == 0:
            break

        # Выбор реакции
        R = np.random.rand() * RSum
        j = np.searchsorted(np.cumsum(Rate), R)

        # Реакции
        if j == 0:  # адсорбция CO
            N_CO += 1
        elif j == 1:  # десорбция CO
            N_CO -= 1
        elif j == 2:  # реакция образования CO2 из CO и O
            N_CO -= 1
            N_O -= 1
        elif j == 3:  # реакция образования CO2 из CO и Os
            N_CO -= 1
            N_Os -= 1
        elif j == 4:  # адсорбция O2
            N_O += 2
        elif j == 5:  # переход O -> Os
            N_O -= 1
            N_Os += 1

        # Вычисление времени
        t -= np.log(np.random.rand()) / RSum

    return np.array(results)

# Размеры сетки для моделирования
grid_sizes = [10, 20, 50, 100]

# Построение графиков для разных размеров сетки
for grid_size in grid_sizes:
    results = run_simulation(grid_size)
    tt = results[:, 0]
    xt_CO = results[:, 1]
    xt_O = results[:, 2]
    xt_Os = results[:, 3]

    plt.figure(figsize=(10, 6))
    plt.plot(tt, xt_CO, label='CO', linewidth=1.5)
    plt.plot(tt, xt_O, label='O', linewidth=1.5)
    plt.plot(tt, xt_Os, label='Os', linewidth=1.5)

    plt.xlabel('Time, t')
    plt.ylabel('Coverages')
    plt.title(f'STM KMC - Grid {grid_size}x{grid_size}')
    plt.legend()
    plt.grid()
    plt.show()
