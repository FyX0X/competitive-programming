#include <iostream>

#include <vector>
#include <list>
#include <limits>


static constexpr int kMaxInt = std::numeric_limits<int>::max();

std::vector<std::list<int>> create_double_graph_from_input(int& node_count, int& edge_count) {
    std::cin >> node_count >> edge_count;

    std::vector<std::list<int>> graph(node_count);

    for (size_t i = 0; i < edge_count; i++)
    {
        int u, v;
        std::cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    return graph;
}

/** returns the distance of each node to source */
std::vector<int> breadth_first_search(const std::vector<std::list<int>>& graph, int source) {

    std::list<int> queue{source};

    std::vector<int> distance(graph.size(), kMaxInt);
    distance[source] = 0;

    while (!queue.empty()) {
        
        int node = queue.front();
        queue.pop_front();

        int dist = distance[node];

        for (int neighbour : graph[node])
        {
            // bfs not dijkstra so if distance finite => already optimal
            if (distance[neighbour] < kMaxInt) {
                continue;
            }

            distance[neighbour] = dist + 1;
            queue.push_back(neighbour);
        }
    }

    return distance;
}

int main() {

    int node_count, edge_count;
    std::vector<std::list<int>> graph = create_double_graph_from_input(node_count, edge_count);

    std::vector<int> distances_from_origin = breadth_first_search(graph, 0);

    int max = 0;

    for (int dist : distances_from_origin) 
    {
        max = (max < dist) ? dist : max;
    }
    
    std::cout << max << '\n';

    return 0;
}