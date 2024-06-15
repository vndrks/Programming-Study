#pragma once
#include <vector>

using namespace std;

class Solution_43165
{
public:
	Solution_43165();

private:
	int solution(vector<int> numbers, int target);

	int dfs1(const vector<int>& numbers, int target, int index, int currentSum);
	void dfs2(int sum, int index, vector<int> numbers, int target, int& answer);
	int solution_recursive(vector<int> numbers, int target);

};