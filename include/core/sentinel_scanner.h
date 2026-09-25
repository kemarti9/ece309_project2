#pragma once
#include <string>

class SentinelScanner {
public:
    explicit SentinelScanner(std::string sentinel);

    // Feed a chunk of text into the scanner.
    // Returns true if the sentinel was found.
    bool feed(const std::string& chunk, std::string& safe_output);

    // Flush any remaining safe text.
    std::string flush();

private:
    std::string sentinel_;
    std::string pending_;
};
