#include <cstdint>
#include <cstddef>

namespace Math
{

template<typename T>
struct Quaternion
{
public:

public:
    T X, Y, Z, W;
};

template struct Quaternion<float>;
template struct Quaternion<double>;

using Quat  = Quaternion<float>;
using Quatd = Quaternion<double>;

} //namespace Math