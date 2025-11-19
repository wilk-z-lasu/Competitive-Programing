#include <bits/stdc++.h>
using namespace std;
#define int long long

#define pi pair<int,int>
#define f first
#define s second
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn = 2e5+7;

int n,r;
int a[maxn];
int L[maxn];
int R[maxn];

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin>>n>>r;
    for(int i=1;i<=n;++i)
        cin>>a[i];
    
    if(r>=0)
    {
        sort(&a[1], &a[n+1]);
        for(int i=1;i<=n;++i)
            cout<<a[i]<<' ';
        return 0;
    }

    sort(&a[1], &a[n+1], greater<int>());

    r = -r;
    set<pi>S;//I can move them
    set<int>B;//blocked
    for(int i=2;i<=n-1;++i)
    {
        L[i] = i-1;
        R[i] = i+1;

        if((a[i-1]-a[i+1]) <= r)
            S.insert({a[i], i});
        else
            B.insert(i);
    }
    B.insert(n);
    vector<int>solv = {a[1]};
    for(int i = 2; i <= n; ++i)
    {
        auto it = S.lower_bound({solv.back() - r, 0});
        if(it == S.end())
        {
            solv.pb(a[*B.begin()]);
            B.erase(B.begin());
        }
        else
        {
            int val = (*it).f;
            int poz = (*it).s;
            solv.pb(val);
            int left = L[poz];
            int right = R[poz];

            R[left] = right;
            L[right] = left;
        
            if(S.find({a[left], left}) != S.end() && abs(a[L[left]] - a[R[left]]) > r)
            {
                S.erase({a[left], left});
                B.insert(left); //left dodaj do B
            }
            if(S.find({a[right], right}) != S.end() && abs(a[L[right]] - a[R[right]]) > r)
            {
                S.erase({a[right], right});
                B.insert(right); //right dodaj do B
            }
            S.erase(it);
        }
    }
    for(auto &u: solv)
        cout<<u<<' ';
    return 0;
}