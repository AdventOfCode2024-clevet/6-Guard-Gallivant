#pragma once

#ifndef POSITIONCOUNTER_HPP
    #define POSITIONCOUNTER_HPP

    #include <set>
    #include <string>
    #include <tuple>
    #include <vector>

    namespace GuardGallivant
    {
        enum Orientation
        {
            UPWARDS = '^',
            DOWNWARDS = 'v',
            LEFTWARDS = '<',
            RIGHTWARDS = '>'
        };

        class PositionCounter
        {
            public:
                static int countPositionsPartOne(const std::vector<std::string> &grid)
                {
                    auto guard = findGuard(grid);
                    auto markedGrid = markPositions(grid, std::get<0>(guard), std::get<1>(guard), std::get<2>(guard));

                    return (countVisitedCells(markedGrid));
                }

                static int countPositionsPartTwo(const std::vector<std::string> &grid)
                {
                    auto guard = findGuard(grid);

                    return (countValidPositions(grid, std::get<0>(guard), std::get<1>(guard), std::get<2>(guard)));
                }

            private:
                static std::tuple<int, int, Orientation> findGuard(const std::vector<std::string> &grid)
                {
                    for (int i = 0; i < grid.size(); i++)
                    {
                        for (int j = 0; j < grid[i].size(); j++)
                        {
                            if (grid[i][j] == UPWARDS || grid[i][j] == DOWNWARDS || grid[i][j] == LEFTWARDS || grid[i][j] == RIGHTWARDS)
                            {
                                std::tuple<int, int, Orientation> guard = std::make_tuple(i, j, static_cast<Orientation>(grid[i][j]));
                                return (guard);
                            }
                        }
                    }

                    return (std::make_tuple(-1, -1, UPWARDS));
                }

                static std::vector<std::string> markPositions(const std::vector<std::string> &grid, int startI, int startJ, Orientation startOrientation)
                {
                    int i = startI, j = startJ;
                    Orientation orientation = startOrientation;
                    std::vector<std::string> markedGrid = grid;

                    while (i >= 0 && i < markedGrid.size() && j >= 0 && j < markedGrid[i].size()) {
                        int di = 0, dj = 0;

                        switch (orientation)
                        {
                            case UPWARDS: di = -1; break;
                            case DOWNWARDS: di = 1; break;
                            case LEFTWARDS: dj = -1; break;
                            case RIGHTWARDS: dj = 1; break;
                        }

                        int ni = i + di, nj = j + dj;
                        bool notOutOfBounds = ni >= 0 && ni < markedGrid.size() && nj >= 0 && nj < markedGrid[0].size();
                        bool blocked = false;

                        if (notOutOfBounds)
                        {
                            blocked = markedGrid[ni][nj] == '#';
                        }

                        if (notOutOfBounds && blocked)
                        {
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

                        if (i >= 0 && i < markedGrid.size() && j >= 0 && j < markedGrid[i].size())
                        {
                            markedGrid[i][j] = 'X';
                        }
                    }

                    return (markedGrid);
                }

                static int countVisitedCells(const std::vector<std::string> &grid)
                {
                    int visitedCells = 0;

                    for (const auto &line : grid)
                    {
                        for (char cell : line)
                        {
                            if (cell == 'X')
                            {
                                visitedCells++;
                            }
                        }
                    }

                    return (visitedCells);
                }

                static bool simulateGuard(const std::vector<std::string> &grid, int startI, int startJ, Orientation startOrientation)
                {
                    int i = startI, j = startJ;
                    Orientation orientation = startOrientation;
                    std::set<std::tuple<int, int, Orientation>> visited;

                    while (i >= 0 && i < grid.size() && j >= 0 && j < grid[i].size())
                    {
                        if (visited.count({i, j, orientation}))
                        {
                            return (true);
                        }

                        visited.insert({i, j, orientation});

                        int di = 0, dj = 0;
                        switch (orientation)
                        {
                            case UPWARDS: di = -1; break;
                            case DOWNWARDS: di = 1; break;
                            case LEFTWARDS: dj = -1; break;
                            case RIGHTWARDS: dj = 1; break;
                        }

                        int ni = i + di, nj = j + dj;
                        bool notOutOfBounds = ni >= 0 && ni < grid.size() && nj >= 0 && nj < grid[0].size();
                        bool blocked = false;

                        if (notOutOfBounds)
                        {
                            blocked = grid[ni][nj] == '#' || grid[ni][nj] == 'O';
                        }

                        if (notOutOfBounds && blocked)
                        {
                            switch (orientation)
                            {
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

                static int countValidPositions(const std::vector<std::string> &grid, int startI, int startJ, Orientation startOrientation)
                {
                    int validPositions = 0;
                    std::vector<std::string> gridCopy = grid;

                    for (int i = 0; i < gridCopy.size(); i++)
                    {
                        for (int j = 0; j < gridCopy[i].size(); j++)
                        {
                            if (gridCopy[i][j] != '.' || (i == startI && j == startJ))
                            {
                                continue;
                            }

                            gridCopy[i][j] = 'O';

                            if (simulateGuard(gridCopy, startI, startJ, startOrientation))
                            {
                                validPositions++;
                            }

                            gridCopy[i][j] = '.';
                        }
                    }

                    return (validPositions);
                }
        };
    }

#endif /* POSITIONCOUNTER_HPP */
