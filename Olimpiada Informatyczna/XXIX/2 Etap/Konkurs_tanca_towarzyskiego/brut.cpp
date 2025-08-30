#include <bits/stdc++.h>
using namespace std;
// #define int long long

#define pb push_back
#define sz(A) (int)A.size()
#define pi pair<int,int>
#define f first
#define s second

constexpr int maxq = 5000+7;
constexpr int inf = 1e9+7;

int q;
char c;
int x;
vector<int>vec[maxq];

int32_t main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vec[1].pb(2);
    vec[2].pb(1);

    cin>>q;
    int it=2;
    while(q--)
    {
        cin>>c>>x;
        if(c == '?')
            cout<<vec[x].size()<<'\n';
        if(c == 'Z')
        {
            vec[++it] = vec[x];
            for(auto &u: vec[it])
                vec[u].pb(it);
        }
        if(c == 'W')
        {
            ++it;
            vec[it].pb(x);
            vec[x].pb(it);
        }
    }
    return 0;
}