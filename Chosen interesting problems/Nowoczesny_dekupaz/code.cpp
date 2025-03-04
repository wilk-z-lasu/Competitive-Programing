#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast, unroll-loops")
// #define int long long
#define sz(A) (int)A.size()
#define pb push_back
#define pi pair<int,int>
#define f first
#define s second

constexpr int inf = 1e9+1;
constexpr int maxn = 5e5+1;

constexpr int p = 13;
constexpr __int128 mod = 1e18+3;
__int128 pot[maxn];

int n,m;
char s[maxn];
int tab[maxn];

int a[maxn],b[maxn];

int indentify(char z) {
	if(z=='(')
		return 1;
	else if(z==')')
		return -1;
	else if(z=='[')
		return 2;
	else if(z==']')
		return -2;
	else if(z=='{')
		return 3;
	else if(z=='}')
		return -3;
	else if(z=='<')
		return 4;
	else
		return -4;
}
map<__int128,int>M1;
int Free;

vector<int> kub[maxn];

constexpr int M =(1<<19);
struct drzewo {
	__int128 tree[2*M];
	void clear()
	{
		for(int i=0;i<2*M;++i)
			tree[i]=0;
	}
	inline void add_tree(int a, int b, __int128 val, int v=1, int l=1, int r=M)
	{
		if(r<a || b<l) return;
		if(a<=l && r<=b)
		{
			tree[v]=(tree[v]+val)%mod;
			return;
		}
		int mid=(l+r)>>1;
		add_tree(a,b,val,2*v,l,mid);
		add_tree(a,b,val,2*v+1,mid+1,r);
	}
	__int128 get_tree(int poz)
	{
		poz = M + poz - 1;
		__int128 odp=0;
		while(poz)
		{
			odp=(odp+tree[poz] + mod+mod)%mod;
			poz>>=1;
		}
		return odp;
	}
} allowed, hashes;

vector<__int128> solv()
{
	vector<__int128>odp;
	vector<pi>S;
	int wyk=0;
	for(int i=1;i<=n;++i)
	{
		if(tab[i] > 0)
		{
			wyk++;
			hashes.add_tree(1,i,(tab[i]*pot[wyk])%mod);
			S.pb({tab[i],i});
		}
		else if(tab[i] < 0)
		{
			if(S.empty() || S.back().f != -tab[i])
			{
				allowed.add_tree(1,i,1);
				S.clear();
				wyk=0;
			}
			else
			{
				hashes.add_tree(1,S.back().s,-(-tab[i]*pot[wyk])%mod);
				allowed.add_tree(S.back().s+1,i,1);
				S.pop_back();
				wyk--;
			}
		}

		for(auto &start: kub[i])
		{
			if(allowed.get_tree(start) > 0) continue;
			if(S.empty() || S.back().s < start)
			{
				++Free;
				continue;
			}
			odp.pb((hashes.get_tree(start)*pot[n-wyk])%mod);
		}
	}
	return odp;
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>s[i];

	for(int i=1;i<=n;i++)
		tab[i] = indentify(s[i]);

	pot[0]=1;
	for(int i=1;i<=n+1;i++)
		pot[i] = (pot[i-1]*p)%mod;

	for(int i=1;i<=m;i++)
		cin>>a[i]>>b[i];

	for(int i=1;i<=m;i++)
		kub[b[i]].pb(a[i]);

	vector<__int128>left = solv();
	for(auto &u: left)
		M1[u]++;

	Free=0;
	allowed.clear();
	hashes.clear();
	for(int i=1;i<=n;i++)
		kub[i].clear();

	reverse(&tab[1], &tab[n+1]);
	for(int i=1;i<=n;i++)
		tab[i]=-tab[i];

	for(int i=1;i<=m;i++)
		kub[n-a[i]+1].pb(n-b[i]+1);

	vector<__int128>right = solv();
	int Solv = (Free>>1);

	for(auto &u: right)
	{
		if(M1[u]>0)
		{
			M1[u]--;
			Solv++;
		}
	}
	cout<<Solv<<endl;
}1