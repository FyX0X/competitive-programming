#include <vector>
#include <queue>
#include <iostream>
#include <limits>
#include <array>

struct Point
{
	int r;
	int c;
};

struct Grid
{
	std::vector<std::vector<char>> cells;
	int rows;
	int cols;
	Point start;
	std::vector<Point> fire_starts;
	std::vector<std::vector<int>> fire_time;


	Grid(int rows, int cols) : rows(rows), cols(cols)
	{
		cells.resize(rows, std::vector<char>(cols, '.'));
		fire_time.resize(rows, std::vector<int>(cols, std::numeric_limits<int>::max()));
	}
};

Grid getGraphFromInput()
{
	int rows, cols;
	std::cin >> rows >> cols;
	Grid grid(rows, cols);


	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			char c;
			std::cin >> c;
			grid.cells[i][j] = c;

			if (c == 'J') 
			{
				grid.start = { i, j };
			}
			else if (c == 'F') 
			{
				grid.fire_starts.push_back({ i, j });
				grid.fire_time[i][j] = 0;
			}
		}
	}
	return grid;
}



int escapeBFS(const Grid& grid, const Point& source)
{
	std::queue<Point> q;
	q.push(source);

	std::vector<std::vector<int>> dist(grid.rows, std::vector<int>(grid.cols, std::numeric_limits<int>::max()));
	dist[source.r][source.c] = 0;

	static constexpr std::array<Point, 4> dir = { {{-1, 0}, {1, 0}, {0, -1}, {0, 1}} };

	while (!q.empty())
	{
		Point u = q.front();
		q.pop();

		for (const Point& d : dir) {
			Point v = { u.r + d.r, u.c + d.c };

			if (v.r < 0 || v.r >= grid.rows || v.c < 0 || v.c >= grid.cols)
			{
				// found an exit
				return dist[u.r][u.c] + 1;
			}

			if (grid.cells[v.r][v.c] == '#')		// wall
			{
				continue;
			}

			int u_cell_dist = dist[u.r][u.c];

			if (dist[v.r][v.c] > u_cell_dist + 1)
			{
				// check for fire timing
				if (grid.fire_time[v.r][v.c] <= u_cell_dist + 1)
				{
					continue;
				}

				dist[v.r][v.c] = u_cell_dist + 1;
				q.push(v);
			}
		}
	}


	return -1;	// no exit found



}



void propagateFire(Grid& grid)
{

	std::queue<Point> q;
	std::vector<std::vector<int>> dist(grid.rows, std::vector<int>(grid.cols, std::numeric_limits<int>::max()));

	for (const Point& fire_start : grid.fire_starts)
	{

		q.push(fire_start);
		dist[fire_start.r][fire_start.c] = 0;
	}


	static constexpr std::array<Point, 4> dir = { {{-1, 0}, {1, 0}, {0, -1}, {0, 1}} };

	while (!q.empty())
	{
		Point u = q.front();
		q.pop();

		for (const Point& d : dir) {
			Point v = { u.r + d.r, u.c + d.c };

			if (v.r < 0 || v.r >= grid.rows || v.c < 0 || v.c >= grid.cols)
			{
				continue;
			}

			if (grid.cells[v.r][v.c] == '#')		// wall
			{
				continue;
			}

			if (grid.fire_time[v.r][v.c] > grid.fire_time[u.r][u.c] + 1)
			{
				grid.fire_time[v.r][v.c] = grid.fire_time[u.r][u.c] + 1;
				q.push(v);
			}
		}
	}


	

}





int main()
{
	Grid grid = getGraphFromInput();
	propagateFire(grid);

	int dist = escapeBFS(grid, grid.start);

	if (dist == -1)
	{
		std::cout << "IMPOSSIBLE\n";
	}
	else
	{
		std::cout << dist << "\n";
	}


	return 0;
}