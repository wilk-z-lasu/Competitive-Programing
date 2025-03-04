#include <bits/stdc++.h>
using namespace std;
vector<vector<int>>vec(300007);

int sprawdz_k(int v,int k,int ojciec)
{
    int suma=0;
    for(int i=0;i<vec[v].size();i++)
        if(vec[v][i]!=ojciec)
            suma = suma + sprawdz_k(vec[v][i],k,v) + 1;
    return max(0,suma-k);
}

int bs(int a,int b)
{
    int srodek;
    while(b>a)
    {
        srodek=(b+a)/2;
        if(sprawdz_k(1,srodek,1)==0 && sprawdz_k(1,srodek-1,1)>0)
            return srodek;

        if(sprawdz_k(1,srodek,1)>0)
            a=srodek+1;
        else
            b=srodek-1;
    }
}

int32_t main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;cin>>n;

    int a,b;
    for(int i=0;i<n-1;i++)
    {
        cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }
    cout<<bs(0,300000);
}