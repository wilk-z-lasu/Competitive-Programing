//O(S), where S = s1 + s2 + ... + sn
//fastest code I wrote for this problem
#include <bits/stdc++.h>
using namespace std;
#define int long long

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)(A.size())

constexpr int maxn = 5e5+7;
int inf = 0;

int n,d;
int s,p;

vector<int>last;//last vector with 0 at the begining and d at the end
vector<int>akt;//current vector with 0 at the begining and d at the end

int pref[2*maxn];

inline void add(int a, int b, int val)//O(1)
{
    pref[a] += val;
    pref[b+1] -= val;
}
inline int get(int a, int b)//O(b-a)
{
    int p = 0;
    int odp = 1e18;
    for(int i=a;i<=b;++i)
    {
        p += pref[i];
        odp = min(odp, p);
    }
    return odp;
}
inline void clear_tree(int a, int b) //O(b-a)
{
    for(int i = a; i <= b+1; ++i)
        pref[i] = 0;
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

    cin>>n>>d;
    for(int iter=1;iter<=n;++iter)
    {
        cin>>s;
        akt.pb(0);
        for(int i=1;i<=s;++i)
        {
            cin>>p;
            akt.pb(p);
        }
        akt.pb(d);

        if(iter==1) 
        {
            last = akt;
            akt.clear();
            continue;
        }

        inf = max(sz(last), sz(akt));

        int it = 0;
        for(int i=0;i<sz(last);++i)
        {
            while(it+1 < sz(akt) && akt[it+1] <= last[i])
                ++it;

            add(-inf+inf, it-i+inf, +last[i]);
            add(it-i+1+inf, +inf+inf, -last[i]);
        }

        it = 0;
        for(int i=0;i<sz(akt);++i)
        {
            while(it+1 < sz(last) && last[it+1] < akt[i])
                ++it;

            add(i-it+inf, +inf+inf, +akt[i]);
            add(-inf+inf, i-it-1+inf, -akt[i]);
        }

        for(int i=-inf;i<=inf;++i)
            add(i+inf,i+inf, abs(sz(akt) - sz(last) - i) * d);

        cout<<get(0, 2*inf)<<'\n';
        clear_tree(0, 2*inf);

        last = akt;
        akt.clear();
    }
}