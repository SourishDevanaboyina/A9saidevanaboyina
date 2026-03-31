#define CATCH_CONFIG_MAIN
#include <vector>
#include "catch2/catch.hpp"

#include "list/singly_linked.hpp"
#include "list/circularly_linked.hpp"
#include "list/doubly_linked.hpp"

TEST_CASE("SinglyLinkedList push_front and push_back basics", "[singly]") {
    dsac::list::SinglyLinkedList<int> L;

    REQUIRE(L.empty());
    REQUIRE(L.size() == 0);

    L.push_front(2);
    L.push_front(1);
    L.push_back(3);
    L.push_back(4);

    REQUIRE_FALSE(L.empty());
    REQUIRE(L.size() == 4);
    REQUIRE(L.front() == 1);
    REQUIRE(L.back() == 4);

    std::vector<int> vals;
    for (int x : L) {
        vals.push_back(x);
    }

    REQUIRE(vals == std::vector<int>{1, 2, 3, 4});
}

TEST_CASE("SinglyLinkedList concatenate nonempty into nonempty", "[singly]") {
    dsac::list::SinglyLinkedList<int> A;
    dsac::list::SinglyLinkedList<int> B;

    A.push_back(1);
    A.push_back(2);
    B.push_back(3);
    B.push_back(4);

    A.concatenate(B);

    REQUIRE(A.size() == 4);
    REQUIRE(B.size() == 0);
    REQUIRE(B.empty());

    REQUIRE(A.front() == 1);
    REQUIRE(A.back() == 4);

    std::vector<int> vals;
    for (int x : A) {
        vals.push_back(x);
    }

    REQUIRE(vals == std::vector<int>{1, 2, 3, 4});
}

TEST_CASE("SinglyLinkedList concatenate empty destination adopts source", "[singly]") {
    dsac::list::SinglyLinkedList<int> A;
    dsac::list::SinglyLinkedList<int> B;

    B.push_back(7);
    B.push_back(8);
    B.push_back(9);

    A.concatenate(B);

    REQUIRE(A.size() == 3);
    REQUIRE(B.size() == 0);
    REQUIRE(A.front() == 7);
    REQUIRE(A.back() == 9);

    std::vector<int> vals;
    for (int x : A) {
        vals.push_back(x);
    }

    REQUIRE(vals == std::vector<int>{7, 8, 9});
}

TEST_CASE("SinglyLinkedList reverse longer list", "[singly]") {
    dsac::list::SinglyLinkedList<int> L;

    L.push_back(10);
    L.push_back(20);
    L.push_back(30);
    L.push_back(40);

    L.reverse();

    REQUIRE(L.size() == 4);
    REQUIRE(L.front() == 40);
    REQUIRE(L.back() == 10);

    std::vector<int> vals;
    for (int x : L) {
        vals.push_back(x);
    }

    REQUIRE(vals == std::vector<int>{40, 30, 20, 10});
}

TEST_CASE("SinglyLinkedList reverse single node and empty list", "[singly]") {
    dsac::list::SinglyLinkedList<int> A;
    dsac::list::SinglyLinkedList<int> B;

    A.reverse();
    REQUIRE(A.empty());
    REQUIRE(A.size() == 0);

    B.push_back(5);
    B.reverse();

    REQUIRE(B.size() == 1);
    REQUIRE(B.front() == 5);
    REQUIRE(B.back() == 5);

    std::vector<int> vals;
    for (int x : B) {
        vals.push_back(x);
    }

    REQUIRE(vals == std::vector<int>{5});
}

TEST_CASE("CircularlyLinkedList push and rotate basics", "[circular]") {
    dsac::list::CircularlyLinkedList<int> L;

    REQUIRE(L.empty());
    REQUIRE(L.size() == 0);

    L.push_back(1);
    L.push_back(2);
    L.push_back(3);

    REQUIRE_FALSE(L.empty());
    REQUIRE(L.size() == 3);
    REQUIRE(L.front() == 1);
    REQUIRE(L.back() == 3);

    L.rotate();
    REQUIRE(L.front() == 2);
    REQUIRE(L.back() == 1);

    L.rotate();
    REQUIRE(L.front() == 3);
    REQUIRE(L.back() == 2);
}

TEST_CASE("CircularlyLinkedList splitEven basic even list", "[circular]") {
    dsac::list::CircularlyLinkedList<int> L, A, B;

    for (int i = 1; i <= 6; ++i) {
        L.push_back(i);
    }

    L.splitEven(A, B);

    REQUIRE(L.empty());
    REQUIRE(L.size() == 0);

    REQUIRE(A.size() == 3);
    REQUIRE(B.size() == 3);

    std::vector<int> a_vals;
    for (int i = 0; i < A.size(); ++i) {
        a_vals.push_back(A.front());
        A.rotate();
    }

    std::vector<int> b_vals;
    for (int i = 0; i < B.size(); ++i) {
        b_vals.push_back(B.front());
        B.rotate();
    }

    REQUIRE(a_vals == std::vector<int>{1, 2, 3});
    REQUIRE(b_vals == std::vector<int>{4, 5, 6});
}

TEST_CASE("CircularlyLinkedList splitEven two-node list", "[circular]") {
    dsac::list::CircularlyLinkedList<int> L, A, B;

    L.push_back(9);
    L.push_back(10);

    L.splitEven(A, B);

    REQUIRE(L.empty());
    REQUIRE(A.size() == 1);
    REQUIRE(B.size() == 1);
    REQUIRE(A.front() == 9);
    REQUIRE(B.front() == 10);
}

TEST_CASE("CircularlyLinkedList splitEven empty list", "[circular]") {
    dsac::list::CircularlyLinkedList<int> L, A, B;

    L.splitEven(A, B);

    REQUIRE(L.empty());
    REQUIRE(A.empty());
    REQUIRE(B.empty());
}

TEST_CASE("CircularlyLinkedList splitEven odd list throws", "[circular]") {
    dsac::list::CircularlyLinkedList<int> L, A, B;

    L.push_back(1);
    L.push_back(2);
    L.push_back(3);

    REQUIRE_THROWS_AS(L.splitEven(A, B), std::logic_error);
}

TEST_CASE("DoublyLinkedList push_front push_back and iteration", "[doubly]") {
    dsac::list::DoublyLinkedList<int> L;

    REQUIRE(L.empty());
    REQUIRE(L.size() == 0);

    L.push_front(2);
    L.push_front(1);
    L.push_back(3);
    L.push_back(4);

    REQUIRE_FALSE(L.empty());
    REQUIRE(L.size() == 4);
    REQUIRE(L.front() == 1);
    REQUIRE(L.back() == 4);

    std::vector<int> vals;
    for (int x : L) {
        vals.push_back(x);
    }

    REQUIRE(vals == std::vector<int>{1, 2, 3, 4});
}

TEST_CASE("DoublyLinkedList concatenate nonempty into nonempty", "[doubly]") {
    dsac::list::DoublyLinkedList<int> A;
    dsac::list::DoublyLinkedList<int> B;

    A.push_back(1);
    A.push_back(2);
    B.push_back(3);
    B.push_back(4);

    A.concatenate(B);

    REQUIRE(A.size() == 4);
    REQUIRE(B.size() == 0);
    REQUIRE(B.empty());

    REQUIRE(A.front() == 1);
    REQUIRE(A.back() == 4);

    std::vector<int> vals;
    for (int x : A) {
        vals.push_back(x);
    }

    REQUIRE(vals == std::vector<int>{1, 2, 3, 4});
}

TEST_CASE("DoublyLinkedList concatenate into empty destination", "[doubly]") {
    dsac::list::DoublyLinkedList<int> A;
    dsac::list::DoublyLinkedList<int> B;

    B.push_back(7);
    B.push_back(8);
    B.push_back(9);

    A.concatenate(B);

    REQUIRE(A.size() == 3);
    REQUIRE(B.size() == 0);
    REQUIRE(A.front() == 7);
    REQUIRE(A.back() == 9);

    std::vector<int> vals;
    for (int x : A) {
        vals.push_back(x);
    }

    REQUIRE(vals == std::vector<int>{7, 8, 9});
}

TEST_CASE("DoublyLinkedList concatenate with empty source does nothing", "[doubly]") {
    dsac::list::DoublyLinkedList<int> A;
    dsac::list::DoublyLinkedList<int> B;

    A.push_back(11);
    A.push_back(12);

    A.concatenate(B);

    REQUIRE(A.size() == 2);
    REQUIRE(B.size() == 0);
    REQUIRE(A.front() == 11);
    REQUIRE(A.back() == 12);

    std::vector<int> vals;
    for (int x : A) {
        vals.push_back(x);
    }

    REQUIRE(vals == std::vector<int>{11, 12});
}