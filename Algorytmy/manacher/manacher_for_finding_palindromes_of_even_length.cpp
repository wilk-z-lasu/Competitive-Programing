#include <bits/stdc++.h>
using namespace std;
//O(n)
//s cointains information in indexes [1...n]
//p[i] calculates information of length of even-length palindrome with left middle element in i

vector<char> s={'#','a','a','a','a','a'};
constexpr int n=5;
int p[n];

void manacher()
{
    int str=0;
    int r=0;
    p[0]=0;
    for(int i=1;i<=n-1;i++)
    {
        p[i]=min(p[max(str - (i-str), 0)], r-i);
        p[i]=max(p[i],0);

        int prawo=i+p[i];
        int lewo=i-p[i]+1;

        while(1<=lewo-1 && prawo+1<=n && s[lewo-1]==s[prawo+1])
        {
            lewo--;
            prawo++;
            p[i]++;
        }

        if(i+p[i]>=r)
        {
            str = i;
            r = i+p[i];
        }
    }
}

int main()
{
    manacher();
    for(int i=1;i<=n;i++)
        cout<<p[i]<<' ';
}