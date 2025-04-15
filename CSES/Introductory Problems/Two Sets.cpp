#include <iostream>
using namespace std;

// #define int long long

int n;

int32_t main() 
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n;
	if(n%4==0)
	{
		cout<<"YES\n";
		cout<<n/2<<'\n';
		for(int i=1;i<=n/4;++i)
			cout<<i<<' '<<n-i+1<<' ';
		cout<<'\n'<<n/2<<'\n';
		for(int i=(n/4)+1;i<=n/2;++i)
			cout<<i<<' '<<n-i+1<<' ';
	}
	if(n%4==1 || n%4==2)
		cout<<"NO\n";
	if(n%4==3)
	{
		n-=3;
		cout<<"YES\n";
		cout<<(n/2)+2<<'\n';
		cout<<1<<' '<<2<<' ';
		for(int i=1;i<=n/4;++i)
			cout<<i + 3<<' '<<n-i+1 + 3<<' ';
		cout<<'\n'<<(n/2)+1<<'\n';
		cout<<3<<' ';
		for(int i=(n/4)+1;i<=n/2;++i)
			cout<<i + 3<<' '<<n-i+1 + 3<<' ';
		
	}
	return 0;
}