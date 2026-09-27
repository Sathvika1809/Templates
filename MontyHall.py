import random
import numpy as np
import matplotlib.pyplot as plt

def simulate_monty_hall(num_trials,num_doors,num_cars):
    wins_stick = 0
    wins_switch = 0
    for _ in range(num_trials):
        winning_doors = random.sample(range(1,num_doors+1),num_cars)
        selected_door = random.randint(1,num_doors)

        if selected_door in winning_doors:
            wins_stick += 1

        losing_doors = [door for door in range(1, num_doors+1) if door not in winning_doors and door != selected_door]
        host_door = random.choice(losing_doors)

        switched_door = [door for door in range(1, num_doors+1) if door != selected_door and door!=host_door][0]

        if switched_door in winning_doors:
            wins_switch += 1
    prob_win_stick = wins_stick/num_trials
    prob_win_switch = wins_switch/num_trials

    return prob_win_stick,prob_win_switch

def plot_surface():
    n_values = np.arange(4,12)
    k_values = np.arange(1,8)
    ratio_matrix = np.zeros((len(n_values),len(k_values)))

    for i,n in enumerate(n_values):
        for j,k in enumerate(k_values):
            if k<n-1:
                prob_win_stick,prob_win_switch = simulate_monty_hall(num_trials,n,k)
                ratio_matrix[i,j] = prob_win_switch/prob_win_stick
            else:
                ratio_matrix[i,j] = float('nan')

    n_mesh, k_mesh = np.meshgrid(n_values, k_values)

    fig = plt.figure(figsize=(12,8))
    ax = fig.add_subplot(111,projection='3d')
    ax.plot_surface(n_mesh.T,k_mesh.T,ratio_matrix,cmap='viridis')
    ax.set_xlabel('Number of doors(n)')
    ax.set_ylabel('Number of cars(k)')
    ax.set_zlabel('Ratio of P(win|Switch) to P(win|Stick)')
    ax.set_title('Monty Hall Simulation: Winning Probability Ratios')
    ax.grid(True, color='grey', linestyle='--')
    plt.show()

if __name__ == "__main__":
    num_trials = 100000
    num_doors = 3
    num_cars = 1
    if num_doors <= num_cars:
        print('Invalid input: Number of cars cannot be greater than number of doors.')
    else:
        probability_win_stick,probability_win_switch = simulate_monty_hall(num_trials,num_doors,num_cars)

        print('Monty Hall Problem with {} doors and {} of the doors having cars'. format(num_doors, num_cars))
        print('Probability of winning with sticking: {:.2f}'.format(probability_win_stick))
        print('Probability of winning with switching: {:.2f}'.format(probability_win_switch))
        print('Ratio of probability for switching to sticking: {:.2f}'.format(probability_win_stick/probability_win_switch))

        plot_surface()
        