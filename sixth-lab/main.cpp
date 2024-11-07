#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>

const int GRID_SIZE = 20;
const int SIMULATION_TIME = 10 * (GRID_SIZE * GRID_SIZE);
const int SLEEP_TIME = 10;
const double MOVE_PROB = 1.0;
const double BIRTH_PROB = 3.0;
const double DEATH_PROB = 2.0;
const double SUM_EVENTS = MOVE_PROB + BIRTH_PROB + DEATH_PROB;

const std::string GRID_FILENAME = "output.txt";
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

enum class PrintType {
	TERMINAL,
	TO_FILE
};

struct Cell {
	int x, y;
	bool alive;
};

std::vector<std::vector<Cell>> initialize_grid(std::vector<std::pair<int, int>>& first_generation);
int count_neighbors(const std::vector<std::vector<Cell>>& grid, int x, int y);
void perform_event(std::vector<std::vector<Cell>>& grid, int x, int y, std::default_random_engine& rng);
void run_simulation(PrintType type);
void print_grid(const std::vector<std::vector<Cell>>& grid);
void print_grid_to_file(const std::vector<std::vector<Cell>>& grid, std::ofstream& output);
Event linear_search(double number);
bool has_alive_cells(const std::vector<std::vector<Cell>>& grid);
PrintType process_user_input();

unsigned short int actions_count = 0;

int main() {
	PrintType type = process_user_input();
	run_simulation(type);

	return 0;
}

PrintType process_user_input() {
	std::cout << "Choose where to print data: enter terminal for terminal and file for file\n>";
	std::string input;
	while(true) {
		std::cin >> input;
		if (input == "terminal") 
			return PrintType::TERMINAL;
		
		else if (input == "file") 
			return PrintType::TO_FILE;
	}
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
	double prob = MOVE_PROB / SUM_EVENTS;
	if (number < prob)
		return Event::MOVE;
	
	prob += BIRTH_PROB / SUM_EVENTS;
	if (number < prob)
		return Event::BIRTH;

	return Event::DEATH;
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
					++actions_count;
				}

				break;
			}
			case Event::DEATH: {
				if (neighbors > 3) {
					grid[x][y].alive = false;
					++actions_count;
				}
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
							++actions_count;
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

void print_grid_to_file(const std::vector<std::vector<Cell>>& grid, std::ofstream& output) {
	for (int i = 0; i < GRID_SIZE; ++i) {
        	for (int j = 0; j < GRID_SIZE; ++j) {
            		output << (grid[i][j].alive ? LIVING_CELL : DEAD_CELL);
        	}
        	output << '\n';
    	}
	output << "\n\n";
}

void run_simulation(PrintType type) {
	std::vector<std::pair<int, int>> first_generation = { {5, 5}, {15, 5}, {5, 15}, {15, 15} };
	auto grid = initialize_grid(first_generation); 
	std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> cell_selector(0, GRID_SIZE - 1);
	
	int chosen_x = 0, chosen_y = 0;
	switch(type){
		case PrintType::TERMINAL: {		
			for (int t = 0; t < SIMULATION_TIME; ++t) {
				std::cout << "\x1b[2J\nStep " << t << ":\n";
				std::cout << "Chosen cell: " << '(' << chosen_x << ';' << chosen_y << ')' << '\n';
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
			break;	
		}

		case PrintType::TO_FILE: {
			std::ofstream output(GRID_FILENAME);
    			if (!output.is_open()){
				std::cerr << "Error in opening file " << GRID_FILENAME << '\n';
				exit(0);
    			}

			for (int t = 0; t < SIMULATION_TIME; ++t) {
				output << "Step " << t << ":\n";
				print_grid_to_file(grid, output);

				int x = cell_selector(rng);
				int y = cell_selector(rng);
				
				perform_event(grid, x, y, rng);

				if(!has_alive_cells(grid)) {
					std::cout << "All the cells died out after " << t << " steps.\n";
					break;
				}
			}
			output.close();
			std::cout << "Data has been saved to " << GRID_FILENAME << '\n';
			break;
		}
	}

	std::cout << "\n\nSome statistics:\n" << actions_count << " actions were taken in " << SIMULATION_TIME << " steps\n";
}

