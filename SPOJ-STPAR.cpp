//Online algo. (without necessarily storing all elements)
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main ()
{
	int n;
	cin>>n;
	while (n>0)
	{
		vector<int> sorted;//ordered array
		stack<int> side; //side street

		int find = 1;
		bool can_order = true;
		for (int i=0; i<n; i++)
		{
			int truck;
			cin>>truck;

			if (truck == find)
			{
				sorted.push_back(truck);
				find++;
			}
			else
			if (truck > find)//implied as (truck < find) is invalid input
			{
				while (!side.empty() && side.top() == find)
				{
					sorted.push_back(side.top());
					side.pop();
					find++;
				}

				if (!side.empty() && side.top() < truck)//greater (or equal (though invalid i/p)) side than truck is fine.
				{
					can_order = false;
					//read and discard remaining trucks in
					//this test
					int x; 
					for (int rem=i+1; rem<n; rem++)
						cin>>x;
					break;
				}

				side.push(truck);
			}
		}
		string res = (can_order?"yes":"no");
		cout<<res<<endl;
		cin>>n;
	}
}
