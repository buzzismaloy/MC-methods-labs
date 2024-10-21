from ast import parse

import numpy as np
import matplotlib.pyplot as plt

# Функция для плотности распределения Коши
def cauchy_density(x, x0, gamma):
    return 1 / (np.pi * gamma * (1 + ((x - x0) / gamma) ** 2))

# Функция для парсинга данных из файла с несколькими запусками
def parse_runs(file_path):
    with open(file_path, 'r') as f:
        data = f.read()

    runs = data.split('Run')  # Разбиваем на части по ключевому слову 'Run'
    parsed_runs = []

    for run in runs[1:]:  # Пропускаем первую пустую часть
        run_data = run.strip().splitlines()[1:]  # Пропускаем строку 'Run N:'
        run_samples = np.array([float(x) for x in run_data])
        parsed_runs.append(run_samples)

    return parsed_runs


# Параметры распределения Коши
x_center = 0.0
gamma = 0.5
boundary = [-1, 9]  # Диапазон выборки

samples100 = parse_runs("/home/buzzismaloy/University_shit/7th-term/monte-karlo/third-lab/samples100.txt")
samples1000 = parse_runs("/home/buzzismaloy/University_shit/7th-term/monte-karlo/third-lab/samples1000.txt")


# Построение и сохранение графиков для каждого запуска
def plot_and_save_runs(runs, title_prefix, boundary, x_center, gamma, save_dir):
    for i, run_samples in enumerate(runs, 1):
        plt.figure(figsize=(8, 6))
        # Построение гистограммы для выборки
        plt.hist(run_samples, bins=30, density=True, alpha=0.6, color='green', label=f'Metropolis Run {i}')

        # Теоретическая плотность распределения Коши
        x_values = np.linspace(boundary[0], boundary[1], 1000)
        plt.plot(x_values, cauchy_density(x_values, x_center, gamma), 'r-', lw=2, alpha=0.6, label='Cauchy PDF')

        # Оформление графика
        plt.title(f'{title_prefix} - Run {i}')
        plt.legend()
        plt.grid(True)

        # Сохранение графика в файл
        file_name = f'{save_dir}/{title_prefix}_Run_{i}.png'
        plt.savefig(file_name)
        plt.close()



plot_and_save_runs(samples100, 'Cauchy_Distribution_samples100', boundary, x_center, gamma,
                   "/home/buzzismaloy/University_shit/7th-term/monte-karlo/third-lab/plots")

plot_and_save_runs(samples1000, 'Cauchy_Distribution_samples1000', boundary, x_center, gamma,
                   "/home/buzzismaloy/University_shit/7th-term/monte-karlo/third-lab/plots")