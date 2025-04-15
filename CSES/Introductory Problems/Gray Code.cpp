#include <iostream>
#include <vector>
using namespace std;

#define pb push_back
#define sz(A) (int)A.size()

int n;

vector<vector<bool>>vec;

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n;

	vec.pb({0});
	vec.pb({1});
	for(int i=2;i<=n;++i)
	{
		for(int j=sz(vec)-1;j>=0;--j)
			vec.pb(vec[j]);

		for(int j=0;j<sz(vec)/2;++j)
			vec[j].pb(0);
		for(int j=sz(vec)/2;j<sz(vec);++j)
			vec[j].pb(1);
	}

	for(int i=0;i<sz(vec);++i)
	{
		for(auto u: vec[i])
			cout<<u;
		cout<<'\n';
	}
}