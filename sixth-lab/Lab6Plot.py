import matplotlib.pyplot as plt

# Функция для парсинга файла
def parse_file(filename):
    steps = []
    live_cells = []

    with open(filename, 'r') as file:
        step = 0
        alive_count = 0
        in_step = False

        for line in file:
            if line.startswith("Step"):  # Определяем начало нового шага
                if in_step:  # Если это не первый шаг, сохраняем данные предыдущего шага
                    steps.append(step)
                    live_cells.append(alive_count)

                step = int(line.split()[1].strip(':'))  # Получаем номер шага
                alive_count = 0  # Обнуляем счётчик живых клеток для нового шага
                in_step = True
            elif '.' in line or 'O' in line:  # Считываем состояние клеток в строке
                alive_count += line.count('O')  # Считаем живые клетки ('O')

        # Добавляем последний шаг в данные
        if in_step:
            steps.append(step)
            live_cells.append(alive_count)

    return steps, live_cells

# Функция для построения графика
def plot_data(steps, live_cells):
    plt.figure(figsize=(10, 6))
    plt.plot(steps, live_cells, marker='o', color='b', linestyle='-', label='Live Cells')
    plt.title('Number of Live Cells over Steps (Time)')
    plt.xlabel('Step (Time)')
    plt.ylabel('Number of Live Cells')
    plt.grid(True)
    plt.legend()
    plt.show()

# Основная функция
if __name__ == '__main__':
    filename = '/home/buzzismaloy/University_shit/7th-term/monte-karlo/sixth-lab/output.txt'  # Укажите путь к вашему файлу
    steps, live_cells = parse_file(filename)
    plot_data(steps, live_cells)
