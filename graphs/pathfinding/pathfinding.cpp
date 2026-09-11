
#include <iostream>

#include <list>
#include <vector>

void create_graph_from_input(int& node_count, int& edge_count, std::vector<std::list<int>>& graph) {
    
    // get dimensions from first line.
    std::cin >> node_count >> edge_count;

    graph.resize(node_count);

    for (size_t i = 0; i < edge_count; i++)
    {
        int u, v; 
        std::cin >> u >> v;
        graph[u].push_back(v);
    }
}

bool does_path_exists(const std::vector<std::list<int>>& graph, int source, int destination) {
    std::list<int> queue;
    std::vector<bool> visited(graph.size());

    queue.push_back(source);
    visited[source] = true;

    if (source == destination) {
        return true;
    }  
    
    while (!queue.empty()) {
        int current_node = queue.back();
        queue.pop_back();
        for (int neighbour : graph[current_node])
        {
            // visit edge (current, neighbour)
            if (visited[neighbour]) {
                continue;
            }

            if (neighbour == destination) {
                return true;
            }

            visited[neighbour] = true;
            queue.push_back(neighbour);

        }
        
    }

    return false;
}

/**
 * REturns a vector containing the nodes from source to destination or empty vector if impossible.
 */
std::list<int> find_path(const std::vector<std::list<int>>& graph, int source, int destination) {
    std::list<int> queue;
    std::vector<bool> visited(graph.size());

    queue.push_back(source);
    visited[source] = true;

    std::vector<int> previous_node(graph.size());

    if (source == destination) {
        return std::list<int>{ source };
    }

    
    bool found = false;
    while (!queue.empty() && !found) {
        int current_node = queue.front();
        queue.pop_front();
        for (int neighbour : graph[current_node])
        {
            // visit edge (current, neighbour)
            if (visited[neighbour]) {
                continue;
            }

            visited[neighbour] = true;
            queue.push_back(neighbour);
            previous_node[neighbour] = current_node;

            if (neighbour == destination) {
                found = true;
                break; // exit for loop just in case for faster exit.
            }
        }
        
    }

    if (!found) {
        return {};
    }

    std::list<int> path{destination};

    int node = destination;
    while (node != source) {
        node = previous_node[node];
        path.push_front(node);
    }

    return path;
}


int main() {



    // graph G is the combination V(G) set of Vertices (Nodes) and E(G) set of Nodes
    // We will represent it with an array of linked list
    // where graph[u] contains v0, ..., vk. And (u, vi) \in E(G)
    
    int node_count, edge_count;
    std::vector<std::list<int>> graph;
    create_graph_from_input(node_count, edge_count, graph);


    int source, destination;
    std::cin >> source >> destination;


    std::list<int> path = find_path(graph, source, destination);

    if (path.empty()) {
        std::cout << "impossible\n";
    } else {
        for (int node : path) {
            std:: cout << node << (node == destination ? '\n' : ' ');
        }
    }

    return 0;
}