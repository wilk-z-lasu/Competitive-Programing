//O(M^2 + n) M<=2500 n<=250000
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxi=2507;
constexpr int maxn=250007;

int N;
int A[maxn],B[maxn];
bool tab[maxi][maxi];

int miny[maxi][maxi];
int minx[maxi][maxi];

int maxy[maxi][maxi];
int maxx[maxi][maxi];

int wyspy_prawo_gora[maxi][maxi];
int wyspy_lewo_dol[maxi+7][maxi+7];

int koszt_prawo[maxi][maxi];
int koszt_lewo[maxi][maxi];

void preproces()
{
    for(int x=0;x<maxi;++x)
    {
        for(int y=0;y<maxi;++y)
        {
            miny[x][y]=maxi;
            minx[x][y]=maxi;
            maxy[x][y]=-1;
            maxx[x][y]=-1;
        }
    }
}
void licz_min_max()
{
    for(int x=1;x<=maxi-2;++x)
    {
        for(int y=1;y<=maxi-2;++y)
        {
            if(tab[x][y])
            {
                miny[x][y]=y;
                minx[x][y]=x;
            }

            miny[x][y]=min(miny[x][y],miny[x-1][y]);
            miny[x][y]=min(miny[x][y],miny[x][y-1]);

            minx[x][y]=min(minx[x][y],minx[x][y-1]);
            minx[x][y]=min(minx[x][y],minx[x-1][y]);
        }
    }

    for(int x=maxi-2;x>=1;--x)
    {
        for(int y=maxi-2;y>=1;--y)
        {
            if(tab[x][y])
            {
                maxy[x][y]=y;
                maxx[x][y]=x;
            }

            maxy[x][y]=max(maxy[x][y],maxy[x+1][y]);
            maxy[x][y]=max(maxy[x][y],maxy[x][y+1]);

            maxx[x][y]=max(maxx[x][y],maxx[x][y+1]);
            maxx[x][y]=max(maxx[x][y],maxx[x+1][y]);
        }
    }
}
void licz_wyspy()
{
    for(int x=maxi-2;x>=1;--x)
    {
        for(int y=1;y<=maxi-2;++y)
        {
            wyspy_prawo_gora[x][y] = wyspy_prawo_gora[x+1][y]+wyspy_prawo_gora[x][y-1]-wyspy_prawo_gora[x+1][y-1];
            if(tab[x][y]) wyspy_prawo_gora[x][y]++;
        }
    }
    for(int x=1;x<=maxi-2;++x)
    {
        for(int y=maxi-2;y>=1;--y)
        {
            wyspy_lewo_dol[x][y] = wyspy_lewo_dol[x-1][y]+wyspy_lewo_dol[x][y+1]-wyspy_lewo_dol[x-1][y+1];
            if(tab[x][y]) wyspy_lewo_dol[x][y]++;
        }
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>N;
    for(int i=1;i<=N;++i)
    {
        cin>>A[i]>>B[i];
        tab[B[i]][A[i]]=1;
    }

    preproces();
    licz_min_max();
    licz_wyspy();

    for(int x=maxi-2;x>=1;--x)
    {
        for(int y=1;y<=maxi-2;++y)
        {
            if(wyspy_prawo_gora[x][y] == 0) continue;
            int X = maxx[1][y+1]; X = max(X, x);
            int Y = miny[x-1][maxi-2]; Y = min(Y, y);
            koszt_prawo[x][y] = wyspy_prawo_gora[x][y] + koszt_prawo[X][Y]; 
        }
    }
    for(int x=1;x<=maxi-2;++x)
    {
        for(int y=maxi-2;y>=1;--y)
        {
            if(wyspy_lewo_dol[x][y] == 0) continue;
            int X = minx[maxi-2][y-1]; X = min(X, x);
            int Y = maxy[x+1][1]; Y = max(Y, y);
            koszt_lewo[x][y] = wyspy_lewo_dol[x][y] + koszt_lewo[X][Y]; 
        }
    }
    
    for(int i=1;i<=N;++i)
    {
        int x=B[i];
        int y=A[i];
        cout<<koszt_prawo[x][y]+koszt_lewo[x][y]+N-3<<'\n';
    }
    return 0;
}