#pragma once

struct PhysicalBall{
    float x,y;
    float vx,vy;
    float ax,ay;
    float radius;
    float mass;

    PhysicalBall(float x, float y, float radius, float ma = 1.0f)
        : x(x), y(y), vx(0.0f), vy(0.0f), ax(0.0f), ay(0.0f), radius(radius), mass(mass) {}

    // update the position and velocity of the ball based on the acceleration and time step
    void Update(float dt) {
        vx += ax * dt;
        vy += ay * dt;
        x += vx * dt;
        y += vy * dt;

        ax = 0.0f;
        ay = 0.0f;
    }

    // apply a force to the ball, which will change its acceleration
    void ApplyForce(float fx, float fy) {
        ax += fx / mass;
        ay += fy / mass;
    }
};

class PhysixHelper
{
public: 
    PhysixHelper() {}
    ~PhysixHelper() {}

    // calculate the collision response between two balls, which will change their velocities
    static bool CheckCollision(PhysicalBall& ball1, PhysicalBall& ball2);
    static void HandleBoudaryCollision(PhysicalBall& ball, float width, float height);

    static void ResolveCollision(PhysicalBall& ball1, PhysicalBall& ball2);
private:

};
