#include <iostream>
using namespace std;

char x;

bool tab[9][9];

bool vis1[9];
bool vis2[20];
bool vis3[20];


int odp=0;
void solv(int idx=1)
{
	if(idx==9)
	{
		odp++;
		return;
	}
	for(int i=1;i<=8;++i)
	{
		if(tab[idx][i]) continue;
		if(!vis1[i] && !vis2[idx+i] && !vis3[idx-i+9])
		{
			vis1[i]=1;
			vis2[idx+i]=1;
			vis3[idx-i+9]=1;
			solv(idx+1);
			vis1[i]=0;
			vis2[idx+i]=0;
			vis3[idx-i+9]=0;
		}
	}
}
int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	for(int i=1;i<=8;++i)
	{
		for(int j=1;j<=8;++j)
		{
			cin>>x;
			if(x=='*')
				tab[i][j]=1;
			else
				tab[i][j]=0;
		}
	}

	solv();
	cout<<odp;
	return 0;
}