#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

struct Range
{
	uint64_t lower;
	uint64_t upper;
};




int main(int argc, char** argv)
{
	if (argc < 2)
		return 1;

	// Read the file and load the data
	std::vector<Range> list;
	list.reserve(500);

	std::fstream fs;
	std::stringstream ss;
	
	fs.open(argv[1]);
	std::string inputStr;
	fs >> inputStr;
	ss.str(inputStr);

	while(1)
	{
		Range range;
		ss >> range.lower;
		ss.get();			// Discards the '-'
		ss >> range.upper;
		list.emplace_back(range);
		ss.get();			// Discards the ','

		// std::cout << range.lower << " " << range.upper << "\n";
		if (ss.eof())
			break;
	}

	fs.close();


	
	// Check numbers that are invalid
	uint64_t total = 0;

#if 0
	// Part 1
	// For each range
	for (const Range& r : list)
	{
		// For each number in the range
		for (uint64_t currNum = r.lower; currNum <= r.upper; ++currNum)
		{
			std::string numberAsString = std::to_string(currNum);

			// If currNum has odd number of digit we don't have to check
			if (numberAsString.size() % 2 == 1)
				continue;

			std::string leftHalf = numberAsString.substr(0, numberAsString.size() / 2);
			std::string rightHalf = numberAsString.substr(numberAsString.size() / 2);
			
			if (leftHalf == rightHalf)
			{
				std::cout << "Invalid: " << currNum << "\n";
				total += currNum;
			}	
		}
	}
#endif 

#if 1
	// Part 2
	// For each range
	for (const Range& r : list)
	{
		// For each number in the range
		for (uint64_t currNum = r.lower; currNum <= r.upper; ++currNum)
		{
			std::string numberAsString = std::to_string(currNum);
			
			// Substring size
			for (size_t i = 1; i <= numberAsString.size() / 2; ++i)
			{
				std::string firstSubstr = numberAsString.substr(0, i);
				std::vector<bool> substrSame;							// In each substr, is it same as the first one?

				// Where to start to substring
				for (size_t j = 0; j < numberAsString.size(); j += i)
				{
					std::string substrToTest = numberAsString.substr(j, i);
					
					// Check whether firstSubstr is the same as the substrToTest
					substrSame.push_back(firstSubstr == substrToTest);
				}

				// Go through all the subStrSame bool, if all are true, then it's invalid number
				if (std::all_of(substrSame.begin(), substrSame.end(), [](bool b){ return b; }))
				{
					std::cout << "Invalid: " << currNum << "\n";
					total += currNum;
					break;
				}
			}

		}
	}
#endif
	std::cout << "Total: " << total << "\n";
}