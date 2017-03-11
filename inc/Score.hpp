#ifndef SCORE_HPP
#define SCORE_HPP

#include <SFML/Graphics.hpp>

namespace sf {
    class Score: public Text {
        public:
            Score();
            int getScore();
            void setScore(int score);
        private:
            int score;
    };
}

#endif // SCORE_HPP
