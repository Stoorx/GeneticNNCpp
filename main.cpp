#include <Random.h>
#include <iostream>
#include <FourierHypersurface.h>

int main() {
    FourierHypersurface fs = FourierHypersurface::CreateFromRandom(6, 5);
    for (auto &pfs : fs) {
        for (auto &fe :pfs) {
            std::cout << "(" << fe.Amplitude << ", " << fe.Phase << "); ";
        }
        std::cout << "* " << pfs.Pitch << "=>" << pfs.Calculate(0) << "\n";
    }

    std::cout << fs.Calculate(
            std::vector<double>(
                    {1, 1, 1, 1, 1, 1}
            )
    );

    return 0;
}