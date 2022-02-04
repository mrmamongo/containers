//
// Created by MrMam on 03.02.2022.
//

#ifndef LEARNING_ARRAY_H
#define LEARNING_ARRAY_H

#include <i_collection.h>

namespace learning {
    template<typename T, size_t ArrSize>
    class array_iterator;
    template<typename T, size_t ArrSize>
    class recursive_array_iterator;

    template<typename T, size_t ArrSize, class Trait = std::is_constructible<T, void>>
    class array : public i_collection<T> {
    public:
        array(std::initializer_list<T> list) {
            size_t i = 0;
            for (auto&& elem : list) {
                if (i < ArrSize){
                    _data[i++] = elem;
                }
            }
            for (; i < ArrSize; ++i) {
                _data[i] = T();
            }
        }
        explicit array(T elem = T()){
            for (size_t i = 0; i < ArrSize; ++i) {
                _data[i] = elem;
            }
        }
        array(array const& other) {
            for (size_t i = 0; i < ArrSize; ++i) {
                _data[i] = other._data[i];
            }
        }

        array(array&& other) noexcept: _data(std::move(other._data)) {}
        array& operator=(array const& other) {
            if (&other == this) {
            return *this;
            }
            for (size_t i = 0; i < ArrSize; ++i) {
                _data[i] = other._data[i];
            }
            return *this;
        }
        array& operator=(array&& other) noexcept {
            if (&other == this) {
            return *this;
            }
            _data = std::move(other._data);
            return *this;
        }
    public:
        T& at(size_t index) {
            if (index >= ArrSize) {
                throw out_of_range("Out of range");
            }
            return _data[index];
        }

        const T& at(size_t index) const {
            if (index >= ArrSize) {
                throw out_of_range("Out of range");
            }
            return _data[index];
        }

        T& operator[](int index) {
            return at(size_t(index));
        }
        const T& operator[](int index) const {
            return at(size_t(index));
        }
        T& operator[](size_t index) {
            return at(index);
        }
        const T& operator[](size_t index) const {
            return at(index);
        }

    public:
        [[nodiscard]] size_t count() const override {
            return ArrSize;
        }
        void copy_to(T* array, size_t array_size = ArrSize, size_t offset = 0) override {
            for (size_t i = 0; i < ArrSize && i < array_size && i < array_size - offset; ++i) {
                array[i] = _data[i];
            }
        }

        [[nodiscard]] std::lock_guard<std::mutex> sync_root() const override {
            return std::lock_guard(_mutex);
        }

    public:
        i_iterator<T>* get_iterator() override {
            return new array_iterator<T, ArrSize>(this);
        }

        i_iterator<T>* get_riterator() override{
            return new recursive_array_iterator<T, ArrSize>(this);
        }
    private:
        T _data[ArrSize];
        mutable std::mutex _mutex{};
    };

    template<typename T, size_t ArrSize>
    class array_iterator : i_iterator<T> {
        friend class array<T, ArrSize>;

    protected:
        explicit array_iterator(array<T, ArrSize>* data)
                : _data(data), _current_offset(0) {}
    public:

        virtual ~array_iterator() = default;

        array_iterator(const array_iterator& other)
                : _data(other._data), _current_offset(other._current_offset) {}

        bool move_next() override {
            if (!_current_offset || ++_current_offset >= ArrSize) {
                return false;
            }
            return true;
        }

        T& current() override {
            return _data->at(_current_offset);
        }

        const T& current() const override {
            return _data->at(_current_offset);
        }

        [[nodiscard]] size_t current_key() const override{
            return _current_offset;
        }

        void reset() override {
            _data = nullptr;
            _current_offset = 0;
        }

    private:
        array<T, ArrSize>* _data;
        size_t _current_offset;
    };

    template<typename T, size_t ArrSize>
    class recursive_array_iterator : i_iterator<T> {
        friend class array<T, ArrSize>;

    protected:
        explicit recursive_array_iterator(array<T, ArrSize>* data)
                : _data(data), _current_offset(ArrSize - 1) {}
    public:

        virtual ~recursive_array_iterator() = default;


        recursive_array_iterator(const recursive_array_iterator& other)
                : _data(other._data), _current_offset(other._current_offset) {}

        bool move_next() override {
            if (0 >= _current_offset) {
                return false;
            }
            _current_offset--;
            return true;
        }
        T& current() override {
            return _data->at(_current_offset);
        }
        const T& current() const override {
            return _data->at(_current_offset);
        }

        [[nodiscard]] size_t current_key() const override{
            return _current_offset;
        }

        void reset() override {
            _data = nullptr;
            _current_offset = 0;
        }

    private:
        array<T, ArrSize>* _data;
        size_t _current_offset;
    };

}

#endif //LEARNING_ARRAY_H
