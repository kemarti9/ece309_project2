#pragma once
#include <string>
#include <string_view>

class SentinelScanner {
public:
    struct ScanResult {
        bool sentinel_found;
        std::string safe_text;
    };

    explicit SentinelScanner(std::string sentinel);

    // Test API
    bool feed(const std::string& chunk, std::string& safe_output);

    // Harness API
    ScanResult feed(std::string_view chunk);

    ScanResult flush();

private:
    std::string sentinel_;
    std::string pending_;
};