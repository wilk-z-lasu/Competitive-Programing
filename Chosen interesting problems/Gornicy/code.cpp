#include <bits/stdc++.h>
using namespace std;
#define int unsigned
#define f first
#define s second

constexpr int p=4;

int n;
char x;
int tab;

int hash_w[4][4][4][4];
int v0;
int v1;
int v2;
int v3;

unordered_map<int,int>avilable[2];

int how[4][4][4];

inline int how_many_difrent(int x1, int x2, int x3)
{
    return 1+(x2!=x1)+(x3!=x2 && x3!=x1)-(x1==0 || x2==0 || x3==0);
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for(int i0=0;i0<=3;++i0)
    for(int i1=0;i1<=3;++i1)
    for(int i2=0;i2<=3;++i2)
    for(int i3=0;i3<=3;++i3)
    hash_w[i0][i1][i2][i3]=i0*p*p*p+i1*p*p+i2*p+i3;

    for(int i0=0;i0<=3;++i0)
    for(int i1=0;i1<=3;++i1)
    for(int i2=0;i2<=3;++i2)
    how[i0][i1][i2]=how_many_difrent(i0,i1,i2);

    cin>>n;

    avilable[1][hash_w[0][0][0][0]]=0;

    for(int i=1;i<=n;++i)
    {
        cin>>x;
        if(x=='M') tab=1;
        else if(x=='F') tab=2;
        else if(x=='B') tab=3;

        for(auto &u: avilable[i%2])
        {
            v0=(u.f/(p*p*p))%p;
            v1=(u.f/(p*p))%p;
            v2=(u.f/p)%p;
            v3=(u.f/1)%p;

            // cout<<u.f[0]<<" "<<u.f[1]<<" "<<u.f[2]<<" "<<u.f[3]<<" <- "<<u.s<<"\n";
            //opcja 1: dodaje na lewy stos
            avilable[(i+1)%2][min(hash_w[v1][tab][v2][v3],hash_w[v2][v3][v1][tab])] = max(u.s + how[v0][v1][tab], avilable[(i+1)%2][min(hash_w[v1][tab][v2][v3],hash_w[v2][v3][v1][tab])]);
            //opcja 2: dodaje na prawy stos
            avilable[(i+1)%2][min(hash_w[v0][v1][v3][tab],hash_w[v3][tab][v0][v1])] = max(u.s + how[v2][v3][tab], avilable[(i+1)%2][min(hash_w[v0][v1][v3][tab],hash_w[v3][tab][v0][v1])]);
        }
        avilable[i%2].clear();
    }

    int maxi=0;
    for(auto &u: avilable[(n+1)%2])
        maxi=max(maxi,u.s);
    cout<<maxi;

    return 0;
}