// Solution for 73/100 points
// O(n*log(n) + q*(log(n)^2))
// My idea, but written after contest
// Mateusz Woloszyk

#include <bits/stdc++.h>
using namespace std;
#define int long long

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)(A.size())

constexpr int maxn=1e6+7;
constexpr int inf=1e9+7;

int n,q;
int L,R,K;
int d[maxn];
int ones[maxn];

constexpr int M = (1<<19);
struct node {
    int val;
    int pref;
    node *l, *r;
};
vector<node>tree[2*M];

void add_tree(int pos, int val)
{
    pos += M;
    tree[pos].push_back({val, val, nullptr, nullptr});
}
void combine(int v)
{
    node *it1 = &tree[2*v][0];
    node *it2 = &tree[2*v+1][0];
    
    for(int i = 0; i < (sz(tree[2*v]) + sz(tree[2*v+1])) - 1; ++i)
    {
        bool opt;
        if(it1 == &tree[2*v].back())
            opt = 1;
        else if(it2 == &tree[2*v + 1].back())
            opt = 0;
        else if((*(it1+1)).val >= (*(it2+1)).val)
            opt = 0;
        else
            opt = 1;
        
        if(opt==0)
        {
            if(it1 + 1 <= &tree[2*v].back()) {
                it1++;
                tree[v].push_back({(*it1).val, tree[v].back().pref + (*it1).val, it1, it2});
            }
        }
        else
        {
            if(it2 + 1 <= &tree[2*v+1].back()) {
                it2++;
                tree[v].push_back({(*it2).val, tree[v].back().pref + (*it2).val, it1, it2});
            }
        }
    }
}

pi get_tree(int a, int b, node* it, int v = 1, int l = 0, int r = M-1)
{
    if(it == nullptr) return {0,0};
    if(r<a || b<l) return {0,0};
    if(a<=l && r<=b)
        return {(*it).pref, it - &tree[v][0]};
    int mid = (l + r) / 2;
    auto left = get_tree(a, b, (*it).l, 2*v, l, mid);
    auto right = get_tree(a, b, (*it).r, 2*v+1, mid+1, r);
    return {left.f + right.f, left.s + right.s};
}

void wypisz(int v)
{
    for(auto &u: tree[v])
        cout<<u.val<<" "<<u.pref<<" "<<u.l<<" "<<u.r<<endl;
    cout<<endl;
}

int bin_search(int cost, int a, int b)
{
    int l=0;
    int r = sz(tree[1])-1;
    while(l<r)
    {
        int mid = (l+r+1)/2;
        // cout<<l<<" "<<r<<" - "<<mid<<endl;
        if(get_tree(a, b, &tree[1][mid]).s <= cost)
            l = mid;
        else
            r = mid - 1;
    }
    return get_tree(a, b, &tree[1][l]).f;
}
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n>>q;
	for(int i=0;i<n;++i)
		cin>>d[i];

    for(int i=0;2*i<n;++i)
        ones[i] = d[2*i];

    for(int i=1;i<2*M;++i)
        tree[i].push_back({0, 0, nullptr, nullptr});

    for(int i=0;2*i<n;++i)
        add_tree(i, ones[i]);

    for(int i=M-1;i>0;--i)
        combine(i);

    vector<pi>prefix = {make_pair(d[0], 0)};
    for(int i=1;i<n;++i)
        prefix.push_back({prefix.back().f + d[i], i});

    for(int i=1;i<=q;++i)
    {
        cin>>L>>R>>K;
        pi left = {L,0};
        auto l = lower_bound(prefix.begin(), prefix.end(), left);
        pi right = {R,0};
        auto r = lower_bound(prefix.begin(), prefix.end(), right);
        if((*l).s == (*r).s)
        {
            if((*l).s%2 == 0)
                cout<<R-L+1<<'\n';
            else
                cout<<0<<'\n';
            continue;
        }

        int l_one = (*l).s;
        l_one++;
        if(l_one%2 == 1)
            l_one++;
        
        int r_one = (*r).s;
        r_one--;
        if(r_one%2 == 1)
            r_one--;
        
        int ones_left = 0;
        if((*l).s%2 == 0)
            ones_left = (*l).f - L + 1;
        int ones_right = 0;
        if((*r).s%2 == 0)
            ones_right = R - (*(r-1)).f;
        
        l_one /=2;
        r_one /=2;

        int solv = 0;
        if(l_one <= r_one)
        {
            solv = max(solv, bin_search(K/2,l_one, r_one));
            if(K>=1) solv = max(solv, bin_search((K-1)/2,l_one, r_one) + max(ones_left, ones_right));
            if(K>=2) solv = max(solv, bin_search((K-2)/2,l_one, r_one) + ones_left + ones_right);
        }
        else
        {
            if(K>=1)
                solv = max(solv,max(ones_left, ones_right));
            if(K>=2)
                solv = max(solv, ones_left + ones_right);
        }
        cout<<solv<<'\n';
    }
}