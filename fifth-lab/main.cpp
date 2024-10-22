#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <thread>
#include <fstream>
#include <cmath>

const int GRID_SIZE = 20;  // Размер сетки
const int SLEEP_TIME = 100;
const std::string FILENAME = "output.txt";
/*const int V_1 = 1; // вероятность перемещения
const int V_2 = 2; // вероятность смерти клетки если больше 3х соседей
const int V_3 = 3;*/ // вероятность создания клетки

const std::string LIVING_CELL = "O ";
const std::string DEAD_CELL = ". ";
const std::string LIVING_CELL_CMD = "\u2591";
const std::string DEAD_CELL_CMD = "\u2588";
const std::string RESET_COLOUR = "\033[0m"; // Сброс цвета
const std::string LIGHT_GREEN = "\033[1;32m"; // Светло-зеленый

enum class Event {
	MOV = 1,
	DEATH,
	DIV
};

// Функция для вывода текущего состояния сетки
void print_grid(const std::vector<std::vector<int>>& grid, std::ofstream& output) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            output << (grid[i][j] ? LIVING_CELL : DEAD_CELL);
        }
        output << '\n';
    }

    output << "\n\n";
}

void print_grid(const std::vector<std::vector<int>>& grid) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
		if (grid[i][j] == 1) 
			std::cout << LIVING_CELL_CMD;
		else 
			std::cout << LIGHT_GREEN << DEAD_CELL_CMD << RESET_COLOUR;
        }
	std::cout << '\n';
    }
}

// Функция для получения списка соседей клетки
std::vector<std::pair<int, int>> get_neighbors(int x, int y) {
    std::vector<std::pair<int, int>> neighbors = {
        {x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}
    };
    // Фильтрация соседей, чтобы они были в пределах сетки
    neighbors.erase(std::remove_if(neighbors.begin(), neighbors.end(),
        [](std::pair<int, int> p) {
            return p.first < 0 || p.first >= GRID_SIZE || p.second < 0 || p.second >= GRID_SIZE;
        }), neighbors.end());
    return neighbors;
}

// ф-ция для генерации времени по методу первой реакции
double generate_time(double v){
	double e = static_cast<double>(rand()) / RAND_MAX;
	return - std::log(e) / v;
}

// Функция для обработки событий
std::vector<std::vector<int>> process_event(std::vector<std::vector<int>>& grid) {
	std::vector<std::vector<int>> new_grid = grid;

	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			if (grid[i][j] == 1) {
				auto neighbors = get_neighbors(i, j);
				int live_neighbors = 0;
				double t_mov = generate_time(static_cast<double>(static_cast<int>(Event::MOV)));	
				double t_death = generate_time(static_cast<double>(static_cast<int>(Event::DEATH)));	
				double t_div = generate_time(static_cast<double>(static_cast<int>(Event::DIV)));	

				double min_time = std::min({t_mov, t_death, t_div});

				for (const auto& neighbor : neighbors) {
					if (grid[neighbor.first][neighbor.second] == 1) 
						++live_neighbors;
				}

				if (min_time == t_mov ) {
					auto direction = neighbors[rand() % neighbors.size()];
					new_grid[i][j] = 0;
					new_grid[direction.first][direction.second] = 1;
				}
				else if (min_time == t_death && live_neighbors > 3) {
					new_grid[i][j] = 0;
				}
				else if (min_time == t_div && live_neighbors > 0) {
					auto direction = neighbors[rand() % neighbors.size()];

					if (new_grid[direction.first][direction.second] == 0) 
						new_grid[direction.first][direction.second] = 1;
				}


			}
		}
	}
	
	return new_grid;	
}


// Проверка, есть ли живые клетки на поле
bool has_alive_cells(const std::vector<std::vector<int>>& grid) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] == 1) {
                return true;
            }
        }
    }
    return false;
}

void choose_action(int ch){
	// Создаём сетку 19x20 и размещаем начальные клетки
    	std::vector<std::vector<int>> grid(GRID_SIZE, std::vector<int>(GRID_SIZE, 0));
    	std::vector<std::pair<int, int>> initial_positions = {{5, 5}, {15, 5}, {5, 15}, {15, 15}};
    	for (const auto& pos : initial_positions) {
       		grid[pos.first][pos.second] = 1;  // 1 означает, что клетка жива
    	}

    // Основной цикл
   	unsigned long int steps = 0;
	switch(ch){
		case 1:
			for (int i = 0; i < GRID_SIZE * 100; ++i) {
				if (!has_alive_cells(grid)) {
					std::cout << "All the cells died out after " << steps << " steps.\n";
					break;
				}
				std::cout << "\x1b[2J\nStep " << steps << ":\n";
				print_grid(grid);  // Вывод текущего состояния сетки
				grid = process_event(grid); // Обработка событий для всех клеток
        			++steps;
				std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
        			//std::cout << "Press Enter to continue...\n";
       				//std::cin.get();  // Ожидание для продолжения шагов
			}
			break;
		case 2:{		
       			std::ofstream output(FILENAME);//создаем поток вывода в файл
    			if (!output.is_open()){//открываем поток и если он не открылся выводим ошибку и убиваем прогу
				std::cerr << "Error in opening file " << FILENAME << '\n';
				exit(0);
    			}

			for (int i = 0; i < GRID_SIZE * 100; ++i) {
				if (!has_alive_cells(grid)) {
					std::cout << "All the cells died out after " << steps << " steps.\n";
					break;
				}
				output << "Step " << steps << ":\n";
        			print_grid(grid, output);  // Вывод текущего состояния сетки
       				grid = process_event(grid);  // Обработка событий для всех клеток
        			++steps;
			}
			output.close();
			std::cout << "Data has been saved to " << FILENAME <<'\n';
			break;
		}

		case 3:
		       while (has_alive_cells(grid)){
				std::cout << "Step " << steps << ":\n";
				print_grid(grid);
				grid = process_event(grid);
				++steps;
				//std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
        			//std::cout << "Press Enter to continue...\n";
        			//std::cin.get();  // Ожидание для продолжения шагов
			}
    			std::cout << "All the cells died out after " << steps << " steps.\n";
			break;
	}
}

int main() {
    	srand(time(0));  // Инициализация генератора случайных чисел
	std::cout << "To print all data to terminal, enter 1, to print data to file, enter 2(these both variants are executed until";
	std::cout << "the max number of iterations is reached);\nIf you want the program work until all cells die, enter 3, data is displayed to terminal)\n";
	int ch;
	bool right_choice = false;
	while(std::cin >> ch){
		switch(ch) {
			case 1:
			case 2:
			case 3:
				right_choice = true;
				break;
			default:
				std::cout << "\nWrong input, press 1, 2 or 3\n";
		}
		if (right_choice) break;
	}
	choose_action(ch);


	return 0;
}

