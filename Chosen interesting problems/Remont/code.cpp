#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()


constexpr int maxn = 150000+7;

int t;
int n,k;
int tab[maxn];

map<pi, vector<int>>F;
map<pi, bool>blocked;
bool B[2*maxn];

vector<int>vec[2*maxn];
vector<int>vec_odw[2*maxn];

int no(int id)
{
    if(id<=n)
        return id+n;
    else
        return id-n;
}

void Or(int id1, int id2)
{
    vec[no(id1)].pb(id2);
    vec[no(id2)].pb(id1);
    // cout<<no(id2)<<" -> "<<id1<<endl;
}

void Block(int v)
{
    B[v]=1;
    for(auto &u: vec_odw[v])
        if(!B[u])
            Block(u);
}

// bool vis[2*maxn];
// stack<int> toposort;
// void DFS(int v)
// {
//     vis[v]=1;
//     for(auto u: vec[v])
//     {
//         if(!vis[u]) DFS(u);
//     }
//     toposort.push(v);
// }
// int SSS[2*maxn];
// int SS_liczba;
// void make_SSS(int v)
// {
//     SSS[v]=SS_liczba;
//     for(auto u: vec_odw[v])
//         if(SSS[u]==0) 
//             make_SSS(u);
// }

int start;
bool pos=1;
bool vis[2*maxn];
void dfs(int v)
{
    vis[v]=1;
    if(v==no(start))
        pos=0;
    else
    {
        for(auto &u: vec[v])
        {
            if(!vis[u])
            {
                // cout<<v<<" -> "<<u<<endl;
                dfs(u);
            }
        }
    }
}


void solv()
{
    F.clear();
    blocked.clear();
    // SS_liczba=0;
    for(int i=1;i<=2*n;++i)
    {
        vec[i].clear();
        vec_odw[i].clear();
        B[i]=0;
        // vis[i]=0;
        // SSS[i]=0;
    }

    for(int i=2;i<=n-2;++i)
    {
        pi akt = {tab[i], tab[i+1]};
        F[akt].pb(i);
    }
    for(auto &u: F)
    {
        for(auto &u1: u.s)
        {
            for(auto &u2: u.s)
            {
                if(u1!=u2)
                {
                    vec[u1].pb(no(u2));
                    vec_odw[no(u2)].pb(u1);
                    // cout<<u1<<" -> "<<no(u2)<<endl;
                }
            }
        }
    }

    blocked[{tab[1], tab[2]}]=1;
    blocked[{tab[n-1], tab[n]}]=1;

    for(int i=2;i<=n-2;++i)
        if(blocked.find({tab[i], tab[i+1]}) != blocked.end())
            Block(i);

    for(int i=2;i<=n-2;++i)
    {
        if(B[i] && B[no(i)])
        {
            cout<<"NIE\n";
            return;
        }
    }

    for(int i=3;i<=n-2;++i)
        Or(i-1, i);

    dfs(11);
    for(int i=2;i<=n-2;++i)
    {
        for(int j=1;j<=2*n;++j)
            vis[j]=0;
        pos=1;
        start=i;
        dfs(i);
        if(!pos)
        {
            cout<<"NIE\n";
            return;
        }
    }
    for(int i=no(2);i<=no(n-2);++i)
    {
        cout<<i<<endl;
        for(int j=1;j<=2*n;++j)
            vis[j]=0;
        pos=1;
        start=i;
        dfs(i);
        if(!pos)
        {
            cout<<"NIE\n";
            return;
        }
    }

    // for(int i=2;i<=n-2;++i)
    //     if(!vis[i])
    //         DFS(i);
    // for(int i=2;i<=n-2;++i)
    //     if(!vis[no(i)])
    //         DFS(no(i));

    // while(!toposort.empty())
    // {
    //     int top=toposort.top();
    //     toposort.pop();
    //     if(SSS[top]==0) 
    //     {
    //         SS_liczba++;
    //         make_SSS(top);
    //     }  
    // }

    // for(int i=2;i<=n-2;++i)
    // {
    //     if(SSS[i] <= SSS[no(i)])
    //     {
    //         cout<<"NIE\n";
    //         return;
    //     }
    // }




    cout<<"TAK\n";
    return;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        for(int i=1;i<=n;++i)
            cin>>tab[i];

        if(tab[1] == tab[n-1] && tab[2]==tab[n])
        {
            cout<<"NIE\n"; 
            continue;
        }
        solv();
    }
    

    return 0;
}