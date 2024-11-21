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
    int nodes_amount, edges_amount, source_node, target_node;
    cin >> nodes_amount >> edges_amount >> source_node >> target_node;
    source_node--; target_node--;
    vector<unordered_map<int, edge*>> edges(nodes_amount);
    for (int i = 0; i < edges_amount; i++) {
        int start_node, end_node, edge_cap;
        cin >> start_node >> end_node >> edge_cap;
        start_node--; end_node--;
        edge *tmp_edge = new edge{0, edge_cap, end_node}; 
        edges[start_node][end_node] = tmp_edge;
        edges[end_node][start_node] = tmp_edge;
    }
    int max_flow = 0;
    forever {
        unordered_set<int> visited;
        queue<pair<int, int>> visit_order;
        vector<int> parents(nodes_amount, -1);
        visit_order.push(pair<int, int>{source_node, source_node});
        while (!visit_order.empty()) {
            pair<int, int> tmp_pair = visit_order.front();
            visit_order.pop();
            int current_node = tmp_pair.first, parent_node = tmp_pair.second;
            if (visited.count(current_node)) continue;
            visited.insert(current_node);
            parents[current_node] = parent_node;
            if (current_node == target_node) break;
            for (pair<int, edge*> ep : edges[current_node]) {
                if (visited.count(ep.first)) continue;
                int edge_cap = ep.second->cap;
                if (current_node == ep.second->goal) edge_cap = -edge_cap;
                if (ep.second->flow == edge_cap) continue;
                visit_order.push(pair<int, int>{ep.first, current_node});
            }
        }
        if (parents[target_node] == -1) break;
        int addition_flow = -1;
        for (
            int current_node = target_node; 
            current_node != source_node; 
            current_node = parents[current_node]
        ) {
            int edge_flow = 
            abs(edges[current_node][parents[current_node]]->cap)
            -
            abs(edges[current_node][parents[current_node]]->flow);
            if (addition_flow == -1 || addition_flow > edge_flow) addition_flow = edge_flow;
        }
        for (
            int current_node = target_node; 
            current_node != source_node; 
            current_node = parents[current_node]
        ) {
            int tmp_flow = addition_flow;
            if (current_node != edges[current_node][parents[current_node]]->goal) tmp_flow = -tmp_flow;
            edges[current_node][parents[current_node]]->flow += tmp_flow;
        }
        max_flow += addition_flow;
    }
    // cout << max_flow << endl;//DEBUG
    
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int tests_amount;
    cin >> tests_amount;
    for (; tests_amount > 0; tests_amount--) solve();
    flush(cout);
    return 0;
}