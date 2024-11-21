#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#define forever while (1) // because why not 
using namespace std;

struct edge {
    int flow;
    int goal;
};

void solve() {
    int nodes_amount;
    cin >> nodes_amount;
    const int source_node = 0, target_node = 2 * nodes_amount + 1;
    const int nodes_total = target_node + 1;
    vector<unordered_map<int, edge*>> edges(nodes_total);
    forever {
        int start_node, end_node;
        if (cin >> start_node) {
            cin >> end_node;
            end_node += nodes_amount;
            edge* tmp_edge = new edge{0, end_node};
            edges[start_node][end_node] = tmp_edge;
            edges[end_node][start_node] = tmp_edge;
        } else break;
    }
    for (int i = 1; i <= nodes_amount; i++) {
        edge* tmp_edge = new edge{0, i};
        edges[source_node][i] = tmp_edge;
        edges[i][source_node] = tmp_edge;
        int start_node = nodes_amount + i;
        tmp_edge = new edge{0, target_node};
        edges[start_node][target_node] = tmp_edge;
        edges[target_node][start_node] = tmp_edge;
    } 

    int max_flow = 0;
    forever {
        unordered_set<int> visited;
        vector<int> parents(nodes_total, -1);
        queue<pair<int, int>> visit_order;
        visit_order.push(pair<int, int>{source_node, source_node});
        while (!visit_order.empty()) {
            pair<int, int> tmp_pair = visit_order.front();
            visit_order.pop();
            int current_node = tmp_pair.first, parent_node = tmp_pair.second;
            if (visited.count(current_node)) continue;
            visited.insert(current_node);
            parents[current_node] = parent_node;
            if (current_node == target_node) break;
            for (const pair<int, edge*> &edge_pair : edges[current_node]) {
                if (visited.count(edge_pair.first)) continue;
                int edge_flow = edge_pair.second->flow;
                int edge_goal = edge_pair.second->goal;
                if (edge_goal == current_node) edge_flow = (edge_flow == 1) ? 0 : 1;
                if (edge_flow) continue; 
                visit_order.push(pair<int, int>{edge_pair.first, current_node});
            }
        }
        if (parents[target_node] == -1) break;
        for (int current_node = target_node; current_node != source_node; current_node = parents[current_node]) {
            int edge_flow = edges[current_node][parents[current_node]]->flow;
            edge_flow = (edge_flow == 1) ? 0 : 1;
            edges[current_node][parents[current_node]]->flow = edge_flow;
        }
        max_flow++;
    }
    cout << nodes_amount - max_flow << '\n';
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    solve();
    flush(cout);
    return 0;
}