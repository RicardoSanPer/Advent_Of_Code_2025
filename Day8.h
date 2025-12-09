#pragma once
#include "Problem.h"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

//Struct to hold information about a junction box
struct JunctionBox
{
	uint64_t x;
	uint64_t y;
	uint64_t z;

	int id;
};

//Struct to hold information about pairs
struct Pair
{
	int id1;
	int id2;

	uint64_t length = UINT64_MAX;
};

class Day8 : public Problem
{
	std::vector<JunctionBox*> boxes;
	std::vector<Pair*> pairs;
	std::vector<std::set<int>> circuits;

	int highestDistanceIndex = 0;
	int pairsToKeep = 1000;

	uint64_t answer1 = 1;

	void processPart1();
	void addToPairs(int idBox1, int idBox2, uint64_t length);
	void addToCircuits(int idBox1, int idBox2);

	uint64_t getSquareDistance(JunctionBox* box1, JunctionBox* box2);

	void passInputLine(std::string input) override;
	void printAnswer() override;
};

