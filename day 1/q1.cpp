#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct DialAction
{
	char sign;
	int number;

	friend std::ostream& operator<<(std::ostream& os, DialAction c)
	{
		os << "Sign: " << c.sign << ", Num: " << c.number;
		return os;
	}
};

int Wrap(int number)
{
	if ((number % 100) < 0)
		return (number % 100) + 100;
	else
		return (number % 100);
}


int main()
{
	std::vector<DialAction> list;
	list.reserve(5000);

	std::fstream fs;
	fs.open("input.txt");

	while (1)
	{
		std::string inputStr;
		fs >> inputStr;

		if (fs.eof())
			break;

		DialAction combo;
		combo.sign = inputStr[0];
		combo.number = std::stoi(inputStr.substr(1));
		
		list.emplace_back(combo);
	}

	fs.close();
	
	// Part 1
#if 0
	int dialNumber = 50;
	int numberOfZero = 0;

	for (DialAction c : list)
	{
		if (c.sign == 'L')
		{
			dialNumber = Wrap(dialNumber - c.number);
		}
		else
		{
			dialNumber = Wrap(dialNumber + c.number);
		}

		std::cout << c << ", " << dialNumber << "\n";
		if (dialNumber == 0)
			++numberOfZero;
	}

	// Ans: 1055
	std::cout << "Password: " << numberOfZero << "\n";
#endif

	// Part 2
#if 1
	int dialNumber = 50;
	int numberOfZero = 0;

	for (DialAction c : list)
	{
		for (int i = 0; i < c.number; ++i)
		{
			if (c.sign == 'L')
			{
				--dialNumber; 
			}
			else
			{
				++dialNumber;
			}

			if (dialNumber < 0)
				dialNumber += 100;
			else if (dialNumber > 99)
				dialNumber -= 100;

			if (dialNumber == 0)
				++numberOfZero;
		}
		std::cout << c << " dial: " << dialNumber << ", NumOfZero: " << numberOfZero << "\n";
	}
	std::cout << "Password: " << numberOfZero << "\n";
#endif
}