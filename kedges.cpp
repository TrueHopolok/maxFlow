#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#define forever while (1) // because why not 
using namespace std;

struct edge {
    int flow;
    int cost;
    int goal;
    bool operator<(const edge& r) const {
        return this->cost < r.cost;
    }
};
struct cmp_edge {
    bool operator()( const edge& lhs, const edge& rhs ) const {
        return lhs.cost > rhs.cost;
    }
};

/*
If there is no god, than who wrote this code.
...
Me, because it has a segfault.
*/
void mfree(const vector<unordered_map<int, edge*>> &v) {
    // for (const unordered_map<int, edge*> &m : v) {
    //     for (const pair<int, edge*> &p : m) {
    //         free(p.second);
    //     }
    // }
}

void solve() {
    int required_flow, nodes_amount, edges_amount;
    cin >> required_flow >> nodes_amount >> edges_amount;
    int target_node = 2*nodes_amount+1;

    vector<int> nodes(nodes_amount+2);
    for (int i = 1; i <= nodes_amount; i++) cin >> nodes[i];

    vector<unordered_map<int, edge*>> edges(target_node+1); // 2*nodes_amount+2
    for (int i = 1; i <= nodes_amount; i++) {
        edge* tmp_edge = new edge{0, 0, i};
        edges[0][i] = tmp_edge;
        edges[i][0] = tmp_edge;
        edges[i+nodes_amount][target_node] = new edge{0, 0, target_node};
    }

    for (int i = 0; i < edges_amount; i++) {
        int start_node, end_node;
        cin >> start_node >> end_node;
        edge* tmp_edge = new edge{0, nodes[start_node] + nodes[end_node], end_node + nodes_amount};
        end_node += nodes_amount;
        edges[start_node][end_node] = tmp_edge;
        edges[end_node][start_node] = tmp_edge;
    }

    // //DEBUG-start
    // cout << "\n-+-+-+-+-+-+-+-+-+-+-" << endl;
    // for (int i = 0; i < edges.size(); i++) {
    //     for (pair<int, edge*> p : edges[i]) {
    //         if (i == p.second->goal) continue; 
    //         cout << i << "->" << p.first << "==" << p.second->cost << endl;
    //     }
    // }
    // cout << "-+-+-+-+-+-+-+-+-+-+-" << endl << endl;
    // //DEBUG-end

    int answer_cost = 0;
    nodes_amount = 2*nodes_amount+2;
    for (; required_flow > 0; required_flow--) {
        unordered_set<int> visited;
        vector<int> parents(nodes_amount, -1);
        priority_queue<edge, vector<edge>, cmp_edge> visit_order;
        visit_order.push(edge{0, 0, 0});

        while (!visit_order.empty()) {
            edge visit = visit_order.top();
            visit_order.pop();
            if (visited.count(visit.flow)) continue; 

            visited.insert(visit.flow);
            parents[visit.flow] = visit.goal;
            
            for (const pair<int, edge*> &p : edges[visit.flow]) {
                if (visited.count(p.first)) continue;
                if (p.second->flow == ((p.second->goal == p.first) ? 1 : 0)) continue;
                visit_order.push(edge{p.first, p.second->cost + visit.cost, visit.flow});
            }
        }

        if (parents[target_node] == -1) {
            cout << "NIE\n";
            mfree(edges);
            return;
        }

        for (int i = target_node; i != 0; i = parents[i]) {
            edge* tmp_edge = edges[parents[i]][i];
            int tmp_flow = tmp_edge->flow;
            tmp_flow = tmp_flow == 0 ? 1 : 0;
            tmp_edge->flow = tmp_flow;
            if (tmp_flow) answer_cost += tmp_edge->cost;
            else answer_cost -= tmp_edge->cost;
        }
    }
    cout << answer_cost << '\n';
    mfree(edges);
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    solve();
    flush(cout);
    return 0;
}















































































// There is nothing here