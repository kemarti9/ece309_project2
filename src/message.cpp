#include "core/message.h"

// Default constructor
Message::Message()
    : role_(Role::System), content_("") {}

// Constructor with role + content
Message::Message(Role role, std::string content)
    : role_(role), content_(std::move(content)) {}

// Getter for role
Role Message::role() const noexcept {
    return role_;
}

// Getter for content
const std::string& Message::content() const noexcept {
    return content_;
}
