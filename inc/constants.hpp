#ifndef CONSTANTS_H
#define CONSTANTS_H

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

const int WALL_THICKNESS = 20;

const int PADDLE_THICKNESS = 20;
const int PADDLE_LENGTH = 80;
const int R_PADDLE_ACCEL = 7; // lower is more acceleration

const int BALL_RADIUS = 10;
const int BALL_STEP = 10;
const int MAX_BALL_OFFSET = PADDLE_LENGTH/2 + BALL_RADIUS;

const int SPACING = 20;
const int WAIT_TIME = 100;

#endif // CONSTANTS_HPP
