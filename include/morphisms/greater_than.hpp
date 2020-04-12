//
// Created by alclol on 4/12/20.
//
#include "lattice_core.hpp"
#include "merges/boolean_mrg.hpp"

#ifndef MANGO_GREATER_THAN_H
#define MANGO_GREATER_THAN_H

template <class T>
struct CompStruct_L {
private:
    Lattice<T, Max> _threshold;
    T _val;

public:
    CompStruct_L(Lattice<T, Max> threshold) : _threshold(std::move(threshold)) {
       _val = threshold.reveal();
    };

    Lattice<T, Max> greater_than(Lattice<T, Max> target) {
       return Lattice(target.reveal() > this->_val, Or{});
    }

    Lattice<T, Max> greater_than_or_eq(Lattice<T, Max> target) {
       auto gt = target.reveal();
       return Lattice(gt>this->_val || gt==this->_val, Or{});
    }

    Lattice<T, Max> less_than(Lattice<T, Max> target) {
       return Lattice(target.reveal()<this->_val, Or{});
    }

    Lattice<T, Max> less_than_or_eq(Lattice<T, Max> target) {
       auto lt = target.reveal();
       return Lattice(lt<this->_val|| lt==this->_val, Or{});
    }
};

template <class T>
struct CompStruct {
private:
    T threshold;

public:
    CompStruct(T _threshold) : threshold(std::move(_threshold)) {};

    template <class Func>
    typename std::enable_if_t<std::is_same<Func, Max>::value, Lattice<bool, Or>>
    greater_than(Lattice<T, Func> target) {
       return Lattice(target.reveal()>this->threshold, Or{});
    }

    template <class Func>
    typename std::enable_if_t<std::is_same<Func, Max>::value, Lattice<bool, Or>>
    greater_than_or_eq(Lattice<T, Func> target) {
       auto gt = target.reveal();
       return Lattice(gt>this->threshold || gt==this->threshold, Or{});
    }

    template <class Func>
    typename std::enable_if_t<std::is_same<Func, Min>::value, Lattice<bool, Or>>
    less_than(Lattice<T, Func> target) {
       return Lattice(target.reveal()<this->threshold, Or{});
    }

    template <class Func>
    typename std::enable_if_t<std::is_same<Func, Min>::value, Lattice<bool, Or>>
    less_than_or_eq(Lattice<T, Func> target) {
       auto lt = target.reveal();
       return Lattice(lt<this->threshold || lt==this->threshold, Or{});
    }
};

template <class Func, class T>
typename std::enable_if_t<std::is_same<Func, Max>::value, Lattice<bool, Or>>
greater_than(Lattice<T, Func> obj, T n) {
   return Lattice(obj.reveal()>n, Or{});
}

#endif //MANGO_GREATER_THAN_H
