#pragma once
#include <string>

enum class Role {
    System,
    User,
    Assistant
};

class Message {
public:
    Message(Role r, std::string c)
        : role_(r), content_(std::move(c)) {}

    Role role() const { return role_; }
    const std::string& content() const { return content_; }

private:
    Role role_;
    std::string content_;
};
