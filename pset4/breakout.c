//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
void removeGWindow(GWindow window, GObject bricks);
bool won(void);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // ball speed set to random
    double velocity_x = drand48() * 4;
    double velocity_y = 3.0;
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);
        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows top cursor
                double x = getX(event) - getWidth(paddle) / 2;
                double y = 500;
                setLocation(paddle, x, y);
            }
        }   
        // moving the ball
        move(ball, velocity_x, velocity_y);

        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) > getWidth(window))
        {
            velocity_x = -velocity_x;
        }
        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            velocity_x = -velocity_x;
        } 
        // bounce off top edge
        if (getY(ball) <= 0)
        {
            velocity_y = -velocity_y;
        }
        // collision with paddle
        GObject object = detectCollision(window, ball);
        if (object == paddle)
        {
            velocity_y = -velocity_y;
        }
        // break some bricks
        if (object != NULL)
        if ((strcmp(getType(object), "GRect") == 0) && (object != paddle))    
        {
            points++;
            removeGWindow(window, object);
            velocity_y = -velocity_y;
            char s[12];
            sprintf (s,"%i", points);
            setLabel(label, s);
            
            if (points == 50)
            {
                break;
            }

        }
      
        // bounce off bottom edge
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives--;
            removeGWindow(window, ball);
            waitForClick();
            ball = initBall(window);  
        }
       
        // linger before moving again
        pause(10);
    }

    waitForClick();
     
    // game over
    //if points is equal to the number of bricks you win
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // draw bricks
    int i, j;
    int x = 0, y = 50;
        for (i = 0; i < ROWS; i++)
        {
            for (j = 0; j < COLS; j++)
            {
                // brick width and height
                GRect bricks = newGRect(x + 10, y + 10, 35, 15);
                // Spaces between the bricks
                x += (35 + 3);
                // Add color to the bricks
                if (i == 0 && j <= 10)
                {
                    setColor(bricks, "RED");
                }
                if (i == 1 && j <= 10)
                {
                    setColor(bricks, "MAGENTA");
                }
                if (i == 2 && j <= 10)
                {
                    setColor(bricks, "BLUE");
                }
                if (i == 3 && j <= 10)
                {
                    setColor(bricks, "GREEN");
                }
                if (i == 4 && j <= 10)
                {
                    setColor(bricks, "YELLOW");
                }
            setFilled(bricks, true);
            add(window, bricks);
            }
        x = 0;
        y += 35 + 3;
        }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // instantiate circle
    GOval ball = newGOval(200, 250, 20, 20);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
     // instantiate paddle
    GRect paddle = newGRect(200, 500, 70, 10);
    setColor(paddle, "ORANGE");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // instantiate label
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    setLocation(label, 200, 300);
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
