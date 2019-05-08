#include <Random.h>
#include <iostream>

int main() {
    auto    r = Random();
    for(int i = 0; i < 10; ++i) {
        auto d = r.NextDouble();
        std::cout << d << std::endl;
    }
    return 0;
}