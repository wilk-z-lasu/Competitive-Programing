#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

int odp;

vector<int> d;

void getDivisors(int n)
{
    for (int i=1; i<=sqrt(n); i++)
    {
        if (n%i == 0)
        {
            // If divisors are equal, get one
            if (n/i == i)
                d.push_back(i);
  
            else // else get both
            {
                d.push_back(i);
                d.push_back(n/i);
            }
        }
    }
}

int liczba_dzielnikow(int n, int smaller)
{
    int solv=0;
    for (int i=1; i<=sqrt(n); i++)
    {
        if (n%i == 0)
        {
            // If divisors are equal, get one
            if (n/i == i && i<=smaller && i>=2)
                solv++;
  
            else // else get both
            {
                if(i<=smaller && i>=2) solv++;
                if(n/i<=smaller && (n/i)>=2) solv++;
            }
        }
    }
    return solv;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin>>n;

    getDivisors(n);
    for(auto a: d)
        odp += liczba_dzielnikow((n/a)-1, (n/a-1)/3);
    cout<<odp;

    return 0;
}