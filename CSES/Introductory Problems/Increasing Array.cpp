#include <iostream>
using namespace std;

#define int long long
int n;
int last;
int x;

int solv=0;

int32_t main() 
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n;
	cin>>last;
	for(int i=2;i<=n;++i)
	{
		cin>>x;
		if(x<last)
			solv += last-x;
		else
			last = x;
	}
	cout<<solv;
	return 0;
}