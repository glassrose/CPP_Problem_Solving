//AC :)
#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <limits>
using namespace std;

int getValidPrefixLen (const string s)
{
	stack<int> st;
	int okCount=0;
	for (int i=0; i<s.length(); i++)
	{
		if (s[i]=='<')
		{
			if (st.empty())
				okCount = i;
			st.push(s[i]);
		}
		else
		{
			if (st.empty())
				return i;
			if (st.top()=='<')
				st.pop();
		}
	}
	if (st.empty())
		return s.length();
	else
		return okCount;
	return 0;
}

int main ()
{
	int T;
	cin>>T;
	for (int t=0; t<T; t++)
	{
		string s;

		//cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
		//getline (cin, s);
		cin>>s;
		//cout<<"string is:"<<s<<"."<<endl;
		assert (s.length()>=1);

		cout<<getValidPrefixLen(s)<<"\n";
	}
}
