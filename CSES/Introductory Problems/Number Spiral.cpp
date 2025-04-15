#include <iostream>
using namespace std;

#define int long long

int t;
int x,y;

int odp;

int32_t main() 
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>t;
	while(t--)
	{
		cin>>y>>x;
		if(x>=y)
		{
			if(x%2 == 1)
			{
				odp = x*x;
				cout<<odp - y + 1<<'\n';
			}
			else
			{
				odp = x*x - 2*(x-1);
				cout<<odp + y - 1<<'\n';
			}
		}
		else
		{
			if(y%2 == 0)
			{
				odp = y*y;
				cout<<odp - x + 1<<'\n';
			}
			else
			{
				odp = y*y - 2*(y-1);
				cout<<odp + x - 1<<'\n';
			}
		}
	}
	return 0;
}