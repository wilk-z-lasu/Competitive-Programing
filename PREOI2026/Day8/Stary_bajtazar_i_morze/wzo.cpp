#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=1503;

int n,m,q;
char znak;

int cord_to_id(int y, int x)
{
    if(x<1 || x>m || y<1 || y>n) return 0;
    return (y-1)*m+x;
}

constexpr int maxi=maxn*maxn;
int Next[maxi];
vector<int> Rev[maxi];

int vis[maxi];
int timer;
vector<vector<int>> cycles;
int have_cycle(int v)
{
    if(v==0) return false;
    vis[v]=timer;
    int u=Next[v];
    if(vis[u]==timer)
    {
        cycles.pb({v});
        return u;
    }
    if(vis[u]==0)
    {
        int stop_when = have_cycle(u);
        if(stop_when>0)
        {
            cycles.back().pb(v);
            if(v==stop_when) return 0;
            else return stop_when;
        }
    }
    return false;
}
int cycle_num[maxi];// [v] = which cycle v is in
int cycle_ord[maxi];// [v] = which element of cycle v is

int head[maxi];
int tin[maxi];
int tout[maxi];
int depth[maxi];
int czas;
void make_head(int v)
{
    tin[v]=++czas;
    for(auto &u: Rev[v])
    {
        if(head[u]) continue;
        depth[u]=depth[v]+1;
        head[u]=head[v];
        make_head(u);
    }
    tout[v]=czas;
}

bool is_subtree(int a, int b) // is b in subtree of a
{
    if(head[a]!=head[b]) return false;
    return tin[a]<=tin[b] && tout[b]<=tout[a];
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            cin>>znak;
            int v=cord_to_id(i,j);
            int u;
            if(znak=='^')
            {
                u = cord_to_id(i-1,j);
            }
            else if(znak=='v')
            {
                u = cord_to_id(i+1,j);
            }
            else if(znak=='>')
            {
                u = cord_to_id(i,j+1);
            }
            else if(znak=='<')
            {
                u = cord_to_id(i,j-1);
            }

            // cout<<v<<" -> "<<u<<"\n";
            Next[v] = u;
            Rev[u].pb(v);
        }
    }

    // for(int i=1;i<=n;++i)
    // {
    //     for(int j=1;j<=m;++j)
    //         cout<<cord_to_id(i,j)<<" ";
    //     cout<<"\n";
    // }

    for(int i=1;i<=n*m;++i)
    {
        if(vis[i]==0)
        {
            ++timer;
            have_cycle(i);
        }
    }

    cycles.pb({0});

    int k=-1;
    for(auto &cycle: cycles)
    {
        reverse(cycle.begin(), cycle.end());
        ++k;
        // cout<<"cycle["<<k<<"] = ";
        int k_cycle = 0;
        for(auto &v: cycle)
        {
            // cout<<v<<" ";
            head[v]=v;
            depth[v]=0;
            cycle_num[v]=k;
            cycle_ord[v] = k_cycle++;
        }
        // cout<<"\n";
        for(auto &v: cycle)
        {
            czas = 0;
            make_head(v);
        }
    }

    // for(int i=1;i<=n*m;++i)
    // {
    //     cout<<"i: "<<i<<" head: "<<head[i]<<" depth: "<<depth[i]<<" tin: "<<tin[i]<<" tout: "<<tout[i]<<"\n";
    // }

    cin>>q;
    for(int iter=1;iter<=q;++iter)
    {
        int a,b,c,d;
        char Z;
        cin>>a>>b>>c>>d>>Z;
        int v=cord_to_id(a,b);
        int x=cord_to_id(c,d);
        int z;
        if(Z=='^')
            z = cord_to_id(c-1,d);
        else if(Z=='v')
            z = cord_to_id(c+1,d);
        else if(Z=='>')
            z = cord_to_id(c,d+1);
        else if(Z=='<')
            z = cord_to_id(c,d-1);


        // cout<<"zapytanie: "<<v<<" "<<x<<"\n";
        // cout<<head[x]<<endl;

        int odp=0;
        if(head[x] == x) // x jest w cyklu
        {
            if(head[v] == 0) // v jest poza drzewem
                odp = depth[v];
            else if(cycle_num[head[v]] == cycle_num[x]) // v jest w tym samym cyklu co x
            {
                odp = depth[v];
                int cycle_siz = sz(cycles[cycle_num[x]]);
                odp += (cycle_ord[x] - cycle_ord[head[v]] + cycle_siz)%cycle_siz + 1; //ship is in z
                if(head[z] == 0)
                    odp += depth[z];
                else
                    odp = 0;
            }
            else
                odp = 0;
        }
        else // x jest w drzewie
        {
            if(is_subtree(x,v)) // v i x są w tym samym drzewie // v jest w poddrzewie x
            {
                odp = depth[v] - depth[x] + 1;// ship is is z

                if(is_subtree(x,z))
                    odp = 0;
                else
                {
                    if(head[z] == 0)
                        odp += depth[z];
                    else
                        odp = 0;
                }
            }
            else if(head[v] == 0)
                odp = depth[v];
            else
                odp = 0;
        }
        cout<<odp<<'\n';
    }
    return 0;
}