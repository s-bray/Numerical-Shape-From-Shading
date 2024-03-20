#include "../include/matrix.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Helper function to create PLY text from vertices and faces
std::string _make_ply_txt(const std::vector<std::vector<float>>& vertices, const std::vector<std::vector<int>>& faces) {
    std::string header_lines[] = {"ply", "format ascii 1.0", "element vertex " + std::to_string(vertices.size()),
                                  "property float x", "property float y", "property float z",
                                  "element face " + std::to_string(faces.size()),
                                  "property list uchar int vertex_indices", "end_header"};
    std::string header = "";
    for (const auto& line : header_lines) {
        header += line + "\n";
    }

    std::string data_lines = "";
    for (const auto& vertex : vertices) {
        data_lines += std::to_string(vertex[0]) + " " + std::to_string(vertex[1]) + " " + std::to_string(vertex[2]) + "\n";
    }
    for (const auto& face : faces) {
        data_lines += std::to_string(face.size());
        for (const auto& index : face) {
            data_lines += " " + std::to_string(index);
        }
        data_lines += "\n";
    }

    return header + data_lines;
}

// Saves matrix heights to mesh file and PLY file
void matrixToMesh(const string& fichier, const Matrix& M) {
    ofstream mesh(fichier);
    mesh << endl;
    mesh << "MeshVersionFormatted" << endl;
    mesh << "1" << endl;
    mesh << endl;
    mesh << "Dimension" << endl;
    mesh << 3 << endl;
    mesh << endl;
    mesh << "Vertices" << endl;
    mesh << (M.n) * (M.m) << endl;

    std::vector<std::vector<float>> vertices;
    for (int j = 0; j < M.m; j++) {
        for (int i = 0; i < M.n; i++) {
            mesh << i << " " << j << " " << M.val[i][j] << " " << 0 << endl;
            vertices.push_back({static_cast<float>(i), static_cast<float>(j), static_cast<float>(M.val[i][j])});
        }
    }
    mesh << endl;
    mesh << "Quadrilaterals" << endl;
    mesh << (M.m - 1) * (M.n - 1) << endl;

    std::vector<std::vector<int>> faces;
    for (int j = 0; j < M.m - 1; j++) {
        for (int i = 0; i < M.n - 1; i++) {
            mesh << j * M.n + i + 1 << " " << j * M.n + i + 2 << " " << (j + 1) * M.n + i + 2 << " " << (j + 1) * M.n + i + 1 << " " << 0 << endl;
            faces.push_back({j * M.n + i + 1, j * M.n + i + 2, (j + 1) * M.n + i + 2, (j + 1) * M.n + i + 1});
        }
    }

    // Save as PLY file
    string ply_path = fichier.substr(0, fichier.find_last_of('.')) + ".ply";
    ofstream ply_file(ply_path);
    ply_file << _make_ply_txt(vertices, faces);
}