#include "Day4.h"

#include <iostream>
#include <fstream>
#include <string>
#include <ios>

struct passport
{
	std::string byr = "byr";
	std::string iyr = "iyr";
	std::string eyr = "eyr";
	std::string hgt = "hgt";
	std::string hcl = "hcl";
	std::string ecl = "ecl";
	std::string pid = "pid";
	std::string cid = "cid";
	int fields_filled;
	static const int fields_max = 8;
};

passport get_valid_passport(std::ifstream& input, bool cid_optional)
{
	std::string line;
	passport found_passport;
	int counter = 0;
	while (getline(input, line) && line != "")
	{
		std::string lines_to_check[found_passport.fields_max];
		int lines_count = 0;
		int start_index = 0;
		for (size_t i = 0; i < line.size(); i++)
		{
			if (line[i] == ' ')
			{
				lines_to_check[lines_count] = line.substr(start_index, i - start_index);
				start_index = i + 1;
				lines_count++;
			}
		}
		lines_to_check[lines_count] = line.substr(start_index, line.size() - start_index);
		lines_count++;

		for (size_t i = 0; i < lines_count; i++)
		{
			for (size_t j = 0; j < found_passport.fields_max; j++)
			{
				if (lines_to_check[i].substr(0, 3) == (&found_passport.byr)[j])
				{
					lines_to_check[i].replace(0, 4, "");
					(&found_passport.byr)[j] = lines_to_check[i];
					counter++;
					break;
				}
			}
		}

		if (input.eof())
			break;
	}
	found_passport.fields_filled = counter;

	return found_passport;
}

bool check_year(std::string input, int min, int max)
{
	int year = std::stoi(input);
	return (year >= min && year <= max);
}

bool check_hgt(std::string input)
{
	std::string end = input.substr(input.size() - 2, 2);
	int number = 0;
	if (end == "cm")
	{
		for (size_t i = 0; i < input.size() - 2; i++)
		{
			if (input[i] < 48 || input[i] > 57)
				return false;
		}
		number = std::stoi(input.substr(0, input.size() - 2));
		return number >= 150 && number <= 193;
	}

	if (end != "in")
		return false;

	for (size_t i = 0; i < input.size() - 2; i++)
	{
		if (input[i] < 48 || input[i] > 57)
			return false;
	}
	number = std::stoi(input.substr(0, input.size() - 2));
	return number >= 59 && number <= 76;
}

bool check_hcl(std::string input)
{
	if (input.size() < 7 || input.size() > 7)
		return false;
	
	if (input[0] != '#')
		return false;

	for (size_t i = 1; i < input.size(); i++)
	{
		if (input[i] < 48 || input[i] > 102 || (input[i] < 97 && input[i] > 57))
			return false;
	}
	return true;
}

std::string correct_eye_color[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
const int max_eye_color = 7;
bool check_ecl(std::string input)
{
	for (size_t i = 0; i < max_eye_color; i++)
	{
		if (input == correct_eye_color[i])
			return true;
	}
	return false;
}

bool check_pid(std::string input)
{
	if (input.size() != 9)
		return false;

	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] < 48 || input[i] > 57)
			return false;
	}
	return true;
}

bool check_fields_input(passport input, bool strict, bool cid_optional)
{
	if (!strict)
		return true;
	
	bool non_valid = false;
	non_valid |= !check_year(input.byr, 1920, 2002);
	non_valid |= !check_year(input.iyr, 2010, 2020);
	non_valid |= !check_year(input.eyr, 2020, 2030);
	non_valid |= !check_hgt(input.hgt);
	non_valid |= !check_hcl(input.hcl);
	non_valid |= !check_ecl(input.ecl);
	non_valid |= !check_pid(input.pid);

	return !non_valid;
}

bool passport_valid(passport input, bool strict, bool cid_optional)
{
	if (cid_optional)
	{
		if (input.fields_filled == input.fields_max)
			return check_fields_input(input, strict, cid_optional);
		else if (input.fields_filled <= input.fields_max - 2)
			return false;
		if (input.cid.substr(0,3) == "cid")
			return check_fields_input(input, strict, cid_optional);
		return false;
	}

	if (input.fields_filled == input.fields_max)
		return check_fields_input(input, strict, cid_optional);
	return false;
}

int answer_day4_puzzle1()
{
	int valid_passports = -1;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day4_input.txt");
	if (input_file.is_open())
	{
		valid_passports = 0;
		while (true)
		{
			passport pass = get_valid_passport(input_file, true);
			valid_passports += passport_valid(pass, false, true);
			if (input_file.eof())
				break;
		}
	}

	input_file.close();
	return valid_passports;
}

int answer_day4_puzzle2()
{
	int valid_passports = -1;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day4_input.txt");
	if (input_file.is_open())
	{
		valid_passports = 0;
		while (true)
		{
			passport pass = get_valid_passport(input_file, true);
			valid_passports += passport_valid(pass, true, true);
			if (input_file.eof())
				break;
		}
	}

	input_file.close();
	return valid_passports;
}