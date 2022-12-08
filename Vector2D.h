#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <iostream>
#include <cmath>

/// @brief A class representing a 2D vector.
/// @details This class is used to represent a 2D vector. It has an x and y component, and it has a number of functions to perform operations on the vector.
class Vector2D {
    public:
        /// @brief The x component of the vector.
        float x;
        /// @brief The y component of the vector.
        float y;

        /// @brief Creates a new vector with the specified x and y components.
        /// @param x The x component of the vector.
        /// @param y The y component of the vector. 
        Vector2D(float x, float y) {
            this->x = x;
            this->y = y;
        }

        /// @brief Creates a new zero vector.
        /// @details This function creates a new zero vector. It sets the x and y components to 0.
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

        /// @brief Get the magnitude of the vector.
        /// @return The magnitude of the vector.
        /// @details This function returns the magnitude of the vector. The magnitude is the length of the vector.
        /// @see sqrMagnitude()
        float magnitude() const {
            return std::sqrt(x * x + y * y);
        }

        /// @brief Get the squared magnitude of the vector.
        /// @return The squared magnitude of the vector.
        /// @details This function returns the squared magnitude of the vector. The squared magnitude is the length of the vector squared.
        /// @see magnitude()
        /// @note This function is faster than magnitude(), and should be used if you only need to compare the magnitude of two vectors.
        float sqrMagnitude() const {
            return x * x + y * y;
        }

        /// @brief Get the normalized vector.
        /// @return The normalized vector.
        /// @details This function returns the normalized vector. The normalized vector is the vector with the same direction as the original vector, but with a magnitude of 1.
        Vector2D normalized() const {
            float m = magnitude();
            return Vector2D(x / m, y / m);
        }

        /// @brief Get the perpendicular vector.
        /// @return The perpendicular vector.
        /// @details This function returns the perpendicular vector. The perpendicular vector is the vector with the same magnitude as the original vector, but with a direction 90 degrees to the right of the original vector.
        Vector2D perpendicular() const {
            return Vector2D(-y, x);
        }

        /// @brief Get the angle between two vectors.
        /// @param v The vector to compare the angle to.
        /// @return The angle between the two vectors.
        /// @details This function returns the angle between two vectors. The angle is in radians.
        float angle(const Vector2D& v=Vector2D::right()) const {
            float a = atan2(cross(v), dot(v));
            if (a < 0) {
                a += 2 * M_PI;
            }
            return a;
        }

        /// @brief Rotate the vector.
        /// @param angle The angle to rotate the vector by.
        /// @return The rotated vector.
        /// @details This function returns the rotated vector. The angle is in radians.
        /// @see angle()
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

        /// @brief Get the dot product of two vectors.
        /// @param v The vector to dot with.
        /// @return The dot product of the two vectors.
        /// @details This function returns the dot product of two vectors. The dot product is the sum of the products of the components of the vectors.
        float dot(const Vector2D& v) const {
            return x * v.x + y * v.y;
        }

        /// @brief Get the cross product of two vectors.
        /// @param v The vector to cross with.
        /// @return The cross product of the two vectors.
        /// @details This function returns the cross product of two vectors. The cross product is the magnitude of the vector perpendicular to the two vectors.
        float cross(const Vector2D& v) const {
            return x * v.y - y * v.x;
        }
        
        /// @brief Get the distance between two vectors.
        /// @param max The maximum magnitude of the vector.
        /// @return The vector with a magnitude of max if the original vector is greater than max, otherwise the original vector.
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
        
        /// @brief Get the zero vector.
        /// @return A vector (0, 0).
        static Vector2D zero() {
            return Vector2D(0, 0);
        }

        /// @brief Get the one vector.
        /// @return A vector (1, 1).
        static Vector2D one() {
            return Vector2D(1, 1);
        }

        /// @brief Get the up vector.
        /// @return A vector (0, 1).
        static Vector2D up() {
            return Vector2D(0, 1);
        }

        /// @brief Get the down vector.
        /// @return A vector (0, -1).
        static Vector2D down() {
            return Vector2D(0, -1);
        }

        /// @brief Get the left vector.
        /// @return A vector (-1, 0).
        static Vector2D left() {
            return Vector2D(-1, 0);
        }

        /// @brief Get the right vector.
        /// @return A vector (1, 0).
        static Vector2D right() {
            return Vector2D(1, 0);
        }

        /// @brief Interpolate between two vectors.
        /// @param v1 The first vector.
        /// @param v2 The second vector.
        /// @param t The interpolation factor.
        /// @return The interpolated vector.
        /// @details This function returns the interpolated vector. The interpolation factor is a value between 0 and 1. If t is 0, the interpolated vector is v1. If t is 1, the interpolated vector is v2. If t is 0.5, the interpolated vector is halfway between v1 and v2.
        /// @see slerp()
        static Vector2D lerp(const Vector2D& v1, const Vector2D& v2, float t) {
            return v1 + (v2 - v1) * t;
        }

        /// @brief Interpolate between two vectors using spherical linear interpolation.
        /// @param v1 The first vector.
        /// @param v2 The second vector.
        /// @param t The interpolation factor.
        /// @return The interpolated vector.
        /// @details This function returns the interpolated vector. The interpolation factor is a value between 0 and 1. If t is 0, the interpolated vector is v1. If t is 1, the interpolated vector is v2. If t is 0.5, the interpolated vector is halfway between v1 and v2.
        /// @see lerp()
        /// @note This function uses spherical linear interpolation, which is more accurate than linear interpolation, but is more expensive to compute. Use lerp() if you don't need the accuracy.
        static Vector2D slerp(const Vector2D& v1, const Vector2D& v2, float t) {
            float angle = v1.angle(v2);
            return (v1 * sin(angle * (1 - t)) + v2 * sin(angle * t)) / sin(angle);
        }
};

#endif