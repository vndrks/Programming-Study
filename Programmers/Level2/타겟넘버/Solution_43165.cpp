#include "Solution_43165.h"

#include <stack>
#include <functional>

Solution_43165::Solution_43165()
{
}

/* Using Stack */
int Solution_43165::solution(vector<int> numbers, int target)
{
	int answer = 0;

	

	stack<pair<int, int>> st;
	st.push(make_pair(0, 0));

	while (!st.empty())
	{
		int sum = st.top().first;
		int index = st.top().second;
		st.pop();

		if (index == numbers.size())
		{
			if (sum == target)
				++answer;
			continue;
		}

		st.push(make_pair(sum + numbers[index], index + 1));
		st.push(make_pair(sum - numbers[index], index + 1));
	}

	return answer;
}


/* Using Recursive */


int dfs1(const vector<int>& numbers, int target, int index, int currentSum) {
	// Base case: if we've considered all numbers
	if (index == numbers.size()) {
		// Check if the current sum equals the target
		return (currentSum == target) ? 1 : 0;
	}

	// Recursive case: explore both adding and subtracting the current number
	int add = dfs1(numbers, target, index + 1, currentSum + numbers[index]);
	int subtract = dfs1(numbers, target, index + 1, currentSum - numbers[index]);

	// Return the total number of ways from both add and subtract paths
	return add + subtract;
}

void Solution_43165::dfs2(int sum, int index, vector<int> numbers, int target, int& answer)
{
	if (index == numbers.size())
	{
		if (sum == target)
			++answer;
		return;
	}

	dfs2(sum + numbers[index], index + 1, numbers, target, answer);
	dfs2(sum - numbers[index], index + 1, numbers, target, answer);
}



int Solution_43165::solution_recursive(vector<int> numbers, int target)
{
	int answer = 0;
	dfs2(0, 0, numbers, target, answer);
	return answer;
}
