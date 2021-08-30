#pragma once

#include <cmath>
#include <ostream>

class Vec3
{
 public:
    Vec3() : data_{0} {}
    Vec3(double x, double y, double z) : data_{x,y,z} {}
    explicit Vec3(const double *data) : data_{data[0], data[1], data[2]} {}
    auto X() const {return data_[0];} 
    auto Y() const {return data_[1];} 
    auto Z() const {return data_[2];} 
    Vec3 operator-() const {return Vec3(-X(), -Y(), -Z());}
    auto operator[](int i) const {return data_[i];}
    auto& operator[](int i) {return data_[i];}
    Vec3& operator+=(const Vec3& v) {
        data_[0] += v.data_[0];
        data_[1] += v.data_[1];
        data_[2] += v.data_[2];
        return *this;
    }
    Vec3& operator+=(const double t) {
        data_[0] += t;
        data_[1] += t;
        data_[2] += t;
        return *this;
    }
    Vec3& operator-=(const Vec3& v) {
        data_[0] -= v.data_[0];
        data_[1] -= v.data_[1];
        data_[2] -= v.data_[2];
        return *this;
    }
    Vec3& operator-=(const double t) {
        data_[0] -= t;
        data_[1] -= t;
        data_[2] -= t;
        return *this;
    }
    Vec3& operator*=(const Vec3& v) {
        data_[0] *= v.data_[0];
        data_[1] *= v.data_[1];
        data_[2] *= v.data_[2];
        return *this;
    }
    Vec3& operator*=(const double t) {
        data_[0] *= t;
        data_[1] *= t;
        data_[2] *= t;
        return *this;
    }
    Vec3& operator/=(const double t) {
        return *this *= 1.0/t;
    }
    Vec3& operator/=(const Vec3& v) {
        data_[0] /= v[0];
        data_[1] /= v[1];
        data_[2] /= v[2];
        return *this;
    }

    Vec3 operator/(const Vec3& v) const {
        return Vec3(X()/v.X(), Y()/v.Y(), Z()/v.Z());
    }
    Vec3 operator*(const Vec3& v) const {
        return Vec3(X()*v.X(), Y()*v.Y(), Z()*v.Z());
    }
    Vec3 operator+(const Vec3& v) const {
        return Vec3(X()+v.X(), Y()+v.Y(), Z()+v.Z());
    }
    Vec3 operator+(const double t) const {
        return Vec3(X()+t, Y()+t, Z()+t);
    }
    Vec3 operator-(const Vec3& v) const {
        return Vec3(X()-v.X(), Y()-v.Y(), Z()-v.Z());
    }
    inline Vec3 operator*(const double& t) const {
        return Vec3(X()*t, Y()*t, Z()*t);
    }
    inline Vec3 operator/(const double& t) const {
        return *this*(1.0/t);
    }
    double Lenght() const {
        return std::sqrt(LengthSquared());
    }
    double LengthSquared() const {
        return X()*X() + Y()*Y() + Z()*Z();
    }
    double Sum() const {
        return X()+Y()+Z();
    }
    double Dot(const Vec3& v) const {
        return (*this*v).Sum();
    }
    Vec3 Cross(const Vec3& v) const {
        return Vec3(data_[1] * v[2] - data_[2] * v[1],
                    data_[2] * v[0] - data_[0] * v[2],
                    data_[0] * v[1] - data_[1] * v[0]);
    }
    void Normalize() {
        *this /= Lenght();
    }
    Vec3 UnitVector() const {
        return *this/Lenght();
    }
 private:
    double data_[3];
};

inline std::ostream& operator<<(std::ostream &out, const Vec3& v) {
    return out << v.X() << ' ' << v.Y() << ' ' << v.Z();
}
inline Vec3 operator*(const double& t, const Vec3& v) {
    return v*t;
}
inline double Dot(const Vec3 &u, const Vec3 &v) {
    return u.Dot(v);
}

inline Vec3 Cross(const Vec3 &u, const Vec3 &v) {
    return u.Cross(v);
}

inline Vec3 UnitVector(const Vec3& v) {
    return v.UnitVector();
}

using Point = Vec3;
using Color = Vec3;

void WriteColor(std::ostream &out, const Color &c) {
    out << static_cast<int>(255.999*c[0]) << ' '
        << static_cast<int>(255.999*c[1]) << ' '
        << static_cast<int>(255.999*c[2]) << '\n';
}
