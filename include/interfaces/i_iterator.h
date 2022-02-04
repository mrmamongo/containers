//
// Created by MrMam on 04.02.2022.
//

#ifndef LEARNING_I_ITERATOR_H
#define LEARNING_I_ITERATOR_H

#include <functional>

namespace learning {
    using size_t = unsigned long;

    template <typename T>
    class i_iterator {
    public:
        virtual ~i_iterator() = default;

        virtual bool move_next() = 0;
        virtual T& current() = 0;
        virtual const T& current() const = 0;
        virtual size_t current_key() const = 0;
        virtual void reset() = 0;
    };
}

#endif //LEARNING_I_ITERATOR_H
