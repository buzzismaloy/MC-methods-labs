#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <string>

//const std::string& FILE_NAME = "samples.txt";
const int NUM_RUNS = 5;

// Функция для плотности распределения Коши
double cauchy_density(double x, double x0, double gamma) {
    return 1.0 / (M_PI * gamma * (1.0 + std::pow((x - x0) / gamma, 2)));
}

// Реализация метода Метрополиса
std::vector<double> metropolis_algorithm(double start_point, double scale, int total_samples, int warmup, std::pair<double, double> bounds) {
    std::vector<double> data;
    double current_position = start_point;

    // Генераторы случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> uniform_dist(-1.0, 1.0);
    std::uniform_real_distribution<> acceptance_dist(0.0, 1.0);

    for (int step = 0; step < total_samples + warmup; ++step) {
        // Предлагаем новую точку
        double candidate_position = current_position + uniform_dist(gen);

        // Проверка, чтобы точка была в пределах заданного диапазона
        if (candidate_position < bounds.first || candidate_position > bounds.second) {
            continue;
        }

        // Вероятность принятия нового состояния
        double acceptance_prob = cauchy_density(candidate_position, start_point, scale) / cauchy_density(current_position, start_point, scale);

        // Принимаем новую точку с вероятностью acceptance_prob
        if (acceptance_dist(gen) < std::min(1.0, acceptance_prob)) {
            current_position = candidate_position;
        }

        // Добавляем точку в выборку после фазы разогрева
        if (step >= warmup) {
            data.push_back(current_position);
        }
    }

    return data;
}

void write_samples_to_file(std::ofstream& output, const std::vector<double>& samples, int run_number) {
    output << "Run " << run_number << ":\n";

    for(double sample : samples)
	    output << sample << '\n';
    output << '\n';
}

int main() {
    // Параметры распределения Коши
    double x_center = 0.0;      // Сдвиг по оси
    double gamma = 0.5;         // Гамма
    std::vector<int> nums_samples = {100, 1000};      // Количество семплов
    int warmup_steps = 500;     // Отбрасываемое количество точек
    double initial_x = 0.0;     // Стартовая точка
    std::pair<double, double> boundary = {-1.0, 9.0}; // Границы выборки


    for (int num_samples : nums_samples) {
	std::string filename = "samples" + std::to_string(num_samples) + ".txt";//создаем имя файла	
    	std::ofstream output(filename);//создаем поток вывода в файл
    	if (!output.is_open()){//открываем поток и если он не открылся выводим ошибку и убиваем прогу
		std::cerr << "Error in opening file " << filename << '\n';
		exit(1);
    	}
	
	for (int run = 0; run < NUM_RUNS; ++run) {	
    		// Получаем выборку методом Метрополиса
    		std::vector<double> generated_samples = metropolis_algorithm(initial_x, gamma, num_samples, warmup_steps, boundary);
		write_samples_to_file(output, generated_samples, run);
		std::cout << "Run #" << run << " for sample size " << num_samples << " saved to " << filename << '\n';

	}

	/*for (double sample : generated_samples) {
        	output << sample << std::endl;
   	 }*/

    	output.close();
    }

    return 0;
}

