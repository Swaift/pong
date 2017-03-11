#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>

namespace sf {
    class Ball: public CircleShape {
        public:
            Ball(float radius);
            void reset();
            float getDx();
            float getDy();
            void setDx(float dx);
            void setDy(float dy);
            float getCenter();
        private:
            float dx, dy;
    };
}

#endif // BALL_HPP
