#include "Day8.h"

/// 1. Extract vector's value and add to list of vectors
/// 2. When all vectors have been extracted, calculate distance from each one to the others
///		and keep the 10/1000 pairs with the shortest distances
/// 3. Use the list of pairs to create the circuits
/// 4. If neither box is in a circuit, create a new one with those two. If one is and the other isnt,
///		add the later to the same circuit as the former. If both are in different circuits, merge the circuits

/// @brief Function to sort list of pairs by distance in ascending order
/// @param p1 
/// @param p2 
/// @return 
bool comparePairs(Pair* p1, Pair* p2)
{
	return p1->length < p2->length;
}
/// @brief Sort sets by size (descending)
/// @param set1 
/// @param set2 
/// @return 
bool compareSets(const std::set<int>& set1, const std::set<int>& set2)
{
	return set1.size() > set2.size();
}

/// @brief Processes part 1
void Day8::processPart1()
{
	JunctionBox* box1;
	JunctionBox* box2;

	uint64_t distance = 0;

	//Check the distance between all pairs
	for (int i = 0; i < boxes.size(); i++)
	{
		box1 = boxes[i];

		for (int j = i + 1; j < boxes.size(); j++)
		{
			box2 = boxes[j];
			uint64_t distance = getSquareDistance(box1, box2);

			//Check against the list of shortest distances, keep if applies
			addToPairs(box1->id, box2->id, distance);
		}
	}
	//Sort lists
	std::sort(pairs.begin(), pairs.end(), comparePairs);
	std::sort(pairs2.begin(), pairs2.end(), comparePairs);

	//create circuits for part 1
	for (Pair* pair : pairs)
	{
		addToCircuits(pair->id1, pair->id2, circuits);
	}

	//Create circuit for part 2
	for (Pair* pair : pairs2)
	{
		if (addToCircuits(pair->id1, pair->id2, circuits2))
		{
			answer2 = boxes[pair->id1]->x * boxes[pair->id2]->x;
		}
	}

	std::sort(circuits.begin(), circuits.end(), compareSets);

	for (int i = 0; i < 3; i++)
	{
		answer1 *= circuits[i].size();
	}
}

/// @brief Given two vectors it tries to add the edge between them to the list of the shortest edges
/// @param idBox1 
/// @param idBox2 
/// @param length 
void Day8::addToPairs(int idBox1, int idBox2, uint64_t length)
{
	Pair* pair = new Pair();
	pair->id1 = idBox1;
	pair->id2 = idBox2;
	pair->length = length;

	//Add to list of pairs for part 2
	pairs2.push_back(pair);

	//If max size of shortest lengths hasnt been filled, add
	if (pairs.size() < pairsToKeep)
	{
		pairs.push_back(pair);
	}
	//Else replace highest distance pair with the current if lower
	else
	{
		if (length < pairs[highestDistanceIndex]->length)
		{
			pairs[highestDistanceIndex]->id1 = idBox1;
			pairs[highestDistanceIndex]->id2 = idBox2;
			pairs[highestDistanceIndex]->length = length;
		}
	}
	//Update index of the largest pair in order to facilitate modification
	for (int i = 0; i < pairs.size(); i++)
	{
		if (pairs[i]->length > pairs[highestDistanceIndex]->length)
		{
			highestDistanceIndex = i;
		}
	}
}

/// @brief Given the id of two vectors it tries to add them to the circuits
/// @param idBox1 
/// @param idBox2 
/// @return bool Indicates if a new connection was made
bool Day8::addToCircuits(int idBox1, int idBox2, std::vector<std::set<int>>&sets)
{
	int idCircuit1 = -1;
	int idCircuit2 = -1;

	//Find if the jolt boxes exist in a circuit already
	for (int i = 0; i < sets.size(); i++)
	{
		if (sets[i].count(idBox1))
		{
			idCircuit1 = i;
		}
		if (sets[i].count(idBox2))
		{
			idCircuit2 = i;
		}
	}

	//If either box isnt in any circuit
	if (idCircuit1 == -1 || idCircuit2 == -1)
	{
		//If neither is in any circuit, create new one
		if (idCircuit1 == idCircuit2)
		{
			std::set<int> newCircuit = { idBox1, idBox2 };
			sets.push_back(newCircuit);
		}
		//Else add the circuit without a circuit into the circuit that contains the other one.
		else if (idCircuit1 == -1)
		{
			sets[idCircuit2].insert(idBox1);
		}
		else
		{
			sets[idCircuit1].insert(idBox2);
		}

		return true;
	}
	//Otherwise if both are in a set but different ones, merge sets
	else if(idCircuit1 != idCircuit2)
	{
		sets[idCircuit1].insert(sets[idCircuit2].begin(), sets[idCircuit2].end());
		sets.erase(sets.begin() + idCircuit2);

		return true;
	}

	//if they're already in the same circuit, do nothing
	//Since no connection is made, return false
	return false;
}

/// @brief Squared euclidean distance
/// @param box1 
/// @param box2 
/// @return 
uint64_t Day8::getSquareDistance(JunctionBox* box1, JunctionBox* box2)
{
	//Since they're all unsigned, pick the order of operations to avoid underflow
	uint64_t x = 0;
	if (box1->x < box2->x)
	{
		x = (box2->x) - (box1->x);
	}
	else
	{
		x = (box1->x) - (box2->x);
	}

	uint64_t y = 0;
	if (box1->y < box2->y)
	{
		y = (box2->y) - (box1->y);
	}
	else
	{
		y = (box1->y) - (box2->y);
	}

	uint64_t z = 0;
	if (box1->z < box2->z)
	{
		z = (box2->z) - (box1->z);
	}
	else
	{
		z = (box1->z) - (box2->z);
	}

	return (x * x) + (y * y) + (z * z);
}

/// @brief Extract positions from input
/// @param input 
void Day8::passInputLine(std::string input)
{
	JunctionBox* box = new JunctionBox();
	int val = 0;
	std::string number;

	for (char c : input)
	{
		if (c == ',')
		{
			if (val == 0)
			{
				box->x = stringToUint64(number);
			}
			else if (val == 1)
			{
				box->y = stringToUint64(number);
			}
			number.clear();
			val++;
		}
		else
		{
			number += c;
		}
	}
	box->z = stringToUint64(number);
	box->id = boxes.size();

	boxes.push_back(box);
}

void Day8::printAnswer()
{
	processPart1();

	/*for (Pair* pair : pairs)
	{
		JunctionBox* box1 = boxes[pair->id1];
		JunctionBox* box2 = boxes[pair->id2];

		std::cout << box1->x << ", " << box1->y << ", " << box1->z << " -> ";
		std::cout << box2->x << ", " << box2->y << ", " << box2->z << " : " << pair->length << std::endl;
	}
	for (std::set<int> circuit : circuits)
	{
		
		std::cout << " : " << circuit.size() << " : ";
		for (int i : circuit)
		{
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}*/

	std::cout << "Answer to part 1: " << answer1 << std::endl;
	std::cout << "Answer to part 2: " << answer2 << std::endl;
}
