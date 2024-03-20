// Zadanie wymaga: wyprowadzenie wzorów + obserwacja monotoniczności funkcji + algorytm MO.
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
constexpr int maxn = 1e5+2137;
constexpr int pier = 317;//dla najwiekszej

int n,q;
int k,m;
int c[maxn];
int prefix[maxn];
int sufix[maxn];
int solv[maxn];

vector<pair<int,pair<int,int>>>koszyk[pier];

int left_taken;
int right_taken;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>q;

    for(int i=1;i<=n;i++)
        cin>>c[i];

    sort(c+1,c+n+1);

    for(int i=1;i<=n;i++)
        prefix[i]=prefix[i-1]+c[i];

    for(int i=n;i>=1;i--)
        sufix[i]=sufix[i+1]+c[i];

    for(int i=1;i<=q;i++)
    {
        cin>>k>>m;
        koszyk[m/pier].push_back({k,{m,i}});
    }
    for(int i=0;i<pier;i++)
        sort(koszyk[i].begin(),koszyk[i].end());

    for(int iter=0;iter<pier;iter++)//O(sqrt(n))
    {
        if(koszyk[iter].empty())
            continue;
        // koszyk[i].f-k koszyk[i].s.f-m koszyk[i].s.s-i
        left_taken=0;
        right_taken=n+1;

        // cout<<koszyk[iter][0].f<<" "<<koszyk[iter][0].s.f<<" "<<koszyk[iter][0].s.s<<endl;
        for(int i=1;i<=koszyk[iter][0].s.f;i++)//O(n)
        {
            if(left_taken+1<=n+1 && c[left_taken+1]<=2*koszyk[iter][0].f-c[right_taken-1])
                left_taken++;
            else if(right_taken-1>=0)
                right_taken--;
        }
        // cout<<left_taken<<" "<<right_taken<<endl;
        // cout<<prefix[left_taken]<<" + "<<2*koszyk[iter][0].f*(n+1-right_taken)<<" - "<<sufix[right_taken]<<endl;
        solv[koszyk[iter][0].s.s]=prefix[left_taken]+2*koszyk[iter][0].f*(n+1-right_taken)-sufix[right_taken];
        for(int i=1;i<koszyk[iter].size();i++)
        {
            // cout<<"------- "<<i<<" -------"<<endl;
            // cout<<koszyk[iter][i].f<<" "<<koszyk[iter][i].s.f<<" "<<koszyk[iter][i].s.s<<endl;

            // cout<<"start: "<<left_taken<<" "<<right_taken<<endl;

            while(right_taken+1<=n+1 && c[left_taken+1]<=koszyk[iter][i].f && c[left_taken+1]<2*koszyk[iter][i].f-c[right_taken])//tu dorownuje aby bylo zrobione dla wlasciwego k
            {
                left_taken++;
                right_taken++;
            }
            // cout<<"before: "<<left_taken<<" "<<right_taken<<endl;
            if(koszyk[iter][i].s.f>koszyk[iter][i-1].s.f)
            {
                for(int j=1;j<=koszyk[iter][i].s.f-koszyk[iter][i-1].s.f;j++)
                {
                    if(left_taken==n+1)
                        right_taken--;
                    else if(right_taken==0)
                        left_taken++;
                    else if(left_taken+1<=n+1 && c[left_taken+1]<=2*koszyk[iter][i].f-c[right_taken-1])
                        left_taken++;
                    else if(right_taken-1>=0)
                        right_taken--;
                }
            }
            else if(koszyk[iter][i].s.f<koszyk[iter][i-1].s.f)
            {
                for(int j=1;j<=koszyk[iter][i-1].s.f-koszyk[iter][i].s.f;j++)
                {
                    if(right_taken==n+1)
                        left_taken--;
                    else if(left_taken==0)
                        right_taken++;
                    else if(left_taken-1>=0 && c[left_taken]>2*koszyk[iter][i].f-c[right_taken])
                        left_taken--;
                    else if(right_taken+1<=n+1)
                        right_taken++;
                    // cout<<left_taken<<" "<<right_taken<<endl;
                }
            }
            // cout<<"after: "<<left_taken<<" "<<right_taken<<endl;
            solv[koszyk[iter][i].s.s]=prefix[left_taken]+2*koszyk[iter][i].f*(n+1-right_taken)-sufix[right_taken];
        }
    }

    for(int i=1;i<=q;i++)
        cout<<solv[i]<<'\n';

    return 0;
}