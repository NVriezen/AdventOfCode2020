#include "..\include\Day10.h"

#include "..\include\StringParsing.h"

#include <map>
#include <queue>

bool find_closest_adapter(std::ifstream& input_file, int* previous_adapter, int* difference)
{
	std::string line;
	int actual_number = 0;
	int lowest_difference = 4;
	int lowest_adapter = (*previous_adapter);
	while (input_file >> line)
	{
		actual_number = std::stoi(line);

		if (actual_number <= (*previous_adapter))
			continue;

		int current_difference = actual_number - (*previous_adapter);
		if (current_difference >= 4)
			continue;

		if (current_difference > lowest_difference)
			continue;

		lowest_adapter = actual_number;
		lowest_difference = current_difference;

		if (lowest_difference == 1)
			break;
	}
	input_file.clear();
	input_file.seekg(std::ios::beg);

	(*difference) = lowest_difference;
	(*previous_adapter) = lowest_adapter;

	if (lowest_difference == 4)
		return false;
	return true;
}

int answer_day10_puzzle1()
{
	int total_ = -1;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day10_input.txt");
	if (input_file.is_open())
	{
		total_ = 0;
		int differences[3] = { 0, 0, 1 }; // add 1 already because of device difference
		int previous_adapter = 0;
		while (true)
		{
			int difference = 0;
			if (find_closest_adapter(input_file, &previous_adapter, &difference) == false)
				break;
			differences[difference - 1]++;
		}
		total_ = differences[0] * differences[2];
	}

	input_file.close();
	return total_;
}

std::map<int, uint64_t> answers;
uint64_t find_arrangement(std::ifstream& input_file, int adapter_to_check)//std::queue<int> adapters)
{
	if (answers.count(adapter_to_check) > 0)
	{
		return answers[adapter_to_check];
	}

	std::string line;
	int actual_number = 0;
	int possible_adapters = 0;
	uint64_t total = 0;
	int found_ways[3];
	while (input_file >> line)
	{
		actual_number = std::stoi(line);

		if (actual_number <= adapter_to_check)
			continue;

		int current_difference = actual_number - adapter_to_check;
		if (current_difference >= 4)
			continue;

		found_ways[possible_adapters] = actual_number;
		possible_adapters++;

		if (possible_adapters == 3)
			break;
	}
	input_file.clear();
	input_file.seekg(std::ios::beg);

	for (size_t i = 0; i < possible_adapters; i++)
	{
		total += find_arrangement(input_file, found_ways[i]);
	}

	total += possible_adapters == 0;

	answers.insert({ adapter_to_check, total });
	return total;
}

unsigned long long answer_day10_puzzle2()
{
	uint64_t total_ = -1;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day10_input.txt");
	if (input_file.is_open())
	{
		total_ = find_arrangement(input_file, 0);
	}

	input_file.close();
	return total_;
}