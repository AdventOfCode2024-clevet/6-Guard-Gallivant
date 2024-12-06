#include "FileReader.hpp"

GuardGallivant::FileReader::FileReader(const std::string &fileName)
{
    input.open(fileName);
    if (!input.is_open())
    {
        throw std::runtime_error("Error: could not open file " + fileName);
    }
}

std::vector<std::string> GuardGallivant::FileReader::readLines()
{
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input, line))
    {
        lines.push_back(line);
    }
    return (lines);
}
