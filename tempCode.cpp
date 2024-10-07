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

struct DSU {
    ll n;
    vector<ll> lab;

    DSU(ll _n) {
        n = _n;
        lab.resize(n + 27, -1);
    }

    ll find(ll u) {
        return lab[u] < 0 ? u : lab[u] = find(lab[u]);
    }

    bool join(ll u, ll v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }

    bool connect(ll u, ll v) {
        u = find(u);
        v = find(v);
        return u == v;
    }
};

struct Edge {
    ll u, v;
    db w;
    Edge(ll _u, ll _v, db _w) {
        u = _u, v = _v, w = _w;
    }
    bool operator < (const Edge &other) const {
        return w < other.w;
    }
};

ll n, q, w, h;
ll x[N], y[N], r[N];
bool ans[5][N];
pair<ll, ll> tourist[N];
vector<ll> group[5];
vector<Edge> edge;

db sq(db x) {
    return x * x;
}

db dist(ll i, ll j) { 
    return sqrt(sq(x[i] - x[j]) + sq(y[i] - y[j])) - r[i] - r[j];
}

signed main() {
    // freopen("bdbang.inp", "r", stdin);
    // freopen("bdbang.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q >> w >> h;
    fu(i, 1, n) cin >> x[i] >> y[i] >> r[i];
    fu(i, 1, n) {
        edge.push_back(Edge(n + 1, i, x[i] - r[i]));
        edge.push_back(Edge(n + 2, i, y[i] - r[i]));
        edge.push_back(Edge(n + 3, i, w - x[i] - r[i]));
        edge.push_back(Edge(n + 4, i, h - y[i] - r[i]));
        fu(j, i + 1, n) edge.push_back(Edge(i, j, dist(i, j)));
    }
    sort(all(edge));
    fu(i, 1, q) {
        cin >> tourist[i].ss >> tourist[i].ff;
        tourist[i].ss *= 2;
        group[tourist[i].ff].push_back(i);
    }
    {
        DSU dsu(n + 4);
        vector<pair<ll, ll>> a;
        for (ll id : group[1]) a.push_back(make_pair(tourist[id].ss, id));
        
        sort(all(a));
        ll j = 0;
        fu(i, 0, sz(a) - 1) {
            while (j < sz(edge) && edge[j].w < a[i].ff) {
                dsu.join(edge[j].u, edge[j].v);
                j++;
            }
            ans[1][a[i].ss] = true;
            if (!dsu.connect(n + 1, n + 3) && !dsu.connect(n + 1, n + 2) && !dsu.connect(n + 4, n + 1)) ans[4][a[i].ss] = true;
            if (!dsu.connect(n + 1, n + 2) && !dsu.connect(n + 4, n + 2) && !dsu.connect(n + 3, n + 2)) ans[2][a[i].ss] = true;
            if (!dsu.connect(n + 1, n + 2) && !dsu.connect(n + 4, n + 2) && !dsu.connect(n + 4, n + 3) && !dsu.connect(n + 1, n + 3)) ans[3][a[i].ss] = true;
        }
    }

    {
        DSU dsu(n + 4);
        vector<pair<ll, ll>> a;
        for (ll id : group[2]) a.push_back(make_pair(tourist[id].ss, id));
        sort(all(a));
        ll j = 0;
        fu(i, 0, sz(a) - 1) {
            while (j < sz(edge) && edge[j].w < a[i].ff) {
                dsu.join(edge[j].u, edge[j].v);
                j++;
            }  
            ans[2][a[i].ss] = true;
            if (!dsu.connect(n + 1, n + 3) && !dsu.connect(n + 4, n + 2) && !dsu.connect(n + 2, n + 3) && !dsu.connect(n + 1, n + 4)) ans[4][a[i].ss] = true;
            if (!dsu.connect(n + 1, n + 2) && !dsu.connect(n + 4, n + 2) && !dsu.connect(n + 2, n + 3)) ans[1][a[i].ss] = true;
            if (!dsu.connect(n + 1, n + 3) && !dsu.connect(n + 3, n + 2) && !dsu.connect(n + 4, n + 3)) ans[3][a[i].ss] = true;

        }
    }
    {
        DSU dsu(n + 4);
        vector<pair<ll, ll>> a;
        for (ll id : group[3]) a.push_back(make_pair(tourist[id].ss, id));
        sort(all(a));
        ll j = 0;
        fu(i, 0, sz(a) - 1) {
            while (j < sz(edge) && edge[j].w < a[i].ff) {
                dsu.join(edge[j].u, edge[j].v);
                j++;
            }  
            ans[3][a[i].ss] = true;
            if (!dsu.connect(n + 1, n + 2) && !dsu.connect(n + 4, n + 2) && !dsu.connect(n + 4, n + 3) && !dsu.connect(n + 1, n + 3)) ans[1][a[i].ss] = true;
            if (!dsu.connect(n + 1, n + 3) && !dsu.connect(n + 3, n + 2) && !dsu.connect(n + 4, n + 3)) ans[2][a[i].ss] = true;
            if (!dsu.connect(n + 4, n + 2) && !dsu.connect(n + 4, n + 1) && !dsu.connect(n + 4, n + 3)) ans[4][a[i].ss] = true;

        }
    }
    {
        DSU dsu(n + 4);
        vector<pair<ll, ll>> a;
        for (ll id : group[4]) a.push_back(make_pair(tourist[id].ss, id));
        sort(all(a));
        ll j = 0;
        fu(i, 0, sz(a) - 1) {
            while (j < sz(edge) && edge[j].w < a[i].ff) {
                dsu.join(edge[j].u, edge[j].v);
                j++;
            }  
            ans[4][a[i].ss] = true;
            if (!dsu.connect(n + 1, n + 3) && !dsu.connect(n + 1, n + 2) && !dsu.connect(n + 4, n + 1)) ans[1][a[i].ss] = true;
            if (!dsu.connect(n + 1, n + 3) && !dsu.connect(n + 4, n + 2) && !dsu.connect(n + 2, n + 3) && !dsu.connect(n + 1, n + 4)) ans[2][a[i].ss] = true;
            if (!dsu.connect(n + 4, n + 2) && !dsu.connect(n + 4, n + 1) && !dsu.connect(n + 4, n + 3)) ans[3][a[i].ss] = true;
        }
    }
    fu(i, 1, q) {
        fu(j, 1, 4) if (ans[j][i]) cout << j; 
        cout << el;
    }


}

