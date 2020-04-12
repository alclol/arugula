//
// Created by alclol on 4/12/20.
//
#include "lattice_core.hpp"
#include "merges/boolean_mrg.hpp"

#ifndef MANGO_GREATER_THAN_H
#define MANGO_GREATER_THAN_H

template <class T>
struct GreaterThanStruct {
private:
   T threshold;

public:
   GreaterThanStruct(T _threshold) : threshold(_threshold) {};

   template <class Func>
   typename std::enable_if_t<std::is_same<Func, Max>::value, Lattice<bool, Or>>
   operator()(Lattice<T, Func> target) {
      return Lattice(target.reveal()>this->threshold, Or{});
   }
};

template <class Func, class T>
typename std::enable_if_t<std::is_same<Func, Max>::value, Lattice<bool, Or>>
greater_than(Lattice<T, Func> obj, T n) {
   return Lattice(obj.reveal()>n, Or{});
}

#endif //MANGO_GREATER_THAN_H
