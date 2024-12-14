import numpy as np
from scipy.integrate import solve_ivp
import matplotlib.pyplot as plt

# Глобальные параметры
k1p = 1.0e+00  # константа скорости адсорбции СО
k1m = 2.0e-01  # константа скорости десорбции СО
k2 = 5.0e-01   # константа скорости адсорбции О2
k3 = 1.0e+05   # константа скорости реакции образования CO2 из CO и O
k4 = 3.0e-02   # константа скорости реакции образования CO2 из CO и Os
k5 = 5.0e-03   # константа скорости образования CO2 из CO и Os

# Функция для расчета правых частей ОДУ
def f_ode(t, x):
    x1, x2, x3 = x  # Концентрации: x1 - CO, x2 - O, x3 - Os
    xx = 1 - x1 - x2 - x3  # Свободные места
    dx1 = k1p * xx - k1m * x1 - 4 * k3 * x1 * x2 - 4 * k5 * x1 * x3
    dx2 = 4 * k2 * xx**2 - 4 * k3 * x1 * x2 - k4 * x2
    dx3 = k4 * x2 - 4 * k5 * x1 * x3
    return [dx1, dx2, dx3]

# Функция для запуска расчета на сетке заданного размера
def run_simulation(grid_size, tmax_ode):
    tmin_ode = 0.0
    tspan = (tmin_ode, tmax_ode)
    x0_ode = [0.0, 0.0, 0.0]  # Начальные условия

    # Решение системы ОДУ
    solution = solve_ivp(f_ode, tspan, x0_ode, method='BDF', rtol=1e-8, atol=1e-8)

    # График результатов
    plt.figure()
    plt.plot(solution.t, solution.y[0], label='CO', linewidth=2)
    plt.plot(solution.t, solution.y[1], label='O', linewidth=2)
    plt.plot(solution.t, solution.y[2], label='Os', linewidth=2)
    plt.xlabel('t')
    plt.ylabel('Coverages')
    plt.title(f'STM ODE - Grid Size {grid_size}x{grid_size}')
    plt.legend()
    plt.grid()
    plt.show()

# Основная функция
if __name__ == "__main__":
    grid_sizes = [10, 20, 50, 100, 500]  # Размеры сеток
    tmax_ode = 1000.0  # Максимальное время расчета

    for grid_size in grid_sizes:
        print(f"Running simulation for grid size: {grid_size}x{grid_size}")
        run_simulation(grid_size, tmax_ode)
