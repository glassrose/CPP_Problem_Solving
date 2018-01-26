#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
using namespace std;

long long getMaxRectangularAreaUnderHistogram (vector<int> &hist)
{
	stack<int> st; // holds indices
	long long max_area = 0;

	int i=0;
	while (i<hist.size())
	{
		if (st.empty() || hist[st.top()] <= hist[i])
		{
			st.push(i++);
		}
		else
		{
			int poppedInd = st.top();
			st.pop();

			long long  area_with_top = (long long) hist[poppedInd] *
					  (st.empty() ? i : (i-st.top()-1));
					  /* Always perform top() on non-empty
					   * stack */


			if (max_area < area_with_top)
				max_area = area_with_top;
		}
	}

	while (!st.empty())
	{
		int poppedInd = st.top();
		st.pop();

		long long  area_with_top = (long long) hist[poppedInd] *
				  (st.empty() ? i : (i-st.top()-1));

		if (max_area < area_with_top)
			max_area = area_with_top;
	}

	return max_area;
}


int main ()
{
	int N;
	cin>>N;
	while (N != 0)
	{
		vector<int> v(N);
		for (int i=0; i<N; i++)
			cin>>v[i];

		cin>>N;
		cout<<getMaxRectangularAreaUnderHistogram(v)<<endl;

	}
}
