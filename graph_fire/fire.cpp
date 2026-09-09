#include <iostream>
#include <vector>
#include <list>


constexpr char kJoe = 'J';


struct Vec2 {
    int row;
    int col;

    Vec2 operator+(const Vec2& rhs) {
        return {
            .row = row + rhs.row,
            .col = col + rhs.col
        };
    }
};


std::vector<std::vector<char>> create_maze_from_input(int& rows, int& columns, Vec2& joe) {

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

            if (c == kJoe) {
                joe = { row, col };
            }
        }
        
    }
    

    return maze;
}


int main() {


    int rows, columns;
    Vec2 joe;
    std::vector<std::vector<char>> maze = create_maze_from_input(rows, columns, joe);



    return 0;
}