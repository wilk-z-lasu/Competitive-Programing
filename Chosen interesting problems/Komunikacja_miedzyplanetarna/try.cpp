#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define ld long double

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)(A.size())

constexpr int maxn=1e5+7;

int n;
pi tab[maxn];

ld odl(ld x1, ld y1, ld x2, ld y2)
{
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

ld distance(ld x, ld y)
{
    ld res = 0;
    for(int i=1;i<=n;++i)
        res += odl(x,y,tab[i].f,tab[i].s);
    return res;
}


int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>tab[i].f>>tab[i].s;
    
    for(int i=1;i<=n;++i)
        cout<<distance(tab[i].f, tab[i].s)<<'\n';
}