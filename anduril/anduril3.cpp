#include <iostream>

 

// Math layer

struct Vector2D {

    double x;

    double y;

    Vector2D operatorplus(Vector2D other){return{x + other.x, y +other.y};}

    Vector2D operatorminus(Vector2D other){return{x - other.x, y-other.y};}

    Vector2D operatortimes(Vector2D other){return{x * other.x, y*other.y};}

    Vector2D operatortimes(double k){return{k * x, k * y};}

    Vector2D operatordivide(double k){return{k / x, k / y};

    }

};

 

// Physical Layer

class Drone {

    private:

    public:

        double mass;

        Vector2D position;

        Vector2D velocity;

};

 

// Physics / Data processing layers

class PIDController {

    private:

        double kp;

        double kd;

        double ki;

        Vector2D prev_error;

        Vector2D error;

        Vector2D integral_error;

    public:

 

    Vector2D get_control_effort(Drone drone, Drone target_drone){

        // Porportional control

        Vector2D error = target_drone.position.operatorminus(drone.position);

        Vector2D cp = error.operatortimes(kp);

 

        // Integral control

        integral_error = integral_error.operatorplus(error);

        Vector2D ci = integral_error.operatortimes(ki);

 

        // Derivative control

        Vector2D derivative_error = error.operatorminus(prev_error);

        Vector2D cd = derivative_error.operatortimes(kd);

 

        prev_error = error;

       

        return cp.operatorplus(ci.operatorplus(cd));

    };

 

};

 

class Integrator {

    public:

        void update_position(Drone& drone, Vector2D commanded_control_effort, double dt){

            // Calculate acceleration (F = ma)

            Vector2D acc = commanded_control_effort.operatordivide(drone.mass);

            // update velocity with euler's method of integration

            drone.velocity = drone.velocity.operatorplus(acc.operatortimes(dt));

            // update position with velocity and dt

            drone.position = drone.position.operatorplus(drone.velocity.operatortimes(dt));

    }

};

 

int main() {

    double dt = 0.01;

    double tf = 5;

    Drone drone;

    Drone target_drone;

    PIDController controller;

    Integrator integrator;

 

    for (double i = 0; i <= tf; i+= dt){

        // Calculate control effort

        Vector2D commanded_control_effort = controller.get_control_effort(drone, target_drone);

        // Update position of the drone

        integrator.update_position(drone, commanded_control_effort, dt);

        // Print out what we find

        std::cout << "Time: " << i << ", Position: " << drone.position;

    }

    return 0;

}