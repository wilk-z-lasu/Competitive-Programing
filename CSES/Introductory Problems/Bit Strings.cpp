#include <iostream>
using namespace std;

#define int long long

constexpr int mod = 1e9 + 7;

int n;

int pot(int x, int k)
{
	int odp=1;
	while(k)
	{
		if(k%2==1)
			odp = (odp*x)%mod;
		x = (x*x)%mod;
		k/=2;
	}
	return odp;
}
int32_t main() 
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n;
	cout<<pot(2,n);
	return 0;
}