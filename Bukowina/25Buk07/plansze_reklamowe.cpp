#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

#define f first
#define s second
#define pi pair<int,int>

#define pb push_back
#define sz(A) (int)A.size()

constexpr int inf = 1e18+7;

int n;

vector<pair<pi,pi>> obj;
vector<pair<pi,pi>> del;
vector<pair<int,pi>> zap;
map<int,int>skal;

constexpr int M=(1<<20);//20
int tree[2*M];
multiset<int> akt[2*M];

void add_tree(int a, int b, int val, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return;
    if(a<=l && r<=b)
        akt[v].insert(val);
    else
    {
        int mid = (l+r)/2;
        add_tree(a,b,val, 2*v, l,mid);
        add_tree(a,b,val, 2*v+1, mid+1,r);
        tree[v] = min(tree[2*v], tree[2*v+1]);
    }
    if(!akt[v].empty()) tree[v] = max(tree[v], *(--akt[v].end()));
}
void del_tree(int a, int b, int val, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return;
    if(a<=l && r<=b)
    {
        tree[v]=0;
        akt[v].erase(akt[v].find(val));
    }
    else
    {
        int mid = (l+r)/2;
        del_tree(a,b,val, 2*v, l,mid);
        del_tree(a,b,val, 2*v+1, mid+1,r);
    }
    if(v < M) tree[v] = min(tree[2*v], tree[2*v+1]);
    if(!akt[v].empty()) tree[v] = max(tree[v], *(--akt[v].end()));
}
int get_tree(int a, int b, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return inf;
    if(a<=l && r<=b)
        return tree[v];
    int mid = (l+r)/2;
    int mini = min(
        get_tree(a,b, 2*v, l,mid),
        get_tree(a,b, 2*v+1, mid+1,r));
    mini = max(mini, tree[v]);
    mini = max(mini, min(tree[2*v], tree[2*v+1]));
    return mini;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
    {
        char c;
        cin>>c;
        if(c=='+')
        {
            int l,p,w;
            cin>>l>>p>>w;
            p--;
            skal[l]=skal[p]=skal[p+1]=1;
            obj.pb({{i,w},{l,p}});
        }
        else if(c=='-')
        {
            int r;
            cin>>r;
            --r;
            del.pb({{i,obj[r].f.s},obj[r].s});
        }
        else if(c=='?')
        {
            int l,p;
            cin>>l>>p;
            p--;
            skal[l]=skal[p]=skal[p+1]=1;
            zap.pb({i,{l,p}});
        }
    }

    int cnt=0;
    for(auto &u: skal)
        u.s = ++cnt;

    // for(auto &u: skal)
    //     cout<<u.f<<' '<<u.s<<endl;

    reverse(obj.begin(), obj.end());
    reverse(del.begin(), del.end());
    reverse(zap.begin(), zap.end());

    // cout<<"wczytane"<<endl;
    for(int i=1;i<=n;++i)
    {
        // cout<<"---"<<i<<"----"<<endl;
        if(!obj.empty() && obj.back().f.f==i)
        {
            // cout<<"dodaj: "<<skal[obj.back().s.f]<<" "<<skal[obj.back().s.s]<<" "<<obj.back().f.s<<endl;
            add_tree(skal[obj.back().s.f], skal[obj.back().s.s], obj.back().f.s);
            obj.pop_back();
        }
        if(!del.empty() && del.back().f.f==i)
        {
            del_tree(skal[del.back().s.f], skal[del.back().s.s], del.back().f.s);
            del.pop_back();
        }
        if(!zap.empty() && zap.back().f==i)
        {
            // cout<<"zapytaj: "<<skal[zap.back().s.f]<<" "<<skal[zap.back().s.s]<<endl;
            cout<<get_tree(skal[zap.back().s.f], skal[zap.back().s.s])<<'\n';
            zap.pop_back();
        }
    }
    
    return 0;
}