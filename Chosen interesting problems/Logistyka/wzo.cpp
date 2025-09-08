#include <bits/stdc++.h>
using namespace std;
#define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) ((int)(A).size())

constexpr int maxn = 1e6 + 7;

int n,m;
char z;
int k,a;
int s,c;

int driver[maxn];

constexpr int M = (1<<30);

struct node{
    int max, num, sum;
    int l, r;
    node(){
        max = num = sum = 0;
        l = r = -1;
    }
};
vector<node> vec(1);

void add_tree(int pos, int val, int v = 0, int l = 0, int r = M-1) 
{
    // cout<<"preorder: "<<v<<endl;
    vec[v].max = 0;
    if(r<pos || pos<l) return;
    if(l == pos && r == pos)
    {
        vec[v].sum += val*pos;
        vec[v].num += val;
        if(vec[v].num > 0)
            vec[v].max = pos;
        return;
    }
    int mid = (l+r)/2;
    if(pos <= mid)
    {
        if(vec[v].l == -1)
        {
            vec.pb({});
            vec[v].l = sz(vec)-1;
        }
        add_tree(pos, val, vec[v].l, l, mid);
    }
    else
    {
        if(vec[v].r == -1)
        {
            vec.pb({});
            vec[v].r = sz(vec)-1;
        }
        add_tree(pos, val, vec[v].r, mid+1, r);
    }

    vec[v].max = 0;
    if(vec[v].l != -1)
        vec[v].max = max(vec[v].max, vec[vec[v].l].max);
    if(vec[v].r != -1)
        vec[v].max = max(vec[v].max, vec[vec[v].r].max);
    vec[v].num = 0; 
    if(vec[v].l != -1)
        vec[v].num += vec[vec[v].l].num;
    if(vec[v].r != -1)
        vec[v].num += vec[vec[v].r].num;
    vec[v].sum = 0; 
    if(vec[v].l != -1)
        vec[v].sum += vec[vec[v].l].sum;
    if(vec[v].r != -1)
        vec[v].sum += vec[vec[v].r].sum;
}

int get_num(int a, int b, int v = 0, int l = 0, int r = M-1)
{
    if(r<a || b<l) return 0;
    if(a<=l && r<=b)
        return vec[v].num;
    int mid = (l+r)/2;    
    int solv=0;
    if(vec[v].l != -1)
        solv += get_num(a,b, vec[v].l, l, mid);
    if(vec[v].r != -1)
        solv += get_num(a,b, vec[v].r, mid+1, r);
    return solv;
}
int get_sum(int a, int b, int v = 0, int l = 0, int r = M-1)
{
    if(r<a || b<l) return 0;
    if(a<=l && r<=b)
        return vec[v].sum;
    int mid = (l+r)/2;
    int solv=0;
    if(vec[v].l != -1)
        solv += get_sum(a,b, vec[v].l, l, mid);
    if(vec[v].r != -1)
        solv += get_sum(a,b, vec[v].r, mid+1, r);
    return solv;
}
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n>>m;
    add_tree(0, +n);
    
    for(int i=1;i<=m;++i)
    {
        cin>>z;
        if(z=='U')
        {
            cin>>k>>a;
            add_tree(driver[k], -1);
            driver[k] = a;
            add_tree(driver[k], +1);
        }
        else
        {
            cin>>c>>s;
            int m = get_num(s, M-1);//number of drivers larger then s
            int sum = 0;//sum of drivers smaller then s
            if(0 <= s-1)
                sum = get_sum(0, s-1);
            if((c-m)*s <= sum)
                cout<<"TAK\n";
            else
                cout<<"NIE\n";
        }
    }
	return 0;
}