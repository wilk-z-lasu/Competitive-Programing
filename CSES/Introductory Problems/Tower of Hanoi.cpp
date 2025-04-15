#include <iostream>
#include <vector>
using namespace std;

#define pb push_back

vector<int>vec[4];

void ruch(int x1, int x2)
{
	if(vec[x1].back() > vec[x2].back()) swap(x1,x2);
	vec[x2].pb(vec[x1].back());
	vec[x1].pop_back();
	cout<<x1<<' '<<x2<<'\n';
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n;
	cin>>n;
	int k = (1<<n)-1;
	cout<<k<<'\n';
	int a=1,b=2,c=3;

	vec[1].pb(n+1);
	vec[2].pb(n+1);
	vec[3].pb(n+1);
	for(int i=n;i>=1;--i)
		vec[1].pb(i);
	if(n%2==1) swap(b,c);
	for(int i=0;i<k;++i)
	{
		if(i%3==0)
			ruch(a,b);
		if(i%3==1)
			ruch(a,c);
		if(i%3==2)
			ruch(b,c);
		// cout<<vec[1].back()<<' '<<vec[2].back()<<' '<<vec[3].back()<<'\n';
	}
}