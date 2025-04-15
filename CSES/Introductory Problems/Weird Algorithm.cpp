#include <iostream>
using namespace std;

#define int long long

int n;

int32_t main() 
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n;
	while(n!=1)
	{
		cout<<n<<' ';
		if(n%2 == 0)
			n /= 2;
		else
			n = 3*n + 1; 
	}
	cout<<n;
	return 0;
}