#include "core/conversation.h"

// ---------------- Rule of Five ----------------

Conversation::Conversation(const Conversation& other)
    : messages_(other.messages_) {}

Conversation::Conversation(Conversation&& other) noexcept
    : messages_(std::move(other.messages_)) {}

Conversation& Conversation::operator=(const Conversation& other) {
    if (this != &other) {
        messages_ = other.messages_;
    }
    return *this;
}

Conversation& Conversation::operator=(Conversation&& other) noexcept {
    if (this != &other) {
        messages_ = std::move(other.messages_);
    }
    return *this;
}

// ---------------- Add Message Helpers ----------------

void Conversation::addMessage(const Message& msg) {
    messages_.push_back(msg);
}

void Conversation::add_system_message(const std::string& content) {
    messages_.push_back(Message(Role::System, content));
}

void Conversation::add_user_message(const std::string& content) {
    messages_.push_back(Message(Role::User, content));
}

void Conversation::add_assistant_message(const std::string& content) {
    messages_.push_back(Message(Role::Assistant, content));
}

// ---------------- Accessors ----------------

const std::vector<Message>& Conversation::messages() const noexcept {
    return messages_;
}

std::size_t Conversation::size() const noexcept {
    return messages_.size();
}
