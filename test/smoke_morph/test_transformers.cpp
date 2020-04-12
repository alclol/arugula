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
   Lattice f(false, Or{});
   Lattice t(true, Or{});
   Lattice l1(std::make_tuple(Lattice(static_cast<int>(10),Max{}), Lattice(10,Max{})), LWWMerge{});
   auto res = greater_than(l1, 12);
   REQUIRE(!res.reveal());
   Lattice l2(std::make_tuple(Lattice(static_cast<int>(16),Max{}), Lattice(5,Max{})), LWWMerge{});
   l1 += l2;
   res += greater_than(l1, 12);
   auto expr = f + t;
}
