import os
import subprocess
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import tkinter as tk
from tkinter import ttk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

def parse_output_file(file_path):
    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()

            if len(lines) < 1:
                raise ValueError("File is empty or does not contain expected data.")

            metadata = lines[0].strip().split()
            if len(metadata) != 5:
                raise ValueError("Metadata line is not in the expected format.")

            size = int(metadata[0])
            total_steps = int(metadata[1])
            total_neighbors = int(metadata[2])
            time_taken = float(metadata[3])
            is_found = metadata[4] == '1'

            steps = []
            index = 1

            while index < len(lines):
                line = lines[index].strip()
                if line and line.split()[0].isdigit():
                    step_info = line.split()
                    obj_value = int(step_info[1])
                    value1 = int(step_info[2])
                    value2 = int(step_info[3])
                    index += 1

                    matrix = [[[0 for _ in range(size)] for _ in range(size)] for _ in range(size)]

                    for z in range(size):
                        for x in range(size):
                            if index >= len(lines):
                                raise ValueError("Unexpected end of file while reading cube data.")
                            row = list(map(int, lines[index].strip().split()))
                            for y in range(size):
                                matrix[z][x][y] = row[y]
                            index += 1
                    
                    steps.append((matrix, obj_value, value1, value2))
                else:
                    index += 1

            return size, total_steps, total_neighbors, time_taken, is_found, steps

    except FileNotFoundError:
        print(f"Error: File '{file_path}' not found.")
        return None
    except ValueError as ve:
        print(f"Value Error: {ve}")
        return None
    except Exception as e:
        print(f"An error occurred while reading the file: {e}")
        return None

def visualize_cube_step(matrix, obj_value, step_num, value1, value2, ax, canvas):
    ax.clear()
    size = len(matrix)

    for z in range(size):
        for x in range(size):
            for y in range(size):
                ax.text(x, y, z, f"{matrix[z][x][y]}", color='blue', ha='center', va='center', fontsize=10)

    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.set_title(f"Step {step_num}\nObjective Function Value: {obj_value}\nChanges: {value1} <=> {value2}")

    ax.set_xticks(range(size))
    ax.set_yticks(range(size))
    ax.set_zticks(range(size))

    ax.view_init(elev=20, azim=30)
    canvas.draw()

def create_gui(steps, size, total_steps, total_neighbors, time_taken, is_found):
    step_num = 0

    root = tk.Tk()
    root.title("3D Cube Visualization - Steps Navigation")

    info_label = tk.Label(root, text=f"Total Steps: {total_steps}\n"
                                     f"Total Neighbors Evaluated: {total_neighbors}\n"
                                     f"Time Taken: {time_taken:.2f} seconds\n"
                                     f"Optimal Solution Found: {'Yes' if is_found else 'No'}",
                          font=("Helvetica", 12))
    info_label.pack()

    fig = plt.Figure()
    ax = fig.add_subplot(111, projection='3d')
    canvas = FigureCanvasTkAgg(fig, master=root)
    canvas.get_tk_widget().pack()

    def show_step(step_num):
        matrix, obj_value, value1, value2 = steps[step_num]
        visualize_cube_step(matrix, obj_value, step_num, value1, value2, ax, canvas)

    def next_step():
        nonlocal step_num
        if step_num < len(steps) - 1:
            step_num += 1
            show_step(step_num)

    def prev_step():
        nonlocal step_num
        if step_num > 0:
            step_num -= 1
            show_step(step_num)

    # Create navigation buttons
    button_frame = ttk.Frame(root)
    button_frame.pack()
    prev_button = ttk.Button(button_frame, text="Previous", command=prev_step)
    prev_button.grid(row=0, column=0, padx=5)
    next_button = ttk.Button(button_frame, text="Next", command=next_step)
    next_button.grid(row=0, column=1, padx=5)

    show_step(step_num)

    root.mainloop()

def run_algorithm(algorithm, input_file=None):
    try:
        if input_file:
            subprocess.run(['./src/class/main', algorithm, input_file], check=True)
        else:
            subprocess.run(['./src/class/main', algorithm], check=True)

        file_path = 'output.txt'
        result = parse_output_file(file_path)

        if result:
            size, total_steps, total_neighbors, time_taken, is_found, steps = result
            print(f"Cube Size: {size}")
            print(f"Total Steps: {total_steps}")
            print(f"Total Neighbors Evaluated: {total_neighbors}")
            print(f"Time Taken: {time_taken:.2f} seconds")
            print(f"Optimal Solution Found: {'Yes' if is_found else 'No'}\n")

            create_gui(steps, size, total_steps, total_neighbors, time_taken, is_found)
        else:
            print("Failed to parse the output file.")
    except subprocess.CalledProcessError:
        print("Error: Failed to run the algorithm. Please ensure the executable is compiled and available.")

print("Choose your Algorithm:")
print("1. Steepest Ascent Hill-Climbing")
print("2. Stochastic Hill-Climbing")
print("3. Hill-Climbing with Sideways Moves")
print("4. Random Restart Hill-Climbing")
print("5. Simulated Annealing")
print("6. Genetic Algorithm")
option = input("Enter the number corresponding to your choice: ")

algorithm_map = {
    '1': 'SteepestAscent',
    '2': 'Stochastic',
    '3': 'SidewaysMove',
    '4': 'RandomRestart',
    '5': 'SimulatedAnnealing',
    '6': 'GeneticAlgorithm'
}

if option in algorithm_map:
    selected_algorithm = algorithm_map[option]
    
    load_file = input("Do you want to provide an input file for the cube? (y/n): ")
    input_file = None
    
    if load_file.lower() == 'y':
        input_file = input("Enter the input file path (e.g., cube.txt): ")
        if not os.path.exists(input_file):
            print(f"Error: File '{input_file}' not found.")
            input_file = None
        else:
            print(f"Using input file: {input_file}")
    
    run_algorithm(selected_algorithm, input_file)

else:
    print("Invalid choice. Please select a valid option.")
