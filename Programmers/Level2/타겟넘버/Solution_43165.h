#pragma once
#include <vector>

using namespace std;

class Solution_43165
{
public:
	Solution_43165();

	int solution(vector<int> numbers, int target);

	int dfs1(const vector<int>& numbers, int target, int index, int currentSum);
	void do_visit(int sum, int index, const vector<int>& numbers, int target, int& answer);
	int solution_recursive(vector<int> numbers = { 4, 1, 2, 1 }, int target = 4);

};