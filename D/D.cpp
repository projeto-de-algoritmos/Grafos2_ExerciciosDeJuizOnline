#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef tuple<double, int, int> edge;

class UnionFind {
public:
    vector<int> parent, rank;

    UnionFind(int n) {
        parent.assign(n, 0);
        rank.assign(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    bool same_set(int u, int v) {
        return find_set(u) == find_set(v);
    }

    void union_set(int u, int v) {
        u = find_set(u);
        v = find_set(v);
        if (u != v) {
            if (rank[u] < rank[v])
                swap(u, v);
            parent[v] = u;
            if (rank[u] == rank[v])
                rank[u]++;
        }
    }
};

double msf(int k, int N, vector<edge>& es) {
    sort(es.begin(), es.end());

    double cost = 0;

    int cc = N;

    UnionFind ufds(N);

    for (auto [w, u, v] : es) {
        if (not ufds.same_set(u, v)) {
            cost = max(cost, w);
            ufds.union_set(u, v);

            if (--cc == k) return cost;
        }
    }

    return cost;
}

double solve(int S, int P, const vector<ii>& ps) {
    vector<edge> es;

    for (int i = 0; i < P; ++i) {
        auto [x, y] = ps[i];

        for (int j = i + 1; j < P; ++j) {
            auto [z, w] = ps[j];
            auto dist = hypot(x - z, y - w);

            es.emplace_back(dist, i, j);
            es.emplace_back(dist, j, i);
        }
    }

    return msf(S, P, es);
}

int main() {
    int N;
    cin >> N;

    while (N--) {
        int S, P;
        cin >> S >> P;

        vector<ii> ps(P);
        for (int i = 0; i < P; ++i) {
            cin >> ps[i].first >> ps[i].second;
        }

        double result = solve(S, P, ps);

        cout << fixed << setprecision(2) << result << endl;
    }

    return 0;
}