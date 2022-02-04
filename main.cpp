#include <array.h>
#include <list.h>
#include <vector.h>
#include <iostream>

struct Man {
    std::string name;
    size_t age;

    [[nodiscard]] std::string greet() const {
      return std::string("Hello, i'm " + name + " and i'm " + std::to_string(age) + " old!");
    };
};

struct comparator {
    int value_to_compare;

    void operator()(int& rhs) const {
       if (value_to_compare == rhs){
           std::cout << "Found value is: " << value_to_compare << '\n';
       }
    }
};

int main() {
//    learning::array<int, 10> array{1, 2, 3, 4};
//
//    learning::for_each_k(&array, [](int& i, size_t key) {
//        std::cout << "1 - array: " << key << ": " << i << '\n';
//        ++i;
//    });
//
//    learning::for_each(&array, comparator{.value_to_compare = 3});
//
//    learning::for_each_k_r(&array,  [](int& i, size_t key) {
//        std::cout << "1 - array: " << key << ": " << i << '\n';
//    });
//
//    learning::array<Man, 3> humen;
//
//    learning::for_each_k(&humen, [](Man& i, size_t key) {
//        i.age = key;
//        i.name = "Man-" + std::to_string(key);
//    });
//
//    learning::for_each_k(&humen, [](Man& i, size_t key) {
//       std::cout << key << ": " << i.greet() << '\n';
//    });

    std::vector<int> v;

    for(int i = 0; i < 17; ++i) {
        v.emplace_back(i);
        std::cout << v.size() << " " << v.capacity() << '\n';
    }

    learning::vector<int> v2;

    for(int i = 0; i < 17; ++i) {
        v2.emplace_back(i);
        std::cout << v2.count() << " " << v2.capacity() << '\n';
    }


    learning::for_each(&v2, [](int& i) {
        std::cout << "foreach: " << i << '\n';
    });


}
