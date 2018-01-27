#include <iostream>
#include <stack>
using namespace std;

int flipsNeeded (string &s)
{
	int flips = 0; //unflipped_open : not needed.
	stack<char> st;

	for (int i=0; i<s.length(); i++)
	{
		if (s[i]=='}')
		{
			if (st.empty())
			{
				flips++;
				st.push ('{');
			}
			else
			{
				//if (st.top() == '{') //always
				st.pop();
			}
		}
		else //s[i] == '{'
		{
			//if (st.empty() || st.top()== '{') //st.top == '}' never happens
			st.push (s[i]);
		}
	}

	flips += st.size()/2;

	return flips;
}

int main ()
{
	string s;
	cin>>s;

	while (s[0]!='-')
	{
		static int t = 1;
		cout<<t<<". "<<flipsNeeded(s)<<endl;
		cin>>s;
		t++;
	}
}
