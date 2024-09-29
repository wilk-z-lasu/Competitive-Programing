#include <bits/stdc++.h>
using namespace std;
#define int long long

constexpr int maxk=1000007;

int k;
char s[maxk];

int P[maxk];
int shortest_P[maxk];//najkrotszy nie zerowy prefixo-sufix

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>k;

    for(int i=1;i<=k;i++)
        cin>>s[i];

    //KMP
    P[0] = 0;
    P[1] = 0;
    int pre;
    for(int i=2;i<=k;i++) 
    {
        pre=P[i-1];
        //cofniecie sie do ostatniego prefixo-sufixa, ktorego da sie rozszarzyc lub dojscie ze jest on pusty
        while(pre>0 && s[pre+1]!=s[i])
            pre=P[pre];
        //rozszerzenie prefixo-sufixa jesi sie da
        if(s[pre+1]==s[i])
            pre++;
        //zapisanie prefixo-sufixa 1-i w tabeli P
        P[i]=pre;
    }

    for(int i=1;i<=k;i++) 
    {
        if(P[i]==0)
            shortest_P[i]=i;
        else 
            shortest_P[i]=shortest_P[P[i]];
    }
    
    // for(int i=1;i<=k;i++) 
    //     cout<<shortest_P[i]<<" ";

    int solv=0;
    for(int i=1;i<=k;i++)
        solv+= i-shortest_P[i];
        
    cout<<solv;

    return 0;
}