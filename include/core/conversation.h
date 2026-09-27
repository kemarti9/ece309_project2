#pragma once
#include <vector>
#include <string>
#include "core/message.h"

class Conversation {
public:
    // ---------------- Constructors / Rule of Five ----------------
    Conversation() = default;                                // default
    Conversation(const Conversation& other);                 // copy ctor
    Conversation(Conversation&& other) noexcept;             // move ctor
    Conversation& operator=(const Conversation& other);      // copy assign
    Conversation& operator=(Conversation&& other) noexcept;  // move assign
    ~Conversation() = default;                               // destructor

    // ---------------- Message Adding Helpers ----------------
    void addMessage(const Message& msg);

    void add_system_message(const std::string& content);
    void add_user_message(const std::string& content);
    void add_assistant_message(const std::string& content);

    // ---------------- Accessors ----------------
    const std::vector<Message>& messages() const noexcept;
    std::size_t size() const noexcept;

private:
    std::vector<Message> messages_;
};
