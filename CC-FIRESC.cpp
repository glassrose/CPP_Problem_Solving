//Using adjacency list - AC :) ( SIGABRT was due to non-void function returning void )
#include <iostream>
#include <list>
#include <vector>
using namespace std;

class graphCC {
public:
	int nodescount;

	graphCC()
	{
		nodescount = 0;
	}
};

void DFS (vector<list<int> > &G, int node, vector<bool> &visited, graphCC &comp)
{
//	cout<<"visited node: "<<node<<endl;
	visited[node] = true;
	comp.nodescount++;

	for (list<int>::iterator it = G[node].begin(); it!=G[node].end(); it++)
		if (!visited[*it])
			DFS(G, *it, visited, comp);
}

void get_connected_components(vector<list<int> > G,
					 vector<graphCC> &cc)
{
	vector<bool> visited(G.size(), false);

	for (int i=0; i<G.size(); i++)
		if (!visited[i])
		{
			graphCC comp;
//			cout<<"connected component: "<<cc.size()+1<<endl;
			DFS(G, i, visited, comp);
			cc.push_back (comp);
		}
}

int main ()
{
	int T, N, M;
	cin>>T;

	vector<graphCC> cc;
	for (int t=0; t<T; t++)
	{
		cin>>N>>M;
		vector<list<int> > G = vector<list<int> > (N, list<int> ());
//		for (int i=0; i<N; i++)
		int u, v;
		for (int i=0; i<M; i++)
		{
			cin>>u>>v;
			G[u-1].push_back(v-1);
			G[v-1].push_back(u-1);
		}

		get_connected_components(G, cc);
		long waysOfSelectingCaptains = 1, MOD = 1000000007;
		for (int i=0; i<cc.size(); i++)
			waysOfSelectingCaptains = (waysOfSelectingCaptains *
						   (cc[i].nodescount%MOD)
						  ) % MOD;
		cout<<cc.size()<<" "<<waysOfSelectingCaptains<<endl;
		cc.clear();
	}
}
