#include <Random.h>
#include <iostream>
#include <FourierHypersurface.h>

int main() {
    FourierHypersurface fs = FourierHypersurface::CreateFromRandom(15, 5);
    for (auto &pfs : fs) {
        for (auto &fe :pfs) {
            std::cout << "(" << fe.Amplitude << ", " << fe.Phase << "); ";
        }
        std::cout << std::endl;
    }


    return 0;
}