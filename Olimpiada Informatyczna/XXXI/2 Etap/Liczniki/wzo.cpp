#include <bits/stdc++.h>
using namespace std;
#define int long long

#define f first
#define s second
#define pi pair<int,int>

int n,m;
int a;
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n>>m;

	vector<pi>vec(n+7);
	vector<int>start(n+7);
	vector<multiset<int>>price(m+7);

	for(int i=1;i<=n;++i)
		cin>>vec[i].f;

	for(int i=1;i<=n;++i)
		cin>>vec[i].s;
	for(int j=1;j<=m;++j)
	{
		for(int i=1;i<=n;++i)
		{
			cin>>a;
			price[j].insert(a);
		}
	}
	int solv = 0;
	sort(&vec[1], &vec[n+1], greater<pi>());
	for(int j=1;j<=n;++j)
	{
		int cost = vec[j].f;
		int last = vec[j].s;
		for(int i=1;i<=m;++i)
		{
			auto nx = price[i].lower_bound(last);
			if(nx != price[i].end())
			{
				last = *nx;
				price[i].erase(nx);
			}
			else
			{
				cout<<"NIE";
				return 0;
			}
		}
		solv += (last-vec[j].s)*cost;
	}
	cout<<solv;
	return 0;
}