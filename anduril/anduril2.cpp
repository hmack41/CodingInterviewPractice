// Drone altitude controller

#include <iostream>
#include <vector>
#include <cmath>

class PIDController {
private:
    double kp,ki,kd;
    double integral = 0.0;
    double prev_error = 0.0;

public:
    PIDController(double p, double i, double d) : kp(p), ki(i), kd(d) {}

    double calculate(double setpoint, double current_value, double dt) {
        double error = setpoint - current_value;

        // 1. Porportional term
        double p_out = kp * error;

        // 2. Integral term
        integral += error * dt; 
        double i_out = ki *integral;

        // 3. Derivative Term (rate of change of error)
        double derivative = (error - prev_error) / dt;
        double d_out = kd * derivative;

        prev_error = error;

        // Total control effort
        return p_out + i_out + d_out; 
    }
};


class Drone {
public:
    double altitude = 0.0;
    double velocity = 0.0;
    const double mass = 1.5;
    const double gravity = 9.81;

    void update(double thrust_force, double dt) {
        double net_force = thrust_force - (mass * gravity);
        double acceleration = net_force / mass;

        velocity += acceleration * dt;
        altitude += velocity * dt;

        // Ground collision constraint
        if (altitude < 0.0) {
            altitude = 0.0;
            velocity = 0.0;
        }
    }
};

int main() {
    Drone drone;

    PIDController pid(15.0,2.5,8.0);

    double target_altitude = 50.0;
    double dt = 0.05;
    double total_time = 5.0;

    std::cout << "Time(s), Altitude(m), Thrust(N)\n";
    for (double t = 0; t < total_time; t += dt) {
        // 1. Read current state and get controller decision
        double thrust = pid.calculate(target_altitude, drone. altitude, dt);

        // Actuator Limit: drone motors can't provid negative thrust or infinite thrust
        thrust = std::max(0.0, std::min(thrust, 50.0));

        // 2. Step the physical world forward
        drone.update(thrust,dt);

        // Print output to verify convergence
        if (std::abs(static_cast<int>(t*100)%50) == 0 {
            std::cout << t << "s, " << drone.altitude << "m, " << thrust << "N\n";
        }
    }
    return 0;
};