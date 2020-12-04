#include "Day3.h"

#include <iostream>
#include <fstream>
#include <string>

#include "Day1.h"

int x_position = 0;
int y_position = 1;
int end_of_slope = 0;

int get_line_size_without_spaces(std::ifstream& input)
{
	std::streampos current_position = input.tellg();
	input.clear();
	input.seekg(std::ios::beg);
	std::string line;
	input >> line;
	input.seekg(current_position);
	return line.size();
}

int take_step(std::ifstream& input, int x_delta, int y_delta, int pattern_width)
{
	x_position += x_delta;
	y_position += y_delta;
	goto_line(input, y_position);
	int character_to_check = x_position % pattern_width;
	std::string line;
	if (!(input >> line))
	{
		end_of_slope = 1;
		return 0;
	}
	if (line[character_to_check] == '#')
		return 1;
	return 0;
}

int answer_day3_puzzle1()
{
	int total_trees_encountered = -1;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day3_input.txt");
	if (input_file.is_open())
	{
		total_trees_encountered = 0;
		int pattern_width = get_line_size_without_spaces(input_file);
		while (end_of_slope == 0)
		{
			total_trees_encountered += take_step(input_file, 3, 1, pattern_width);
		}
	}

	input_file.close();
	return total_trees_encountered;
}

struct vector2
{
	int x;
	int y;
};

vector2 slopes[] = { vector2{1, 1}, vector2{3, 1}, vector2{5, 1}, vector2{7, 1}, vector2{1, 2} };
int total_slopes = 5;

int answer_day3_puzzle2()
{
	int total_trees_encountered = -1;
	int answer = 1;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day3_input.txt");
	if (input_file.is_open())
	{
		total_trees_encountered = 0;
		int pattern_width = get_line_size_without_spaces(input_file);
		for (size_t i = 0; i < total_slopes; i++)
		{
			while (end_of_slope == 0)
			{
				total_trees_encountered += take_step(input_file, slopes[i].x, slopes[i].y, pattern_width);
			}
			answer *= total_trees_encountered;
			end_of_slope = 0;
			input_file.clear();
			input_file.seekg(std::ios::beg);
			x_position = 0;
			y_position = 1;
			total_trees_encountered = 0;
		}
	}

	input_file.close();
	return answer;
}