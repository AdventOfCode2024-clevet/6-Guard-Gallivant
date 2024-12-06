#pragma once

#ifndef ARGUMENTPARSER_HPP
    #define ARGUMENTPARSER_HPP

    #include <string>

    namespace GuardGallivant
    {
        class ArgumentParser
        {
            public:
                ArgumentParser(int argc, char* argv[]);
                ~ArgumentParser() = default;

                const std::string &getInputFile() const;
                int getPart() const;

            private:
                std::string inputFile;
                int part;
        };
    }

#endif /* ARGUMENTPARSER_HPP */
