import numpy as np
import matplotlib.pyplot as plt

# Функция для вычисления евклидова расстояния между городами
def distance(city1, city2):
    return np.linalg.norm(city1 - city2)

# Функция для вычисления общей длины маршрута
def total_distance(route, cities):
    return sum(distance(cities[route[i]], cities[route[i+1]])
               for i in range(N-1)) + distance(cities[route[-1]], cities[route[0]])

# Функция для генерации нового состояния (переворот участка маршрута)
def generate_new_state(route):
    i, j = sorted(np.random.choice(N, 2, replace=False))
    new_route = route.copy()
    new_route[i:j+1] = np.flip(route[i:j+1])
    return new_route


# Алгоритм имитации отжига
def simulated_annealing(cities, tmax=100, tmin=1e-3, alpha=0.995, max_iter=100000):
    # Инициализация
    route = np.arange(N)
    np.random.shuffle(route)
    best_route = route.copy()
    best_distance = total_distance(best_route, cities)

    current_route = route.copy()
    current_distance = best_distance

    T = tmax
    distances = []

    for k in range(max_iter):
        if T < tmin:
            break

        # Генерация нового состояния
        new_route = generate_new_state(current_route)
        new_distance = total_distance(new_route, cities)

        # Разница в расстояниях
        delta_E = new_distance - current_distance

        # Принимаем новое состояние с вероятностью
        if delta_E < 0 or np.random.rand() < np.exp(-delta_E / T):
            current_route = new_route
            current_distance = new_distance

        # Обновление лучшего маршрута
        if current_distance < best_distance:
            best_route = current_route
            best_distance = current_distance

        # Снижение температуры
        T *= alpha
        distances.append(best_distance)

    return best_route, best_distance, distances


# график
def plot_route(cities, route, title):
    plt.figure(figsize=(8, 8))
    route_cities = cities[route]
    route_cities = np.vstack((route_cities, route_cities[0]))  # Замыкаем маршрут
    plt.plot(route_cities[:, 0], route_cities[:, 1], 'o-', label='Маршрут')
    for i, (x, y) in enumerate(cities):
        plt.text(x, y, str(i), fontsize=12, color='red')
    plt.title(title)
    plt.xlabel('x')
    plt.ylabel('y')
    plt.grid(True)
    plt.legend()
    plt.show()


N = 20 #города
cities = np.random.rand(N, 2) * 10 #Координаты городов в квадрате 10х10
#параметры
tmax = 100
tmin = 1e-3
alpha = 0.995
max_iterations = 100000

best_route, best_distance, distances = simulated_annealing(cities, tmax, tmin, alpha)
plot_route(cities, np.arange(N), 'Initial route')
plot_route(cities, best_route, f'Best route(Lngth: {best_distance:.2f})')

# График изменения длины маршрута в процессе оптимизации
plt.plot(distances)
plt.title('Изменение длины маршрута во времени')
plt.xlabel('Итерации')
plt.ylabel('Длина маршрута')
plt.grid(True)
plt.show()