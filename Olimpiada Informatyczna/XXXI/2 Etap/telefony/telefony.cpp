//wersja z lepszymi liczbami pierwszymi
// XXXI Olimpiada Informatyczna - 2 Etap
// Mateusz Woloszyk
// Solution for 100/100 pkt
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long

constexpr int maxn=500000+7;
constexpr int maxp=1e6+7;
constexpr __int128 mod=1000000000200010009;

int n;
int l;
int k;

vector<int>vec[maxn];

__int128 p1=1000000123;
__int128 p2=1000027087;

__int128 P1[maxp];
__int128 P2[maxp];

map<pair<ll,ll>,vector<int>>m;

int g[maxn];
map<pair<int,int>,bool>con;

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	P1[0]=1;
	for(int i=1;i<maxp;++i)
		P1[i]=(P1[i-1]*p1)%mod;
	P2[0]=1;
	for(int i=1;i<maxp;++i)
		P2[i]=(P2[i-1]*p2)%mod;

	cin>>n;
	for(int j=1;j<=n;++j)
	{
		vec[j].push_back(0);
		cin>>l;
		for(int i=1;i<=l;++i)
		{
			cin>>k;
			if(vec[j][vec[j].size()-1]<j && j<k)
				vec[j].push_back(j);
			vec[j].push_back(k);
		}
		if(vec[j][vec[j].size()-1]<j)
			vec[j].push_back(j);
		//hashuje vec[j]
		__int128 hash1=0;
		__int128 hash2=0;
		for(int i=1;i<vec[j].size();++i)
		{
			hash1=(hash1+((__int128)vec[j][i]*P1[i])%mod)%mod;
			hash2=(hash2+((__int128)vec[j][i]*P2[i])%mod)%mod;
		}
		// cout<<(ll)hash1<<" "<<(ll)hash2<<endl;
		m[{(ll)hash1,(ll)hash2}].push_back(j);
	}

	int num=0;
	for(auto &u: m)
	{
		num++;
		for(auto &v: u.s)
			g[v]=num;
	}
	for(auto &u: m)//tu cos nie smiga
	{
		// vec[u.s[0]] <- zawiera wszystkie polaczenia grupy
		// g[u.s[0]] <-> g[v]
		for(auto &v: vec[u.s[0]])
		{
			if(v==0) continue;
			int a=g[u.s[0]];
			int b=g[v];
			if(a>b) swap(a,b);
			if(a!=b)
				con[{a,b}]=1;
		}
	}

	//sprawdzam przypadek num==1 wtedy od to -1 jesli jest n=1 -2 jesli n>1
	if(num==1)
	{
		if(n==1)
		{
			cout<<1<<'\n';
			cout<<1<<'\n';
		}
		else
		{
			cout<<2<<'\n';
			cout<<2<<' ';for(int i=2;i<=n;++i) cout<<1<<' '; cout<<'\n';
			cout<<1<<' '<<2<<'\n';
		}
		return 0;
	}

	cout<<num<<'\n';
	for(int i=1;i<=n;++i)
		cout<<g[i]<<' ';
	cout<<'\n';
	for(auto &u: con)
		cout<<u.f.f<<' '<<u.f.s<<'\n';
	return 0;
}