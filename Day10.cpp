#include "Day10.h"

void Day10::passInputLine(std::string input)
{
	Machine machine ;

	bool isLight = false;
	bool isButton = false;
	bool isJoltage = false;

	std::string number;
	std::vector<int> button;
	for (char c : input)
	{
		//Extract light config
		if (c == '[')
		{
			isLight = true;
			continue;
		}
		if (c == ']')
		{
			isLight = false;
			continue;
		}
		
		//Extract buttons
		if (c == '(')
		{
			isButton = true;
			continue;
		}
		if (c == ')')
		{
			isButton = false;
			button.push_back(stringToInt(number));
			machine.buttons.push_back(button);

			button.clear();
			number.clear();

			continue;
		}

		//Extract joltage
		if (c == '{')
		{
			isJoltage = true;
			continue;
		}
		if (c == '}')
		{
			machine.joltage += stringToInt(number);
			number.clear();
			isJoltage = false;
			continue;
		}

		if (isLight)
		{
			machine.lights += c;
		}

		if (isButton || isJoltage)
		{
			if (c == ',')
			{
				if (isButton)
				{
					button.push_back(stringToInt(number));
				}
				else if (isJoltage)
				{
					machine.joltage += stringToInt(number);
				}
				number.clear();
				continue;
			}
			number += c;
		}
	}

	machines.push_back(machine);
}

void Day10::processPart1()
{
	
	bool found = false;
	for (Machine machine : machines)
	{
		//Create starting position. All lights turned off and 0 buttons pressed
		std::queue<std::tuple<std::string, int>> queue;
		std::string n(machine.lights.size(), '.');

		std::set<std::string> visited;

		queue.push({ n, 0 });
		visited.insert(n);

		//printMachine(machine);

		//While the desired config isnt found
		while (!found)
		{
			std::tuple<std::string, int> front = queue.front();

			//Apply all buttons to the current combination
			for (std::vector<int> button : machine.buttons)
			{
				//Copy string to modify
				std::string mod(std::get<0>(front));
				int depth = std::get<1>(front);

				//Switch lights
				for (int i : button)
				{
					if (mod[i] == '.')
					{
						mod[i] = '#';
					}
					else if (mod[i] == '#')
					{
						mod[i] = '.';
					}
				}
				//If we get the desired config
				if (mod.compare(machine.lights) == 0)
				{
					found = true;
					answer1 += depth + 1;
					break;
				}
				else
				{
					//If it is a combination seen before already, skip adding it to the queue
					//to avoid revisiting it
					if (visited.find(mod) == visited.end())
					{
						queue.push({ mod, depth + 1 });
						visited.insert(mod);
					}
				}
			}
			queue.pop();
		}
		found = false;
	}
}

void Day10::processPart2()
{

	bool found = false;

	int completed = 0;

	for (Machine machine : machines)
	{
		std::cout << "Completed " << completed << " out of " << machines.size() << std::endl;

		//Create starting position. All lights turned off and 0 buttons pressed
		std::queue<std::tuple<std::string, int>> queue;
		std::string n(machine.lights.size(), 0);

		std::set<std::string> visited;

		queue.push({ n, 0 });
		visited.insert(n);

		//printMachine(machine);

		//While the desired config isnt found
		while (!found)
		{
			std::tuple<std::string, int> front = queue.front();


			//Apply all buttons to the current combination
			for (std::vector<int> button : machine.buttons)
			{
				//Copy string to modify
				std::string mod(std::get<0>(front));
				int depth = std::get<1>(front);

				bool valid = true;

				//Switch lights
				for (int i : button)
				{
					mod[i] = mod[i] + 1;
					if (mod[i] > machine.joltage[i])
					{
						valid = false;
						break;
					}
				}
				if (!valid)
				{
					continue;
				}
				//If we get the desired config
				if (mod.compare(machine.joltage) == 0)
				{
					found = true;
					answer2 += depth + 1;
					break;
				}
				else
				{
					//if combination never seen before, add to queue and viewed combinations
					if (visited.find(mod) == visited.end())
					{
						queue.push({ mod, depth + 1 });
						visited.insert(mod);
					}
				}
			}
			queue.pop();
		}
		found = false;
		completed++;
	}
}

void Day10::printMachine(Machine machine)
{
	std::cout << '[' << machine.lights << "] ";

	for (std::vector<int> button : machine.buttons)
	{
		std::cout << '(';
		for (int val : button)
		{
			std::cout << val << ' ';
		}
		std::cout << '\b' << ") ";
	}

	std::cout << " {";
	for (int j : machine.joltage)
	{
		std::cout << (int)j << ' ';
	}
	std::cout << '\b' << "}";

	std::cout << std::endl;
}

void Day10::printAnswer()
{
	processPart1();
	std::cout << "Answer to part 1: " << answer1 << std::endl;

	processPart2();
	std::cout << "Answer to part 2: " << answer2 << std::endl;
}
