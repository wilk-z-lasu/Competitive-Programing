// XXXI Olimpiada Informatyczna - 1 Etap
// Mateusz Woloszyk
// Solution for 82/100 pkt
#include<bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=1000+7;

int n,p,M;
int a,b;

vector<int> vec[2*maxn];

map<vector<int>,vector<int>>same_left;
map<vector<int>,vector<int>>same_right;

char kody[2*maxn][2*(maxn+2)];//[numer satelity][indeks kodu]

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();

    cin>>n>>p>>M;

    //podzadanie 1,2,3
    if(M>=n+2*ceil(log2(n)))
    {
        for(int i=0;i<2*maxn;i++)
            for(int j=0;j<maxn+2;j++)
                kody[i][j]=0;
        for(int i=1;i<=n;i++)
            kody[i][i]='B';
        for(int i=1;i<=p;i++)
        {
            cin>>a>>b;
            kody[b][a]='B';
        }
        int roz=0;
        for(int j=n+1;j<=2*n;j++)
        {
            for(int i=0;i<=ceil(log2(n));i++)
            {
                if(roz & (1<<i))
                    kody[j][n+1+i]='B';
            }
            roz++;
        }
        M=n+2*ceil(log2(n));
        cout<<M<<'\n';
        for(int i=1;i<=2*n;i++)
        {
            for(int j=1;j<=M;j++)
            {
                if(kody[i][j]=='B')
                    cout<<'B';
                else if(i<=n)
                    cout<<'A';
                else if(i>n)
                    cout<<'C';
            }
            cout<<'\n';
        }
        return 0;
    }

    for(int i=1;i<=p;i++)
    {
        cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }
    for(int i=1;i<=2*n;i++)
        sort(vec[i].begin(),vec[i].end());

    for(int i=1;i<=n;i++)
        same_left[vec[i]].push_back(i);
    
    for(int i=n+1;i<=2*n;i++)
        same_right[vec[i]].push_back(i);

    //sprawdzenie czy dziala
    int left_x=0;
    int max_left_x=0;
    for(auto u: same_left)
    {
        if(u.f.size()>0)
            left_x++;
        max_left_x=max(max_left_x,(int)u.s.size());
    }
    int right_x=0;
    int max_right_x=0;
    for(auto u: same_right)
    {
        if(u.f.size()>0)
            right_x++;
        max_right_x=max(max_right_x,(int)u.s.size());
    }

    int poz=1;
    //lacze satelity
    if(left_x<=right_x)
    {
        for(auto u: same_left)
        {
            if(u.f.size()>0)
            {
                for(auto u2: u.f)
                    kody[u2][poz]='B';
                for(auto u2: u.s)
                    kody[u2][poz]='B';
                poz++;
            }
        }
    }
    else
    {
        for(auto u: same_right)
        {
            if(u.f.size()>0)
            {
                for(auto u2: u.f)
                    kody[u2][poz]='B';
                for(auto u2: u.s)
                    kody[u2][poz]='B';
                poz++;
            }
        }
    }
    //rozrozniam satelity
    for(auto u: same_left)
    {
        if(u.s.size()>1)
        {
            int roz=0;
            for(auto u2: u.s)
            {
                for(int i=0;i<=ceil(log2(max_left_x));i++)
                {
                    if(roz & (1<<i))
                        kody[u2][poz+i]='B';
                }
                roz++;
            }
        }
    }
    if(max_left_x>1)
        poz+=ceil(log2(max_left_x));
    for(auto u: same_right)
    {
        if(u.s.size()>1)
        {
            int roz=0;
            for(auto u2: u.s)
            {
                for(int i=0;i<=ceil(log2(max_right_x));i++)
                {
                    if(roz & (1<<i))
                        kody[u2][poz+i]='B';
                }
                roz++;
            }
        }
    }
    if(max_right_x>1)
        poz+=ceil(log2(max_right_x));

    M=n+2;
    cout<<M<<'\n';
    for(int i=1;i<=2*n;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(kody[i][j]=='B')
                cout<<'B';
            else if(i<=n)
                cout<<'A';
            else if(i>n)
                cout<<'C';
        }
        cout<<'\n';
    }
    return 0;
}