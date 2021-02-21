//
// Created by alclol on 4/11/20.
//
#include "../catch.hpp"
#include "lattice_core.hpp"
#include "merges/setop_mrg.hpp"
#include "merges/boolean_mrg.hpp"
#include "merges/lww_mrg.hpp"
#include "merges/vector_clock_mrg.hpp"
#include "merges/causal_mrg.hpp"
#include "morphisms/transformer.hpp"

TEST_CASE("L_MAX Morphisms functor") {
   Lattice l1(static_cast<int>(10),Max{});
   Lattice goal(static_cast<int>(12),Max{});
   auto gt = CompareTransformer(std::cref(goal), std::cref(l1));
   Lattice<bool, Or> res = gt.greater_than();
   REQUIRE(!res.reveal());
   Lattice l2(static_cast<int>(16),Max{});
   l1 += l2;
   auto res1 = gt.greater_than();
   res += res1;
   REQUIRE(res.reveal());
}

TEST_CASE("+= Morphisms") {
   Lattice l1(static_cast<int>(10),Max{});
   Lattice goal(static_cast<int>(12),Max{});
   auto res = add_delta(l1, static_cast<int>(5));
   REQUIRE(res.reveal() == 15);
   res = deduct_delta(l1, static_cast<int>(5));
   REQUIRE(res.reveal() == 5);
}

TEST_CASE(" set intersect") {
   Lattice ls(std::set<int>{2, 1, 19, 30}, Union{});
   Lattice rs(std::set<int>{2, 3, 4, 19}, Union{});
   auto inter = intersect(std::ref(ls), std::ref(rs));
   REQUIRE(inter.reveal().size() == 2);
   for (auto i : {19,2}) {
      REQUIRE(ls.reveal().count(i));
   }
}


int return_sum(int a, int b, int c) {
    return a + b + c;
}

TEST_CASE("when true/false") {
   Lattice thresholdTrue(true, Or{});
   Lattice OrFalse(false, Or{});
   Lattice thresholdFalse(false, And{});
   Lattice AndTrue(true, And{});
   // when_true(thresholdFalse, static_cast<int>(999), return_sum, 1, 2, 3);
   REQUIRE(when_true(OrFalse, -999, return_sum, 1, 2, 3) == -999);
   REQUIRE(when_true(thresholdTrue, -999, return_sum, 1, 2, 3) == 6);
   REQUIRE(when_false(thresholdFalse, -1, return_sum, 1, 2, 3) == 6);
   REQUIRE(when_false(AndTrue, -1, return_sum, 1, 2, 3) == -1);
}

TEST_CASE("set project") {
   Lattice lset(std::set<int>{2, 1, 3}, Union{});
   std::set<int> result = project(lset, return_sum, 2, 3).reveal();
   REQUIRE(result == std::set<int>{7, 6, 8});
   REQUIRE(lset.reveal() == std::set<int>{2, 1, 3});
}

TEST_CASE("map project") {
    std::map<std::string, int> test_map = { {"xx", 2}, { "yy", 3 } };
    std::map<std::string, int> original(test_map);
    Lattice lmap(test_map, MapUnion{});
    std::map<std::string, int> expected = { {"xx", 7}, {"yy", 8} };
    std::map<std::string, int> result = project(std::ref(lmap), return_sum, 2, 3).reveal();
    REQUIRE(result == expected);
    REQUIRE(lmap.reveal() == original);
}

TEST_CASE("map key_set") {
    Lattice lmap(std::map<std::string, int>{ {"xx", 1}, { "yy", 2 }, { "zz", 3 }}, MapUnion{});
    REQUIRE(key_set(lmap).reveal() == std::set<std::string>{"xx", "yy", "zz"});
}


TEST_CASE("Contains") {
   Lattice ls(std::set<int>{2, 1, 19, 30}, Union{});
   Lattice rs(std::set<int>{2, 3, 4, 19}, Union{});
//   auto res = contains(std::ref(ls), std::ref(rs));
   auto res = contains(std::ref(ls), 19);
   REQUIRE(res.reveal());
}

TEST_CASE("Size") {
   Lattice ls(std::set<int>{2, 1, 19, 30}, Union{});
   Lattice rs(std::set<int>{2, 3, 4, 19}, Union{});
//   auto res = contains(std::ref(ls), std::ref(rs));
   auto res = size(std::ref(ls));
   REQUIRE(res.reveal() == 4);
}

TEST_CASE("At") {
   std::map<std::string, Lattice<int, Max>> leftm = {{"xx", Lattice(2, Max{})},
                                                     {"yy", Lattice(4, Max{})}};
   Lattice lm2(leftm, MapUnion{});
   auto res = At(lm2, static_cast<std::string>("xx"));
   REQUIRE(res.reveal() == 2);

}

TEST_CASE("get_value") {
    VectorClock vc1({ {"x", Lattice(static_cast<unsigned>(2), Max{})},
                   {"y", Lattice(static_cast<unsigned>(4), Max{})} });
    Lattice<std::tuple<VectorClock, Lattice<int, Max>>, CausalMerge> l1(std::make_tuple(vc1, Lattice(10, Max{})), CausalMerge{});
    auto result = get_value(l1);
    REQUIRE(result.reveal() == 10);
    //the return of get_value should make a copy
    result = 100;
    REQUIRE(std::get<1>(l1.reveal()).reveal() == 10);
}
