# Design Log — Project 2

## Growth factor and amortized cost
The Conversation class stores its message in a vector std::vector<Message> which provides amortized O(1) insertion.

## Rule of Five evidence
The Conversation class owns the vector std::vector<Message> and implements the rule of five for safe copying and moving. 

Copy constructor
Conversation::Conversation(const Conversation& other)
    : messages_(other.messages_) {}

Move contructor
Conversation::Conversation(Conversation&& other) noexcept
    : messages_(std::move(other.messages_)) {}

Copy assignment operator
Conversation& Conversation::operator=(const Conversation& other) {
    if (this != &other) {
        messages_ = other.messages_;
    }
    return *this;
}

Move assignment operator
Conversation& Conversation::operator=(Conversation&& other) noexcept {
    if (this != &other) {
        messages_ = std::move(other.messages_);
    }
    return *this;
}

Destructor operator
Not explicity written because std::vector manages that automatically

## Sentinel scanner: bounded pending_ proof
Sentinel scanner detects <|end_conversation|>, even when it is split between chunks, and ends the conversation without printing the sentinel. 
Pending_ stores the last sentinel.size()-1 of the combined stream across chunks, allowing the new chunk with the latter part of the sentinel to be appended to previous one.

code snippet
if (pending_.size() > keep) { // keep is the size of the sentinel - 1
    pending_ = pending_.substr(pending_.size() - keep);
}

This bounds pending_  to less than or equal to the sentinel length minus 1. The reasoning is that, if pending_ is the whole length of the sentinel (20 characters), then the sentinel is not actually split and pending_ is not necessary. 

## What I would change differently
I developed the code to test using MSVC. Later on, I built it with cmake and made it compile with AddressSanitizer. In the future, I will implement the full API from the beginning to avoid integration issues.