// XXXI Olimpiada Informatyczna - 1 Etap
// Mateusz Woloszyk
// Solution for 100/100 pkt
#include<bits/stdc++.h>
using namespace std;

constexpr int maxn=1500+7;

int n,m;
char x;
int tab[maxn][maxn];//[wiersz][kolumna]
int najx[maxn][2];
int najy[maxn][2];
int solv;
int pre[maxn];
int suf[maxn];
int dlugi_y[2];
int dlugi_x[2];

int dpl[maxn][maxn];//[wiersz][kolumna]
int dpr[maxn][maxn];//[wiersz][kolumna]

void uwzglednij(int v)
{
    solv=max(solv,v);
}

bool check(int v)
{
    for(int j=1;j<=n;j++)//j-kolumna
    {
        for(int i=v;i<=n;i++)//i-wiersz
        {
            if(tab[i][j]-tab[i][j-1]-tab[i-v][j]+tab[i-v][j-1]==0 && max({dpl[i][j-1],dpr[i][j+1],pre[i-v],suf[i+1]})>=v)
                return true;
        }
    }
    return false;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();

    cin>>n>>m;

    for(int j=1;j<=n;j++)
    {
        for(int i=1;i<=n;i++)
        {
            cin>>x;
            if(x=='X')//X
                tab[j][i]=1;
        }
    }
    //licze najx i dlugi_x
    for(int i=1;i<=n;i++)
    {
        //licze wynik dla i-tej kolumny
        int tmp_wynik=0;
        for(int j=1;j<=n;j++)
        {
            if(!tab[j][i])
                tmp_wynik++;
            if(tab[j][i] || j==n)
            {
                najx[i][1]=max(najx[i][1],tmp_wynik);
                if(najx[i][1]>najx[i][0])
                    swap(najx[i][1],najx[i][0]);
                tmp_wynik=0;
            }
        }
        dlugi_x[1]=max(dlugi_x[1],najx[i][0]);
        if(dlugi_x[1]>dlugi_x[0])
            swap(dlugi_x[1],dlugi_x[0]);
        dlugi_x[1]=max(dlugi_x[1],najx[i][1]);
        if(dlugi_x[1]>dlugi_x[0])
            swap(dlugi_x[1],dlugi_x[0]);
    }
    // licze najy i dlugi_y
    for(int i=1;i<=n;i++)
    {
        //licze wynik dla i-tego rzedu
        int tmp_wynik=0;
        for(int j=1;j<=n;j++)
        {
            if(!tab[i][j])
                tmp_wynik++;
            if(tab[i][j] || j==n)
            {
                najy[i][1]=max(najy[i][1],tmp_wynik);
                if(najy[i][1]>najy[i][0])
                    swap(najy[i][1],najy[i][0]);
                tmp_wynik=0;
            }
        }
        dlugi_y[1]=max(dlugi_y[1],najy[i][0]);
        if(dlugi_y[1]>dlugi_y[0])
            swap(dlugi_y[1],dlugi_y[0]);
        dlugi_y[1]=max(dlugi_y[1],najy[i][1]);
        if(dlugi_y[1]>dlugi_y[0])
            swap(dlugi_y[1],dlugi_y[0]);
    }

    if(m==1)//licze odp gdy m=1
    {
        for(int i=1;i<=n;i++)
            uwzglednij(max(najx[i][0],najy[i][0]));
        cout<<solv;
        return 0;
    }
    //dpl
    for(int i=1;i<=n;i++)//i=wiersz
    {
        int tmp_wynik=0;
        for(int j=1;j<=n;j++)//j=kolumna
        {
            if(!tab[i][j])
                tmp_wynik++;
            if(tab[i][j])
                tmp_wynik=0;
            dpl[i][j]=max(tmp_wynik,max(dpl[i][j-1],dpl[i-1][j]));
        }
    }
    //dpr
    for(int i=1;i<=n;i++)//i=wiersz
    {
        int tmp_wynik=0;
        for(int j=n;j>=1;j--)//j=kolumna
        {
            if(!tab[i][j])
                tmp_wynik++;
            if(tab[i][j])
                tmp_wynik=0;
            dpr[i][j]=max(tmp_wynik,max(dpr[i][j+1],dpr[i-1][j]));
        }
    }

    // zmienia tab w sumy prefixowe
    for(int j=1;j<=n;j++)
        for(int i=1;i<=n;i++)
            tab[j][i]=tab[j][i]+tab[j-1][i]+tab[j][i-1]-tab[j-1][i-1];

    //licze sumy prefixowe i sufixowe na y
    for(int i=1;i<=n;i++)
        pre[i]=max(pre[i-1],najy[i][0]);
    for(int i=n;i>=1;i--)
        suf[i]=max(suf[i+1],najy[i][0]);

    uwzglednij(dlugi_x[1]);
    uwzglednij(dlugi_x[0]/2);
    uwzglednij(dlugi_y[1]);
    uwzglednij(dlugi_y[0]/2);

    int l=0, r=n, mid;
    while(l<r)
    {
        mid=(l+r+1)/2;
        if(check(mid))
            l=mid;
        else
            r=mid-1;
    }
    cout<<max(solv,l);
    return 0;
}