#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define int long long 

int q;
int k;

int pot[20];
int dp[20];

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	pot[0]=1;
	for(int i=1;i<=19;++i)
		pot[i] = pot[i-1]*10;

	for(int i=1;i<=17;++i)
		dp[i] = dp[i-1] + 9*pot[i-1]*i;

	cin>>q;
	while(q--)
	{
		cin>>k;

		int znaki=1;
		while(dp[znaki]<k)
			znaki++;
		// cout<<"znaki: "<<znaki<<endl;
		k-=dp[znaki-1];

		k--;
		int digit = k%znaki;
		// cout<<"digit: "<<digit<<endl;
		int num = (k/znaki) + pot[znaki-1];
		// cout<<"num: "<<num<<endl;

		digit = znaki-digit - 1;
		while(digit--)
			num/=10;
		cout<<num%10<<endl;
	}
	return 0;
}