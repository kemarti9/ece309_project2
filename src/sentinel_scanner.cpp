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
    std::size_t keep = sentinel_.size() - 1;

    if (combined.size() >= keep) {
        // Emit everything except the last `keep` chars
        safe_output = combined.substr(0, combined.size() - keep);
        pending_ = combined.substr(combined.size() - keep);
    } else {
        // Not enough to emit anything yet
        safe_output.clear();
        pending_ = combined;
    }

    // ⭐ CRITICAL FIX: Clamp pending_ so it NEVER exceeds keep
    if (pending_.size() > keep) {
        pending_ = pending_.substr(pending_.size() - keep);
    }

    return false;
}

std::string SentinelScanner::flush() {
    std::string leftover = pending_;
    pending_.clear();
    return leftover;
}
