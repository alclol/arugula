//
// Created by alclol on 4/11/20.
//
#include "../catch.hpp"
#include "lattice_core.hpp"
#include "merges/setop_mrg.hpp"
#include "merges/boolean_mrg.hpp"
#include "merges/lww_mrg.hpp"
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
