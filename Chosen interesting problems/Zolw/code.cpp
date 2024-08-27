#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=5e5+7;
constexpr int inf=1e9+7;

int n;
int sum;
int taken;
int tab[maxn];
int wilco[maxn];

int odl[maxn];
int Left[maxn];
int Right[maxn];
int Next[maxn];

void make_odl() {
    
    int last=inf, last_full=inf;
    for(int i=1;i<=n;i++)
    {
        if(tab[i]==-1)
            last=i;
        else
            Left[i] = last;
    }
    
    last=inf, last_full=inf;
    for(int i=n;i>=1;i--)
    {
        if(tab[i]==-1)
            last=i;
        else if(tab[i]>0)
        {
            Right[i] = last;
            Next[i]=last_full;

            last_full=i;
        }
    }

    for(int i=1;i<=n;i++)
        odl[i] = (int)2 * min(abs(Right[i]-i), abs(Left[i]-i));
}

map<int,int>mam;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>tab[i];
        if(tab[i]!=-1)
            sum+=tab[i];
    }
    for(int i=1;i<=n;i++)
        wilco[i]=2*(i-1);

    make_odl();

    for(int i=1;i<=n;i++)
    {
        if(tab[i] <= 0) continue;

        int special_addition=odl[i];
        special_addition = min(special_addition, (int)2 * max(Right[i]-Next[i], (int)0));
        tab[i]--;

        if(tab[i])
        {
            mam[odl[i]] += tab[i];
            taken += odl[i] * tab[i];
            while(!mam.empty() && taken + i - 1 > wilco[i])
            {
                auto [a, b] = *(--mam.end());
                if (taken + i - 1 - a * b > wilco[i])
                {
                    taken -= a * b;
                    mam.erase(--mam.end());
                }
                else
                {
                    int need_to_del = taken + i - 1 - wilco[i] - 1;
                    int del = need_to_del / a;
                    taken -= del * a;
                    mam[a] -= del;
                    break;
                }
            }
        }

        if(taken + i - 1 <= wilco[i])
        {
            taken+=special_addition;
            mam[special_addition]++;
        }
        else if((--mam.end())->f > special_addition)
        {
            auto [a, b] = *(--mam.end());
            taken -= a;
            mam[a]--;
            if(mam[a]==0)
                mam.erase(mam.find(a));

            taken+= special_addition;
            mam[special_addition]++;
        }
    }

    for(auto &[a, b] : mam)
        sum -= b;
    cout<<sum;
    return 0;
}