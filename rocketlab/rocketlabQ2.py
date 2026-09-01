## Interview question 2: Mass spring damper system
## Next steps: Make unified function for running the sim,
## make more efficent parameter tracability
import csv
import numpy as np

##############################
## Runge-Kutta 4 Integrator ##
##############################
def rk4_integrator(state,dt,k,m): # Runge-Kutta 4 integrator
    k1 = dt * system_dynamics(state, k,m)
    k2 = dt * system_dynamics(state + 0.5 * k1,k,m)
    k3 = dt * system_dynamics(state + 0.5 * k2,k,m)
    k4 = dt * system_dynamics(state + k3, k,m)
    return state + (k1 + 2 * k2 + 2 * k3 + k4) / 6

#####################
## Spring Dynamics ##
#####################
def system_dynamics(state,k,m): # Spring dynamics 
    pos = state[0]
    vel = state[1]
    if(pos < 0):
        return np.array([vel,-1*k*pos/m])
    else:
        return np.array([vel,0])

##########################
## Initalize Parameters ##
##########################
mass = 12
dt = 0.01
MC = True
xi = [-0.15312, 0] # initial state vector
k = 182

if (MC):  ## Monte Carlo to find the right spring constant
  k = 1
  with open('simulation_results.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Final Vel (m/s)', 'K Constant'])
    while k < 500:
      t = 0
      x = xi
      while t < 5:
        newx = rk4_integrator(x, dt, k, mass)
        t += dt
        x = newx
      writer.writerow([x[1], k])
      print(f"V final: {x[1]}, K = {k}")
      k += 0.1
  # Answer from CSV: K = 182!

else: ## Monte Carlo Disabled - Single Run to probe points
  t = 0
  x = xi
  while t < 5:
    newx = rk4_integrator(x, dt, k, mass)
    t += dt
    x = newx
  print(f"Payload Mass: {mass}, V final: {x[1]}, K = {k}")