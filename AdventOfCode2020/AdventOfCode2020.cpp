// AdventOfCode2020.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Day1.h"
#include "Day2.h"
#include "Day3.h"
#include "Day4.h"
#include "Day5.h"

int main()
{
    std::cout << "Advent Of Code 2020 - NVriezen\n";
	std::cout << "Day 1 \t Puzzle 1: " << answer_day1_puzzle1() << "\t Puzzle 2: " << answer_day1_puzzle2() << "\n";
	std::cout << "Day 2 \t Puzzle 1: " << answer_day2_puzzle1() << "\t\t Puzzle 2: " << answer_day2_puzzle2() << "\n";
	std::cout << "Day 3 \t Puzzle 1: " << answer_day3_puzzle1() << "\t\t Puzzle 2: " << answer_day3_puzzle2() << "\n";
	std::cout << "Day 4 \t Puzzle 1: " << answer_day4_puzzle1() << "\t\t Puzzle 2: " << answer_day4_puzzle2() << "\n";
	std::cout << "Day 5 \t Puzzle 1: " << answer_day5_puzzle1() << "\t\t Puzzle 2: " << answer_day5_puzzle2() << "\n";
}
