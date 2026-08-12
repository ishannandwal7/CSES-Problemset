#include "bits/stdc++.h"
using namespace std;

/*
    For variable x:

    positive literal  -> 2 * x
    negative literal  -> 2 * x + 1

    Example:

    x1  -> 0
    !x1 -> 1

    x2  -> 2
    !x2 -> 3
*/

int getNode(char sign, int variable) {
    int x = variable - 1;

    if (sign == '+')
        return 2 * x;

    return 2 * x + 1;
}

/*
    Every literal has a corresponding opposite.

    0 <-> 1
    2 <-> 3
    4 <-> 5
*/
int getOpposite(int node) {
    return node ^ 1;
}

/*
    For:

        A OR B

    add:

        NOT A -> B
        NOT B -> A
*/
void addClause(
    int A,
    int B,
    vector<vector<int>>& graph,
    vector<vector<int>>& reverseGraph
) {
    int notA = getOpposite(A);
    int notB = getOpposite(B);

    graph[notA].push_back(B);
    graph[notB].push_back(A);

    reverseGraph[B].push_back(notA);
    reverseGraph[A].push_back(notB);
}

/*
    First DFS of Kosaraju.

    We only need the finishing order.
*/
void dfs1(
    int node,
    vector<vector<int>>& graph,
    vector<bool>& visited,
    vector<int>& order
) {
    visited[node] = true;

    for (int next : graph[node]) {
        if (!visited[next]) {
            dfs1(next, graph, visited, order);
        }
    }

    // Add after exploring children
    order.push_back(node);
}

/*
    Second DFS of Kosaraju.

    Assign every node to its SCC.
*/
void dfs2(
    int node,
    vector<vector<int>>& reverseGraph,
    vector<bool>& visited,
    vector<int>& component,
    int id
) {
    visited[node] = true;
    component[node] = id;

    for (int next : reverseGraph[node]) {
        if (!visited[next]) {
            dfs2(
                next,
                reverseGraph,
                visited,
                component,
                id
            );
        }
    }
}

/*
    Run Kosaraju and return SCC ID
    for every node.
*/
vector<int> findSCC(
    vector<vector<int>>& graph,
    vector<vector<int>>& reverseGraph
) {
    int N = graph.size();

    vector<bool> visited(N, false);
    vector<int> order;

    // First DFS
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            dfs1(i, graph, visited, order);
        }
    }

    // Second DFS
    fill(visited.begin(), visited.end(), false);

    vector<int> component(N, -1);

    reverse(order.begin(), order.end());

    int id = 0;

    for (int node : order) {
        if (!visited[node]) {
            dfs2(
                node,
                reverseGraph,
                visited,
                component,
                id
            );

            id++;
        }
    }

    return component;
}

/*
    Check whether the 2-SAT problem
    is actually satisfiable.
*/
bool isPossible(
    int m,
    vector<int>& component
) {
    for (int i = 0; i < m; i++) {

        int positive = 2 * i;
        int negative = 2 * i + 1;

        // x and !x cannot be in same SCC
        if (component[positive] == component[negative]) {
            return false;
        }
    }

    return true;
}

/*
    Construct the actual toppings.

    The SCC with the larger ID gets chosen.
*/
vector<char> getAnswer(
    int m,
    vector<int>& component
) {
    vector<char> answer(m);

    for (int i = 0; i < m; i++) {

        int positive = 2 * i;
        int negative = 2 * i + 1;

        if (component[positive] > component[negative]) {
            answer[i] = '+';
        } else {
            answer[i] = '-';
        }
    }

    return answer;
}

void solve() {

    int n, m;
    cin >> n >> m;

    // 2 nodes per variable:
    // x and !x
    int totalNodes = 2 * m;

    vector<vector<int>> graph(totalNodes);
    vector<vector<int>> reverseGraph(totalNodes);

    /*
        Read every customer.

        Example:

        + 1 - 2

        means:

        x1 OR !x2
    */

    for (int i = 0; i < n; i++) {

        char sign1, sign2;
        int x, y;

        cin >> sign1 >> x >> sign2 >> y;

        int A = getNode(sign1, x);
        int B = getNode(sign2, y);

        addClause(
            A,
            B,
            graph,
            reverseGraph
        );
    }

    // Find SCCs
    vector<int> component =
        findSCC(graph, reverseGraph);

    // Check for contradiction
    if (!isPossible(m, component)) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    // Build answer
    vector<char> answer =
        getAnswer(m, component);

    for (char c : answer) {
        cout << c << ' ';
    }

    cout << '\n';
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

//  fast_io;
#ifndef ONLINE_JUDGE
  if (fopen("input.txt", "r")) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
  }
#endif

    solve();

    return 0;
}