#include "pt.h"

VX generateXs(size_t n, double lambda){
    VX vx(lambda);
    for (size_t i = 0; i < n; i++) {
        vx.setX(GM::getRandomNumberFromTheInterval(0, 1));
    }
    return vx;
}
