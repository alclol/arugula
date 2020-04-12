//
// Created by alclol on 4/12/20.
//
#include "lattice_core.hpp"
#include "merges/boolean_mrg.hpp"

#ifndef MANGO_GREATER_THAN_H
#define MANGO_GREATER_THAN_H

//typedef struct MaxStruct Max;
typedef struct MapUnionStruct MapUnion;
typedef struct CausalMergeStruct CausalMerge;

//template <class QFunc = Func>
//typename std::enable_if_t<std::is_same<QFunc, Max>::value, Lattice<bool, Or>>
//struct greater_than {
//private:
//
//   T l_val = this->reveal();
//   bool result = n < l_val;
//   return Lattice(result, Or{});
//}
//
template <class Func, class T>
typename std::enable_if_t<std::is_same<Func, Max>::value, Lattice<bool, Or>>
greater_than(Lattice<T, Func> obj, T n) {
   return Lattice(obj.reveal()>n, Or{});
}

//template <class K, class vT, class Q = T, class QFunc = Func>
//typename std::enable_if_t<std::is_same<Q, std::map<K, vT>>::value&& std::is_same<QFunc, MapUnion>::value, vT>
//At(K key) {
//   return this->reveal().at(key);
//}
//
//
//class greater_than {
//
//};


#endif //MANGO_GREATER_THAN_H
