/* Game: Find String in 4-or-8-connected Board without repeating alphabets in any cell
 *
 * Program tells you if the word-string is present as a path(cycle-less) in the board.
 *
 * Some 4 connected example strings found in below board example are:
 *	cattle, eel, reel, fat
 * Some 8 connected example strings found in the below board apart from the above strings are:
 *	craft, raft, after, feel, fare, care, flee
 *
 */
#include <iostream>
#include <string>
#include <stack>
//#include <utility>
using namespace std;

void isStringPresent(const char (&board)[3][3], int r, int c, string s);
bool foundStringInBoardDFS (const char (&board)[3][3], bool **visited, int r, int c, int x, int y,
			                           string s, int spos,
						   stack<pair<int, int>> &st);

int main ()
{
	string s;
	cin>>s;

	char board[3][3] =
	{
		'c', 'a', 't',
		'r', 'f', 't',
		'e', 'e', 'l'
	};

	isStringPresent(board, 3, 3, s);
}

void isStringPresent(const char (&board)[3][3], int r, int c, string s)
{
	bool **visited = new bool*[r];
	for (int i=0; i<r; i++)
	{
		visited[i] = new bool[c](); //value initialised array
	}

	bool found = false;
	stack<pair<int, int>> st;
	for (int i=0; i<r && !found; i++)
	{
		for (int j=0; j<c; j++)
		{
			if (foundStringInBoardDFS (board, visited, r, c, i, j,
						   s, 0, st))
			{
				found = true;
				break;
			}
		}
	}

	if (found)
	{
		cout<<"Found! :D"<<endl;
		while (!st.empty())
		{
			cout<< "(" << st.top().first << "," << st.top().second <<
				")" << endl;
			st.pop();
		}
	}
	else
		cout<<"Not Found :("<<endl;

}

bool is_safe(int a, int b, int r, int c)
{
	return 0<=a && a<r && 0<=b && b<c;
}

bool foundStringInBoardDFS (const char (&board)[3][3], bool **visited, int r, int c, int x, int y,
		       string s, int spos, stack<pair<int, int>> &st)
{
	if (spos >= s.length())
		return true;
	if (board[x][y] != s[spos])
		return false;

	//Visit the 
	visited[x][y] = true;

	// 4-connected
/*	const int connectivity = 4;
	int xdiff[connectivity] = {1, 0, -1, 0};
	int ydiff[connectivity] = {0, -1, 0, 1};
*/


	//8-connected
	const int connectivity = 8;
	int xdiff[connectivity] = {1,  1,  0, -1, -1, -1, 0, 1};
	int ydiff[connectivity] = {0, -1, -1, -1,  0,  1, 1, 1};

	bool found = false;
	for (int i=0; i<connectivity; i++)
	{
		int a = x+xdiff[i];
		int b = y+ydiff[i];
		if (is_safe(a, b, r, c) && !visited[a][b])
		{
			bool found = foundStringInBoardDFS(board, visited, r, c, a, b, s,
					      spos+1, st);
			if (found)
			{
				st.push(make_pair(x, y));
				//backtrack to unmark (x,y)
				visited[x][y] = false;
				return true;
			}
		}
	}

	//backtrack to unmark(x,y)
	visited[x][y] = false;
	return false;
}
