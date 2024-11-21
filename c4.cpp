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
    extra_source_node = 2 * nodes_amount + 1,
    extra_target_node = extra_source_node + 1,
    target_node = extra_target_node + 1,
    nodes_total = target_node + 1,
    infinite_cap = nodes_total * 1e5 + 5;
    vector<unordered_map<int, edge*>> edges(nodes_total);
    {
        edge *tmp_edge = new edge{0, infinite_cap, extra_source_node};
        edges[extra_source_node][extra_target_node] = tmp_edge;
        edges[extra_target_node][extra_source_node] = tmp_edge;
    }
    for (int i = 1; i <= nodes_amount; i++) {
        edge *tmp_edge = new edge{0, infinite_cap, i};
        edges[extra_source_node][i] = tmp_edge;
        edges[i][extra_source_node] = tmp_edge;
        tmp_edge = new edge{0, infinite_cap, extra_target_node};
        int j = i + nodes_amount; 
        edges[j][extra_target_node] = tmp_edge;
        edges[extra_target_node][j] = tmp_edge;
        tmp_edge = new edge{0, infinite_cap, j};
        edges[source_node][j] = tmp_edge;
        edges[j][source_node] = tmp_edge;
        tmp_edge = new edge{0, infinite_cap, target_node};
        edges[i][target_node] = tmp_edge;
        edges[target_node][i] = tmp_edge;
    }
    for (; edges_amount > 0; edges_amount--) {
        int i, j, border, capacity;
        cin >> i >> j >> border >> capacity;
        edge *tmp_edge = new edge{0, capacity - border, j};
        edges[i][j] = tmp_edge;
        edges[j][i] = tmp_edge;
    }
    // regular max flow, if all edges that are in beetwen main nodes not full, then say NO, otherwise YES
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    solve();
    flush(cout);
    return 0;
}