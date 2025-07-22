#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

struct Point {
    int r;
    int c;

    Point(int rv, int cv) : r(rv), c(cv) {}

    // For set lookup
    bool operator<(const Point& other) const {
        return (r < other.r) || (r == other.r && c < other.c);
    }

    bool operator==(const Point& other) const {
        return r == other.r && c == other.c;
    }
};

vector<Point> findNeighbours(Point p, const vector<vector<char>>& g) {
    vector<Point> result;
    int row = g.size();
    int col = g[0].size();

    if (p.r + 1 < row && g[p.r + 1][p.c] != '#')
        result.emplace_back(p.r + 1, p.c);
    if (p.r - 1 >= 0 && g[p.r - 1][p.c] != '#')
        result.emplace_back(p.r - 1, p.c);
    if (p.c + 1 < col && g[p.r][p.c + 1] != '#')
        result.emplace_back(p.r, p.c + 1);
    if (p.c - 1 >= 0 && g[p.r][p.c - 1] != '#')
        result.emplace_back(p.r, p.c - 1);

    return result;
}

bool dfs(vector<vector<char>>& g, Point start, Point end) {
    if (g.empty() || g[0].empty()) {
        cout << "Grid is empty or invalid.\n";
        return false;
    }

    if (g[start.r][start.c] == '#' || g[end.r][end.c] == '#') {
        cout << "Start or end point is blocked.\n";
        return false;
    }

    if (start == end) {
        cout << "Start and end points are the same.\n";
        return true;
    }

    set<Point> visited;
    stack<Point> explore;

    explore.push(start);
    visited.insert(start);

    while (!explore.empty()) {
        Point head = explore.top();
        explore.pop();

        if (head == end)
            return true;

        vector<Point> neighbours = findNeighbours(head, g);
        for (auto p : neighbours) {
            if (visited.find(p) == visited.end()) {
                explore.push(p);
                visited.insert(p);
            }
        }
    }

    return false;
}

int main() {
    // Sample grid
    vector<vector<char>> grid = {
        {'.', '.', '.', '#', '.'},
        {'#', '#', '.', '#', '.'},
        {'.', '.', '.', '.', '.'},
        {'#', '.', '#', '#', '.'},
        {'.', '.', '.', '.', '.'}
    };

    // Start and End points
    Point start(0, 0); // Top-left
    Point end(4, 4);   // Bottom-right

    bool pathExists = dfs(grid, start, end);

    if (pathExists)
        cout << "✅ Path found from start to end.\n";
    else
        cout << "❌ No path found.\n";

    return 0;
}

