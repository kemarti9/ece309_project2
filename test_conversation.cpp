#include <iostream>
#include "core/conversation.h"

int main() {
    Conversation convo;

    convo.addMessage(Message(Role::User, "Hello"));
    convo.addMessage(Message(Role::Assistant, "Hi there!"));
    convo.addMessage(Message(Role::User, "How are you?"));

    std::cout << "Conversation size: " << convo.size() << "\n\n";

    for (const auto& msg : convo.messages()) {
        std::cout << static_cast<int>(msg.role()) << ": "
                  << msg.content() << "\n";
    }

    return 0;
}
