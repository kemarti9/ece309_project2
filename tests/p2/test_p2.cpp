// tests/p2/test_p2.cpp
//
// YOUR test suite goes here. At least 12 assert-based test cases — see
// spec §5 for the required categories and the sample test for the
// expected level of rigor.
//
// This file is a stub so the project builds out of the box; replace the
// body of main() with your own tests.

#include "core/conversation.h"
#include "core/message.h"
#include "core/sentinel_scanner.h"
#include "harness/harness.h"
#include "model/replay_client.h"
#include "model/scripted_client.h"
#include <cassert>
#include <iostream>

int main() {

    // Test 1
    {
        Conversation c;                 
        assert(c.size() == 0);

        auto msgs = c.messages();
        assert(msgs.size() == 0);

        for (const auto& m : msgs) {
            assert(false);
        }
    
        std::cout << "Test 1 passed.\n";
    }

    // Test 2
    {
        Conversation c;

        c.add_system_message("sys");
        c.add_user_message("u1");
        c.add_assistant_message("a1");
        c.add_user_message("u2");

        auto msgs = c.messages();

        assert(msgs.size() == 4);
        assert(msgs[0].role() == Role::System);
        assert(msgs[1].role() == Role::User);
        assert(msgs[2].role() == Role::Assistant);
        assert(msgs[3].role() == Role::User);

        std::cout << "Test 2 passed.\n";
    }

    // Test 3
    {
        Conversation c1;
        c1.add_system_message("sys");
        c1.add_user_message("hello");

        Conversation c2 = c1;   // copy

        auto m1 = c1.messages();
        auto m2 = c2.messages();

        assert(m1.size() == m2.size());
        assert(m1[0].content() == m2[0].content());
        assert(m1[1].content() == m2[1].content());

        assert(&m1[0] != &m2[0]);
        assert(&m1[1] != &m2[1]);

        std::cout << "Test 3 passed.\n";
    }

    // Test 4
    {
        Conversation c1;
        c1.add_system_message("sys");
        c1.add_user_message("hello");

        auto before = c1.size();

        Conversation c2 = std::move(c1);

        assert(c1.size() == 0);
        assert(c1.messages().size() == 0);

        assert(c2.size() == before);
        auto msgs = c2.messages();
        assert(msgs[0].content() == "sys");
        assert(msgs[1].content() == "hello");

        std::cout << "Test 4 passed.\n";
    }


    //Test 5
{
    Conversation c;

    // Push enough messages to force multiple reallocations
    const int N = 200;  // definitely triggers vector growth

    for (int i = 0; i < N; i++) {
        c.add_user_message("msg_" + std::to_string(i));
    }

    assert(c.size() == N);

    // Verify all messages survived reallocation correctly
    for (int i = 0; i < N; i++) {
        assert(c.messages().at(i).content() == "msg_" + std::to_string(i));
        assert(c.messages().at(i).role() == Role::User);
    }
    std::cout << "Test 5 passed.\n";
}


    //Test 6: I couldn't get this one to work
{
    std::cout << "Test 6 failed.\n";
}

    //Test 7
{
    const std::string sentinel = "<|end_conversation|>";
    const int L = sentinel.size();

    for (int split = 1; split < L; split++) {
        SentinelScanner scanner(sentinel);

        std::string safe;
        bool found = false;

        // First chunk = first `split` chars of sentinel
        std::string chunk1 = sentinel.substr(0, split);

        // Second chunk = remaining chars
        std::string chunk2 = sentinel.substr(split);

        found = scanner.feed(chunk1, safe);
        assert(found == false);     // cannot detect yet

        found = scanner.feed(chunk2, safe);
        assert(found == true);      // must detect here
    }
    std::cout << "Test 7 passed.\n";
}

    //Test 8
{
    const std::string sentinel = "<|end_conversation|>";
    SentinelScanner scanner(sentinel);

    std::string safe;
    bool found = false;

    // Similar but NOT the sentinel
    found = scanner.feed("<|end_world|>", safe);
    assert(found == false);

    found = scanner.feed("<|end_conversation", safe);  // missing "|>"
    assert(found == false);

    found = scanner.feed("<|end_conversation||", safe); // extra '|'
    assert(found == false);

    found = scanner.feed("<|end_conversation|>oops", safe); // sentinel + extra text
    assert(found == true);  // this one should detect

    std::cout << "Test 8 passed.\n";
}

//Test 9
{
    const std::string sentinel = "<|end_conversation|>";
    const int keep = sentinel.size() - 1;

    SentinelScanner scanner(sentinel);

    std::string safe;
    bool found = false;

    // Feed a large adversarial stream
    std::string big(5000, 'x');

    found = scanner.feed(big, safe);
    assert(found == false);

    // pending_ must never exceed keep
    std::string leftover = scanner.flush();
    assert(leftover.size() <= keep);

    std::cout << "Test 9 passed.\n";
}

//Test 10
{
    const int TurnLimit = 5;

    Conversation convo;
    SentinelScanner scanner("<|end_conversation|>");

    for (int turn = 0; turn < TurnLimit; turn++) {
        convo.add_user_message("u" + std::to_string(turn));
        convo.add_assistant_message("a" + std::to_string(turn));
    }

    assert(convo.size() == TurnLimit * 2);

    std::cout << "Test 10 passed.\n";
}

//Test 11
{
    const std::string sentinel = "<|end_conversation|>";
    SentinelScanner scanner(sentinel);

    std::string safe;
    bool found = false;

    found = scanner.feed("Hello ", safe);
    assert(found == false);

    found = scanner.feed("<|end_", safe);
    assert(found == false);

    found = scanner.feed("conversation|>", safe);
    assert(found == true);   // must detect here
    std::cout << "Test 11 passed.\n";
}

//Test 12: I couldn't get this to work
{
    std::cout << "Test 12 failed.\n";
}

}
