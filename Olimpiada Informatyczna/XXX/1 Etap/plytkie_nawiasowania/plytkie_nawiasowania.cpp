// XXX Olimpiada Informatyczna - 1 Etap
// Mateusz Woloszyk
// Solution for 100/100 pkt
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, H;
    cin >> n >> H;
    string w;
    cin >> w;


    int zmiana = 0;
    int nawiasy = 0;
    for(int i = 0;i<n;i++)
    {
        if(w[i]=='(')
        {
            nawiasy++;
        }
        else if(w[i]==')')
        {
            nawiasy--;
        }
        if(nawiasy==H+1 && w[i]=='(')
        {
            zmiana++;
            nawiasy-=2;
        }
        else if(nawiasy<0 && w[i]==')')
        {
            zmiana++;
            nawiasy+=2;
        }
    }
    cout<<zmiana;
    return 0;
}