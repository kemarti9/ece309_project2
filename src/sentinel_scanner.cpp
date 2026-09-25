#include "core/sentinel_scanner.h"

SentinelScanner::SentinelScanner(std::string sentinel)
    : sentinel_(std::move(sentinel)) {}

bool SentinelScanner::feed(const std::string& chunk, std::string& safe_output) {
    // Combine pending + new chunk
    std::string combined = pending_ + chunk;

    // Look for sentinel
    std::size_t pos = combined.find(sentinel_);
    if (pos != std::string::npos) {
        // Sentinel found
        safe_output = combined.substr(0, pos);
        pending_.clear();
        return true;
    }

    // No sentinel found
    // We must keep enough trailing characters to detect partial matches later.
    std::size_t keep = sentinel_.size() - 1;
    if (combined.size() >= keep) {
        safe_output = combined.substr(0, combined.size() - keep);
        pending_ = combined.substr(combined.size() - keep);
    } else {
        // Entire combined is too small; keep all in pending
        safe_output.clear();
        pending_ = combined;
    }

    return false;
}

std::string SentinelScanner::flush() {
    std::string leftover = pending_;
    pending_.clear();
    return leftover;
}
