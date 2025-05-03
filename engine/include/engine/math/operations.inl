namespace math
{

template<typename T>
Vector2<T> operator*(const Matrix2<T>& m, const Vector2<T> v)
{
    return Vector2<T>
    {
        m.arr[0] * v.x + m.arr[2] * v.y,
        m.arr[1] * v.x + m.arr[3] * v.y
    };
}

template<typename T>
Vector3<T> operator*(const Matrix3<T>& m, const Vector3<T> v)
{
    return Vector3<T>
    {
        m.arr[0] * v.x + m.arr[3] * v.y + m.arr[6] * v.z,
        m.arr[1] * v.x + m.arr[4] * v.y + m.arr[7] * v.z,
        m.arr[2] * v.x + m.arr[5] * v.y + m.arr[8] * v.z
    };
}

template<typename T>
Vector4<T> operator*(const Matrix4<T>& m, const Vector4<T> v)
{
    return Vector4<T>
    {
        m.arr[0] * v.x + m.arr[4] * v.y + m.arr[8]  * v.z + m.arr[12] * v.w,
        m.arr[1] * v.x + m.arr[5] * v.y + m.arr[9]  * v.z + m.arr[13] * v.w,
        m.arr[2] * v.x + m.arr[6] * v.y + m.arr[10] * v.z + m.arr[14] * v.w,
        m.arr[3] * v.x + m.arr[7] * v.y + m.arr[11] * v.z + m.arr[15] * v.w
    };
}

template<typename T>
Quaternion<T> operator*(const Quaternion<T>& q, const Vector3<T> v)
{
    T dot            = q.x * v.x + q.y * v.y + q.z * v.z;
    Vector3<T> cross = Vector3( 
        q.y * v.z - q.z * v.y, 
        q.z * v.x - q.x * v.z,
        q.x * v.y - q.y * v.x 
    );

    Quaternion<T> other = Quaternion(
        q.w * v.x + cross.x,
        q.w * v.y + cross.y,
        q.w * v.z + cross.z,
        -dot
    );
    Quaternion<T> conj = q.GetConjugated();

    cross = Vector3( 
        other.y * conj.z - other.z * conj.y, 
        other.z * conj.x - other.x * conj.z,
        other.x * conj.y - other.y * conj.x 
    );
    
    return Vector3<T>(
        other.w * conj.x + conj.w * other.x + cross.x,
        other.w * conj.y + conj.w * other.y + cross.y,
        other.w * conj.z + conj.w * other.z + cross.z
    );
}

} //namespace math