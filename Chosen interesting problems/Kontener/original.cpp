// O(q*log(q))
//code which is used in testing this task
//I included it here, because it is the only one I currently have that solves for larger package of test cases
#include <bits/stdc++.h>
using namespace std;

#define ll long long
constexpr int M = (1 << 17);

struct P
{
	ll t,x,y;
	void rd(){cin >> t >> x >> y;}
	ll v1(){return (ll)x*x+(ll)2*x*y;}
	ll v2(){return (ll)y*y;}
	bool operator <(P a){return (ll)(v1()*a.v2()) < (ll)(a.v1()*v2());}
	bool operator >=(P a){return (ll)(v1()*a.v2()) >= (ll)(a.v1()*v2());}
}arr[M];

struct
{
	pair<ll,ll> tree[2*M];
	void insert(int it, P a)
	{
		it += M; tree[it] = {a.v1(), a.v2()};
		while(it)
		{
			it>>=1;
			tree[it].first = max(tree[it*2].first,tree[it*2+1].first);
			tree[it].second = max(tree[it*2].second,tree[it*2+1].second);
		}
	}
	pair<ll,ll> query(int a, int b)
	{
		if(b < a) return {0,0};
		pair<ll,ll> res = {0,0}; a += M; b += M;
		for(; a<=b; a=(a+1)/2, b=(b-1)/2)
		{
			if(a&1)
			{
				res.first = max(res.first, tree[a].first);
				res.second = max(res.second, tree[a].second);
			}
			if(!(b&1))
			{
				res.first = max(res.first, tree[b].first);
				res.second = max(res.second, tree[b].second);
			}
		}
		return res;
	}
}seg;

int it[M];
bool f;
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int q,x; cin >> q; vector <int> ls;
	for(int i=1; i<=q; i++)
	{
		arr[i].rd();
		if(arr[i].t == 1) ls.push_back(i);
	}
	sort(ls.begin(),ls.end(),[&](int i,int j){return arr[i]<arr[j];});
	for(int i=0; i<(int)ls.size(); i++) it[ls[i]] = i+1;

	for(int i=1; i<=q; i++)
	{
		if(arr[i].t == 1) seg.insert(it[i],arr[i]),f=1;
		else if(f)
		{
			swap(arr[i].x,arr[i].y); int l=0, r=(int)ls.size();
			while(l < r)
			{
				int mid=(l+r+1)/2;
				if(arr[i] >= arr[ls[mid]]) l = mid;
				else r = mid-1;
			}
			if(arr[i] < arr[ls[0]]) x = 0;
			else if(l == ls.size()) x = l+1;
			else x = it[ls[l]];
			ll r1 = (ll)seg.query(1,x).first*arr[i].v2();
			ll r2 = (ll)seg.query(x+1,(int)ls.size()).second*arr[i].v1();
			cout << max(r1,r2) << '\n';
		}
		else cout << "0\n";
	}
}