#include <bits/stdc++.h>
using namespace std;

constexpr int maxn=1e6+7;
constexpr int maxi=5e6+7;

int n;
int a[maxn];
int sum;

int ile[maxi];

bitset<maxi>knapsack;
void add(int val) {
	knapsack |= (knapsack<<val);
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];

	sort(&a[1], &a[n+1]);

	knapsack[0]=1;
	for(int i=1;i<=n-1;++i)
	{
		sum+=a[i];
		ile[a[i]]++;
	}
	for(int i=1;i<maxi;i++)
	{
		while(ile[i]>=3)
		{
			ile[i]-=2;
			ile[2*i]++;
		}
	}
	for(int i=1;i<maxi;i++)
		while(ile[i]--)
			add(i);

	int small=sum/2;
	while(knapsack[small]==0)
		small--;
	cout<<small+a[n];
}