#include<iostream>
#include "CPMesh.h"
#include <vector>
#include <graphics.h> // From EasyX, for visualization

float dt = 1.0f / 60.0f; // time step

void UpdateDT()
{
    dt += 0.00005f;

    if (dt > 60.0f)
    {
        dt = 1.0f / 60.0f;
    }
}

int main()
{
    const int width = 800;
    const int height = 600;
    
    const float gravity = 980.0f; // gravity acceleration

    // Initialize the graphics window
    initgraph(width, height);
    // Create some physical balls
    std::vector<PhysicalBall> balls;
    for (size_t i = 0; i < 5; i++)
    {
        float x = rand() % (width - 100) + 50; // random x position within the window, avoiding edges
        float y = rand() % (height - 100) + 100; // random y position within the window, avoiding edges
        float vx = (rand() % 200 - 100) / 100.0f; // random velocity between -100 and 100
        float vy = (rand() % 200 - 100) / 100.0f; // random velocity between -100 and 100
        PhysicalBall ball(x, y, 20.0f, 1.0f); // radius of 20, mass of 1, initial velocities
        ball.vx = vx * 200.0f; // scale velocity for better visualization
        ball.vy = vy * 200.0f; // scale velocity for better visualization
        balls.push_back(ball);
    }
    
    while (true)
    {
        // 1. add gravity
        for (auto& ball : balls)
        {
            ball.ApplyForce(0.0f, gravity * ball.mass);
        }

        // 2. update positions
        for (auto& ball : balls)
        {
            ball.Update(dt);
        }

        // 3. handle boundary collisions
        for(auto& ball : balls)
        {
            PhysixHelper::HandleBoudaryCollision(ball, width, height);
        }

        // 4. handle ball collisions
        for (size_t i = 0; i < balls.size(); i++)
        {
            for (size_t j = i + 1; j < balls.size(); j++)
            {
                if (PhysixHelper::CheckCollision(balls[i], balls[j]))
                {
                    PhysixHelper::ResolveCollision(balls[i], balls[j]);
                }
            }
        }

        // 5. render the balls
        cleardevice();
        int i = 0;
        for (const auto& ball : balls)        
        {
            setfillcolor(RGB(i, 255, 0)); // green color for the balls
            solidcircle(static_cast<int>(ball.x), static_cast<int>(ball.y), static_cast<int>(ball.radius));
            i += 50;
        }
        Sleep(16); // delay for ~60 FPS

        UpdateDT();
    }
    
    closegraph();
    return 0;
}











