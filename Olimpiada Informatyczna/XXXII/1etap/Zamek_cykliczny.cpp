#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

// constexpr int maxn=2e5+7;

string w;

bool jeden()
{
    if(w[0]!='1')
        return false;
    for(int i=1;i<w.size();i++)
        if(w[i]!='0')
            return false;
    return true;
}

int f(int x)
{
    int odp=0;
    int cost=1;
    for(int i=(int)w.size()-1;i>=(int)w.size()-x;i--)
    {
        odp += cost*(9-(w[i]-'0'));
        cost *= 10;
    }
    while((int)w.size()-x-1>=0 && w[(int)w.size()-x-1]=='9')
        x++;

    for(int i=0;i<(int)w.size()-x;i++)
    {
        if(w[i]!='0')
        {
            odp++;
            odp += (9-(w[i]-'0'));
        }
    }
    return odp + 2;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>w;
    if(w[0]=='1' && w.size()==1)
    {
        cout<<0;
        return 0;
    }
    if(jeden())
    {
        cout<<1;
        return 0;
    }

    int solv = 1e18+7;
    for(int i=0;i<=min((int)w.size(), (int)10);i++)
        solv = min(solv, f(i));
    cout<<solv;
}