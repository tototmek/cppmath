#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <iostream>
#include <cmath>

class Vector2D {
    public:
        float x;
        float y;

        Vector2D(float x, float y) {
            this->x = x;
            this->y = y;
        }

        Vector2D() {
            this->x = 0;
            this->y = 0;
        }
        
        Vector2D operator+(const Vector2D& v) const {
            return Vector2D(x + v.x, y + v.y);
        }

        Vector2D operator-(const Vector2D& v) const {
            return Vector2D(x - v.x, y - v.y);
        }

        Vector2D operator*(const float& f) const {
            return Vector2D(x * f, y * f);
        }

        Vector2D operator*(const Vector2D& v) const {
            return Vector2D(x * v.x, y * v.y);
        }

        Vector2D operator/(const Vector2D& v) const {
            return Vector2D(x / v.x, y / v.y);
        }

        Vector2D operator/(const float& f) const {
            return Vector2D(x / f, y / f);
        }

        Vector2D operator-() const {
            return Vector2D(-x, -y);
        }

        Vector2D operator+=(const Vector2D& v) {
            x += v.x;
            y += v.y;
            return *this;
        }

        Vector2D operator-=(const Vector2D& v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        Vector2D operator*=(const float& f) {
            x *= f;
            y *= f;
            return *this;
        }

        Vector2D operator/=(const float& f) {
            x /= f;
            y /= f;
            return *this;
        }

        float magnitude() const {
            return std::sqrt(x * x + y * y);
        }

        float sqrMagnitude() const {
            return x * x + y * y;
        }

        Vector2D normalized() const {
            float m = magnitude();
            return Vector2D(x / m, y / m);
        }

        Vector2D perpendicular() const {
            return Vector2D(-y, x);
        }

        float angle(const Vector2D& v) const {
            return acos(dot(v) / (magnitude() * v.magnitude()));
        }

        Vector2D rotate(float angle) const{
            float s = sin(angle);
            float c = cos(angle);
            return Vector2D(x * c - y * s, x * s + y * c);
        }

        bool operator==(const Vector2D& v) const {
            return x == v.x && y == v.y;
        }

        bool operator!=(const Vector2D& v) const {
            return x != v.x || y != v.y;
        }

        Vector2D operator=(const Vector2D& v) {
            x = v.x;
            y = v.y;
            return *this;
        }

        float dot(const Vector2D& v) const {
            return x * v.x + y * v.y;
        }

        float cross(const Vector2D& v) const {
            return x * v.y - y * v.x;
        }
        
        Vector2D clampMagnitude(float max) const {
            if (sqrMagnitude() > max * max) {
                return normalized() * max;
            }
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
            os << "(" << v.x << ", " << v.y << ")";
            return os;
        }
        
        static Vector2D zero() {
            return Vector2D(0, 0);
        }

        static Vector2D one() {
            return Vector2D(1, 1);
        }

        static Vector2D up() {
            return Vector2D(0, 1);
        }

        static Vector2D down() {
            return Vector2D(0, -1);
        }

        static Vector2D left() {
            return Vector2D(-1, 0);
        }

        static Vector2D right() {
            return Vector2D(1, 0);
        }

        static Vector2D lerp(const Vector2D& v1, const Vector2D& v2, float t) {
            return v1 + (v2 - v1) * t;
        }

        static Vector2D slerp(const Vector2D& v1, const Vector2D& v2, float t) {
            float angle = v1.angle(v2);
            return (v1 * sin(angle * (1 - t)) + v2 * sin(angle * t)) / sin(angle);
        }
};

#endif