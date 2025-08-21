//code I got from a friend
# include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll inf = 1e9 + 7;
const ll mod =  1e6 + 3;
const ll Mx = 1000000;
ll n , m , k , d , r , ans = 0 , N1 , H1 , N2 , H2;
struct node {
    ll l , r , kol , heigh;
};
struct Segment_tree {
        vector<pair<ll , ll> >tree;
        ll sz;
        void init(ll n) {
              sz = 1;
              while (sz < n)sz *= 2;
              tree.clear();
              tree.assign(sz * 2 + 5 , {0 , 0});
        }
        void update(ll nom , ll fl , ll x , ll lx , ll rx) {
               if (rx - lx == 1) {
                    tree[x].first += nom * fl;
                    tree[x].second += fl;
                    return;
               }
               ll mid = (lx + rx) / 2;
               if (nom < mid)update(nom , fl , x * 2 + 1 , lx , mid);
               else update(nom , fl , x * 2 + 2 , mid , rx);
               tree[x].first = tree[x * 2 + 1].first + tree[x * 2 + 2].first;
               tree[x].second = tree[x * 2 + 1].second + tree[x * 2 + 2].second;
        }
        ll get_kol(ll have , ll x , ll lx , ll rx) {
           //    cout << "lx = " << lx << " rx = " << rx << " have = " << have << " cnt = " << tree[x].second << endl;
               if (rx - lx == 1) {
                    if (tree[x].second == 0)return 0;
                    ll one = tree[x].first / tree[x].second;
                    return (have / one);
               }
               ll mid = (lx + rx) / 2;
          //     cout << "left = " << tree[x * 2 + 1].first << endl;
               if (tree[x * 2 + 1].first > have)return get_kol(have , x * 2 + 1 , lx , mid);
               else return tree[x * 2 + 1].second + get_kol(have - tree[x * 2 + 1].first , x * 2 + 2 , mid , rx);
        }
};
Segment_tree s_t;
bool can_build(ll n1 , ll n2 , ll sh , ll H , ll sz) {
        if (sh > n1 + (n2 / H))return 0;
        if (sh > n1)n2 -= H * (sh - n1) , n1 = 0;
        else n1 -= sh;
       // cout << "ok" << endl;
        ll kol_can = s_t.get_kol(n2 , 0 , 0 , s_t.sz);
     //   cout << "kol_can = " << kol_can << endl;
        if (kol_can + n1 >= sz)return 1;
        else return 0;
}
void f(ll H1 , ll H2 , ll N1 , ll N2 , vector<ll>&x , vector<ll>&h) {
        vector<node>vec;
        for (int l = 0; l < n; ) {
              ll r = l , kol = 1 , max_pos = x[l] + h[l];
              while (r + 1 < n && max_pos >= x[r + 1]) {
                   r++;
                   max_pos = max(max_pos , x[r] + h[r]);
                   kol++;
              }
              vec.push_back({x[l] , x[r] , kol , max_pos - x[r]});
              l = r + 1;
        }
       // cout << vec[0].kol << endl;
        ll H = H1 / H2;
      //  cout << "ok2" << endl;
        s_t.init(2e6 + 1);
        ans = max(ans , vec[0].kol);
        ll l = 0 , cur_kol = vec[0].kol , sh = 0;
        for (int r = 1; r < vec.size(); r++) {
              ll d = vec[r].l - vec[r - 1].r - vec[r - 1].heigh;
              if (d < 0)assert(0);
              ll ai = d / H1 , bi = (d % H1) / H2 + (((d % H1) % H2) > 0);
              sh += ai;
             // cout << "r = " << r << " ai = " << ai << " bi = " << bi << endl;
              s_t.update(bi , 1 , 0 , 0 , s_t.sz);
            //  cout << "upd +1 " << bi << endl;
              cur_kol += vec[r].kol;
            //  cout << "r = " << r << endl;
           //   cout << "sh = " << sh << endl;
              while (l < r && !can_build(N1 , N2 , sh , H , r - l)) {
                //     cout << "l++" << endl;
                     ll d_prev = vec[l + 1].l - vec[l].r - vec[l].heigh;
                     ll al = d_prev / H1 , bl = (d_prev % H1) / H2 + (((d_prev % H1) % H2) > 0);
                     sh -= al;
                     s_t.update(bl , -1 , 0 , 0 , s_t.sz);
                 //    cout << "upd -1 " << bi << endl;
                     cur_kol -= vec[l].kol;
                     l++;
              }
            //  cout << "l = " << l << " r = " << r << " kol = " << cur_kol << " d = " << d << endl;
              ans = max(ans , cur_kol);
        }
}
int main() {
  //  freopen("tests.txt" , "r" , stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
   // for (int test = 1; test <= 100000; test++) {
        cin >> n;
        vector<ll>x(n) , h(n);
        for (int i = 0; i < n; i++) {
              cin >> x[i] >> h[i];
        }
        cin >> N1 >> H1 >> N2 >> H2;
        if (H2 % H1 == 0) {
            swap(N1 , N2);
            swap(H1 , H2);
        }
        ans = 1;
      //  cout << "fir" << endl;
        f(H1 , H2 , N1 , N2 , x , h);
        reverse(x.begin() , x.end());
        reverse(h.begin() , h.end());
       // cout << "sec" << endl;
        for (int i = 0; i < n; i++) x[i] *= -1;
        f(H1 , H2 , N1 , N2 , x , h);
        cout << ans + N1 + N2;
   /*     cout << "test = " << test << endl;
        ll real_res;
        cin >> real_res;
        cout << ans << ' ' << real_res << endl;
        if (ans != real_res) {
             reverse(x.begin() , x.end());
             reverse(h.begin() , h.end());
             for (int i = 0; i < n; i++) x[i] *= -1;
            cout << n << endl;
            for (int i = 0; i < n; i++) {
                 cout << x[i] << ' ' << h[i] << endl;
            }
            cout << N1 << ' ' << H1 << ' ' << N2 << ' ' << H2 << endl;
            cout << ans << ' ' << real_res << endl;
            return 0;
        }
    } */
}
/*
5
0 4
5 4
11 4
15 4
20 4
0 1 0 3
*/