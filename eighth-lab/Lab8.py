import random
import numpy as np
import matplotlib.pyplot as plt

# Константы
k1 = 0.1  # Жертва рождается в присутствии другой жертвы в соседней ячейке
k2 = 0.5  # Хищник ест жертву и размножается
k3 = 0.07  # Хищник умирает от старости
d1 = 0     # Жертва не перемещается по сетке
d2 = 2     # Хищник перемещается по сетке

# Глобальная переменная сетки (grid), заполняем её пустыми клетками (0)
def initialize_grid(grid_size):
    return [[0 for _ in range(grid_size)] for _ in range(grid_size)]

# Функция для получения списка соседей клетки (x, y)
def get_neighbors(x, y, grid_size):
    neighbors = [
        (x - 1, y), (x + 1, y),
        (x, y - 1), (x, y + 1)
    ]
    # Возвращаем только тех соседей, которые находятся в пределах сетки
    return [(nx, ny) for nx, ny in neighbors if 0 <= nx < grid_size and 0 <= ny < grid_size]

# Функция для обработки одного события на сетке (хищник/жертва)
def process_event(grid, grid_size):
    new_grid = [row[:] for row in grid]

    possible_events = []

    # Проходим по всем клеткам, чтобы собрать все возможные события
    for i in range(grid_size):
        for j in range(grid_size):
            if grid[i][j] == 1:  # Если клетка содержит жертву
                neighbors = get_neighbors(i, j, grid_size)
                free_neighbors = [(x, y) for x, y in neighbors if grid[x][y] == 0]
                live_neighbors = sum(1 for x, y in neighbors if grid[x][y] == 1)

                # Добавляем возможные события для жертвы
                if free_neighbors:
                    for direction in free_neighbors:
                        possible_events.append(('move', i, j, direction))

                if free_neighbors and live_neighbors > 0:
                    for direction in free_neighbors:
                        possible_events.append(('divide', i, j, direction))

            elif grid[i][j] == 2:  # Если клетка содержит хищника
                neighbors = get_neighbors(i, j, grid_size)
                free_neighbors = [(x, y) for x, y in neighbors if grid[x][y] == 0]
                prey_neighbors = [(x, y) for x, y in neighbors if grid[x][y] == 1]

                # Добавляем возможные события для хищника
                if free_neighbors:
                    for direction in free_neighbors:
                        possible_events.append(('move', i, j, direction))

                if prey_neighbors:
                    for direction in prey_neighbors:
                        possible_events.append(('eat', i, j, direction))

                if len(prey_neighbors) > 0:  # Если хищник поел, размножаем его
                    for direction in free_neighbors:
                        possible_events.append(('divide', i, j, direction))

    # Выбираем случайное событие
    if possible_events:
        total_events = len(possible_events)
        event_probabilities = [1 / total_events] * total_events  # Равномерное распределение вероятностей
        chosen_event_index = random.choices(range(total_events), event_probabilities)[0]
        event_type, i, j, *direction = possible_events[chosen_event_index]

        if event_type == 'move':
            new_grid[i][j] = 0
            new_grid[direction[0][0]][direction[0][1]] = 1 if grid[i][j] == 1 else 2
        elif event_type == 'divide':
            new_grid[direction[0][0]][direction[0][1]] = 1 if grid[i][j] == 1 else 2
        elif event_type == 'eat':
            new_grid[i][j] = 2
            new_grid[direction[0][0]][direction[0][1]] = 0

    return new_grid

# Функция для симуляции
def run_simulation(grid_size=20, t_max=1000, dt=0.1, initial_prey=10, initial_predator=5):
    # Инициализация сетки
    grid = initialize_grid(grid_size)

    # Устанавливаем начальные позиции для жертв и хищников
    positions = []
    for _ in range(initial_prey):
        x, y = random.randint(0, grid_size - 1), random.randint(0, grid_size - 1)
        positions.append((x, y, 1))  # Жертвы (1)
    for _ in range(initial_predator):
        x, y = random.randint(0, grid_size - 1), random.randint(0, grid_size - 1)
        positions.append((x, y, 2))  # Хищники (2)

    for x, y, entity in positions:
        grid[x][y] = entity

    times = []
    prey_counts = []
    predator_counts = []

    t = 0
    t_out = 0.0

    # Симуляция
    while t < t_max:
        if t >= t_out:
            prey_count = sum(row.count(1) for row in grid)  # Считаем количество жертв
            predator_count = sum(row.count(2) for row in grid)  # Считаем количество хищников

            times.append(t)
            prey_counts.append(prey_count)
            predator_counts.append(predator_count)
            t_out += dt

        # Выполняем событие
        grid = process_event(grid, grid_size)
        t += dt

    return times, prey_counts, predator_counts

# Размеры сетки для тестирования
grid_sizes = [10, 20, 50]

# Визуализация результатов для различных размеров сетки
plt.figure(figsize=(12, 10))

for grid_size in grid_sizes:
    times, prey_counts, predator_counts = run_simulation(grid_size=grid_size, initial_prey=30, initial_predator=10)
    plt.plot(times, prey_counts, label=f"Жертвы (Grid size {grid_size})")
    plt.plot(times, predator_counts, label=f"Хищники (Grid size {grid_size})")

plt.xlabel("Время")
plt.ylabel("Количество")
plt.title("Модель хищников и жертв для различных размеров сетки")
plt.legend()
plt.grid(True)
plt.show()