#include <iostream>
#include <algorithm>
using namespace std;

#define int long long

int t;
int a,b;

int32_t main() 
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>t;
	while(t--)
	{
		cin>>a>>b;
		if(a>b) swap(a,b);
		if((a+b)%3==0)
		{
			if(b-a <= (a+b)/3)
				cout<<"YES\n";
			else
				cout<<"NO\n";
		}
		else
			cout<<"NO\n";
	}
	return 0;
}