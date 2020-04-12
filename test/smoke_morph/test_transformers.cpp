//
// Created by alclol on 4/11/20.
//
#include "../catch.hpp"
#include "lattice_core.hpp"
#include "merges/setop_mrg.hpp"
#include "merges/boolean_mrg.hpp"
#include "merges/lww_mrg.hpp"
#include "morphisms/greater_than.hpp"

TEST_CASE("L_MAX Morphisms") {
   Lattice l1(static_cast<int>(10),Max{});
   Lattice<bool, Or> res = greater_than(l1, 12);
   REQUIRE(!res.reveal());
   Lattice l2(static_cast<int>(16),Max{});
   l1 += l2;
   auto res1 = greater_than(l1, 12);
   res = res + res1;
   REQUIRE(res.reveal());
}
