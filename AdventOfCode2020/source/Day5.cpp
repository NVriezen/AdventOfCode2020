#include "..\include\Day5.h"

#include "..\include\StringParsing.h"

int max_rows = 127;
int max_columns = 7;

int get_seat_row(std::string input)
{
	int max_row = max_rows;
	int min_row = 0;
	for (size_t i = 0; i < 7; i++)
	{
		if (input[i] == 'F')
		{
			max_row -= ((max_row - min_row) / 2.0f) + 0.5f;
		}
		else {
			min_row += ((max_row - min_row) / 2.0f) + 0.5f;
		}
	}
	return min_row;
}

int get_seat_column(std::string input)
{
	int max_column = max_columns;
	int min_column = 0;
	for (size_t i = input.size() - 3; i < input.size(); i++)
	{
		if (input[i] == 'L')
		{
			max_column -= ((max_column - min_column) / 2.0f) + 0.5f;
		}
		else {
			min_column += ((max_column - min_column) / 2.0f) + 0.5f;
		}
	}
	return min_column;
}

int get_seat_id(std::string input)
{
	int row = get_seat_row(input);
	int column = get_seat_column(input);
	return row * 8 + column;
}

int answer_day5_puzzle1()
{
	int boarding_pass_id = -1;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day5_input.txt");
	if (input_file.is_open())
	{
		boarding_pass_id = 0;
		std::string line;
		while (input_file >> line)
		{
			int seat_id = get_seat_id(line);
			if (seat_id > boarding_pass_id)
				boarding_pass_id = seat_id;
		}
	}

	input_file.close();
	return boarding_pass_id;
}

int answer_day5_puzzle2()
{
	int boarding_pass_id = -1;
	std::ifstream input_file("D:/c++/repos/AdventOfCode2020/AdventOfCode2020/inputs/day5_input.txt");
	if (input_file.is_open())
	{
		boarding_pass_id = 0;
		std::string line;

		uint8_t seatGrid[128 * 8] = { 0 };

		while (input_file >> line)
		{
			int seat_id = get_seat_id(line);
			seatGrid[seat_id] += 1;
		}

		for (size_t i = 0; i < 128 * 8; i++)
		{
			if (seatGrid[i] == 0)
			{
				bool both_noeighbours_not_present = false;
				if (i > 0)
					both_noeighbours_not_present |= !seatGrid[i - 1];
				if (i < 128 * 8 - 1)
					both_noeighbours_not_present |= !seatGrid[i + 1];

				if (!both_noeighbours_not_present)
				{
					boarding_pass_id = i;
					break;
				}
			}
		}
	}

	input_file.close();
	return boarding_pass_id;
}