#pragma once
#include <vector>
#include "core/message.h"

class Conversation {
public:
    //Default constructor
    Conversation() = default;

    //Declares a function that doesnt return anything and adds a message to Conversation
    void addMessage(const Message& msg); //Message& means you can pass the message by reference (no copying) and won't modify the copy

    //Getter: returns all messages (read-only)
    const std::vector<Message>& messages() const noexcept;

    //Convenience: number of messages
    std::size_t size() const noexcept;

private:
    //for storage of conversation
    std::vector<Message> messages_;
};
