// Solution for 4/10 pkt //
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n,m;
    cin>>n>>m;

    //vector<vector<char>>tab(n,vector<char>(m));
    char tab[n][m];
    string w;
    for(int i =0;i<n;i++)
    {
        cin>>w;
        for(int j =0;j<w.size();j++)
        {
            tab[i][j]=w[j];
        }
    }


    int k;
    cin>>k;

    int chwila;
    cin>>w;
    for(int iter=0;iter<k;iter++)
    {
        if(w[iter]=='G')
        {
            for(int i=0;i<m;i++)
            {
                chwila=0;
                for(int j=0;j<n;j++)
                {
                    if(tab[j][i]!='.')
                    {
                        swap(tab[j][i],tab[chwila][i]);
                        chwila++;
                    }
                }
            }
        }
        else if(w[iter]=='D')
        {
            for(int i=0;i<m;i++)
            {
                chwila=n-1;
                for(int j=n-1;j>=0;j--)
                {
                    if(tab[j][i]!='.')
                    {
                        swap(tab[j][i],tab[chwila][i]);
                        chwila--;
                    }
                }
            }
        }
        else if(w[iter]=='L')
        {
            for(int i=0;i<n;i++)
            {
                chwila=0;
                for(int j=0;j<m;j++)
                {
                    if(tab[i][j]!='.')
                    {
                        swap(tab[i][j],tab[i][chwila]);
                        chwila++;
                    }
                }
            }
        }
        else if(w[iter]=='P')
        {
            for(int i=0;i<n;i++)
            {
                chwila=m-1;
                for(int j=m-1;j>=0;j--)
                {
                    if(tab[i][j]!='.')
                    {
                        swap(tab[i][j],tab[i][chwila]);
                        chwila--;
                    }
                }
            }
        }
    }

    for(int i =0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cout<<tab[i][j];
        }
        cout<<"\n";
    }
    return 0;
}