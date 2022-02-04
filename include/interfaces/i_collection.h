//
// Created by MrMam on 03.02.2022.
//

#ifndef LEARNING_I_CONTAINER_H
#define LEARNING_I_CONTAINER_H

#include <i_iterable.h>
#include <exceptions.h>
#include <mutex>

namespace learning {
    template <typename T>
    class i_collection : public i_iterable<T>{
    public:
        virtual ~i_collection() = default;

        virtual size_t count() const = 0;
        virtual void copy_to(T* array, size_t array_size, size_t offset) = 0;

        virtual std::lock_guard<std::mutex> sync_root() const = 0;
    };
}

#endif //LEARNING_I_CONTAINER_H
