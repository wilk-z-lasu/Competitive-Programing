#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=2e5+7;
int n;
pair<int,int>tab[maxn];

bool extra=0;
int taken_cnt=0;
int last;
bool taken[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>tab[i].f>>tab[i].s;
    sort(&tab[1], &tab[n+1]);

    last=tab[n].s;
    taken[n]=1;
    taken_cnt=1;
    for(int i=n-1;i>=1;i--)
    {
        if(tab[i].s > last)
        {
            last = tab[i].s;
            taken[i]=1;
            taken_cnt++;
        }
        else if(tab[i].s > tab[n].s)
            extra=1;
    }
    last = -1;
    for(int i=1;i<=n;i++)
    {
        if(taken[i])
            last = tab[i].s;
        else if(tab[i].s < last)
            extra=1;
    }

    if(taken_cnt%2==0 || extra)
        cout<<"TAK";
    else
        cout<<"NIE";
    return 0;
}