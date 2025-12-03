#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>

int main(int argc, char** argv)
{
	if (argc < 2)
		return 1;

	// Read the file and load the data
	std::vector<std::string> allBanks;
	allBanks.reserve(500);

	std::fstream fs;
	fs.open(argv[1]);

	while(1)
	{
		std::string inputStr;
		fs >> inputStr;
		
		if (fs.eof())
			break;
		
		allBanks.emplace_back(inputStr);
		std::cout << allBanks.size() - 1 << ": " << inputStr << "\n";
	}

	fs.close();


#if 0
	// Part 1
	std::vector<uint64_t> highestJolt(allBanks.size(), 0);

	// For each bank
	for (size_t i = 0; i < allBanks.size(); ++i)
	{
		// For each word
		for (size_t j = 0; j < allBanks[i].size()-1; ++j)
		{
			for (size_t k = j+1; k < allBanks[i].size(); ++k)
			{
				std::string testNumber = {allBanks[i][j], allBanks[i][k]};
				uint64_t jolt = std::stoull(testNumber);

				if (jolt > highestJolt[i])
					highestJolt[i] = jolt;
			}
		}
		std::cout << "Highest for Bank " << i << ": " << highestJolt[i] << "\n";
	}

	uint64_t result = std::accumulate(highestJolt.begin(), highestJolt.end(), 0);
	std::cout << result << "\n";

#endif

#if 1
	// Part 2
	uint64_t totalJolt = 0;
	int numberToChoose = 12;

	// For each bank
	for (size_t i = 0; i < allBanks.size(); ++i)
	{
		// Sliding window method
		size_t startRange = 0;
		size_t endRange = allBanks[i].size() - numberToChoose;
		uint64_t joltForCurrBank = 0;
		
		// We need to pick 12 numbers
		for (int j = 0; j < numberToChoose; ++j)
		{
			// Stores the largest battery in the current window
			size_t largestIdx = 0;
			char largestBattery = '0';

			// Within the sliding window, pick the largest
			for (size_t k = startRange; k <= endRange; ++k)
			{
				if (allBanks[i][k] > largestBattery)
				{
					largestBattery = allBanks[i][k];
					largestIdx = k;
				}
			}

			joltForCurrBank = joltForCurrBank * 10 + (allBanks[i][largestIdx] - '0');
			
			// Move the window
			startRange = largestIdx + 1;
			endRange += 1;
		}

		// Convert to number
		std::cout << "Bank #" << i << ": " << joltForCurrBank << "\n";
		totalJolt += joltForCurrBank;
	}

	std::cout << "Total Jolt: " << totalJolt << "\n";


#endif 

	
}