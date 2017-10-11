#include <iostream>
#include <vector>
#include <string>
using namespace std;

string get_next_perm(vector<int>& v)
{
	//find the lagest suffix that is non-increasing
	int pos_suffix_start;
	for (pos_suffix_start = v.size()-1;
	     pos_suffix_start > 0 &&
	     v[pos_suffix_start-1] >= v[pos_suffix_start];
	     pos_suffix_start--
	    )
		;

	if (pos_suffix_start == 0)
		return "-1";

	int pos_pivot = v.size()-1;
	if (pos_suffix_start > 0)
	{
		pos_pivot = pos_suffix_start-1;

		//find the rightmost digit in suffix that is the least number greater
		//than the pivot. We call this swapper.
		int pos_swapper;
		for (pos_swapper = v.size()-1;
		     pos_swapper > pos_pivot &&
		     v[pos_swapper] <= v[pos_pivot];
		     pos_swapper--
		    )
			;

		//Swap pivot digit with swapper digit
		int tmp = v[pos_pivot];
		v[pos_pivot] = v[pos_swapper];
		v[pos_swapper] = tmp;
	}

	//Prepare resulting string with reversing elements after the pivot digit
	string res = "";
	for (int i=0; i<=pos_pivot; i++)
		res+=to_string(v[i]);
	for (int i=v.size()-1; i>pos_pivot; i--)
		res+=to_string(v[i]);

	return res;
}

int main ()
{
	int T;
	cin>>T;
	for (int t=0; t<T; t++)
	{
		int n;
		cin>>n;
		vector<int> v;
		for (int i=0; i<n; i++)
		{
			int digit;
			cin>>digit;
			v.push_back(digit);
		}
		cout<<get_next_perm(v)<<endl;
	}
}
