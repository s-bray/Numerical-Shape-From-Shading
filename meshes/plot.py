import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def load_mesh(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
        vertices = []
        quadrilaterals = []
        read_vertices = False
        read_quadrilaterals = False

        for line in lines:
            line = line.strip()
            if line == "Vertices":
                read_vertices = True
                continue
            elif line == "Quadrilaterals":
                read_vertices = False
                read_quadrilaterals = True
                continue

            if read_vertices:
                parts = line.split()
                if len(parts) >= 3:
                    vertices.append([float(parts[0]), float(parts[1]), float(parts[2])])
            elif read_quadrilaterals:
                parts = line.split()
                if len(parts) >= 4:
                    quadrilaterals.append([int(parts[0]), int(parts[1]), int(parts[2]), int(parts[3])])

    return np.array(vertices), np.array(quadrilaterals)

# Plot the mesh - Scatter Logic
def plot_mesh(vertices, quadrilaterals):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Plot vertices as scatter points
    ax.scatter(vertices[:, 0], vertices[:, 1], vertices[:, 2], c='b', marker='.', s=0.1)  # Adjust the marker size 's' as needed

    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    plt.show()

# Plot the mesh - Wire Logic
# def plot_mesh(vertices, quadrilaterals):
#     fig = plt.figure()
#     ax = fig.add_subplot(111, projection='3d')
    
#     # Plot vertices
#     # ax.scatter(vertices[:, 0], vertices[:, 1], vertices[:, 2], c='r', marker='.')
    
#     # Plot quadrilaterals wireframe
#     for quad in quadrilaterals:
#         x = [vertices[quad[0]-1, 0], vertices[quad[1]-1, 0], vertices[quad[2]-1, 0], vertices[quad[3]-1, 0], vertices[quad[0]-1, 0]]
#         y = [vertices[quad[0]-1, 1], vertices[quad[1]-1, 1], vertices[quad[2]-1, 1], vertices[quad[3]-1, 1], vertices[quad[0]-1, 1]]
#         z = [vertices[quad[0]-1, 2], vertices[quad[1]-1, 2], vertices[quad[2]-1, 2], vertices[quad[3]-1, 2], vertices[quad[0]-1, 2]]
#         ax.plot(x, y, z, c='b', linestyle='-', linewidth=0.2)
    
#     ax.set_xlabel('X')
#     ax.set_ylabel('Y')
#     ax.set_zlabel('Z')
#     plt.show()

def main():
    filename = "vase2.mesh"  # Replace with your mesh file
    vertices, quadrilaterals = load_mesh(filename)
    plot_mesh(vertices, quadrilaterals)

if __name__ == "__main__":
    main()
