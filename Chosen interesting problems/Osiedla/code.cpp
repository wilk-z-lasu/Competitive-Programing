#include<bits/stdc++.h>
using namespace std;
// #define int long long

#define f first
#define s second
#define pi pair<int,int>
#define sz(A) (int)(A.size())

constexpr int maxn=1e6+7;

int n,m;
int a,b;
pi con[maxn];
bool taken[maxn];
vector<int>vec[maxn];

int solution;
bool solv[maxn];

vector<int>G[maxn];
vector<int>G_odw[maxn];

void dfs(int v)
{
	for(auto &i: vec[v])
	{
		if(taken[i]) continue;
		taken[i] = 1;
		int u = con[i].s;
		if(u==v)
		{
			solv[i]=1;
			u = con[i].f;
		}
		// cout<<v<<" -> "<<u<<endl;
		G[v].push_back(u);
		G_odw[u].push_back(v);
		dfs(u);
	}
}

bool vis[maxn];
vector<int>postorder;
void get_postorder(int v)
{
	vis[v]=1;
	for(auto &u: G[v])
	{
		if(vis[u]) continue;
		get_postorder(u);
	}
	postorder.push_back(v);
}

bool vis2[maxn];
void mark_sss(int v)
{
	vis2[v]=1;
	for(auto &u: G_odw[v])
	{
		if(vis2[u]) continue;
		mark_sss(u);
	}
}
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n>>m;

	for(int i=1;i<=m;i++)
	{
		cin>>a>>b;
		con[i]={a,b};
		vec[a].push_back(i);
		vec[b].push_back(i);
	}

	for(int i=1;i<=n;i++)
		dfs(i);

	for(int i=1;i<=n;i++)
		if(!vis[i])
			get_postorder(i);

	while(!postorder.empty())
	{
		int v = postorder.back();
		postorder.pop_back();
		if(!vis2[v])
		{
			solution++;
			mark_sss(v);
		}
	}

	cout<<solution<<'\n';
	for(int i=1;i<=m;i++)
	{
		if(solv[i]==0)
			cout<<'>';
		else
			cout<<'<';
	}
	return 0;
}