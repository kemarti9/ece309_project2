#pragma once
#include <string>
#include <vector>
#include "core/message.h"

class Conversation {
public:
    Conversation() = default;
    Conversation(const Conversation& other);
    Conversation(Conversation&& other) noexcept;
    Conversation& operator=(const Conversation& other);
    Conversation& operator=(Conversation&& other) noexcept;

    void addMessage(const Message& msg);
    void add_system_message(const std::string& content);
    void add_user_message(const std::string& content);
    void add_assistant_message(const std::string& content);

    // harness API
    void append(const Message& msg);

    // main.cpp expects pointer iteration
    const Message* begin() const;
    const Message* end() const;

    const std::vector<Message>& messages() const noexcept;
    std::size_t size() const noexcept;

private:
    std::vector<Message> messages_;
};
