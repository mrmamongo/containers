//
// Created by MrMam on 04.02.2022.
//

#ifndef LEARNING_VECTOR_H
#define LEARNING_VECTOR_H

#include <i_iterable.h>

namespace learning {
    template<typename T>
    class vector_iterator;
    template<typename T>
    class recursive_vector_iterator;

    template<typename T, class Trait = std::is_constructible<T, void>>
    class vector : public i_collection<T> {
    public:
        virtual ~vector() {
            delete[] _data;
        }

        vector(std::initializer_list<T> list) {
            _size = list.size();
            _capacity = _size * 2;
            _data = new T[_size];
            for (auto&& elem : list) {
                emplace_back(elem);
            }
        }
        explicit vector(size_t size = 0, T elem = T()): _size(size){
            _capacity = _size * 2;
            if (_capacity == 0) {
                return;
            }
            _data = new T[_capacity];
            for (size_t i = 0; i < _size; ++i) {
                _data[i] = elem;
            }
        }
        vector(vector const& other) {
            _size = other._size;
            _capacity = other._capacity;
            _data = new T[_size];
            for (size_t i = 0; i < _size; ++i) {
                _data[i] = other._data[i];
            }
        }

        vector(vector&& other) noexcept
            : _data(std::move(other._data)), _size(other._size), _capacity(other._capacity) {}

        vector& operator=(vector const& other) {
            if (&other == this) {
                return *this;
            }
            _size = other._size;
            _capacity = other._capacity;
            _data = new T[_size];
            for (size_t i = 0; i < _size; ++i) {
                _data[i] = other._data[i];
            }
            return *this;
        }
        vector& operator=(vector&& other) noexcept {
            if (&other == this) {
                return *this;
            }
            _size = other._size;
            _capacity = other._capacity;
            _data = std::move(other._data);
            return *this;
        }
    public:
        T& at(size_t index) {
            if (index >= _size) {
                throw out_of_range("Out of range");
            }
            return _data[index];
        }

        const T& at(size_t index) const {
            if (index >= _size) {
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
            return _size;
        }

        size_t capacity() const {
            return _capacity;
        }

        void copy_to(T* array, size_t array_size, size_t offset = 0) override {
            for (size_t i = 0; i < _size && i < array_size && i < array_size - offset; ++i) {
                array[i] = _data[i];
            }
        }
        [[nodiscard]] std::lock_guard<std::mutex> sync_root() const override {
            return std::lock_guard(_mutex);
        }
    public:
        i_iterator<T>* get_iterator() override {
            return new vector_iterator<T>(this);
        }

        i_iterator<T>* get_riterator() override{
            return new recursive_vector_iterator<T>(this);
        }

        T& front() {
            return _data[0];
        }

        T& back() {
            return _data[_size - 1];
        }
        const T& front() const {
            return _data[0];
        }

        const T& back() const {
            return _data[_size - 1];
        }

    public:
        void pop_back() {
            _size--;
        }

        void emplace_back(const T& v) {
            if (_size >= _capacity) {
                resize();
            }

            _data[_size++] = v;
        }
        void emplace_back(T&& v) {
            if (_size >= _capacity) {
                resize();
            }

            _data[_size++] = v;
        }

        template<typename ...Args>
        void emplace_back(Args&& ...args) {
            if (_size >= _capacity) {
                resize();
            }

            _data[_size++] = T(std::forward<Args>(args)...);
        }
    private:
        void resize() {
            _capacity = ((_capacity + 1) * 2 / 2)* 2 - 1;
            auto temp = _data;
            _data = new T[_capacity];
            for (size_t i = 0; i < _size; ++i) {
                _data[i] = temp[i];
            }
        }
    private:
        size_t _size;
        size_t _capacity;
        T* _data;
        mutable std::mutex _mutex{};
    };

    template<typename T>
    class vector_iterator : i_iterator<T> {
        friend class vector<T>;

    protected:
        explicit vector_iterator(vector<T>* data)
                : _data(data), _current_offset(0) {}
    public:

        virtual ~vector_iterator() = default;

        vector_iterator(const vector_iterator& other)
                : _data(other._data), _current_offset(other._current_offset) {}

        bool move_next() override {
            if (!_data || ++_current_offset >= _data->count()) {
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
        vector<T>* _data;
        size_t _current_offset;
    };

    template<typename T>
    class recursive_vector_iterator : i_iterator<T> {
        friend class vector<T>;

    protected:
        explicit recursive_vector_iterator(vector<T>* data)
                : _data(data) {
            _current_offset = _data->count();
        }
    public:

        virtual ~recursive_vector_iterator() = default;


        recursive_vector_iterator(const recursive_vector_iterator& other)
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
        vector<T>* _data;
        size_t _current_offset;
    };
}

#endif //LEARNING_VECTOR_H
