#include <iostream>
#include <vector>



std::vector<std::vector<bool>> create_grid_from_input(int& r, int& c, int& brace_count) {
    std::cin >> r >> c;
    std::vector<std::vector<bool>> grid(r, std::vector<bool>(c, false));

    brace_count = 0;
    for (size_t i = 0; i < r; i++)
    {
        std::string line;
        std::cin >> line;
        for (size_t j = 0; j < c; j++)
        {
            int b = (line[j] == 1) ? 1 : 0;
            grid[i][j] = b;
            brace_count += b;
        }
    }
    return grid;
}

std::vector<bool> find_filled_cols(const std::vector<std::vector<bool>>& grid) {
    int rows = grid.size();
    int cols = grid.front().size();

    std::vector<bool> filled_cols(cols, false);
    for (int c = 0; c < cols; c++)
    {
        for (int r = 0; r < rows; r++)
        {
            if (grid[r][c]) {
                filled_cols[c] = true;
                break;
            }
        }
    }
    return filled_cols;   
}

std::vector<bool> find_filled_rows(const std::vector<std::vector<bool>>& grid) {
    int rows = grid.size();
    int cols = grid.front().size();

    std::vector<bool> filled_rows(rows, false);
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (grid[r][c]) {
                filled_rows[r] = true;
                break;
            }
        }
    }
    return filled_rows;    
}

int main() {

    int r, c, brace_count;
    std::vector<std::vector<bool>> grid = create_grid_from_input(r, c, brace_count);


    int min_total_brace_count = r + c - 1; // calculated from degrees of freedom.

    // find redondant constraints count ?

    int brace_to_add = 0; /* compute */

    std::vector<bool> filled_rows = find_filled_rows(grid);
    std::vector<bool> filled_cols = find_filled_cols(grid);

    int empty_rows = r;
    int empty_cols = c;
    for (bool filled : filled_rows)
    {
        empty_rows -= filled;
    }
    for (bool filled : filled_cols)
    {
        empty_cols -= filled;
    }

    if (empty_rows == 0 || empty_cols == 0) {
        brace_to_add = empty_rows + empty_cols;
    } else {
        brace_to_add = empty_rows + empty_cols - 1;    
    }
    
    

    std::cout << brace_to_add << '\n';

    return 0;
}