#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <list>
using namespace std;

pair<int,int> dfs_util (vector<list<int> > &g, vector<bool> &visited,
			int current)
{
	visited[current] = true;

	int farthest = current;
	int max_downpath_len = -1;

	for (list<int>::iterator j = g[current].begin();
	     j!= g[current].end();
	     j++)
		if(!visited[*j])
		{
			pair<int, int> ret = dfs_util(g, visited, *j);
			if (max_downpath_len < ret.second)
			{
				farthest = ret.first;
				max_downpath_len = ret.second;
			}
		}
	return make_pair(farthest, ++max_downpath_len);
}

int longest_tree_path_dfs (vector<list<int> > &g)
{
	vector<bool> visited(g.size());// default filled to 0

	pair<int, int> ret = dfs_util (g, visited, 0);

	fill (visited.begin(), visited.end(), 0);
	return dfs_util(g, visited, ret.first).second;
}

int main ()
{
	int n;
	cin>>n;

	//Use adj. list rep. of graph
	vector<list<int> > g(n);

	for (int i=1; i<n; i++)
	{
		int u,v;
		cin>>u>>v;

		g[u-1].push_back(v-1);
		g[v-1].push_back(u-1);
	}

	cout<<longest_tree_path_dfs(g);
}
