#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#define forever while (1) // because why not 
using namespace std;

struct edge {
    int flow;
    int cap;
    int goal;
};

void solve() {
    int nodes_amount, edges_amount;
    cin >> nodes_amount >> edges_amount;
    const int 
    source_node = 0,
    target_node = nodes_amount + 1,
    nodes_total = target_node + 1,
    infinite_cap = nodes_amount * 1e5 + 5;
    vector<unordered_map<int, edge*>> edges(nodes_total);
    for (int i = 1; i <= nodes_amount; i++) {
        edge *tmp_edge = new edge{0, 0, i};
        edges[i][source_node] = tmp_edge;
        edges[source_node][i] = tmp_edge;
        tmp_edge = new edge{0, 0, target_node};
        edges[i][target_node] = tmp_edge;
        edges[target_node][i] = tmp_edge;
    }
    vector<pair<int, edge*>> original_edges(edges_amount);
    int required_flow = 0;
    for (int edge_num = 0; edge_num < edges_amount; edge_num++) {
        int i, j, border, capacity;
        cin >> i >> j >> border >> capacity;
        edge *tmp_edge = new edge{0, capacity - border, j};
        edges[i][j] = tmp_edge;
        edges[j][i] = tmp_edge;
        original_edges[edge_num] = {border, tmp_edge};
        edges[source_node][j]->cap += border;
        edges[target_node][i]->cap += border;
        required_flow += border;
    }

    // regular max flow, if all edges that are in beetwen main nodes not full, then say NO, otherwise YES
    int max_flow = 0;
    forever {
        unordered_set<int> visited;
        vector<int> parents(nodes_total, -1);
        queue<pair<int, int>> visit_order;
        visit_order.push({source_node, source_node});
        while (!visit_order.empty()) {
            pair visit_pair = visit_order.front();
            visit_order.pop();
            int cur_node = visit_pair.first, par_node = visit_pair.second;
            if (visited.count(cur_node)) continue;
            visited.insert(cur_node);
            parents[cur_node] = par_node;
            for (const pair<int, edge*> &edge_pair : edges[cur_node]) {
                int n = edge_pair.first;
                if (visited.count(n)) continue;
                edge *e = edge_pair.second;
                int e_cap = e->cap;
                if (e->goal == cur_node) e_cap = 0;
                if (e_cap == e->flow) continue;
                visit_order.push({n, cur_node});
            }
        }
        if (parents[target_node] == -1) break;
        int add_flow = 0;
        for (int i = target_node, j = parents[target_node]; i != source_node; i = parents[i], j = parents[j]) {
            int f;
            if (j == edges[i][j]->goal) f = edges[i][j]->flow;
            else f = edges[i][j]->cap  - edges[i][j]->flow;
            if (add_flow == 0 || add_flow > f) add_flow = f;
        }
        for (int i = target_node, j = parents[target_node]; i != source_node; i = parents[i], j = parents[j]) {
            int a = add_flow;
            if (j == edges[i][j]->goal) a = - a;
            edges[i][j]->flow += a; 
        }
        max_flow += add_flow;
    }
    if (max_flow != required_flow) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    for (int i = 0; i < edges_amount; i++) cout << original_edges[i].second->flow + original_edges[i].first << '\n';

    // //DEBUG
    // for (int i = 0; i < nodes_total; i++) {
    //     for (const pair<int, edge*> &p : edges[i]) {
    //         if (i == p.second->goal) continue;
    //         cout << i << "->" << p.first << '|' << p.second->flow << '/' << p.second->cap << endl;
    //     }
    // }
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    solve();
    flush(cout);
    return 0;
}