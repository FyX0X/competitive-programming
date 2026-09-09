#include <iostream>
#include <vector>
#include <list>


std::vector<std::list<int>> create_graph_from_input(int& n, int& m) {

    std::cin >> n >> m;

    std::vector<std::list<int>> graph(n);

    for (size_t i = 0; i < m; i++)
    {
        int u, v;
        std::cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    return graph;
}

std::vector<int> get_components(const std::vector<std::list<int>>& graph, int& component_count) {
    component_count = 0;

    int n = graph.size();
    std::vector<int> components(n, 0);

    for (int bfs_source = 0; bfs_source < n; bfs_source++)
    {
        if (components[bfs_source] != 0) {      // already in a component
            continue;
        }

        // start bfs
        component_count++;
        
        std::list<int> queue{bfs_source};
        components[bfs_source] = component_count;

        while (!queue.empty()) {
            int node = queue.front();
            queue.pop_front();

            for (int next : graph[node]) {

                if (components[next] != 0) {
                    continue;
                }

                components[next] = component_count;
                queue.push_back(next);
            }
        }

    }
    
    return components;

}


int main() {

    int n, m;
    std::vector<std::list<int>> graph = create_graph_from_input(n, m);

    int component_count;
    std::vector<int> components = get_components(graph, component_count);

    int q;
    std::cin >> q;


    std::cout << component_count << '\n';

    for (size_t i = 0; i < q; i++)
    {
        int a, b;
        std::cin >> a >> b;
        if (components[a] == components[b]) {
            std::cout << "yes\n";
        } else {
            std::cout << "no\n";
        }
    }

    return 0;
}