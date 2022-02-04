//
// Created by MrMam on 03.02.2022.
//

#ifndef LEARNING_I_ENUMERABLE_H
#define LEARNING_I_ENUMERABLE_H

#include <i_iterator.h>
#include <type_traits>

namespace learning {
    template <typename T>
    class i_iterable {
    public:
        virtual ~i_iterable() = default;

        virtual i_iterator<T>* get_iterator()  = 0;
        virtual i_iterator<T>* get_riterator() = 0;
    };


    template<typename T, class Pred, class PredTrait = std::is_invocable<Pred, T&>>
    void for_each(i_iterable<T>* data, Pred predicate) {
        auto it = data->get_iterator();
        do {
            predicate(it->current());
        } while (it->move_next());
    }
    template<typename T, class Pred, class PredTrait = std::is_invocable<Pred, T&, size_t>>
    void for_each_k(i_iterable<T>* data, Pred predicate) {
        auto it = data->get_iterator();
        do {
            predicate(it->current(), it->current_key());
        } while (it->move_next());
    }

    template<typename T, class Pred, class PredTrait = std::is_invocable<Pred, T&>>
    void for_each_r(i_iterable<T>* data, Pred predicate) {
        auto it = data->get_riterator();
        do {
            predicate(it->current());
        } while (it->move_next());
    }
    template<typename T, class Pred, class PredTrait = std::is_invocable<Pred, T&, size_t>>
    void for_each_k_r(i_iterable<T>* data, Pred predicate) {
        auto it = data->get_riterator();
        do {
            predicate(it->current(), it->current_key());
        } while (it->move_next());
    }
}

#endif //LEARNING_I_ENUMERABLE_H
