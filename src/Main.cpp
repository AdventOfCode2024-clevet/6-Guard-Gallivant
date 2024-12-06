#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <unistd.h>

enum Orientation
{
    UPWARDS = '^',
    DOWNWARDS = 'v',
    LEFTWARDS = '<',
    RIGHTWARDS = '>'
};

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

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input, line)) {
        lines.push_back(line);
    }

    // We first need to find the guard in the grid (could be any orientation)
    std::tuple<int, int, Orientation> guard;
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == UPWARDS || lines[i][j] == DOWNWARDS || lines[i][j] == LEFTWARDS || lines[i][j] == RIGHTWARDS) {
                guard = std::make_tuple(i, j, static_cast<Orientation>(lines[i][j]));
                break;
            }
        }
    }

    // std::cout << "Guard found at: " << std::get<0>(guard) << ", " << std::get<1>(guard) << std::endl;

    // Now we can start moving the guard, each time the guard lives a cell, the cell becomes an 'X'
    // Each time the guard encounters '#', it rotates 90 degrees to the right
    // We do this until the guard exits the grid
    int i = std::get<0>(guard);
    int j = std::get<1>(guard);
    Orientation orientation = std::get<2>(guard);

    while (i >= 0 && i < lines.size() && j >= 0 && j < lines[i].size()) {
        // std::cout << "Current position: (" << i << ", " << j << "), Orientation: " << orientation << std::endl;

        int di = 0, dj = 0;
        switch (orientation) {
            case UPWARDS: di = -1; break;
            case DOWNWARDS: di = 1; break;
            case LEFTWARDS: dj = -1; break;
            case RIGHTWARDS: dj = 1; break;
        }

        // Vérifiez les limites avant d'accéder à `lines`
        int ni = i + di, nj = j + dj;
        if (ni >= 0 && ni < lines.size() && nj >= 0 && nj < lines[ni].size() && lines[ni][nj] == '#') {
            // std::cout << "Obstacle at (" << ni << ", " << nj << "). Rotating..." << std::endl;
            switch (orientation) {
                case UPWARDS: orientation = RIGHTWARDS; break;
                case RIGHTWARDS: orientation = DOWNWARDS; break;
                case DOWNWARDS: orientation = LEFTWARDS; break;
                case LEFTWARDS: orientation = UPWARDS; break;
            }
            continue;
        }

        // Déplacement
        i = ni;
        j = nj;

        // Assurez-vous que la cellule est dans les limites avant de modifier
        if (i >= 0 && i < lines.size() && j >= 0 && j < lines[i].size()) {
            // std::cout << "Marking (" << i << ", " << j << ") as visited" << std::endl;
            lines[i][j] = 'X';
        }
    }

    // std::cout << "Guard exited at: " << i << ", " << j << std::endl;

    // Result is the number of cells visited
    int result = 0;
    for (const auto& line : lines) {
        for (const auto& cell : line) {
            if (cell == 'X') {
                result++;
            }
        }
    }

    std::cout << "Result: " << result << std::endl;

    return (0);
}
