// XXXI Olimpiada Informatyczna - 2 Etap
// Mateusz Woloszyk
// Solution for 9/100 pkt
#include <bits/stdc++.h>
using namespace std;
#define int long long

constexpr int maxn=1e6+7;
int n,k;
int a[maxn];
int syt;//ile wystapilo sytuacji a>k
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]>k)
			syt++;
	}

	// if(n<=6 && k<=6)
	// {
	// 	//nie umiem na razie
	// }
	if(syt==0)
	{
		cout<<"TAK\n";
		for(int i=1;i<=n;i++)
			cout<<1<<' '<<i<<' '<<a[i]<<'\n';
		return 0;
	}
	if(syt==1)
	{
		int wolne=0;
		int need=0;
		int nr;
		for(int i=1;i<=n;i++)
		{
			if(a[i]<=k)
				wolne+= k-a[i];
			else if(a[i]>k)
			{
				need=a[i]-k;
				nr=i;
			}
		}
		if(wolne<need)
		{
			cout<<"NIE\n";
			return 0;
		}
		else if(wolne>=need)
		{
			cout<<"TAK\n";
			for(int i=1;i<=n;i++)
			{
				if(k-a[i]>0)
				{
					cout<<2<<' '<<i<<' '<<a[i]<<' '<<nr<<' '<<min(need,k-a[i])<<'\n';
					need=need-min(need,k-a[i]);
				}
				else
					cout<<1<<' '<<i<<' '<<min(a[i],k)<<'\n';
			}
			return 0;
		}
	}


}