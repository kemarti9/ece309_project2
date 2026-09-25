#pragma once
#include <string>

// Enum declares fixed (3) and named values: system, user, and assistant
enum class Role {
    System,
    User,
    Assistant
};

class Message {
public:
    // Default constructor: sets role to System and content to empty string
    Message();

    // Constructor that initializes the private fields so role_ = role and content_ = content
    Message(Role role, std::string content);

    // Getter - returns the role of a message
    Role role() const noexcept;

    // Getter - returns the content of a message
    const std::string& content() const noexcept;

private:
    Role role_;              // The role of the message
    std::string content_;    // The text content of the message
};
