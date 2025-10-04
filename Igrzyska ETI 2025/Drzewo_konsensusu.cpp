#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

#define pb push_back
#define sz(A) (int)A.size()
#define pi pair<int,int>
#define f first
#define s second

int t;
int n,p;
string s;
bool part_of_name(const char& c) {
    if(c!='(' && c!=',' && c!=')' && c!=';')
        return 1;
    else
        return 0;
}

map<string,int>name_ID;//needs clearing
map<int,string>ID_to_NAME;//needs clearing
map<vector<int>, int>Con;//needs clearing
vector<pair<int,vector<int>>>Pernament_Con;//needs clearing
vector<vector<pi>>VEC;

void make_tree(const string& tree) {
    vector<vector<int>>vec = {{}};
    vector<int>up = {0};
    vector<vector<int>>IDs = {{}};

    int v=0;
    for(int i=0; i<sz(tree); ++i)
    {
        if(tree[i] == ',' || tree[i] == ')' || tree[i] == ';')
        {
            sort(IDs[v].begin(), IDs[v].end());
            Con[IDs[v]]++;

            for(auto &u: IDs[v])
                IDs[up[v]].pb(u);

            v = up[v];
        }
        else
        {
            int new_node = sz(vec);
            vec[v].pb(new_node);
            vec.pb({});
            up.pb(v);
            IDs.pb({});

            if(tree[i]!='(')
            {
                string name = "";
                name += tree[i];
                while(part_of_name(tree[i+1]))
                    name += tree[++i];
                IDs[new_node].pb(name_ID[name]);
            }
            v = new_node;
        }
    }
}

void dfs(int v, int name_val)
{
    if(v<=name_val)
        cout<<ID_to_NAME[v];
    else
        cout<<'(';

    for(const auto &u: VEC[v])
    {
        if(u!=VEC[v][0])
            cout<<',';
        dfs(u.s, name_val);
    }
    if(v>name_val)
        cout<<')';
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>t;
    while(t--)
    {
        //CLEAR
        name_ID.clear();
        ID_to_NAME.clear();
        Con.clear();
        Pernament_Con.clear();
        //

        cin>>n>>p;
        cin>>s;
        for(int i=0;i+1<sz(s);++i)
        {
            string name = "";
            while(part_of_name(s[i+1]))
                name += s[++i];
            if(name != "")
                name_ID[name] = 1;
        }

        int nadaj=0;
        for(auto &u: name_ID)
        {
            u.s=++nadaj;
            ID_to_NAME[nadaj] = u.f;
        }

        // for(auto &u: name_ID)
        //     cout<<u.f<<": "<<u.s<<endl;

        make_tree(s);
        for(int i=2;i<=n;++i)
        {
            cin>>s;
            make_tree(s);
        }

        for(auto &u: Con)
            if(u.s * 100 >= p * n)
                Pernament_Con.pb({sz(u.f), u.f});
        sort(Pernament_Con.begin(), Pernament_Con.end());

        vector<int>rep(nadaj+1);
        for(int i=0; i<=nadaj; ++i)
            rep[i]=i;
        vector<vector<bool>>Lacz(sz(Pernament_Con)+1, vector<bool>(sz(Pernament_Con)+1, 0));
        VEC.resize(sz(Pernament_Con)+1);
        for(int i=0; i<=sz(Pernament_Con); ++i)
            VEC[i].clear();
        vector<int>mini(sz(Pernament_Con)+1);
        mini[0]=0;
        int v=1;
        for(const auto &[xd, u]: Pernament_Con)
        {
            for(const auto& e: u)
                Lacz[v][rep[e]]=1;
            for(const auto& e: u)
                rep[e] = v;
            mini[v] = u[0];
            ++v;
        }

        for(int i=1; i<=sz(Pernament_Con); ++i)
        {
            for(int j=1; j<i; ++j)
                if(Lacz[i][j])
                    VEC[i].pb({mini[j],j});
            sort(VEC[i].begin(), VEC[i].end());
        }
        dfs(sz(Pernament_Con), nadaj);
        cout<<";\n";
    }
    return 0;
}