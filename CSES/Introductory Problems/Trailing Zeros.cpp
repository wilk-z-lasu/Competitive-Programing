#include <iostream>
using namespace std;

#define int long long

int n;

int32_t main() 
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n;
	int solv=0;
	for(int i=5;i<=n;i*=5)
		solv += n / i;
	cout<<solv;
	return 0;
}