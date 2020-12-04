#include "Day2.h"

#include <iostream>
#include <fstream>
#include <string>

std::string* custom_line_split(std::ifstream& input)
{
	std::string* split_string = new std::string[4];
	split_string[0] = "";
	while (input.peek() != '-')
	{
		split_string[0] += input.get();
	}

	input.ignore(1);
	while (input.peek() != ' ')
	{
		split_string[1] += input.get();
	}
	input.ignore(1);
	split_string[2] = input.get();
	input.ignore(2);
	while (input.peek() != '\n')
	{
		split_string[3] += input.get();
	}
	input.ignore(1);

	return split_string;
}

std::string* custom_string_line_split(std::string& input)
{
	std::string* split_string = new std::string[2];

	int i = 0;
	while (input[i] != '-')
	{
		split_string[0] += input[i];
		i++;
	}

	i++; //skip '-'
	while (i < input.size())
	{
		split_string[1] += input[i];
		i++;
	}

	return split_string;
}

int answer_day2_puzzle1()
{
	int total_correct_passwords = -1;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day2_input.txt");
	if (input_file.is_open())
	{
		total_correct_passwords = 0;
		std::string string_to_check;
		std::string part_of_line;
		while (input_file >> part_of_line)
		{
			std::string* strings = custom_string_line_split(part_of_line);
			if (strings == nullptr)
				break;
			int minimalCount = std::stoi(strings[0]);
			int maximumCount = stoi(strings[1]);
			delete[] strings;
			input_file >> part_of_line;
			input_file >> string_to_check;
			int total_character_found = 0;
			for (size_t i = 0; i < string_to_check.size(); i++)
			{
				if (string_to_check[i] == part_of_line[0])
				{
					total_character_found++;
				}
			}

			if (total_character_found >= minimalCount && total_character_found <= maximumCount)
			{
				++total_correct_passwords;
			}
		}
	}

	input_file.close();
	return total_correct_passwords;
}

int answer_day2_puzzle2()
{
	int total_correct_passwords = -1;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day2_input.txt");
	if (input_file.is_open())
	{
		total_correct_passwords = 0;
		std::string string_to_check;
		std::string part_of_line;
		while (input_file >> part_of_line)
		{
			std::string* strings = custom_string_line_split(part_of_line);
			if (strings == nullptr)
				break;
			int firstPosition = std::stoi(strings[0]);
			int secondPosition = stoi(strings[1]);
			delete[] strings;
			input_file >> part_of_line;
			input_file >> string_to_check;
			int total_character_found = 0;
			if (firstPosition > string_to_check.size())
				continue;
			if (string_to_check[firstPosition - 1] == part_of_line[0])
			{
				total_character_found++;
			}
			if (secondPosition <= string_to_check.size() && string_to_check[secondPosition - 1] == part_of_line[0])
			{
				total_character_found++;
			}

			if (total_character_found == 1)
			{
				++total_correct_passwords;
			}
		}
	}

	input_file.close();
	return total_correct_passwords;
}