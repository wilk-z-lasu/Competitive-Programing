#include<bits/stdc++.h>
using namespace std;
#define int long long

constexpr int maxn=5e5+7;
constexpr int inf=1e18+7;

int n,s;
int l[maxn];
int p[maxn];

int sizeL, sizeP;
bool activeP, activeL;
int solv1, solv2;

bool decision1[maxn];//l=0 p=1
bool decision2[maxn];//l=0 p=1

bool decision[maxn];

vector<int> solution;

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>s;
	for(int i=1;i<=n-1;i++)
		cin>>l[i]>>p[i];

	sizeL=s-1;
	sizeP=n-s;

	//przypadek 1
	if(sizeL==0)
		solv1=inf;
	else
	{
		solv1 += l[1];
		decision1[1]=0;
		for(int i=2;i<=n-1;i++)
		{
			if(i<=sizeL+1 && p[i] <= l[i])
				activeP=1;
			solv1 += min(l[i], p[i]);

			if(l[i]<p[i])
				decision1[i]=0;
			else
				decision1[i]=1;
		}
		if(!activeP)
		{
			int add=inf;
			int modify;
			for(int i=2;i<=sizeL+1;i++)
			{
				if(p[i]-l[i] < add)
				{
					add = p[i]-l[i];
					modify=i;
				}
			}
			solv1 += add;
			decision1[modify]=!decision1[modify];
		}
	}

	//przypadek 2
	if(sizeP==0)
		solv2=inf;
	else
	{
		solv2 += p[1]; 
		decision2[1]=1;
		for(int i=2;i<=n-1;i++)
		{
			if(i<=sizeP+1 && l[i] <= p[i])
				activeL=1;
			solv2 += min(l[i], p[i]);

			if(p[i]<l[i])
				decision2[i]=1;
			else
				decision2[i]=0;
		}
		if(!activeL)
		{
			int add=inf;
			int modify;
			for(int i=2;i<=sizeP+1;i++)
			{
				if(l[i]-p[i] < add)
				{
					add = l[i]-p[i];
					modify=i;
				}
			}
			solv2 += add;
			decision2[modify]=!decision2[modify];
		}
	}

	cout<<min(solv1, solv2)<<'\n';

	if(solv1 <= solv2)
		for(int i=1;i<=n-1;i++)
			decision[i] = decision1[i];
	else
		for(int i=1;i<=n-1;i++)
			decision[i] = decision2[i];

	// for(int i=1;i<=n-1;i++)
	// {
	// 	if(decision[i]==0)
	//  		cout<<"L";
	//  	else 
	// 		cout<<"P";
	// }
	// cout<<endl;

	deque<int> slots;
	for(int i=1;i<=n;i++)
	{
		if(i==s) continue;
		slots.push_back(i);
	}

	solution.push_back(s);
	for(int i=1;i<=n-1;i++)
	{
		int ile=1;
		while(i+1<=n-1 && decision[i]==decision[i+1])
		{
			ile++;
			i++;
		}
		vector<int>addition;
		if(decision[i])
		{
			while(ile--)
			{
				addition.push_back(slots.back());
				slots.pop_back();
			}
		}
		else
		{
			while(ile--)
			{
				addition.push_back(slots.front());
				slots.pop_front();
			}
		}
		reverse(addition.begin(), addition.end());
		for(auto &u: addition)
			solution.push_back(u);
	}

	// ostateczne rozwiazanie
	for(auto &u: solution)
		cout<<u<<' ';
	return 0;
}