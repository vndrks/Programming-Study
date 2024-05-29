#include "Solution_43162.h"

using namespace std;

Solution_43162::Solution_43162()
{
	vector<pair<int, vector<vector<int>>>> test_cases = {
		
		{3, {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}}}, // 2
		{3, {{1, 1, 0}, {1, 1, 1}, {0, 1, 1}}}, // 1
		{4, {{1, 1, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 0}, {1, 1, 0, 1}}}, // 1
		{4, {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}}, // 4
		{4, {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 1, 1}, {0, 0, 1, 1}}}, // 2
		{5, {{1, 0, 0, 0, 1}, {0, 1, 1, 0, 0}, {0, 1, 1, 1, 0}, {0, 0, 1, 1, 1}, {1, 0, 0, 1, 1}}}, // 1
		
		{3, {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}}, // 1
		{4, {{1, 0, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 0}, {1, 1, 0, 1}}}, // 1
		{5, {{1, 0, 1, 0, 0}, {0, 1, 0, 0, 1}, {1, 0, 1, 0, 1}, {0, 0, 0, 1, 0}, {0, 1, 1, 0, 1}}}, // 2
		{5, {{1, 1, 0, 1, 0}, {1, 1, 0, 0, 0}, {0, 0, 1, 0, 1}, {1, 0, 0, 1, 1}, {0, 0, 1, 1, 1}}}, // 1
		{3, {{1, 0, 1}, {0, 1, 1}, {1, 1, 1}}}, // 1
		{3, {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}}}, // 1
		{4, {{1, 0, 0, 1}, {0, 1, 0, 0}, {0, 0, 1, 1}, {1, 0, 1, 1}}}, // 2
		/*
		{4, {{1, 0, 0, 0}, {0, 1, 0, 0}, {1, 0, 1, 0}, {1, 0, 0, 1}}}, // 단방향은 성립 안됨의 TC. Expected 2, got 4.
		{3, {{1, 0, 0}, {0, 1, 0}, {1, 0, 1}}}, // 단방향은 성립 안됨의 TC. Expected 2, got 3. 
		*/
	};

	vector<int> expected_results = { 2, 1, 1, 4, 2, 1, 1, 1, 2, 1, 1, 1, 2, /*2, 2*/};

	for_each(test_cases.begin(), test_cases.end(), [&, i = 0](pair<int, vector<vector<int>>> e) mutable {
		int result = solution(e.first, e.second);
		cout << "###Test Case " << i + 1 << ": ";

		if (result == expected_results[i])
			cout << "### Passed" << endl;
		else
			cout << "### Failed (Expected " << expected_results[i] << ", got " << result << ")" << endl;

		++i;
	});
}

int Solution_43162::solution(int n, vector<vector<int>> computers) {
	int answer = 0;
	vector<bool> visited(n, false);

	auto do_visit = [&](int start_node) {
		stack<int> st;
		st.push(start_node);

		while (!st.empty())
		{
			int node = st.top();
			st.pop();

			if (!visited[node])
			{
				visited[node] = true;
				for (int i = 0; i < n; ++i)
				{
					if (computers[node][i] == 1 && !visited[i])
						st.push(i);
				}
			}
		}
		};

	for (int i = 0; i < n; ++i)
	{
		if (!visited[i])
		{
			do_visit(i);
			++answer;
		}
	}

	return answer;
}

int solution_bfs(int n = 4, vector<vector<int>> computers = { { 1, 0, 0, 1 }, {0, 1, 1, 0}, {0, 1, 1, 0}, {1, 1, 0, 1} }) {
	int answer = 0;
	vector<bool> visited(n, false);

	auto do_visit = [&](int node) {
		queue<int> q;
		q.push(node);
		visited[node] = true;

		while (!q.empty())
		{
			int current = q.front();
			q.pop();

			for (int i = 0; i < n; ++i)
			{
				if (computers[current][i] == 1 && !visited[i])
				{
					q.push(i);
					visited[i] = true;
				}
			}
		}
		};

	for (int i = 0; i < n; ++i)
	{
		if (!visited[i])
		{
			do_visit(i);
			++answer;
		}
	}

	return answer;
}

/* Union-Find structure */
vector<int> parent;
vector<int> v_rank;

int do_find(int x)
{
	if (parent[x] != x)
		parent[x] = do_find(parent[x]);
	return parent[x];
}

void do_union(int x, int y)
{
	int root_x = do_find(x);
	int root_y = do_find(y);

	if (v_rank[root_x] > v_rank[root_y])
	{
		parent[y] = root_x;
	}
	else if (v_rank[root_x] < v_rank[root_y])
	{
		parent[x] = root_y;
	}
	else
	{
		parent[root_y] = root_x;
		v_rank[root_x]++;
	}
}

int solution_union_find(int n = 4, vector<vector<int>> computers = { { 1, 0, 0, 1 }, {0, 1, 1, 0}, {0, 1, 1, 0}, {1, 1, 0, 1} }) {
	int answer = 0;

	parent.assign(computers.size(), 0);
	v_rank.assign(computers.size(), 0);

	for (int i = 0; i < n; ++i)
		parent[i] = i;

	for (int i = 0; i < computers.size(); ++i)
	{
		for (int j = 0; j < computers[i].size(); ++j)
		{
			if (computers[i][j] == 1 || computers[j][i] == 1)
			{
				do_union(i, j);
			}
		}
	}

	set<int> networks;
	for (int i = 0; i < n; ++i)
		networks.insert(do_find(i));

	answer = networks.size();
	return answer;
}