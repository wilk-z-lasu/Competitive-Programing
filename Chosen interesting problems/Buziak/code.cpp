#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int inf = 1e9+7;
constexpr int maxk = 5e5+7;

string w;
int n,k;
string s;

struct node
{
    int next[26] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int link=0;
    int solv=inf;
    vector<int>id;
};
vector<node>vec;

void BFS()
{
    queue<int>q;
    q.push(0);
    while(!q.empty())
    {
        int v = q.front();
        q.pop();

        for(int i=0;i<26;i++)
        {
            if(v==0 && vec[v].next[i]==0)
                continue;
            else if(vec[v].next[i]==-1)
            {
                vec[v].next[i] = vec[vec[v].link].next[i];
                // if(vec[v].next[i]!=0) cout<<(char)(i+'a')<<": "<<v<<" -> "<<vec[v].next[i]<<endl;
            }
            else
            {
                vec[vec[v].next[i]].link = vec[vec[v].link].next[i];
                if(v==0) vec[vec[v].next[i]].link = 0;
                q.push(vec[v].next[i]);
                // cout<<vec[v].next[i]<<" ==>> "<<vec[vec[v].next[i]].link<<endl;
            }
        }
    }
}

vector<int>graf[maxk];
int solv[maxk];
int siz[maxk];

void DFS(int v=0)
{
    for(auto &u: graf[v])
    {
        DFS(u);
        vec[v].solv = min(vec[v].solv, vec[u].solv);
    }
    for(auto &u: vec[v].id)
        solv[u] = vec[v].solv;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>w; n = w.size();
    w = '#' + w;

    vec.push_back({});

    cin>>k;
    for(int it=1;it<=k;it++)
    {
        cin>>s;
        siz[it] = s.size(); 
        int v = 0;
        for(int i=0;i<s.size();i++)
        {
            if(vec[v].next[s[i]-'a']==-1)
            {
                vec.push_back({});
                vec[v].next[s[i]-'a'] = vec.size()-1;
                // cout<<v<<" -> "<<vec[v].next[s[i]-'a']<<endl;
            }
            v = vec[v].next[s[i]-'a'];
        }
        vec[v].id.push_back(it);
    }

    vec[0].link=0;
    for(auto &u: vec[0].next)
        if(u==-1)
            u = 0;
    BFS();

    int v=0;
    for(int i=1;i<w.size();i++)
    {
        v = vec[v].next[w[i]-'a'];
        vec[v].solv = min(vec[v].solv, i);
        // cout<<v<<": "<<vec[v].solv<<endl;
    }

    for(int i=1;i<vec.size();i++)
        graf[vec[i].link].push_back(i);

    DFS();

    for(int i=1;i<=k;i++)
    {
        if(solv[i]==inf)
            cout<<-1<<'\n';
        else
            cout<<solv[i]-siz[i]+1<<'\n';
    }
    return 0;
}