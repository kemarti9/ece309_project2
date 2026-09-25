#include "core/conversation.h"

void Conversation::addMessage(const Message& msg) {
    messages_.push_back(msg); //adds the message to the end of vector<Message>
}

//makes conversation history readable
const std::vector<Message>& Conversation::messages() const noexcept {
    return messages_;
}

std::size_t Conversation::size() const noexcept {
    return messages_.size(); //returns number of messages
}
