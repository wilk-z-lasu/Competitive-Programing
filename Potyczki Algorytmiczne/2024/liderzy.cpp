#include <bits/stdc++.h>
using namespace std;

constexpr int maxn=500000+7;
int n;

int x;
int tab[maxn];

multiset<int>m;
int solv;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;i++)
    {
        cin>>x;
        tab[x]++;
    }
    for(int i=1;i<=n;i++)
        if(tab[i]>0)
            m.insert(tab[i]);


    while(!m.empty())
    {
        solv++;
        auto top=m.end();top--;
        int need= *top - 1;
        m.erase(top);

        while(!m.empty() && need>0)
        {
            auto bot=m.begin();
            if(*bot<=need)
                need-=*bot;
            else
            {
                m.insert(*bot-need);
                need=0;
            }
            m.erase(bot);
        }
    }
    cout<<solv;

    return 0;
}