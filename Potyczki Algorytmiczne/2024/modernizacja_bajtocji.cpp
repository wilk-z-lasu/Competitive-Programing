#include <bits/stdc++.h>
using namespace std;

constexpr int maxn=300000+7;
constexpr int maxq=1000000+7;

int n;
int q;
char x;
int a,b;

set<int> ss[maxn+maxq];//jaka wielkosc ma spojna
int which_ss[maxn];//do ktorej spojnej naleze

int computers[maxn+maxq];//ile komputerow ma spojna
int akt_ss;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        ss[i].insert(i);
        which_ss[i]=i;
    }
        
    akt_ss=n;

    for(int iter=1;iter<=q;iter++)
    {
        cin>>x;
        if(x=='+')
        {
            cin>>a>>b;
            if(which_ss[a]==which_ss[b])
                computers[which_ss[a]]++;
            else
            {
                int spojna1=which_ss[a];
                int spojna2=which_ss[b];

                if(ss[spojna1].size()>ss[spojna2].size()) swap(spojna1,spojna2); //ss[spojna1].size() <= ss[spojna2].size()
                
                // cout<<spojna1<<" <= "<<spojna2<<endl;
                while(!ss[spojna1].empty())
                {
                    which_ss[*ss[spojna1].begin()]=spojna2;
                    ss[spojna2].insert(*ss[spojna1].begin());
                    // cout<<"spojna: "<<spojna2<<" add: "<<*ss[spojna1].begin()<<endl;
                    ss[spojna1].erase(ss[spojna1].begin());
                }
                computers[spojna2]++;
                computers[spojna2]+=computers[spojna1];
            }

        }
        else if(x=='-')
        {
            cin>>a;
            computers[which_ss[a]]--;
            ss[which_ss[a]].erase(a);

            akt_ss++;
            which_ss[a]=akt_ss;
            ss[akt_ss].insert(a);
        }
        else if(x=='?')
        {
            cin>>a;
            if(computers[which_ss[a]]==0)
                cout<<0;
            else if(computers[which_ss[a]]==ss[which_ss[a]].size())
                cout<<1;
            else
                cout<<'?';
            // cout<<endl;
        }
    }
    return 0;
}