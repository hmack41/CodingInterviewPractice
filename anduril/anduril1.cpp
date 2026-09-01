#include <iostream>
#include <vector>
#include <cmath>

struct Vector2D {
    double x, y;
};

class Target {
public:
    Vector2D pos;
    Vector2D vel;
    
    void update(double dt) {
        pos.x += vel.x * dt;
        pos.y += vel.y * dt;
    }
};

class Simulation {
private:
    Target target;
    Vector2D sensorPos{0.0, 0.0};
    double radius;
    double dt;
    bool isAlerting = false;

public:
    Simulation(Target t, double r, double timeStep) 
        : target(t), radius(r), dt(timeStep) {}

    void run(double totalTime) {
        for (double t = 0; t < totalTime; t += dt) {
            target.update(dt);
            double dist = std::hypot(target.pos.x - sensorPos.x, target.pos.y - sensorPos.y);
            
            if (dist <= radius && !isAlerting) {
                isAlerting = true;
                std::cout << "[" << t << "s] ALERT: Target entered radius. Dist: " << dist << "\n";
            } else if (dist > radius && isAlerting) {
                isAlerting = false;
                std::cout << "[" << t << "s] CLEAR: Target left radius. Dist: " << dist << "\n";
            }
        }
    }
};

int main() {
    Target t{{-10.0, 0.0}, {2.0, 0.0}}; // Starts at x=-10, moves right at 2 units/sec
    Simulation sim(t, 5.0, 0.1);         // Alert radius 5, time step 0.1s
    sim.run(10.0);                       // Run for 10 seconds
    return 0;
}
