#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i=a; i<=b; ++i)
#define ll long long
#define eb emplace_back
#define f first
#define s second
#define pb push_back
#define sz(A) (int)(A.size())
#define V vector

int n, q;
ll d, w, l;
V<ll> res;

pair<ll, ll> norm(pair<ll, ll> val, ll odl) {
  val.s+=odl;
  val.f+=(val.s)/d;
  val.s%=d;
  return val;
}

void rozw_stol(V<ll> &A) {
  int ln = sz(A)-1;
  V<V<pair<ll, ll>>> dp(ln+1, V<pair<ll, ll>>(ln+1, {0, 0}));
  FOR(i, 1, ln) {
    FOR(j, 0, i-1) {
      pair<ll, ll> val = {0, 0};
      if(j>=1) val=norm({dp[i-1][j-1].f+1, 0}, A[i]-A[i-1]-d);
      dp[i][j]=max({norm(dp[i-1][j], A[i]-A[i-1]), val});
    }
  }

  V<ll> nowy(n+1, 0);
  FOR(i, 0, n) {
    FOR(j, 0, ln-1) {
      if(i+j>n) break;
      nowy[i+j]=max(nowy[i+j], res[i]+dp[ln][ln-1-j].f);
    }
  }
  swap(nowy, res);
}

int main() {
  cin.tie(0) -> ios_base::sync_with_stdio(0);
  cin >> n >> q >> d >> l >> w;
  res.resize(n+1);
  FOR(i, 1, n) res[i]=-7e18;
  V<V<ll>> stoly(l+1);
  FOR(i, 1, l) stoly[i].eb(0);
  ll k, p;
  FOR(i, 1, n) {
    cin >> k >> p;
    stoly[k].eb(p);
  }
  FOR(i, 1, l) stoly[i].eb(w);
  FOR(i, 1, l) sort(stoly[i].begin(), stoly[i].end());
  FOR(i, 1, l) rozw_stol(stoly[i]);

  ll m;
  while(q--) {
    cin >> m;
    bool f=0;
    FOR(i, 0, n) {
      if(res[i]>=n+m) {
        cout << i << '\n';
        f=1;
        break;
      }
    }
    if(!f) cout << "-1\n"; 
  }
}