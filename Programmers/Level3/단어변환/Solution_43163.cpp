#include "Solution_43163.h"

#include <algorithm>
#include <queue>
#include <iostream>

Solution_43163::Solution_43163()
{
	vector<pair<vector<string>, vector<string>>> test_cases = {
		{{"hit", "cog"}, { "hot", "dot", "dog", "lot", "log", "cog" }},
		{{"hit", "cog"}, { "hot", "dot", "dog", "lot", "log" }},
		{{"cog", "hot"}, { "hot", "dot", "dog", "lot", "log", "cog" }},
	};

	vector<int> expected_results = { 4, 0, 3 };

	for_each(test_cases.begin(), test_cases.end(), [&, i = 0](pair<vector<string>, vector<string>> e) mutable {
		int result = solution(e.first[0], e.first[1], e.second);
		cout << "###Test Case " << i + 1 << ": ";

		if (result == expected_results[i])
			cout << "### Passed" << endl;
		else
			cout << "### Failed (Expected " << expected_results[i] << ", got " << result << ")" << endl;

		++i;
	});
}

int Solution_43163::solution(string begin, string target, vector<string> words)
{
	int answer = 0;

	auto check_transform = [](string current, string word) {
		auto diff_count = count_if(current.begin(), current.end(), [&, i = 0](char c) mutable {
			return c != word[i++];
		});
		return diff_count;
	};

	queue<pair<string, int>> q;
	q.push(make_pair(begin, 0));

	while (!q.empty())
	{
		string current = q.front().first;
		int step = q.front().second;
		q.pop();

		if (current == target)
			return step;

		for (int i = 0; i < words.size(); ++i)
		{
			if (check_transform(current, words[i]) == 1)
			{
				q.push(make_pair(words[i], step + 1));
				words.erase(remove_if(words.begin(), words.end(), [&](string str) {
					return words[i] == str;
				}), words.end());
			}
		}
	}
	return 0;
}
