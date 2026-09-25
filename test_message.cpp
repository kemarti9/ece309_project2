#include <iostream>
#include "core/message.h"

int main() {
    // Test default constructor
    Message m1;
    std::cout << "m1.role = " << static_cast<int>(m1.role()) << "\n";
    std::cout << "m1.content = " << m1.content() << "\n\n";

    // Test parameterized constructor
    Message m2(Role::User, "Hello!");
    std::cout << "m2.role = " << static_cast<int>(m2.role()) << "\n";
    std::cout << "m2.content = " << m2.content() << "\n\n";

    // Test assistant message
    Message m3(Role::Assistant, "Sure, I can help.");
    std::cout << "m3.role = " << static_cast<int>(m3.role()) << "\n";
    std::cout << "m3.content = " << m3.content() << "\n";

    return 0;
}
