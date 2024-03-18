// XXXI Olimpiada Informatyczna - 2 Etap
// Mateusz Woloszyk
// Solution for 100/100 pkt
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=300000+7;

int n,m;
int a;

int c[maxn];
int p[maxn];

vector<pair<int,int>>kolejnosc;//rozpatruje od najdrozszych i najmniejszym poczatku(chyba nie potrzebne)
//.f=koszt .s=-poczatek

void koniec()
{
	cout<<"NIE\n";
	exit(0);
}

int solv;

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n>>m;
	vector<multiset<int>>vec(m+1);

	for(int i=1;i<=n;++i)
		cin>>c[i];
	for(int i=1;i<=n;++i)
		cin>>p[i];

	for(int i=1;i<=n;++i)
		kolejnosc.push_back({c[i],-p[i]});

	sort(kolejnosc.begin(),kolejnosc.end(),greater<pair<int,int>>());

	for(int j=1;j<=m;++j)
	{
		for(int i=1;i<=n;++i)
		{
			cin>>a;
			vec[j].insert(a);
		}
	}

	for(auto &u: kolejnosc)
	{
		u.s=-u.s;
		int last=u.s;
		for(int j=1;j<=m;++j)
		{
			auto it=vec[j].lower_bound(last);
			if(it==vec[j].end())
				koniec();
			last=*it;
			vec[j].erase(it);
		}
		solv+=(last-u.s)*u.f;
	}
	cout<<solv;
	return 0;
}