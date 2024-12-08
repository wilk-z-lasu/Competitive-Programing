#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=1e5+7;
constexpr int inf=1e10+7;

int n;
int a,b;
bool kolor[maxn];
int dp[maxn][2][2];//[numer wierzcholka][kolor][wcisniecie] //moj stan jest opisany a wierzcholki mojego poddrzewa sa wylaczone
vector<int>vec[maxn];

void dfs(int v=1, int ojciec=0)
{
	if(vec[v].size()==1 && vec[v][0]==ojciec)//lisc
	{
		dp[v][kolor[v]][0]=0;
		dp[v][!kolor[v]][0]=inf;
		dp[v][!kolor[v]][1]=1;
		dp[v][kolor[v]][1]=inf;
		return;
	}
	for(auto u: vec[v])
	{
		if(u==ojciec) continue;
		dfs(u,v);
	}
	vector<int> bez_wcisku_upgrade;//o ile ulepsze wynik jak zmienie
	int bez_wcisku_wynik=0;
	for(auto u: vec[v])
	{
		if(u==ojciec) continue;
		bez_wcisku_upgrade.push_back(dp[u][0][0]-dp[u][0][1]);
		bez_wcisku_wynik+=dp[u][0][0];
	}
	sort(bez_wcisku_upgrade.begin(),bez_wcisku_upgrade.end(),greater<int>());
	int p=0;
	int pom=0;
	while(p+1<bez_wcisku_upgrade.size() && bez_wcisku_upgrade[p]+bez_wcisku_upgrade[p+1]>0)
	{
		pom+=bez_wcisku_upgrade[p]+bez_wcisku_upgrade[p+1];
		p+=2;
	}
	dp[v][kolor[v]][0]=bez_wcisku_wynik-pom;

	bez_wcisku_wynik=bez_wcisku_wynik-bez_wcisku_upgrade[0];
	p=1;
	pom=0;
	while(p+1<bez_wcisku_upgrade.size() && bez_wcisku_upgrade[p]+bez_wcisku_upgrade[p+1]>0)
	{
		pom+=bez_wcisku_upgrade[p]+bez_wcisku_upgrade[p+1];
		p+=2;
	}
	dp[v][!kolor[v]][0]=bez_wcisku_wynik-pom;



	vector<int> z_wciskiem_upgrade;//o ile ulepsze wynik jak zmienie
	int z_wciskiem_wynik=0;
	for(auto u: vec[v])
	{
		if(u==ojciec) continue;
		z_wciskiem_upgrade.push_back(dp[u][1][0]-dp[u][1][1]);
		z_wciskiem_wynik+=dp[u][1][0];
	}
	sort(z_wciskiem_upgrade.begin(),z_wciskiem_upgrade.end(),greater<int>());

	p=0;
	pom=0;
	while(p+1<z_wciskiem_upgrade.size() && z_wciskiem_upgrade[p]+z_wciskiem_upgrade[p+1]>0)
	{
		pom+=z_wciskiem_upgrade[p]+z_wciskiem_upgrade[p+1];
		p+=2;
	}
	dp[v][!kolor[v]][1]=z_wciskiem_wynik-pom+1;

	z_wciskiem_wynik=z_wciskiem_wynik-z_wciskiem_upgrade[0];
	p=1;
	pom=0;
	while(p+1<z_wciskiem_upgrade.size() && z_wciskiem_upgrade[p]+z_wciskiem_upgrade[p+1]>0)
	{
		pom+=z_wciskiem_upgrade[p]+z_wciskiem_upgrade[p+1];
		p+=2;
	}
	dp[v][kolor[v]][1]=z_wciskiem_wynik-pom+1;
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);


    cin>>n;

    for(int i=1;i<=n-1;i++)
    {
    	cin>>a>>b;
    	vec[a].push_back(b);
    	vec[b].push_back(a);
    }
    for(int i=1;i<=n;i++)
    	cin>>kolor[i];

    dfs();

    if(min(dp[1][0][0],dp[1][0][1])>=inf)
    	cout<<"impossible";
    else
    	cout<<min(dp[1][0][0],dp[1][0][1]);
    
	return 0;
}