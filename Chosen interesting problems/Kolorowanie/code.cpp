#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=107;
int n;

int gora[maxn];
int dol[maxn];

bool i_already_have[maxn];

int oposite[2*maxn];

void prepere()
{
    for(int i=1;i<=n;i++)
        cin>>gora[i];
    for(int i=1;i<=n;i++)
        cin>>dol[i];
    for(int i=1;i<=n;i++)
    {
        if(i_already_have[gora[i]])
            gora[i]+=n;
        else 
            i_already_have[gora[i]]=1;
    }
    for(int i=1;i<=n;i++)
    {
        if(i_already_have[dol[i]])
            dol[i]+=n;
        else 
            i_already_have[dol[i]]=1;
    }
    for(int i=1;i<=n;i++)
        oposite[gora[i]]=dol[i];
    for(int i=1;i<=n;i++)
        oposite[dol[i]]=gora[i];
}

int second_number(int x)
{
    if(x<=n) return x+n;
    else return x-n;
}

int vis[2*maxn];
void mark_as_done(int x)
{
    if(vis[x]==1) return;
    else if(vis[x]==2)
    {
        cout<<0;
        exit(0);
    }
    vis[x]=1;
    // cout<<"i marked "<<x<<" as 1\n";
    vis[oposite[x]]=2;
    // cout<<"i marked "<<oposite[x]<<" as 2\n";

    mark_as_done(second_number(oposite[x]));
}
int solv;
vector<int>odp;

void cout_odp()
{
    for(int i=odp.size()-1;i>=0;--i)
        cout<<odp[i];
    cout<<endl;
}

void multiply_odp()
{
    int pomoc=0;
    for(int i=0;i<odp.size();++i)
    {
        odp[i]*=2;
        odp[i]+=pomoc;
        pomoc=0;
        // cout<<i<<": "<<odp[i]<<endl;

        if(odp[i]>=10)
        {
            pomoc=odp[i]/10;
            odp[i]%=10;
        }
    }
    if(pomoc>0)
        odp.push_back(pomoc);
    // cout_odp();
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    prepere();

    for(int i=1;i<=n;i++)
    {
        if(vis[gora[i]]==0)
        {
            solv++;
            mark_as_done(gora[i]);
        }
    }

    odp.push_back(1);

    while(solv>0)
    {
        multiply_odp();
        solv--;
    }

    cout_odp();
    
    return 0;
}