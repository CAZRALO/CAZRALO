#include <bits/stdc++.h>

#define el "\n"
#define fu(i, a, b) for (int i = a; i <= b; ++i)
#define fd(i, a, b) for (int i = a; i >= b; --i)
#define ff first
#define ss second
#define all(v) (v).begin(), (v).end()
#define sz(v) (ll)(v).size()
#define mask(i) (1LL << (i))
#define bit(x, i) ((x) >> (i) & 1)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;

mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll Rand(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r) (rng);
}

ll last(ll msk)     {return msk & (-msk);}
ll pop_cnt(ll msk)  {return __builtin_popcountll(msk);}
ll ctz(ll msk)      {return __builtin_ctzll(msk);}
ll lg(ll msk)       {return 63 - __builtin_clzll(msk);}

template<class T1, class T2> bool minimize(T1 &a, T2 b) {
    return a > b ? a = b, 1 : 0;
}

template<class T1, class T2> bool maximize(T1 &a, T2 b) {
    return a < b ? a = b, 1 : 0;
}

template<class T> void print(T a) {
    for (auto x : a) cout << x << " ";
    cout << el;
}

template<class T> void compress(T &a) {
    sort(all(a));
    a.resize(unique(all(a)) - a.begin());
}

const long long N = 1e5 + 27, M = 1e5 + 27, inf = 2e18, bl = 320, base = 311, mod = 123456789, lim = 1e6;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}

