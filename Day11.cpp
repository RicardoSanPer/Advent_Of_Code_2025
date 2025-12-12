#include "Day11.h"

void Day11::passInputLine(std::string input)
{
	Node* node = nullptr;
	std::string s;

	bool isId = true;
	for (char c : input)
	{
		//Pass on node ID
		if (c == ':')
		{
			isId = false;
			//If the node was already created as the chil of another, do nothing
			if (nodes.find(s) != nodes.end())
			{
				node = nodes[s];
			}
			//else create the new node, pass the id and add to set
			else
			{
				node = new Node();
				node->id = s;
				nodes.insert({ s, node });
			}
			s.clear();
		}
		else if (c == ' ' && !s.empty())
		{
			//Add id as child of node
			node->children.push_back(s);
			updateChildNodeParent(node->id, s);
			s.clear();
		}
		else if (c == ' ')
		{
			continue;
		}
		else
		{
			s += c;
		}
	}
	if (node != nullptr)
	{
		node->children.push_back(s);
		updateChildNodeParent(node->id, s);
	}
}

void Day11::processPart1(std::string root)
{
	traverseTree(nodes[root]);
}

void Day11::processPart2(std::string root)
{
	traverseTreePart2(nodes[root]);
	answer2 = visited[root];
}

void Day11::propagatePart2(std::string root)
{
	//First propagate dac and fft
	std::set<std::string> visited;
	std::queue<std::string> nodesToVisit;

	Node* node = nodes[root];

	//Mark dac and fft
	if (root.compare("dac") == 0)
	{
		node->dac = true;
	}
	else if (root.compare("fft") == 0)
	{
		node->fft = true;
	}

	//dac
	for (std::string child : node->children)
	{
		nodesToVisit.push(child);
	}

	visited.insert(root);
	std::string id;

	//Propagate downwards
	while (!nodesToVisit.empty())
	{
		id = nodesToVisit.front();
		nodesToVisit.pop();

		if (id.compare("out") == 0)
		{
			continue;
		}

		node = nodes[id];

		//Flag it as dac or fft
		if (root.compare("dac") == 0)
		{
			node->dac = true;
		}
		else if (root.compare("fft") == 0)
		{
			node->fft = true;
		}

		visited.insert(id);
		for (std::string child : node->children)
		{
			//If child has not been visited, add to list of nodes to visit
			if (visited.find(child) == visited.end())
			{
				nodesToVisit.push(child);
				visited.insert(child);
			}
		}

	}
	visited.clear();

	node = nodes[root];
	visited.insert(root);
	id.clear();

	for (std::string parent : node->parents)
	{
		nodesToVisit.push(parent);
	}

	//Propagate upwards
	while (!nodesToVisit.empty())
	{
		id = nodesToVisit.front();
		nodesToVisit.pop();

		if (id.compare("svr") == 0)
		{
			continue;
		}

		node = nodes[id];

		//Flag it as dac or fft
		if (root.compare("dac") == 0)
		{
			node->dac = true;
		}
		else if (root.compare("fft") == 0)
		{
			node->fft = true;
		}

		visited.insert(id);
		for (std::string parent : node->parents)
		{
			//If parent has not been visited, add to list of nodes to visit
			if (visited.find(parent) == visited.end())
			{
				nodesToVisit.push(parent);
				visited.insert(parent);
			}
		}
	}
}

void Day11::updateChildNodeParent(std::string parent, std::string child)
{	
	//If child node doesnt exist in the list of nodes, create it first
	if (nodes.find(child) == nodes.end())
	{
		Node* newnode = new Node();
		newnode->id = child;
		nodes.insert({ child, newnode });
	}
	//add to list of parents
	nodes[child]->parents.push_back(parent);
}

void Day11::traverseTree(Node* node)
{
	for (std::string child : node->children)
	{
		//std::cout << node->id << "->" << child << std::endl;
		if (child.compare("out") == 0)
		{
			answer1++;
			continue;
		}
		traverseTree(nodes[child]);
	}
}

void Day11::traverseTreePart2(Node* node)
{
	Node* childNode;
	visited[node->id] = 0;

	for (std::string child : node->children)
	{
		if (child.compare("out") == 0)
		{
			visited[node->id]++;
			continue;
		}
		childNode = nodes[child];

		//If child is part of a path that goes throug fft and dac and hasnt been visited
		if (childNode->fft && childNode->dac && visited.find(child) == visited.end())
		{
			traverseTreePart2(childNode);
		}
		//Add counter of the child to the current node
		visited[node->id] += visited[child];
	}
}

void Day11::printAnswer()
{
	processPart1("you");
	std::cout << "Answer to part 1: " << answer1 << std::endl;

	propagatePart2("dac");
	std::cout << "Propagated dac" << std::endl;
	propagatePart2("fft");
	std::cout << "Propagated fft" << std::endl;
	processPart2("svr");
	std::cout << "Answer to part 2: " << answer2 << std::endl;

	/*for (std::pair<std::string, Node*> it : nodes)
	{
		Node* node = it.second;

		if (!node->dac || !node->fft)
		{
			continue;
		}

		std::cout << it.first << " \n\tChildren: ";
		for (std::string s : node->children)
		{
			std::cout << s << " ";
		}
		std::cout << " \n\tParent: ";
		for (std::string s : node->parents)
		{
			std::cout << s << " ";
		}
		std::cout << std::endl;
	}*/

}
