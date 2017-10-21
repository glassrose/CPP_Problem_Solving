#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

class GridPos
{
public:
	int x;
	int y;

	GridPos(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

int isSafePoint (int n, int x, int y)
{
	if (x>=0 && x<n && y>=0 && y<n)
		return true;
	return false;
}

void push_to_q (int x, int y, const vector<vector<long long> > &maze,
		vector<vector<bool> > &visited,
		queue<GridPos> &q)
{
	if (isSafePoint(maze.size(), x, y) && maze[x][y]>=0
	    && !visited[x][y])
	{
		visited[x][y] = true;
		//cout<<"Pushing x:"<<x<<" y:"<<y<<endl;
		q.push(GridPos(x, y));
	}

}

int has_path_bfs (vector<vector<long long> > &maze)
{
	int n = maze.size();
	queue<GridPos> q;
	vector<vector<bool> > visited;

	//initialize all elements to 0
	for (int i=0; i<n; i++)
	{
		visited.push_back(vector<bool>());
		for (int j=0; j<n; j++)
			visited[i].push_back(false);
	}

	q.push (GridPos(0, 0));
	visited[0][0] = true;
	while (!q.empty())
	{
		GridPos out = q.front();

		//cout<<"Popping x:"<<out.x<<" y:"<<out.y<<endl;
		q.pop();//popped here as popping is not destroying GridPos 'out'

		if (out.x==n-1 && out.y==n-1)
			return true;

		//Working with adjacent points in grid
		int x, y;
		x = out.x;
		y = out.y+1;
		if (x==n-1 && y==n-1)
			return true;
		push_to_q(x, y, maze, visited, q);

		x = out.x+1;
		y = out.y;
		if (x==n-1 && y==n-1)
			return true;
		push_to_q(x, y, maze, visited, q);

		x = out.x;
		y = out.y-1;
		if (x==n-1 && y==n-1)
			return true;
		push_to_q(x, y, maze, visited, q);

		x = out.x-1;
		y = out.y;
		if (x==n-1 && y==n-1)
			return true;
		push_to_q(x, y, maze, visited, q);

	}
	return false;
}

void dp(vector<vector<long long> > &grid)
{
	int n = grid.size();
	long long mod = (1LL<<31) -1;

	//initialize column 0
	for (int i=0; i<n; i++)
		if (grid[i][0]==0)
			grid[i][0]=1;
		else
			break;

	for (int i=1; i<n; i++)
		if (grid[0][i]==0)
			grid[0][i]=1;
		else
			break;

	for (int i=1; i<n; i++)
		for (int j=1; j<n; j++)
		{
			if (grid[i][j]==-1)
				continue;

			if (grid[i-1][j]>0)
				grid[i][j] = ( grid[i][j]
					     + grid[i-1][j]
					     ) % mod;
			if (grid[i][j-1]>0)
				grid[i][j] = ( grid[i][j]
					     + grid[i][j-1]
					     ) % mod;
		}
}

int main ()
{
	int n;
	cin>>n;

	vector<vector<long long> > grid;
	for (int i=0; i<n; i++)
	{
		grid.push_back(vector<long long>());
		for (int j=0; j<n; j++)
		{
			char in;
			cin>>in;
			if (in == '.')
				grid[i].push_back(0);
			else
				grid[i].push_back(-1);
		}
	}

	dp(grid);
	if (grid[n-1][n-1] == 0)/* no paths from s to t while only
					       going right and down */
	{
		if (!has_path_bfs(grid)) /* grid is possibly modified by dp()
					    call but blocked cells are -1 and
					    non-blocked cells are >=0 */
			cout<<"INCONCEIVABLE"<<endl; /* No paths s to t at all */
		else
			cout<<"THE GAME IS A LIE"<<endl;/* there are paths s to t when
							   going up and left is
							   allowed */
	}
	else
		cout<<grid[n-1][n-1]<<endl;
}
