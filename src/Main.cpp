#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <tuple>

enum Orientation
{
    UPWARDS = '^',
    DOWNWARDS = 'v',
    LEFTWARDS = '<',
    RIGHTWARDS = '>'
};

bool simulateGuard(std::vector<std::string> grid, int startI, int startJ, Orientation startOrientation) {
    int i = startI, j = startJ;
    Orientation orientation = startOrientation;
    std::set<std::tuple<int, int, Orientation>> visited;

    while (i >= 0 && i < grid.size() && j >= 0 && j < grid[i].size()) {
        if (visited.count({i, j, orientation})) {
            return (true);
        }
        visited.insert({i, j, orientation});

        int di = 0, dj = 0;
        switch (orientation) {
            case UPWARDS: di = -1; break;
            case DOWNWARDS: di = 1; break;
            case LEFTWARDS: dj = -1; break;
            case RIGHTWARDS: dj = 1; break;
        }

        int ni = i + di, nj = j + dj;
        if (ni >= 0 && ni < grid.size() && nj >= 0 && nj < grid[ni].size() && (grid[ni][nj] == '#' || grid[ni][nj] == 'O')) {
            switch (orientation) {
                case UPWARDS: orientation = RIGHTWARDS; break;
                case RIGHTWARDS: orientation = DOWNWARDS; break;
                case DOWNWARDS: orientation = LEFTWARDS; break;
                case LEFTWARDS: orientation = UPWARDS; break;
            }
            continue;
        }

        i = ni;
        j = nj;
    }

    return (false);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input>" << std::endl;
        return (1);
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Error: could not open file " << argv[1] << std::endl;
        return (1);
    }

    std::vector<std::string> grid;
    std::string line;
    while (std::getline(input, line)) {
        grid.push_back(line);
    }

    std::tuple<int, int, Orientation> guard;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == UPWARDS || grid[i][j] == DOWNWARDS || grid[i][j] == LEFTWARDS || grid[i][j] == RIGHTWARDS) {
                guard = {i, j, static_cast<Orientation>(grid[i][j])};
                break;
            }
        }
    }

    int startI = std::get<0>(guard);
    int startJ = std::get<1>(guard);
    Orientation startOrientation = std::get<2>(guard);

    int validPositions = 0;
    int iterations = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] != '.' || (i == startI && j == startJ)) {
                continue;
            }

            grid[i][j] = 'O';
            if (simulateGuard(grid, startI, startJ, startOrientation)) {
                validPositions++;
            }
            grid[i][j] = '.';
        }
    }

    std::cout << "Result: " << validPositions << std::endl;
    return 0;
}
