//
// Created by MrMam on 04.02.2022.
//

#ifndef LEARNING_I_QUERYABLE_H
#define LEARNING_I_QUERYABLE_H

#include <i_iterable.h>

namespace learning {

    template <typename T>
    class i_queryable : public i_iterable<T> {
    };
}

#endif //LEARNING_I_QUERYABLE_H
