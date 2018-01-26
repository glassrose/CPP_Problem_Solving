#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <limits>
using namespace std;

int getMMass (const string& s)
{
	stack<int> sums; //-1: '('

	for (int i=0; i<s.length(); i++)
	{
		int poppedSum = 0;
		switch (s[i])
		{
		case '(':
			sums.push (-1);
			break;
		case 'H':
			if (sums.top() == -1)
				sums.push (0);
			if (i+1<s.length() && s[i+1]>='0' && s[i+1]<='9')
			{
				sums.top() += s[i+1]-'0';
				i++;
			}
			else
				sums.top() += 1;
			break;
		case 'C':
			if (sums.top() == -1)
				sums.push (0);
			if (i+1<s.length() && s[i+1]>='0' && s[i+1]<='9')
			{
				sums.top() += 12*(s[i+1]-'0');
				i++;
			}
			else
				sums.top() += 12;
			break;
		case 'O':
			if (sums.top() == -1)
				sums.push (0);
			if (i+1<s.length() && s[i+1]>='0' && s[i+1]<='9')
			{
				sums.top() += 16*(s[i+1]-'0');
				i++;
			}
			else
				sums.top() += 16;
			break;
		case ')':
			while (sums.top() != -1)
			{
				poppedSum += sums.top();
				sums.pop();
			}
			sums.pop(); //pop -1
			sums.push(poppedSum);
			break;
		default:
			//s[i] is between 1 to 9
			sums.top() *= s[i]-'0';
		}
	}

	assert(sums.size()==1);
	return sums.top();

}

int main ()
{
	string s;

	//cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
	//getline (cin, s);
	cin>>s;
	//cout<<"string is:"<<s<<"."<<endl;
	assert (s.length()<=100);

	cout<<getMMass("("+s+")")<<"\n";
}
