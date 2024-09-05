#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=1000+7;

int n,q;
char x;
int zap;
int tab[maxn][maxn];

constexpr int M=(1<<10);
int tree[2*M][2*M];

void change_tree_y(int f, int y, int add)
{
    y=y+M-1;
    tree[f][y] += add;
    y/=2;
    while(y)
    {
        tree[f][y] = tree[f][2*y] + tree[f][2*y+1];
        y/=2;
    }
}

void change_tree_x(int x, int y, int add, int v=1, int l=1, int r=M)
{
    change_tree_y(v, y, add);
    if(l==r) return;
    int mid=(l+r)/2;
    if(x<=mid)//ide do lewego drzewa
        change_tree_x(x,y,add, 2*v, l, mid);
    else//ide do prawego drzewa
        change_tree_x(x,y,add, 2*v+1, mid+1, r);
}

int sum_tree_y(int Y1, int Y2, int org, int v=1, int l=1, int r=M)
{
    if(r<Y1 || Y2<l) return 0;
    if(Y1<=l && r<=Y2)
        return tree[org][v];
    int mid=(l+r)/2;
    return sum_tree_y(Y1,Y2,org, 2*v, l,mid) + sum_tree_y(Y1,Y2,org, 2*v+1, mid+1,r);
}

int sum_tree_x(int X1, int X2, int Y1, int Y2, int v=1, int l=1, int r=M)
{
    if(r<X1 || X2<l) return 0;
    if(X1<=l && r<=X2)
        return sum_tree_y(Y1,Y2, v);
    int mid=(l+r)/2;
    return sum_tree_x(X1,X2,Y1,Y2, 2*v, l,mid) + sum_tree_x(X1,X2,Y1,Y2, 2*v+1, mid+1,r);
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>x;
            if(x=='*')
            {
                tab[j][i]=1;
                change_tree_x(j,i,1);
            }
        }
    }
    while(q--)
    {
        cin>>zap;
        if(zap==1)
        {
            int X,Y;
            cin>>Y>>X;
            if(!tab[X][Y])
                change_tree_x(X,Y,1);
            else
                change_tree_x(X,Y,-1);
            tab[X][Y] = !tab[X][Y];
        }
        else if(zap==2)
        {
            int X1,Y1, X2,Y2;
            cin>>Y1>>X1>>Y2>>X2;
            cout<<sum_tree_x(X1,X2,Y1,Y2)<<'\n';
        }
    }
    return 0;
}