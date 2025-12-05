#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

struct Range
{
	uint64_t lower;
	uint64_t upper;
};

std::vector<Range> ranges;
std::vector<uint64_t> ids;


void Parse(const char* filename)
{
	ranges.reserve(1100);
	ids.reserve(100);

	std::fstream fs;
	fs.open(filename);

	// Parse the ranges
	while (1)
	{
		std::string inputStr;
		fs >> inputStr;

		if (fs.eof())
			break;

		// If inputStr have '-' then it's parsing the range
		if (inputStr.find('-') != std::string::npos)
		{
			std::stringstream ss(inputStr);
			Range r;
			ss >> r.lower;
			ss.get();		// Flush the -
			ss >> r.upper;
			ranges.emplace_back(r);
			std::cout << "[" << r.lower << "," << r.upper << "]\n";
		}
		// Otherwise it's parsing the value
		else
		{
			ids.emplace_back(std::stoull(inputStr));
			std::cout << "ID: " << ids.back() << "\n";
		}
	}
	fs.close();
}

int CheckNumberOfFresh()
{
	int count = 0;

	for (uint64_t id : ids)
	{
		for (Range r : ranges)
		{
			if (id >= r.lower && id <= r.upper)
			{
				++count;
				break;
			}
		}
	}

	return count;
}

uint64_t Min(uint64_t a, uint64_t b)
{
	if (a < b) 
		return a;
	else
		return b;
}

uint64_t Max(uint64_t a, uint64_t b)
{
	if (a > b) 
		return a;
	else
		return b;
}

uint64_t MergeRange()
{
	std::vector<Range> mergedRange;
	mergedRange.reserve(100);
	
	// For each range
	for (Range r : ranges)
	{		
		// If only 0 elements in merged range, then just insert a new one
		if (mergedRange.size() == 0)
		{
			mergedRange.emplace_back(r);
			continue;
		}

		Range currProcessRange = r;

		// Go through all existing ranges
		for (int i = 0; i < mergedRange.size(); ++i)
		{
			// If got overlap
			if (currProcessRange.upper >= mergedRange[i].lower && currProcessRange.lower <= mergedRange[i].upper)
			{
				// Merge the range
				currProcessRange.lower = Min(currProcessRange.lower, mergedRange[i].lower);
				currProcessRange.upper = Max(currProcessRange.upper, mergedRange[i].upper);
				mergedRange.erase(mergedRange.begin() + i);
				i = -1;
			}
		}

		mergedRange.emplace_back(currProcessRange);
	}

	uint64_t totalFreshIDs = 0;
	for (Range r : mergedRange)
	{
		std::cout << "[" << r.lower << "," << r.upper << "]\n";
		totalFreshIDs += (r.upper - r.lower + 1);
	}
	return totalFreshIDs;
}


int main(int argc, char** argv)
{
	if (argc < 2)
		return 1;

	Parse(argv[1]);

	int count = CheckNumberOfFresh();
	std::cout << "Number of fresh ingredients: " << count << "\n";

	std::cout << "\nMerged Ranges:\n";
	uint64_t totalFreshIDs = MergeRange();
	std::cout << "Total fresh IDs: " << totalFreshIDs << "\n";
}