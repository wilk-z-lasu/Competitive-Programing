#include <bits/stdc++.h>
using namespace std;
#include "kaslib.h"
#define int long long

constexpr int inf=1e18;

constexpr int limit_pierwszy=3e5;

bool composite[limit_pierwszy+7];
vector<int>primes;
void get_primes()
{
    composite[1]=1;
    for(int i=1;i<=limit_pierwszy;i++)
    {
        if(!composite[i])
        {
            for(int j=2*i;j<=limit_pierwszy;j+=i)
                composite[j]=1;
        }
    }
    for(int i=1;i<=limit_pierwszy;i++)
        if(!composite[i])
            primes.push_back(i);
}

int dziel[30000];
bool skip[30000];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    get_primes();

    int clear=primes.size()-1;
    int solutions=0;
    while(solutions<2000)
    {
        int wykladniki=1;

        for(int i=0;i<=clear;i++)
            dziel[i]=primes[i];
        for(int i=0;i<=clear;i++)
            skip[i]=0;
        clear=0;

        int round=0;
        for(int i=0;i<primes.size();)
        {
            if(round==1 && wykladniki<60)
                break;
            if(round==2 && wykladniki<120)
                break;
            if(round==3 && wykladniki<180)
                break;
            if(round==6 && wykladniki<400)
                break;
            if(round==10 && wykladniki<10000)
                break;
            if(round==100 && wykladniki<4000000)
                break;
            if(round==300 && wykladniki<14e8)
                break;
            if(round==1000 && wykladniki<34e11)
                break;
            round++;
            if(skip[i])
            {
                i++;
                continue;
            }
            int ask=1;

            int koniec=i;
            for(int j=i; j<primes.size() && (__int128)ask*(__int128)dziel[j] <= (__int128)inf ;j++)
            {
                if(skip[j])
                    continue;
                ask*=dziel[j];
                koniec=j;
            }
            clear=max(clear,koniec);

            int nwd = Pytaj(ask);
            for(int j=i;j<=koniec;j++)
            {
                if(skip[j])
                    continue;
                if(nwd%dziel[j]==0)
                {
                    wykladniki*=primes[j];
                    dziel[j]*=primes[j];
                }
                else
                    skip[j]=1;
            }

            if((__int128)wykladniki * (__int128)primes[i] > (__int128)inf)
            {
                solutions++;
                Odpowiedz(wykladniki);
                break;
            }
        }
        Szturchnij();
    }
    while(true)
        Szturchnij();
    return 0;
}