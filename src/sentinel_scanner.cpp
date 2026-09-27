#include "core/sentinel_scanner.h"

SentinelScanner::SentinelScanner(std::string sentinel)
    : sentinel_(std::move(sentinel)) {}

bool SentinelScanner::feed(const std::string& chunk, std::string& safe_output) {
    std::string combined = pending_ + chunk;

    std::size_t pos = combined.find(sentinel_);
    if (pos != std::string::npos) {
        safe_output = combined.substr(0, pos);
        pending_.clear();
        return true;
    }

    std::size_t keep = sentinel_.size() - 1;

    if (combined.size() >= keep) {
        safe_output = combined.substr(0, combined.size() - keep);
        pending_ = combined.substr(combined.size() - keep);
    } else {
        safe_output.clear();
        pending_ = combined;
    }

    if (pending_.size() > keep) {
        pending_ = pending_.substr(pending_.size() - keep);
    }

    return false;
}

SentinelScanner::ScanResult SentinelScanner::feed(std::string_view chunk) {
    std::string safe;
    bool found = feed(std::string(chunk), safe);
    return {found, safe};
}

SentinelScanner::ScanResult SentinelScanner::flush() {
    std::string leftover = pending_;
    pending_.clear();
    return {false, leftover};
}