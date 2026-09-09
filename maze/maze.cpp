

#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <sstream>


constexpr char kSource = 'S';
constexpr char kTarget = 'T';
constexpr char kWall = '#';
constexpr char kPath = '.';


struct Vec2 {
    int row;
    int col;

    Vec2 operator+(const Vec2& rhs) const {
        return { .row = row + rhs.row, .col = col + rhs.col };
    }

    std::string to_string() const {
        std::stringstream ss;
        ss << row << ' ' << col;
        return ss.str();
    }
};

constexpr std::array<Vec2, 4> kDirections = {{ {1, 0}, {0, 1}, {-1, 0}, {0, -1} }};

std::vector<std::vector<char>> create_maze_from_input(int& rows, int& columns, Vec2& source, Vec2& target) {

    std::cin >> rows >> columns;
    std::vector<std::vector<char>> maze(rows, std::vector<char>(columns));

    for (int row = 0; row < rows; row++)
    {
        std::string line;
        std::cin >> line;
        for (int col = 0; col < columns; col++)
        {
            char c = line[col];
            maze[row][col] = c;
            if (c == kSource) {
                source = { .row = row, .col = col};
            }
            if (c == kTarget) {
                target = { .row = row, .col = col};
            }
        }
    }
    return maze;
}




std::list<Vec2> find_path(const std::vector<std::vector<char>>& maze, Vec2 source, Vec2 target) {
    int rows = maze.size();
    int columns = maze.front().size();

    std::list<Vec2> queue{source};

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(columns));
    std::vector<std::vector<Vec2>> parent(rows, std::vector<Vec2>(columns));

    visited[source.row][source.col] = true;

    bool found = false;
    while (!queue.empty() && !found) {

        // carefull here its front not back since queue is FIFO
        Vec2 node = queue.front();
        queue.pop_front();

        // std::cout << "visiting: " << node.to_string() << "\n";

        for (Vec2 dir : kDirections)
        {
            Vec2 next = node + dir;

            char next_cell = maze[next.row][next.col];

            if (next_cell == kWall || visited[next.row][next.col]) {
                continue;
            }

            queue.push_back(next);
            visited[next.row][next.col] = true;
            parent[next.row][next.col] = node;

            if (next_cell == kTarget) {
                found = true;
                break;
            }
        }
    }

    if (!found) {
        return {};
    }

    std::list<Vec2> path{target};
    Vec2 node = target;
    char cell = maze[node.row][node.col];

    while (cell != kSource) {
        node = parent[node.row][node.col];
        path.push_front(node);
        cell = maze[node.row][node.col];
    }

    return path;
}


int main() {

    int rows, columns;
    Vec2 source, target;

    std::vector<std::vector<char>> maze = create_maze_from_input(rows, columns, source, target);



    std::list<Vec2> path = find_path(maze, source, target);

    for (Vec2 node : path)
    {
        std::cout << node.row << ' ' << node.col << '\n';
    }
    

    return 0;
}