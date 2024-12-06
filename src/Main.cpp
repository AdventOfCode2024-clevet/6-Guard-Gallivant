#include <iostream>

#include "ArgumentParser.hpp"
#include "FileReader.hpp"
#include "PositionCounter.hpp"

int main(int argc, char* argv[]) {
    try {
        GuardGallivant::ArgumentParser parser(argc, argv);

        GuardGallivant::FileReader reader(parser.getInputFile());
        auto lines = reader.readLines();

        int result = 0;
        switch (parser.getPart()) {
            case 1:
                result = GuardGallivant::PositionCounter::countPositionsPartOne(lines);
                std::cout << "Result (part 1): " << result << std::endl;
                break;
            case 2:
                result = GuardGallivant::PositionCounter::countPositionsPartTwo(lines);
                std::cout << "Result (part 2): " << result << std::endl;
                break;
            default:
                throw std::invalid_argument("Error: part must be 1 or 2");
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }

    return (0);
}
