#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define sz(A) (int)A.size()
#define pb push_back
#define pi pair<int,int>
#define f first
#define s second

constexpr int maxn=1e5+7;

int q;
int n;
int a[maxn],b[maxn];

bool vis[maxn];
map<int,vector<int>>M[2];
vector<int>vec[maxn][2];
vector<pi>solv;

int dfs(int v, bool k=0)
{
	vis[v]=1;
	vector<int>Next;
	for(const auto &u: vec[v][!k])
	{
		if(!vis[u])
		{
			int tmp = dfs(u,!k);
			if(tmp!=-1)//UwU
				Next.pb(tmp);
		}
	}
	int Straight=-1;
	for(const auto &u: vec[v][k])
	{
		if(!vis[u])
		{
			int tmp = dfs(u,k);
			if(tmp!=-1)//UwU
				Straight=tmp;
		}
	}

	if(sz(Next)==2)
		solv.pb({Next[0], Next[1]});
	if(sz(Next)==1)
	{
		solv.pb({v,Next[0]});
		return Straight;
	}

	if(Straight == -1)
		return v;
	else 
	{
		solv.pb({v, Straight});
		return -1;
	}
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>q;
	while(q--)
	{
		cin>>n;
		for(int i=1;i<=n;++i)
		{
			cin>>a[i]>>b[i];
			M[0][a[i]+b[i]].pb(i);
			M[1][a[i]-b[i]].pb(i);
		}
			//robie graf
		for(int j=0;j<=1;++j)
			for(auto &[xd, list]: M[j])
				for(int i=1;i<sz(list);++i)
				{
					vec[list[i]][j].pb(list[i-1]);
					vec[list[i-1]][j].pb(list[i]);
				}

		vector<pi>stopien;
		for(int i=1;i<=n;++i)
			stopien.pb({sz(vec[i][0]) + sz(vec[i][1]), i});
		sort(stopien.begin(), stopien.end());

		bool possible=1;
		for(auto &[xd, i]: stopien)
		{
			if(!vis[i] && dfs(i)!=-1)
			{
				possible = 0;
				break;
			}
		}
		if(possible)
		{
			cout<<"TAK\n";
			for(auto &u: solv)
				cout<<u.f<<' '<<u.s<<endl;
		}
		else
			cout<<"NIE\n";

		M[0].clear();
		M[1].clear();
		for(int i=1;i<=n;++i)
		{
			vec[i][0].clear();
			vec[i][1].clear();
			vis[i]=0;
		}
		solv.clear();
	}
}