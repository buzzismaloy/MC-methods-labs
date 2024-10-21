#include <iostream>
#include <fstream>
#include <random>
#include <vector>

const int GRID_SIZE = 31;
const int NUM_STEPS_1 = 1000;
const int NUM_STEPS_2 = 10000;
const int LAUNCHES_NUM = 3;

const int START_POS = 15;

void randomWalk(int steps, std::vector<std::vector<int>>& trajectory){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 5);

	int x = START_POS, y = START_POS, z = START_POS;
	trajectory.push_back({x, y, z});

	for(int i = 0; i < steps; ++i){
		int dir = dist(gen);

		switch (dir) {
			case 0: x = (x + 1) % GRID_SIZE; break; // вправо
           		case 1: x = (x - 1 + GRID_SIZE) % GRID_SIZE; break; // влево
            		case 2: y = (y + 1) % GRID_SIZE; break; // вверх
            		case 3: y = (y - 1 + GRID_SIZE) % GRID_SIZE; break; // вниз
            		case 4: z = (z + 1) % GRID_SIZE; break; // вперед
            		case 5: z = (z - 1 + GRID_SIZE) % GRID_SIZE; break; // назад
		}

		trajectory.push_back({x, y, z});
	}
}

void saveToFile(const std::vector<std::vector<std::vector<int>>>& trajectories, const std::string& filename) {
	std::ofstream output(filename);

	if (!output.is_open()){
		std::cerr << "Error in opening file " << filename << '\n';
		exit(1);
	}

	for(const auto& trajectory : trajectories) {
		for(const auto& i : trajectory) {
			output << i[0] << ',' << i[1] << ',' << i[2] << '\n';
		}
		output << '\n';
	}

	output.close();
}

int main(){
	std::vector<std::vector<std::vector<int>>> trajectories_1;
	std::vector<std::vector<std::vector<int>>> trajectories_2;

	for(int i = 0; i < LAUNCHES_NUM; ++i) {
		std::vector<std::vector<int>> trajectory;
		randomWalk(NUM_STEPS_1, trajectory);
		trajectories_1.push_back(trajectory);
	}


	for(int i = 0; i < LAUNCHES_NUM; ++i) {
		std::vector<std::vector<int>> trajectory;
		randomWalk(NUM_STEPS_2, trajectory);
		trajectories_2.push_back(trajectory);
	}

	saveToFile(trajectories_1, "trajectories_1000.txt");
	saveToFile(trajectories_2, "trajectories_10000.txt");

	std::cout << "Data has been saved!\n";

	return 0;
}	
