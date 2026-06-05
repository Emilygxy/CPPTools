#include "CPMesh.h"
#include<cmath>

bool PhysixHelper::CheckCollision(PhysicalBall& ball1, PhysicalBall& ball2)
{
    // calculate the distance between the centers of the two balls
    float dx = ball2.x - ball1.x;
    float dy = ball2.y - ball1.y;
    float distance = sqrt(dx * dx + dy * dy);

    // check if the distance is less than the sum of the radii, which means a collision has occurred
    return (distance < ball1.radius + ball2.radius);
}

void PhysixHelper::HandleBoudaryCollision(PhysicalBall& ball, float width, float height)
{
    // check collision with left and right walls
    if (ball.x - ball.radius < 0.0f) {
        ball.x = ball.radius;  // reposition the ball to the edge
        ball.vx = -ball.vx;   // reverse the velocity
    }
    else if (ball.x + ball.radius > width) {
        ball.x = width - ball.radius;  // reposition the ball to the edge
        ball.vx = -ball.vx;            // reverse the velocity
    }

    // check collision with top and bottom walls
    if (ball.y - ball.radius < 0.0f) {
        ball.y = ball.radius;  // reposition the ball to the edge
        ball.vy = -ball.vy;   // reverse the velocity
    }
    else if (ball.y + ball.radius > height) {
        ball.y = height - ball.radius;  // reposition the ball to the edge
        ball.vy = -ball.vy;             // reverse the velocity
    }
}

void PhysixHelper::ResolveCollision(PhysicalBall& ball1, PhysicalBall& ball2)
{
    // Calculate the unit normal vector (from ball1 to ball2)
    float dx = ball2.x - ball1.x;
    float dy = ball2.y - ball1.y;
    float dist = sqrt(dx*dx + dy*dy);
    if (dist == 0) return;  // Avoid division by zero

    float nx = dx / dist;
    float ny = dy / dist;
    // Calculate the unit tangent vector
    float tx = -ny;
    float ty = nx;
    // Project the velocities onto the normal and tangent vectors
    float v1n = ball1.vx * nx + ball1.vy * ny;
    float v1t = ball1.vx * tx + ball1.vy * ty;
    float v2n = ball2.vx * nx + ball2.vy * ny;
    float v2t = ball2.vx * tx + ball2.vy * ty;
    // Calculate the new normal velocities using the 1D elastic collision equations
    float v1n_new = (v1n * (ball1.mass - ball2.mass) + 2 * ball2.mass * v2n) / (ball1.mass + ball2.mass);
    float v2n_new = (v2n * (ball2.mass - ball1.mass) + 2 * ball1.mass * v1n) / (ball1.mass + ball2.mass);
    // Convert the scalar normal and tangent velocities back to vectors
    ball1.vx = v1n_new * nx + v1t * tx;
    ball1.vy = v1n_new * ny + v1t * ty;
    ball2.vx = v2n_new * nx + v2t * tx;
    ball2.vy = v2n_new * ny + v2t * ty;
    // separate the balls to prevent them from sticking together: move them apart along the normal direction
    float overlap = (ball1.radius + ball2.radius) - dist + 0.5f; // add a small offset to prevent sticking
    ball1.x -= overlap * nx * 0.5f; // move ball back by half the overlap
    ball1.y -= overlap * ny * 0.5f;
    ball2.x += overlap * nx * 0.5f;
    ball2.y += overlap * ny * 0.5f;
}