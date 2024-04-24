import open3d as o3d
import numpy as np

# Load the first .ply file
ply1 = o3d.io.read_point_cloud("dragon.ply")
#color1 = [0, 0, 1]  # Red color for pcd1

# Assign color to each point cloud
#ply1.paint_uniform_color(color1)
# Load the second .ply file
#ply2 = o3d.io.read_point_cloud("dragon.ply")
scaling_factor = 1
ply1.points = o3d.utility.Vector3dVector(np.asarray(ply1.points) * scaling_factor)
angle_rad = np.radians(-90)  # 90 degrees CCW

# Create the rotation matrix for 90 degrees CCW rotation around the z-axis
rotation_matrix = np.array([
    [np.cos(angle_rad), -np.sin(angle_rad), 0],
    [np.sin(angle_rad), np.cos(angle_rad), 0],
    [0, 0, 1]
])

# Apply rotation to the second point cloud
ply1.rotate(rotation_matrix, center=(0, 0, 0))

o3d.visualization.draw_geometries([ply1])