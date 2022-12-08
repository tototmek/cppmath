#ifndef FRAME_H
#define FRAME_H
#include "Vector2D.h"

/// @brief A class representing a 2D frame.
/// @details This class is used to represent a 2D frame. It has a position, rotation, and scale, and it has a number of functions to perform operations on the frame.
class Frame2D {
    private:
        Frame2D* parent;
        Vector2D position;
        Vector2D scale;
        float rotation;
    public:
        /// @brief Creates a new default frame.
        /// @details This function creates a new default frame. It sets the parent to NULL, the position to (0, 0), the rotation to 0, and the scale to (1, 1).
        Frame2D() {
            parent = NULL;
            position = Vector2D(0, 0);
            scale = Vector2D(1, 1);
            rotation = 0;
        }

        /// @brief Creates a new frame with the specified parent.
        /// @param parent The parent of the frame.
        /// @param position The position of the frame.
        /// @param rotation The rotation of the frame.
        /// @param scale The scale of the frame.
        /// @details This function creates a new frame with the specified parent. It sets the position, rotation, and scale to the specified values.
        Frame2D(Frame2D* parent, Vector2D position, float rotation, Vector2D scale) {
            this->parent = parent;
            this->position = position;
            this->rotation = rotation;
            this->scale = scale;
        }

        /// @brief Converts a vector from global coordinates to local coordinates.
        /// @param globalVector The vector to convert.
        /// @return The converted vector.
        /// @details This function converts a vector from global coordinates to local coordinates. It does this by first converting the vector to the parent's local coordinates, then subtracting the position, rotating by the negative rotation, and scaling by the inverse scale.
        /// @note This function is recursive, and will call itself until it reaches the root frame. 
        Vector2D getLocalCoordinates(Vector2D globalVector) {
            if (parent == NULL) {
                return (globalVector - position).rotate(-rotation) / scale;
            }
            return (parent->getLocalCoordinates(globalVector) - position).rotate(-rotation) / scale;
        }

        /// @brief Converts a vector from local coordinates to global coordinates.
        /// @param localVector The vector to convert.
        /// @return The converted vector.
        /// @details This function converts a vector from local coordinates to global coordinates. It does this by first scaling, rotating, and adding the position, then converting the vector to the parent's global coordinates.
        /// @note This function is recursive, and will call itself until it reaches the root frame.
        Vector2D getGlobalCoordinates(Vector2D localVector) {
            if (parent == NULL) {
                return (localVector * scale).rotate(rotation) + position;
            }
            return parent->getGlobalCoordinates((localVector * scale).rotate(rotation) + position);
        }

        /// @brief Sets the parent of the frame.
        /// @param parent The new parent of the frame.
        void setParent(Frame2D* parent) {
            this->parent = parent;
        }

        /// @brief Sets the position of the frame.
        /// @param position The new position of the frame.
        void setPosition(Vector2D position) {
            this->position = position;
        }

        /// @brief Sets the rotation of the frame.
        /// @param rotation The new rotation of the frame.
        void setRotation(float rotation) {
            this->rotation = rotation;
        }

        /// @brief Sets the scale of the frame.
        /// @param scale The new scale of the frame.
        void setScale(Vector2D scale) {
            this->scale = scale;
        }

        /// @brief Gets the parent of the frame.
        /// @return The parent of the frame.
        Frame2D* getParent() {
            return parent;
        }

        /// @brief Gets the position of the frame.
        /// @return The position of the frame.
        Vector2D getPosition() {
            return position;
        }

        /// @brief Gets the rotation of the frame.
        /// @return The rotation of the frame.
        float getRotation() {
            return rotation;
        }

        /// @brief Gets the scale of the frame.
        /// @return The scale of the frame.
        Vector2D getScale() {
            return scale;
        }
};


#endif