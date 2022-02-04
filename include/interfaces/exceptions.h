//
// Created by MrMam on 04.02.2022.
//

#ifndef LEARNING_EXCEPTIONS_H
#define LEARNING_EXCEPTIONS_H

#include <exception>
#include <string>


namespace learning {
    class out_of_range : public std::exception {
    private:
        std::string _error;
    public:
        template<typename T>
        explicit out_of_range(T error): _error(error) {}

        virtual ~out_of_range() = default;

    public:
        [[nodiscard]] const char *what() const noexcept override {
            return _error.c_str();
        }
};

}

#endif //LEARNING_EXCEPTIONS_H
