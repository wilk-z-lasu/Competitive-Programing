#include<bits/stdc++.h>
using namespace std;
#define int long long

constexpr int maxn = 2000007;

int n, p, d;
int tab[maxn];
int pref[maxn];
int deska[maxn];

int poczatek;//=0
int koniec;

deque<int> maxq;

// Funkcja dodająca element do kolejki maksimów
void pushMax(int num) 
{
    while (!maxq.empty() && num > maxq.back()) 
    {
        maxq.pop_back();
    }
    maxq.push_back(num);
}

// Funkcja usuwająca element z kolejki maksimów
void popMax(int num) 
{
    if (!maxq.empty() && num == maxq.front()) 
        maxq.pop_front();
}

// Funkcja zwracająca największy element w kolejce maksimów
int getMax() 
{
    return maxq.front();
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();

    cin >> n >> p >> d;

    for(int i = 1; i <= n; i++)
    {
        cin >> tab[i];
        pref[i] = tab[i] + pref[i-1];
    }

    for(int i = 1; i <= n; i++)
    {
        deska[i] = pref[i] - pref[i-d];
    }

    int odp = d; // Długość początkowego fragmentu ściany


    for(koniec=1; koniec<=n; koniec++)
    {
        if(poczatek<koniec+d-1)
        {
            poczatek=koniec+d-1;
            pushMax(deska[poczatek]);
        }
        while(poczatek+1<=n && pref[poczatek+1]-pref[koniec-1]-max(deska[poczatek+1],getMax()) <= p)
        {
            poczatek++;
            pushMax(deska[poczatek]);
        }
        odp=max(odp,poczatek-koniec+1);
        popMax(deska[koniec+d-1]);
    }
    cout<<odp;
}