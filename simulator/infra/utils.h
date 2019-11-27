

#ifndef INFRA_UTILS_H
#define INFRA_UTILS_H


template<typename T>
T sign_extend(T x, const int bits) {
    T m = 1;
    m <<= bits - 1;
    return (x ^ m) - m;
}


#endif // INFRA_UTILS_H