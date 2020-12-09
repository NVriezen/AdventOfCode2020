#include "..\include\Day9.h"

#include "..\include\StringParsing.h"
#include <vector>

#include "..\include\Day1.h"

static const int preamble = 25;
int invalid_number = -1;//15690279;

int answer_day9_puzzle1()
{
	if (invalid_number != -1)
		return invalid_number;

	int total_ = -1;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day9_input.txt");
	if (input_file.is_open())
	{
		total_ = 0;
		std::string line;
		int previous_numbers[preamble] = { 0 };
		for (size_t i = 0; i < preamble; i++)
		{
			input_file >> line;
			previous_numbers[i] = std::stoi(line);
		}

		while (input_file >> line)
		{
			int actual_number = std::stoi(line);

			bool is_valid = false;
			for (size_t x = 0; x < preamble; x++)
			{
				for (size_t y = x; y < preamble; y++)
				{
					is_valid |= (previous_numbers[x] != previous_numbers[y]) && (previous_numbers[x] + previous_numbers[y] == actual_number);
				}
			}

			if (!is_valid)
			{
				total_ = actual_number;
				invalid_number = actual_number;
				break;
			}

			for (size_t j = 0; j < preamble - 1; j++)
			{
				previous_numbers[j] = previous_numbers[j + 1];
			}
			previous_numbers[preamble - 1] = actual_number;
		}
	}

	input_file.close();
	return total_;
}

int answer_day9_puzzle2()
{
	answer_day9_puzzle1();

	int total_ = -1;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day9_input.txt");
	if (input_file.is_open())
	{
		total_ = 0;
		std::vector<int> continuous_range;
		int start_line = 0;
		std::string line;
		int actual_number = 0;
		bool range_found = false;
		while (true)
		{
			while (input_file >> line)
			{
				actual_number = std::stoi(line);
				total_ += actual_number;

				if (total_ == invalid_number)
				{
					continuous_range.push_back(actual_number);
					range_found = true;
					break;
				}
				else if (total_ > invalid_number)
				{
					break;
				}

				continuous_range.push_back(actual_number);
			}

			if (range_found)
			{
				int biggest = 0;
				unsigned int smallest = -1;
				for (size_t i = 0; i < continuous_range.size(); i++)
				{
					if (continuous_range[i] > biggest)
						biggest = continuous_range[i];
					if (continuous_range[i] < smallest)
						smallest = continuous_range[i];
				}
				total_ = biggest + smallest;
				break;
			}

			start_line++;
			input_file.clear();
			goto_line(input_file, start_line);
			continuous_range.clear();
			total_ = 0;
		}
	}

	input_file.close();
	return total_;
}