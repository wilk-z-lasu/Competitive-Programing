// XXXI Olimpiada Informatyczna - 2 Etap
// Mateusz Woloszyk
// Solution for 53/100 pkt
#include <bits/stdc++.h>
using namespace std;

constexpr int maxn=1e6+7;
constexpr int inf=1e9+7;

int n,q;
int d[maxn];
int S;

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n>>q;
	for(int i=1;i<=n;++i)
	{
		cin>>d[i];
		S+=d[i];
	}

	if(q<=1e5 && S<=500)//1,2,3 podzadanie
	{
		int tab[507];//zmien na 507
		int wolne=1;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=d[i];++j)
			{
				tab[wolne]=i%2;
				wolne++;
			}
		
		int l,r,k;
		for(int iter=1;iter<=q;++iter)
		{
			int solv=0;
			cin>>l>>r>>k;
			int etapy=1;
			for(int i=l;i<=r-1;i++)
				if(tab[i]!=tab[i+1])
					etapy++;
			if(etapy==1)
			{
				if(tab[l]==1)
					solv=r-l+1;
			}
			else
			{
				int lewa_1=0;
				int prawa_1=0;
				while(tab[l+lewa_1]==1)
					lewa_1++;
				while(tab[r-prawa_1]==1)
					prawa_1++;
				vector<int>vec;
				for(int i=l+lewa_1;i<=r-prawa_1;i++)
				{
					if(tab[i]==1)
					{
						int koniec=i;
						while(tab[koniec+1]==1)
							koniec++;
						vec.push_back(koniec-i+1);
						i=koniec;
					}
				}
				sort(vec.begin(),vec.end(),greater<int>());

				//rozpatruje ze nie biore zadnego
				int odp=0;
				if(1<=k)
					solv=max(solv,odp+max(lewa_1,prawa_1));
				if(2<=k)
					solv=max(solv,odp+lewa_1+prawa_1);

				for(int i=0;i<vec.size();++i)
				{
					if((i+1)*2>k) break;
					odp+=vec[i];
					solv=max(solv,odp);

					if((i+1)*2+1<=k)
						solv=max(solv,odp+max(lewa_1,prawa_1));
					if((i+1)*2+2<=k)
						solv=max(solv,odp+lewa_1+prawa_1);
				}
			}
			cout<<solv<<'\n';
		}
	}
	// if(q<=1e4 && n<=1e4)//4,5,6 podzadanie
	else
	{
		int l,r,k;
		for(int iter=1;iter<=q;++iter)
		{
			int solv=0;
			int lewa_1=0;
			int prawa_1=0;
			int koniec_lewego=-1;
			int koniec_prawego=-1;
			int p,e;//poczatek i koniec interesujacego przedzialu bez 1 brzegowych
			int gdzie_lewy=0;
			int gdzie_prawy=0;

			cin>>l>>r>>k;
			//szukam lewa_1
			int obc=0;
			int poz=0;
			while(obc+d[poz+1]<l)
			{
				poz++;
				obc+=d[poz];
			}

			if((poz+1)%2==1)//jesli ten poczatek to 1
			{
				lewa_1=min(d[poz+1]-((l-1)-obc),r-l+1);
				koniec_lewego=l+lewa_1-1;
			}
			p=poz+2;
			gdzie_lewy=poz+1;

			//szukam prawa_1
			obc=0;
			poz=0;
			while(obc+d[poz+1]<r)
			{
				poz++;
				obc+=d[poz];
			}
			if((poz+1)%2==1)//jesli ten koniec to 1
			{
				prawa_1=r-obc;
				koniec_prawego=r-prawa_1+1;
			}
			e=poz;
			gdzie_prawy=poz+1;

			// cout<<endl<<p<<" "<<e<<" "<<lewa_1<<"-"<<prawa_1<<" "<<gdzie_lewy<<"="<<gdzie_prawy<<": ";//debug

			if(gdzie_lewy==gdzie_prawy)
			{
				if(gdzie_lewy%2==1)
					solv=max(solv,r-l+1);
			}
			else
			{
				vector<int>vec;
				for(int i=p;i<=e;++i)
					if(i%2==1)//jedynka
						vec.push_back(d[i]);
				sort(vec.begin(),vec.end(),greater<int>());


				int sum=0;
				//nie biore zadnego <- do rozpatrzenia
				if(1<=k)
					solv=max(solv,sum+max(lewa_1,prawa_1));
				if(2<=k && (koniec_lewego==-1 || koniec_prawego==-1 || koniec_lewego<koniec_prawego))
					solv=max(solv,sum+lewa_1+prawa_1);

				for(int i=0;i<vec.size();++i)//biore wszystkie na prefixie 0...i
				{
					if((i+1)*2>k) break;
					sum+=vec[i];
					solv=max(solv,sum);

					if((i+1)*2+1<=k)
						solv=max(solv,sum+max(lewa_1,prawa_1));
					if((i+1)*2+2<=k && (koniec_lewego==-1 || koniec_prawego==-1 || koniec_lewego<koniec_prawego))
						solv=max(solv,sum+lewa_1+prawa_1);
				}
			}
			cout<<solv<<'\n';
		}
	}

}