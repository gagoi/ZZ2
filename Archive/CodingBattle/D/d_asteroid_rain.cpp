#include <iostream>
#include <vector>

int main(int, char**)
{
	int Q, N, i, type, val;
	int Qt = 0, QtOld = 0;
	bool end = false;

	std::vector<int> aB;
	std::vector<int> aJ;
	std::vector<int> bin;
	std::vector<int> max;

	std::cin >> Q;
	std::cin >> N;

	for (i = 0; i < N; ++i)
	{
		std::cin >> type;
		std::cin >> val;
		if (type == 1)
			aJ.push_back(val);
		else 
			aB.push_back(val);
	}

	for (int i = 0; i < aB.size(); ++i)
	{
		for (int j = 0; j < aJ.size(); ++j)
		{
			bin.push_back(aB[i] + aJ[j]);
		}
	}

	for (int i = 0; i < bin.size(); ++i)
	{
		
	}
	


	std::cout << QtOld;

	return 0;
}