#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef tuple<ll, ll, ll> iii;

const ll oo = LLONG_MAX;
vector<vector<ll>> dist;
vector<vector<ii>> adj;
vector<ll> fuel;
bitset<301> processed;

void dijkstra(int s, ll N, ll L)
{
    for (ll i = 1; i <= N; i++)
    {
        dist[s][i] = fuel[i] = oo;
    }

    dist[s][s] = 0;
    fuel[s] = L;
    processed.reset();

    priority_queue<iii, vector<iii>, greater<iii>> pq;
    pq.push(iii(0, -L, s));

    while (!pq.empty())
    {
        auto [d, f, u] = pq.top();
        pq.pop();

        if (processed[u])
            continue;

        processed[u] = true;

        for (const auto &[v, c] : adj[u])
        {
            if (c <= fuel[u] && (dist[s][v] > dist[s][u] || (dist[s][v] == dist[s][u] && fuel[u] - c > fuel[v])))
            {
                dist[s][v] = dist[s][u];
                fuel[v] = fuel[u] - c;
                pq.push(iii(dist[s][v], -fuel[v], v));
                continue;
            }

            if (c <= L && (dist[s][v] > dist[s][u] + 1 || (dist[s][v] == dist[s][u] + 1 && L - c > fuel[v])))
            {
                dist[s][v] = dist[s][u] + 1;
                fuel[v] = L - c;
                pq.push(iii(dist[s][v], -fuel[v], v));
            }
        }
    }
}

vector<ll> solve(ll N, ll L, const vector<ii> &qs)
{
    vector<ll> ans(qs.size());

    for (int s = 1; s <= N; ++s)
    {
        dijkstra(s, N, L);
    }

    for (size_t i = 0; i < qs.size(); ++i)
    {
        auto [s, t] = qs[i];
        ans[i] = (dist[s][t] == oo ? -1 : dist[s][t]);
    }

    return ans;
}

int main()
{
    ll N, M, L;
    cin >> N >> M >> L;

    dist.assign(N + 1, vector<ll>(N + 1, oo));
    adj.assign(N + 1, vector<ii>(0));

    for (ll i = 0; i < M; i++)
    {
        ll a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    ll Q;
    cin >> Q;

    vector<ii> queries(Q);
    for (ll i = 0; i < Q; i++)
    {
        ll s, t;
        cin >> s >> t;
        queries[i] = {s, t};
    }

    fuel.assign(N + 1, 0);
    vector<ll> ans = solve(N, L, queries);

    for (ll a : ans)
    {
        cout << a << endl;
    }

    return 0;
}
