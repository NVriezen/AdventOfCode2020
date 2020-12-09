#include "..\include\Day6.h"

#include "..\include\StringParsing.h"

int get_group_sum(std::ifstream& input)
{
	std::string line;
	int counter = 0;
	uint8_t answered_yes[26] = { 0 };
	while (getline(input, line) && line != "")
	{
		for (size_t i = 0; i < line.size(); i++)
		{
			counter += answered_yes[line[i] - 97] == 0;
			answered_yes[line[i] - 97] += 1;
		}
	}


	return counter;
}

int get_group_sum_all_answered(std::ifstream& input)
{
	std::string line;
	int counter = 0;
	int sum = 0;
	uint8_t answered_yes[26] = { 0 };
	std::string group_string = "";
	while (getline(input, line) && line != "")
	{
		group_string.append(line);
		counter++;
	}

	for (size_t i = 0; i < group_string.size(); i++)
	{
		answered_yes[group_string[i] - 97] += 1;
		sum += answered_yes[group_string[i] - 97] == counter;
	}

	return sum;
}

int answer_day6_puzzle1()
{
	int total_sum = -1;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day6_input.txt");
	if (input_file.is_open())
	{
		total_sum = 0;
		while (true)
		{
			total_sum += get_group_sum(input_file);
			if (input_file.eof())
				break;
		}
	}

	input_file.close();
	return total_sum;
}

int answer_day6_puzzle2()
{
	int total_sum = -1;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day6_input.txt");
	if (input_file.is_open())
	{
		total_sum = 0;
		while (true)
		{
			total_sum += get_group_sum_all_answered(input_file);
			if (input_file.eof())
				break;
		}
	}

	input_file.close();
	return total_sum;
}