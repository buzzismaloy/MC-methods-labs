#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <thread>

const int GRID_SIZE = 20;
const int SIMULATION_TIME = 10 * (GRID_SIZE * GRID_SIZE);
const int SLEEP_TIME = 100;
const double MOVE_PROB = 1.0;
const double BIRTH_PROB = 3.0;
const double DEATH_PROB = 2.0;
const double SUM_EVENTS = MOVE_PROB + BIRTH_PROB + DEATH_PROB;

const std::string LIVING_CELL = "O ";
const std::string DEAD_CELL = ". ";
const std::string LIVING_CELL_CMD = "\u2591";
const std::string DEAD_CELL_CMD = "\u2588";
const std::string RESET_COLOUR = "\033[0m"; // Сброс цвета
const std::string LIGHT_GREEN = "\033[1;32m"; // Светло-зеленый

enum class Event {
	MOVE = 1,
	DEATH,
	BIRTH
};
//const int SUM_EVENTS = static_cast<int>(Event::MOVE) + static_cast<int>(Event::DEATH) + static_cast<int>(Event::BIRTH);

struct Cell {
	int x, y;
	bool alive;
};

std::vector<std::vector<Cell>> initialize_grid(std::vector<std::pair<int, int>>& first_generation);
int count_neighbors(const std::vector<std::vector<Cell>>& grid, int x, int y);
void perform_event(std::vector<std::vector<Cell>>& grid, int x, int y, std::default_random_engine& rng);
void run_simulation();
void print_grid(const std::vector<std::vector<Cell>>& grid);
Event linear_search(double number);
bool has_alive_cells(const std::vector<std::vector<Cell>>& grid);


int main() {
	run_simulation();

	return 0;
}

std::vector<std::vector<Cell>> initialize_grid(std::vector<std::pair<int, int>>& first_generation) {
	std::vector<std::vector<Cell>> grid(GRID_SIZE, std::vector<Cell>(GRID_SIZE, {0, 0, false}));
	
	for(const auto& gen : first_generation) {
		grid[gen.first][gen.second].alive = true;
	}
	/*grid[5][5].alive = true;
   	grid[15][5].alive = true;
   	grid[5][15].alive = true;
   	grid[15][15].alive = true;*/	

	return grid;
}

int count_neighbors(const std::vector<std::vector<Cell>>& grid, int x, int y) {
	int count = 0;
	const std::vector<std::pair<int, int>> neighbors = {
		{1, 0}, {-1, 0}, {0, 1}, {0, -1}
	};

	for (const auto& [dx, dy] : neighbors) {
		int nx = (x + dx + GRID_SIZE) % GRID_SIZE;
		int ny = (y + dy + GRID_SIZE) % GRID_SIZE;

		if (grid[nx][ny].alive) ++count;
	}

	return count;
}

Event linear_search(double number) {
	/*std::vector<Event> events = { 
		Event::MOVE, Event::DEATH, Event::BIRTH
       	};

	double probability = 0.0;
	for (int i = 0; i < events.size(); ++i) {
		probability += static_cast<int>(events[i]) / static_cast<double>(SUM_EVENTS);
		if (number <= probability)
			return events[i];
	}

	return events.back();*/

	if (number <= MOVE_PROB / SUM_EVENTS)
		return Event::MOVE;
	if (number <= DEATH_PROB / SUM_EVENTS)
		return Event::DEATH;
	return Event::BIRTH;
}

void perform_event(std::vector<std::vector<Cell>>& grid, int x, int y, std::default_random_engine& rng) {
	int neighbors = count_neighbors(grid, x, y);
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	double event = dist(rng);

	if (grid[x][y].alive) {
		Event action = linear_search(event);

		switch(action){
			case Event::MOVE: {
				std::vector<std::pair<int, int>> moves = {
					{1, 0}, {-1, 0}, {0, 1}, {0, -1}
				};
				int index = rng() % moves.size();
				int nx = (x + moves[index].first + GRID_SIZE) % GRID_SIZE;
				int ny = (y + moves[index].second + GRID_SIZE) % GRID_SIZE;

				if (!grid[nx][ny].alive) {
					grid[nx][ny].alive = true;
					grid[x][y].alive = false;
				}

				break;
			}
			case Event::DEATH: {
				if (neighbors > 3)
					grid[x][y].alive = false;
				break;
			}
			case Event::BIRTH: {
				if (neighbors > 0 && neighbors < 4) {	
					std::vector<std::pair<int, int>> moves = {
						{1, 0}, {-1, 0}, {0, 1}, {0, -1}
					};
					
					for (const auto& move : moves) {
						int nx = (x + move.first + GRID_SIZE) % GRID_SIZE;
						int ny = (y + move.second + GRID_SIZE) % GRID_SIZE;

						if (!grid[nx][ny].alive){
							grid[nx][ny].alive = true;
							break;
						}
					}
				}

				break;
			}
		}
	}	

}

bool has_alive_cells(const std::vector<std::vector<Cell>>& grid) {
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			if (grid[i][j].alive)
				return true;
		}
	}

	return false;
}


void print_grid(const std::vector<std::vector<Cell>>& grid) {
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			if (grid[i][j].alive) 
				std::cout << LIVING_CELL_CMD;
			else 
				std::cout << LIGHT_GREEN << DEAD_CELL_CMD << RESET_COLOUR;
		}

		std::cout << '\n';
	}

	std::cout << '\n';
}

void run_simulation() {
	std::vector<std::pair<int, int>> first_generation = { {5, 5}, {15, 5}, {5, 15}, {15, 15} };
	auto grid = initialize_grid(first_generation); 
	std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> cell_selector(0, GRID_SIZE - 1);

	int chosen_x = 0, chosen_y = 0;
	for (int t = 0; t < SIMULATION_TIME; ++t) {
		std::cout << "\x1b[2J\nStep " << t << ":\n";
		std::cout << "Chosen x: " << chosen_x << " and y: " << chosen_y << '\n';
		print_grid(grid);

		int x = cell_selector(rng);
		int y = cell_selector(rng);
		chosen_x = x;
		chosen_y = y;
		perform_event(grid, x, y, rng);

		if(!has_alive_cells(grid)) {
			std::cout << "All the cells died out after " << t << " steps.\n";
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
	}
}

