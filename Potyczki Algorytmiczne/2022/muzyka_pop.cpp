#include <bits/stdc++.h>
using namespace std;
int licz_bity(int n)
{
    int licz = 0;
    while (n)
    {
        n = n & (n - 1);
        licz++;
    }
    return licz;
}

int main()
{
    //int operacje=0;
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    //cout.tie(0);

    vector< pair<int,int> >bity(2000000);
    for(int i = 0;i<2000000;i++)
    {
        bity[i].first=licz_bity(i);
        bity[i].second=i;
    }
/*
    for(int i = 0;i<10;i++)
    {
        cout<<bity[i].second<<" "<<bity[i].first<<endl;
    }
*/

    int n;
    cin>>n;


    //vector< pair<int,int> >vec(0);
    int j,i;
    //int prze=0;
    int brak=n;

    for(i = 1;i<=n;i*=2)//tu zmienic i dopasowac liczby
    {
        //cout<<"i: "<<i<<"\n";
        for(j = 0;j<i;j++)
        {
            //cout<<"i+j: "<<j+i<<"\n";
            //if(brak-bity[i+j].first>=0)
            //{
                //0
                //vec.push_back(bity[i+j]);
                brak-=bity[i+j].first;
                //operacje++;
            //}
        }
        /*
        if(vec[i+j-1]!=bity[i+j-1])
        {
            //vec.push_back(bity[i+j-1]);
            prze++;
        }
        */
    }
/*
    cout<<brak<<endl;
    for(int x = 0;x<20;x++)
    {
        cout<<vec[x].second<<" "<<vec[x].first<<endl;
    }
    */
    i--;
    //cout<<"sprawdzanie: \n";
    //cout<<bity[i].second<<endl<<bity[i].first<<endl;

    while(brak<0)
    {
        if(brak+bity[i].first<=0)
        {
            brak+=bity[i].first;
            bity[i]=make_pair(0,0);
        }
        i--;
    }

    int odp=0;
    brak=0;
    for(int iter = 0;iter<=n;iter++)
    {
        if(brak + bity[iter].first<=n && bity[iter]!=make_pair(0,0))
        {
            odp++;
            brak+=bity[iter].first;
        }
    }
    //cout<<brak<<endl;
    cout<<odp<<"\n";
    for(int iter = n;iter>=0;iter--)
    {
        if(bity[iter]!=make_pair(0,0))
        {
            cout<<bity[iter].second<<" ";
        }
    }



    return 0;
}