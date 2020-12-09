#include "..\include\Day7.h"

#include "..\include\StringParsing.h"
#include <vector>
#include <regex>

std::string get_bag_name(std::string input)
{
	size_t index = input.find("bags");
	return input.substr(0, index - 1);
}

bool check_bag_contains(std::string input, std::string should_contain)
{
	std::string bag_name = get_bag_name(input);
	std::smatch m;
	std::regex e("(" + should_contain + ")");
	std::regex_search(input, m, e);
	return m.size() > 0;
}

std::vector<std::string> bags_to_add(std::string input, int* total_bag_count, int multiplier)
{
	//std::string bag_name = get_bag_name(input);
	int bag_count = 0;
	size_t index = input.find("bags");
	std::string contains_string = input.substr(index + 5, input.size());
	std::vector<std::string> bag_types_found;
	std::smatch m;
	std::regex e("([0-9])");
	int counter = 0;
	while (std::regex_search(contains_string, m, e)) 
	{
		counter++;
		std::string bag_type = m.str(0) + std::string(m.suffix());
		size_t index = std::string(m.suffix()).find("bag");
		std::string first_char = m[0];
		if (first_char[0] > 57)
		{
			bag_count++;
			continue;
		}

		int bags_to_add = std::stoi(first_char);
		bag_count += bags_to_add;
		bag_types_found.push_back(std::to_string(bags_to_add * multiplier) + bag_type.substr(1, index - 1));
		
		contains_string = m.suffix(); 
	}

	(*total_bag_count) += bag_count * multiplier;
	return bag_types_found;
}

int answer_day7_puzzle1()
{
	int total_bags = -1;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day7_input.txt");
	if (input_file.is_open())
	{
		total_bags = 0;
		std::string line;
		std::vector<std::string> contains_gold_bag;
		contains_gold_bag.push_back("shiny gold");
		for (size_t i = 0; i < contains_gold_bag.size(); i++)
		{
			while (getline(input_file, line))
			{
				if (check_bag_contains(line, contains_gold_bag[i]))
				{
					std::string bag_name = get_bag_name(line);
					auto it = std::find(contains_gold_bag.begin(), contains_gold_bag.end(), bag_name);
					if (it == contains_gold_bag.end())
					{
						total_bags++;
						contains_gold_bag.push_back(bag_name);
					}
				}
			}
			input_file.clear();
			input_file.seekg(std::ios::beg);
		}
	}

	input_file.close();
	return total_bags;
}

int answer_day7_puzzle2()
{
	int total_bags = -1;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day7_input.txt");
	if (input_file.is_open())
	{
		total_bags = 0;
		std::string line;
		std::vector<std::string> contains_gold_bag;
		contains_gold_bag.push_back("1 shiny gold");
		for (size_t i = 0; i < contains_gold_bag.size(); i++)
		{

			std::smatch m;
			std::regex e("([0-9]{0,9999})");
			std::regex_search(contains_gold_bag[i], m, e);
			int multiplier = std::stoi(m.str(0));//std::stoi(contains_gold_bag[i].substr(0, 1));
			std::string bag_to_find = m.suffix();
			bag_to_find = bag_to_find.substr(1, bag_to_find.size() - 1);
			while (getline(input_file, line))
			{
				std::string bag_name = get_bag_name(line);
				if (bag_name == bag_to_find)
				{
					std::vector<std::string> bags = bags_to_add(line, &total_bags, multiplier);
					for (size_t j = 0; j < bags.size(); j++)
					{
						contains_gold_bag.push_back(bags[j]);
					}
					break;
				}
			}
			input_file.clear();
			input_file.seekg(std::ios::beg);
		}
	}

	input_file.close();
	return total_bags;
}