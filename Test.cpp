/*
 * Test.cpp
 *
 *  Created on: 14 April 2020
 *      Author: oriel malihi
 */
#include "doctest.h"
#include <string>
#include "FamilyTree.hpp"
using namespace std;
using namespace family;

static Tree t("a");

TEST_CASE("addFather/addfMother method")
{
    CHECK_NOTHROW(t.addFather("a", "b"));
    CHECK_NOTHROW(t.addMother("a", "c"));
    CHECK_NOTHROW(t.addFather("b", "d"));
    CHECK_NOTHROW(t.addMother("b", "e"));
    CHECK_THROWS(t.addFather("b", "f"));
    CHECK_THROWS(t.addMother("b", "g"));
    CHECK_NOTHROW(t.addFather("d", "h"));
    CHECK_NOTHROW(t.addMother("d", "i"));
    CHECK_NOTHROW(t.addFather("h", "j"));
    CHECK_NOTHROW(t.addMother("h", "k"));
    CHECK_NOTHROW(t.addFather("c", "l"));
    CHECK_NOTHROW(t.addMother("c", "m"));
    CHECK_THROWS(t.addFather("c", "n"));
    CHECK_NOTHROW(t.addMother("l", "o"));
    CHECK_NOTHROW(t.addFather("o", "p"));
    CHECK_NOTHROW(t.addMother("o", "q"));
    CHECK_NOTHROW(t.addFather("e", "r"));
    CHECK_NOTHROW(t.addMother("e", "s"));
    CHECK_NOTHROW(t.addFather("q", "t"));
    CHECK_NOTHROW(t.addMother("q", "u"));
}

TEST_CASE("display method")
{
    CHECK_NOTHROW(t.display());
}

TEST_CASE("realation method")
{
    CHECK(t.relation("a") == "me");
    CHECK(t.relation("b") == "father");
    CHECK(t.relation("c") == "mother");
    CHECK(t.relation("m") == "grandmother");
    CHECK(t.relation("e") == "grandmother");
    CHECK(t.relation("l") == "grandfather");
    CHECK(t.relation("d") == "grandfather");
    CHECK(t.relation("f") == "unrelated");
    CHECK(t.relation("g") == "unrelated");
    CHECK(t.relation("n") == "unrelated");
    CHECK(t.relation("h") == "great-grandfather");
    CHECK(t.relation("r") == "great-grandfather");
    CHECK(t.relation("i") == "great-grandmother");
    CHECK(t.relation("s") == "great-grandmother");
    CHECK(t.relation("o") == "great-grandmother");
    CHECK(t.relation("j") == "great-great-grandfather");
    CHECK(t.relation("p") == "great-great-grandfather");
    CHECK(t.relation("k") == "great-great-grandmother");
    CHECK(t.relation("q") == "great-great-grandmother");
    CHECK(t.relation("t") == "great-great-great-grandfather");
    CHECK(t.relation("u") == "great-great-great-grandmother");
    CHECK(t.relation("a ") == "unrelated");
    CHECK(t.relation(" b") == "unrelated");
    CHECK(t.relation(" ") == "unrelated");
    CHECK(t.relation("v") == "unrelated");
    CHECK(t.relation("w") == "unrelated");
    CHECK(t.relation("x") == "unrelated");
    CHECK(t.relation("y") == "unrelated");
    CHECK(t.relation("z") == "unrelated");
    CHECK(t.relation("aa") == "unrelated");
}

TEST_CASE("find method")
{
    CHECK(t.find("me") == "a");
    CHECK(t.find("father") == "b");
    CHECK(t.find("mother") == "c");
    CHECK(string("dl").find(t.find("grandfather")) != string::npos);
    CHECK(string("em").find(t.find("grandmother")) != string::npos);
    CHECK(string("hr").find(t.find("great-grandfather")) != string::npos);
    CHECK(string("iso").find(t.find("great-grandmother")) != string::npos);
    CHECK(string("jp").find(t.find("great-great-grandfather")) != string::npos);
    CHECK(string("kq").find(t.find("great-great-grandmother")) != string::npos);
    CHECK(string("t").find(t.find("great-great-great-grandfather")) != string::npos);
    CHECK(string("u").find(t.find("great-great-great-grandmother")) != string::npos);
}

TEST_CASE("remove method")
{
    CHECK_NOTHROW(t.addFather("t", "i"));
    CHECK_NOTHROW(t.addMother("t", "i"));
    CHECK_NOTHROW(t.remove("i"));
    CHECK(t.relation("i") == "unrelated");
    CHECK_NOTHROW(t.addMother("d", "i"));
    CHECK_NOTHROW(t.remove("d"));
    CHECK(t.relation("d") == "unrelated");
    CHECK(t.relation("i") == "unrelated");
    CHECK(t.relation("h") == "unrelated");
    CHECK(t.relation("k") == "unrelated");
    CHECK(t.relation("j") == "unrelated");
    CHECK_NOTHROW(t.remove("b"));
    CHECK(t.relation("b") == "unrelated");
    CHECK(t.relation("e") == "unrelated");
    CHECK(t.relation("r") == "unrelated");
    CHECK(t.relation("s") == "unrelated");
    CHECK_NOTHROW(t.remove("q"));
    CHECK(t.relation("q") == "unrelated");
    CHECK(t.relation("t") == "unrelated");
    CHECK(t.relation("u") == "unrelated");
    CHECK_NOTHROW(t.remove("o"));
    CHECK(t.relation("o") == "unrelated");
    CHECK(t.relation("p") == "unrelated");
    CHECK_NOTHROW(t.remove("c"));
    CHECK(t.relation("c") == "unrelated");
    CHECK(t.relation("l") == "unrelated");
    CHECK(t.relation("m") == "unrelated");
    CHECK_THROWS(t.remove("a"));
}

TEST_CASE("more tests..")
{
    CHECK_THROWS(t.addFather("v", "b"));
    CHECK_THROWS(t.addFather("w", "x"));
    CHECK_THROWS(t.addFather("i", "k"));
    CHECK_THROWS(t.addFather("b", "d"));
    CHECK_THROWS(t.addFather("k", "z"));
    CHECK_THROWS_MESSAGE(t.find("grandfather"), "ERR was unable to find this tharget");
    CHECK_THROWS_MESSAGE(t.find("father"), "ERR was unable to find this tharget");
    CHECK_THROWS_MESSAGE(t.find("great-grandfather"), "ERR was unable to find this tharget");
    CHECK_THROWS_MESSAGE(t.find("graandfather"), "The tree cannot handle the 'graandfather' relation");
    CHECK_THROWS_MESSAGE(t.find("fother"), "The tree cannot handle the 'fother' relation");
    CHECK_THROWS_MESSAGE(t.find("great--grandfather"), "The tree cannot handle the 'great--grandfather' relation");
    CHECK_THROWS_MESSAGE(t.find("grand father"), "The tree cannot handle the 'grand father' relation");
    CHECK_THROWS_MESSAGE(t.find("dad"), "The tree cannot handle the 'dad' relation");
    CHECK_THROWS_MESSAGE(t.find("Great-grandfather"), "The tree cannot handle the 'Great-grandfather' relation");
}
