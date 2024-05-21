#include "Solution_42895.h"

#include <vector>
#include <unordered_set>

using namespace std;

Solution_42895::Solution_42895()
{
}

int Solution_42895::solution(int N, int number)
{
	int answer = -1;
	vector<unordered_set<long long>> dp_arr(9, unordered_set<long long>());
	int d = 0;

	for (int i = 1; i <= 8; ++i)
	{
		d = d * 10 + N;
		dp_arr[i].insert(d);

		for (int j = 1; j < i; ++j)
		{
			for (auto e1 : dp_arr[j])
			{
				for (auto e2 : dp_arr[i - j])
				{
					dp_arr[i].insert(e1 + e2);
					dp_arr[i].insert(e1 - e2);
					dp_arr[i].insert(e1 * e2);
					if (e2 != 0)
						dp_arr[i].insert(e1 / e2);
				}
			}
		}

		if (dp_arr[i].count(number))
		{
			answer = i;
			break;
		}
	}

	return answer;
}
