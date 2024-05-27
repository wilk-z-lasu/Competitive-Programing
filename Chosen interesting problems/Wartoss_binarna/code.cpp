#include <bits/stdc++.h>
using namespace std;
#define pb push_back

void do_natural()
{
    char c;
    int naturalne;
    vector<int>solv_naturalne;
    cin>>c;
    while(c!='.')
    {
        naturalne*= 10;
        naturalne+= c-'0';
        cin>>c;
    }
    
    if(naturalne!=0)
        while(naturalne!=0)
        {
            solv_naturalne.push_back(naturalne%2);
            naturalne/=2;
        }
    else
        solv_naturalne.push_back(0);
    reverse(solv_naturalne.begin(),solv_naturalne.end());
    
    for(int i=0;i<solv_naturalne.size();i++)
        cout<<solv_naturalne[i];
    cout<<'.';
}

string w;

int naturalne;
vector<int> solv_naturalne;

int top;
int bot;
map<int,int> had;
vector<int>solv;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>w;

    int iter;
    for(iter=0;w[iter]!='.' && iter<w.size();iter++)
    {
        naturalne*= 10;
        naturalne+= w[iter]-'0';
    }
    iter++;

    if(naturalne!=0)
        while(naturalne!=0)
        {
            solv_naturalne.push_back(naturalne%2);
            naturalne/=2;
        }
    else
        solv_naturalne.push_back(0);
    reverse(solv_naturalne.begin(),solv_naturalne.end());

    for(int i=0;i<solv_naturalne.size();i++)
        cout<<solv_naturalne[i];
    cout<<'.';

    top=0;
    bot=1;
    for(;iter<w.size();iter++)
    {
        top*=10;
        top+=w[iter]-'0';
        bot*=10;
    }

    for(int i=0;;i++)
    {
        if(top==0 || had.find(top)!=had.end())
            break;
        had[top]=i;
        top*=2;
        solv.pb(top/bot);
        top%=bot;
    }

    if(top==0)
    {
        for(auto &u: solv)
            cout<<u;
    }
    else
    {
        for(int i=0;i<solv.size();i++)
        {
            if(i==had[top])
                cout<<'(';
            cout<<solv[i];
        }
        cout<<')';
    }
    
    return 0;
}