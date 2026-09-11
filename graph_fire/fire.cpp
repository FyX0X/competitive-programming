#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <array>


constexpr int kMaxInt = std::numeric_limits<int>::max();
constexpr char kJoe = 'J';
constexpr char kWall = '#';
constexpr char kFire = 'F';



struct Vec2 {
    int row;
    int col;

    Vec2 operator+(const Vec2& rhs) {
        return {
            .row = row + rhs.row,
            .col = col + rhs.col
        };
    }


    bool is_out(int width, int height) {
        return row < 0 || col < 0 || row >= height || col >= width;
    }
};

constexpr std::array<Vec2, 4> kDirections = {{ {1, 0}, {0, 1}, {-1, 0}, {0, -1} }};

void print_charmat(const std::vector<std::vector<char>>& matrix) {
    for (const std::vector<char>& row : matrix)
    {
        for (char c : row)
        {
            std::cout << c << ' ';
        }
        std::cout << "\n";
    }
}
void print_intmat(const std::vector<std::vector<int>>& matrix) {
    for (const std::vector<int>& row : matrix)
    {
        for (int c : row)
        {
            if (c == kMaxInt) {
                std::cout << kWall << ' ';
            } else {
            std::cout << c << ' ';
            }
        }
        std::cout << "\n";
    }
}

std::vector<std::vector<char>> create_maze_from_input(int& rows, int& columns, Vec2& joe, std::vector<Vec2>& fires) {

    std::cin >> rows >> columns;

    std::vector<std::vector<char>> maze(rows, std::vector<char>(columns));

    fires.clear();

    for (int row = 0; row < rows; row++)
    {
        std::string line;
        std::cin >> line;
        for (int col = 0; col < columns; col++)
        {
            char c = line[col];
            maze[row][col] = c;

            if (c == kJoe) {
                joe = { row, col };
            }
            if (c == kFire) {
                fires.push_back( { row, col });
            }


        }
        
    }
    

    return maze;
}


int time_joe_escape(const Vec2& joe, const std::vector<std::vector<char>>& maze, const std::vector<Vec2>& fires) {
    /* At each time step :
     *
     * bfs on all fires to get fire_time.
     * 
     * bfs on joe while checking not burned yet. */

    int height = maze.size();
    int width = maze.front().size();
    
    std::vector<std::vector<int>> joe_time(height, std::vector<int>(width, kMaxInt));
    joe_time[joe.row][joe.col] = 0;
    std::vector<std::vector<int>> fire_time(height, std::vector<int>(width, kMaxInt));
    for (const Vec2& fire : fires) {
        fire_time[fire.row][fire.col] = 0;
    }

    std::list<Vec2> queue(fires.begin(), fires.end());

    while(!queue.empty()) {
        Vec2 fire = queue.front();
        queue.pop_front();


        int time = fire_time[fire.row][fire.col];

        // visit neighbours
        for (const Vec2& dir : kDirections) {
            Vec2 next = fire + dir;

            if (next.is_out(width, height) || fire_time[next.row][next.col] != kMaxInt ||
                maze[next.row][next.col] == kWall) {
                continue; // skip if already visited. or out of bound or wall
            }

            fire_time[next.row][next.col] = time + 1;
            queue.push_back(next);
        }
    }

    // std::cout << "maze: \n";
    // print_charmat(maze);
    // std::cout << "fire time:\n";
    // print_intmat(fire_time);

    // fire_time is now completed with correct values
    // do bfs on joe.

    queue.clear(); // not really needed.
    queue.push_back(joe);

    while(!queue.empty()) {
        Vec2 pos = queue.front();
        queue.pop_front();


        int time = joe_time[pos.row][pos.col];
        // std::cout << "current time: " << time << "\n";

        // visit neighbours
        for (const Vec2& dir : kDirections) {
            Vec2 next = pos + dir;

        

            if (next.is_out(width, height)) {

                // std::cout << "found\njoe time\n";
                // print_intmat(joe_time);
                return time + 1;
            }
            
            if (joe_time[next.row][next.col] != kMaxInt || time + 1 >= fire_time[next.row][next.col] ||
                maze[next.row][next.col] == kWall) {
                continue; // skip if already visited. or burned
            }

            joe_time[next.row][next.col] = time + 1;
            queue.push_back(next);
        }
    }

    // std::cout << "joe time\n";
    // print_intmat(joe_time);

    return -1;
}


int main() {


    int rows, columns;
    Vec2 joe;
    std::vector<Vec2> fires;
    std::vector<std::vector<char>> maze = create_maze_from_input(rows, columns, joe, fires);

    
    int time = time_joe_escape(joe, maze, fires);
    if (time > 0) {
        std::cout << time << '\n';
    } else {
        std::cout << "IMPOSSIBLE\n";
    }

    return 0;
}