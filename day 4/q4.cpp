#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> grids;
std::vector<std::vector<int>> adjacency;


void Parse(const char* filename)
{
	std::fstream fs;
	fs.open(filename);

	while (1)
	{
		std::string inputStr;
		fs >> inputStr;
		
		if (fs.eof())
			break;

		grids.emplace_back(inputStr);
	}

	fs.close();

	for (size_t i = 0; i < grids.size(); ++i)
	{
		std::cout << grids[i] << "\n";
	}

	for (size_t i = 0; i < grids.size(); ++i)
	{
		adjacency.emplace_back(std::vector<int>(grids[i].size(), 0));
	}
}

// Count how many adjacent roll of papers
void CalculateAdjacency()
{
	// Each row
	for (size_t i = 0; i < adjacency.size(); ++i)
	{
		// Each column
		for (size_t j = 0; j < adjacency[i].size(); ++j)
		{
			if (grids[i][j] == '.')
				continue;

			// Check right
			if (j < adjacency[i].size() - 1 && grids[i][j+1] == '@')
			{
				++(adjacency[i][j]);
				++(adjacency[i][j+1]);
			}	

			// Check bottom right
			if (j < adjacency[i].size() - 1 && i < adjacency.size() - 1 && grids[i+1][j+1] == '@')
			{
				++(adjacency[i][j]);
				++(adjacency[i+1][j+1]);
			}
			
			// Check bottom
			if (i < adjacency.size() - 1 && grids[i+1][j] == '@')
			{
				++(adjacency[i][j]);
				++(adjacency[i+1][j]);
			}	

			// Check bottom left
			if (j > 0 && i < adjacency.size() - 1 && grids[i+1][j-1] == '@')
			{
				++(adjacency[i][j]);
				++(adjacency[i+1][j-1]);
			}	
			
		}
	}

	// Each row
	for (size_t i = 0; i < adjacency.size(); ++i)
	{
		// Each column
		for (size_t j = 0; j < adjacency[i].size(); ++j)
		{
			std::cout << adjacency[i][j];
		}
		std::cout << "\n";
	}
}

// Count how many rolls of papers that only have 4 or less adjacency
int Tally()
{
	int total = 0;

	// Each row
	for (size_t i = 0; i < adjacency.size(); ++i)
	{
		// Each column
		for (size_t j = 0; j < adjacency[i].size(); ++j)
		{
			if (grids[i][j] == '@' && adjacency[i][j] < 4)
			{
				++total;
				// Convert it to empty space
				grids[i][j] = '.';	
			}
		}
	}

	std::cout << "Total rolls of papers for current iteration: " << total << "\n";
	return total;
}

void ResetAdjacencyCounter()
{
	for (size_t i = 0; i < adjacency.size(); ++i)
	{
		for (size_t j = 0; j < adjacency[i].size(); ++j)
		{
			adjacency[i][j] = 0;
		}
	}
}


int main(int argc, char** argv)
{
	if (argc < 2)
		return 1;

	Parse(argv[1]);
	
	int total = 0;
	while (true)
	{
		CalculateAdjacency();
		int subtotal = Tally();

		// No more wrapping papers can be obtained
		if (subtotal == 0)
			break;
		total += subtotal;

		ResetAdjacencyCounter();
	}

	std::cout << "Total rolls of papers: " << total << "\n";
}