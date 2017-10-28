#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <list>
using namespace std;

pair<int,int> dfs_util (vector<list<int> > &g,
			vector<bool> &tree_node_analysed,
			vector<bool> &visited,
                        int current)
{
        visited[current] = true;
	tree_node_analysed[current] = true;

        int farthest = current;
        int max_downpath_len = -1;

        for (list<int>::iterator j = g[current].begin();
             j!= g[current].end();
             j++)
                if(!visited[*j])
                {
                        pair<int, int> ret = dfs_util(g, tree_node_analysed,
						      visited, *j);
                        if (max_downpath_len < ret.second)
                        {
                                farthest = ret.first;
                                max_downpath_len = ret.second;
                        }
                }
        return make_pair(farthest, ++max_downpath_len);
}

int longest_forest_path_dfs (vector<list<int> > &g,
			     vector<vector<char> > &laby,
			     vector<bool> &tree_node_analysed)
{
	int diameter = 0;
	int r = laby.size();
	int c = laby[0].size();

	int max_diameter = 0;
	for (int i=0; i<r; i++)
		for(int j=0; j<c; j++)
		{
			if (laby[i][j]==0 && !tree_node_analysed[i*c+j])
			{
				vector<bool> visited(r*c);// default filled to 0

				pair<int, int> ret =
					dfs_util (g, tree_node_analysed,
						  visited, i*c+j);

				fill (visited.begin(), visited.end(), 0);
				max_diameter = max (max_diameter,
						    dfs_util(g,
							     tree_node_analysed,
							     visited,
							     ret.first
							     ).second
						    );
			}
		}
	return max_diameter;
}

int isSafePoint (int x, int y, int r, int c)
{
	if (x>=0 && x<r && y>=0 && y<c)
		return true;
	return false;
}

int main ()
{
	int T;
	cin>>T;
	for (int t=0; t<T; t++)
	{
		int c, r;
		cin>>c>>r;
		vector<vector<char> > laby(r, vector<char>(c));

		// Input labyrinth
		for (int i=0; i<r; i++)
			for (int j=0; j<c; j++)
			{
				char ch;
				cin>>ch;
				laby[i][j] = ch - '.'; // -11:#    0:.
			}

		// Use adj. list rep. of graph
		vector<list<int> > g(r*c, list<int>());

		for (int i=0; i<r; i++)
			for (int j=0; j<c; j++)
			{
				if (laby[i][j] == 0)
				{
					int x, y;

					x=i-1; y=j;
					if (isSafePoint(x, y, r, c) &&
					    laby[x][y] == 0)
						g[i*c+j].push_back(x*c+y);

					x=i; y=j+1;
					if (isSafePoint(x, y, r, c) &&
					    laby[x][y] == 0)
						g[i*c+j].push_back(x*c+y);

					x=i+1; y=j;
					if (isSafePoint(x, y, r, c) &&
					    laby[x][y] == 0)
						g[i*c+j].push_back(x*c+y);

					x=i; y=j-1;
					if (isSafePoint(x, y, r, c) &&
					    laby[x][y] == 0)
						g[i*c+j].push_back(x*c+y);

				}
			}

		vector<bool> tree_node_analysed(r*c);
		cout<<"Maximum rope length is "<<
			longest_forest_path_dfs(g, laby, tree_node_analysed)<<
			".\n";
	}
}
