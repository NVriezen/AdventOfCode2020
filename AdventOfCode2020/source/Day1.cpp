#include "..\include\Day1.h"

#include "..\include\StringParsing.h"

std::ifstream& goto_line(std::ifstream& file, unsigned int line_position)
{
	file.seekg(std::ios::beg);
	for (size_t i = 0; i < line_position - 1; i++)
	{
		file.ignore(256, '\n');
	}
	return file;
}

int answer_day1_puzzle1()
{
	std::string line;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day1_input.txt");
	if (input_file.is_open())
	{
		int current_line = 0;
		int line_to_check_with = 0;
		int line_count = 0;
		while (input_file >> current_line)
		{
			line_count++;
			goto_line(input_file, line_count + 1);
			while (input_file >> line_to_check_with)
			{
				if (current_line + line_to_check_with == 2020)
				{
					input_file.close();
					return current_line * line_to_check_with;
				}
			}
			input_file.clear();
			goto_line(input_file, line_count + 1);
		}
	}
	
	input_file.close();
	return -1;
}

int answer_day1_puzzle2()
{
	std::string line;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day1_input.txt");
	if (input_file.is_open())
	{
		int current_line = 0;
		int line_to_check_with = 0;
		int final_line_to_check_with = 0;
		int line_count = 0;
		int second_line_count = 0;
		while (input_file >> current_line)
		{
			line_count++;
			goto_line(input_file, line_count + 1);
			while (input_file >> line_to_check_with)
			{
				second_line_count++;
				goto_line(input_file, line_count + second_line_count + 1);
				while (input_file >> final_line_to_check_with)
				{
					if (current_line + line_to_check_with + final_line_to_check_with == 2020)
					{
						input_file.close();
						return current_line * line_to_check_with * final_line_to_check_with;
					}
				}
				input_file.clear();
				goto_line(input_file, line_count + second_line_count + 1);
			}
			input_file.clear();
			second_line_count = 0;
			goto_line(input_file, line_count + 1);
		}
	}

	input_file.close();
	return -1;
}