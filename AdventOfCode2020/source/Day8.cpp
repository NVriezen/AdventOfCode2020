#include "..\include\Day8.h"

#include "..\include\StringParsing.h"
#include <vector>

#include "..\include\Day1.h"

enum OP
{
	NOP = 110,
	JMP = 106,
	ACC = 97,
};

int acc = 0;
int reg = 0;
int s = 0;

int answer_day8_puzzle1()
{
	int total_ = -1;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day8_input.txt");
	if (input_file.is_open())
	{
		total_ = 0;
		acc = 0;
		reg = 0;
		s = 0;
		std::string line;
		std::vector<int> executed_lines;
		while (getline(input_file, line))
		{
			// check for loop
			bool is_already_executed = false;
			for (size_t i = 0; i < executed_lines.size(); i++)
			{
				is_already_executed |= (executed_lines[i] == s);
			}

			if (is_already_executed)
			{
				break;
			}
			else
				executed_lines.push_back(s);

			// normal emulation
			s++;
			switch (line[0])
			{
			case NOP:
				break;
			case JMP:
				reg = std::stoi(line.substr(4, line.size() - 4));
				goto_line(input_file, s + reg);
				s += (reg - 1);
				break;
			case ACC:
				reg = std::stoi(line.substr(4, line.size() - 4));
				acc += reg;
				break;
			}
		}
	}
	total_ = acc;

	input_file.close();
	return total_;
}

int answer_day8_puzzle2()
{
	int total_ = -1;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day8_input.txt");
	if (input_file.is_open())
	{
		total_ = 0;
		acc = 0;
		reg = 0;
		s = 0;
		int s_to_fix = 0;
		std::string line;
		std::vector<int> executed_lines;
		while (getline(input_file, line))
		{
			// check for loop
			bool is_already_executed = false;
			for (size_t i = 0; i < executed_lines.size(); i++)
			{
				is_already_executed |= (executed_lines[i] == s);
			}

			std::string original_instruction = line;
			std::streampos original_file_position = input_file.tellg();
			int original_s = s;
			int original_acc = acc;
			int changed_s = 0;
			bool changed_op = false;
			if (is_already_executed)
			{
				/*total_ = acc;
				break;*/
				if (line[0] == NOP)
				{
					if (std::stoi(line.substr(4, line.size() - 4)) != 0)
					{
						line.replace(0, 3, "jmp");
						changed_op = true;
						changed_s = s;
					}
				}
				else if (line[0] == JMP)
				{
					line.replace(0, 3, "nop");
					changed_op = true;
					changed_s = s;
				}
			}
			else
				executed_lines.push_back(s);

			// normal emulation
			s++;
			switch (line[0])
			{
			case NOP:
				break;
			case JMP:
				reg = std::stoi(line.substr(4, line.size() - 4));
				goto_line(input_file, s + reg);
				s += (reg - 1);
				break;
			case ACC:
				reg = std::stoi(line.substr(4, line.size() - 4));
				acc += reg;
				break;
			}

			if (changed_op)
			{
				bool is_new_instruction = true;
				for (size_t i = 0; i < executed_lines.size(); i++)
				{
					is_new_instruction &= !(executed_lines[i] == s);
				}

				if (!is_new_instruction)
				{
					// revert it
					input_file.seekg(original_file_position);
					s = original_s + 1;
					acc = original_acc;
					switch (original_instruction[0])
					{
					case NOP:
						break;
					case JMP:
						reg = std::stoi(original_instruction.substr(4, original_instruction.size() - 4));
						goto_line(input_file, s + reg);
						s += (reg - 1);
						break;
					case ACC:
						reg = std::stoi(original_instruction.substr(4, original_instruction.size() - 4));
						acc += reg;
						break;
					}
				}
				else
				{
					s_to_fix = original_s;
				}
			}
		}

		acc = 0;
		reg = 0;
		s = 0;
		input_file.clear();
		input_file.seekg(std::ios::beg);
		while (getline(input_file, line))
		{
			// fix for file
			if (s == s_to_fix)
			{
				if (line[0] == NOP)
				{
					if (std::stoi(line.substr(4, line.size() - 4)) != 0)
					{
						line.replace(0, 3, "jmp");
					}
				}
				else if (line[0] == JMP)
				{
					line.replace(0, 3, "nop");
				}
			}

			// normal emulation
			s++;
			switch (line[0])
			{
			case NOP:
				break;
			case JMP:
				reg = std::stoi(line.substr(4, line.size() - 4));
				goto_line(input_file, s + reg);
				s += (reg - 1);
				break;
			case ACC:
				reg = std::stoi(line.substr(4, line.size() - 4));
				acc += reg;
				break;
			}
		}
	}
	total_ = acc;

	input_file.close();
	return total_;
}