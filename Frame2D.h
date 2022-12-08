#ifndef FRAME_H
#define FRAME_H
#include "Vector2D.h"

// Frame2D class represents a frame of reference in 2D space.
// It can be used to convert between local and global coordinates.
class Frame2D {
    private:
        Frame2D* parent;
        Vector2D position;
        Vector2D scale;
        float rotation;
    public:
        Frame2D() {
            parent = NULL;
            position = Vector2D(0, 0);
            scale = Vector2D(1, 1);
            rotation = 0;
        }

        Frame2D(Frame2D* parent, Vector2D position, float rotation, Vector2D scale) {
            this->parent = parent;
            this->position = position;
            this->rotation = rotation;
            this->scale = scale;
        }

        // Converts a vector from global coordinates to local coordinates. 
        Vector2D getLocalCoordinates(Vector2D globalVector) {
            if (parent == NULL) {
                return (globalVector - position).rotate(-rotation) / scale;
            }
            return (parent->getLocalCoordinates(globalVector) - position).rotate(-rotation) / scale;
        }

        // Converts a vector from local coordinates to global coordinates.
        Vector2D getGlobalCoordinates(Vector2D localVector) {
            if (parent == NULL) {
                return (localVector * scale).rotate(rotation) + position;
            }
            return parent->getGlobalCoordinates((localVector * scale).rotate(rotation) + position);
        }

        void setParent(Frame2D* parent) {
            this->parent = parent;
        }

        void setPosition(Vector2D position) {
            this->position = position;
        }

        void setRotation(float rotation) {
            this->rotation = rotation;
        }

        void setScale(Vector2D scale) {
            this->scale = scale;
        }

        Frame2D* getParent() {
            return parent;
        }

        Vector2D getPosition() {
            return position;
        }

        float getRotation() {
            return rotation;
        }

        Vector2D getScale() {
            return scale;
        }
};


#endif