#include <bits/stdc++.h>
using namespace std;
#define int long long

int n,m;
int P = 1;
int D = 1;
int nwd;
int length;

bool check()//returns 1 if such split can be an anwser
{
    int nwd1 = __gcd(P, m);
    int nwd2 = __gcd(D, n);
    if(nwd1 > 1 || nwd2 > 1)
        return 0;
    return 1;
}
void wypisz()
{
    cout<<P+D<<'\n';
    for(int i=1;i<=P;++i)
        cout<<'P';
    for(int i=1;i<=D;++i)
        cout<<'D';
    exit(0);
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;
    nwd = __gcd(n,m);
    length = max((int)2, nwd);

    P = 0;
    D = length;
    for(int i=1;i<length;++i)
    {
        P++;
        D--;
        if(check())
            wypisz();
    }
    P = 1;
    D = length;
    wypisz();
}