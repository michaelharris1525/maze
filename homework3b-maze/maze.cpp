#include <iostream>
using namespace std;
#include <string>
#include <sstream>
#include <fstream>
#include <array>
#include <random>
#include "Grid.h"

bool find_path(Grid &maze, vector<string> &path, int row, int col, int depth) {
    path.push_back(to_string(row) + " " + to_string(col) + " " + to_string(depth));
    

    if(row == maze.height() - 1 && col == maze.width() - 1 && depth == maze.depth() - 1) {
        // cout << "BASE CAE TRUE\n";
        return true;
    }
    //if out of bounds
    if(row < 0 || row == maze.height() || col < 0 || col == maze.width() || depth < 0 || depth == maze.depth()) {
        path.pop_back();
        // cout<< "you screwed up, out of bounds\n";
        return false;
    }
    //check to see if on the path, if off, then that step is not valid
    if(maze.at(row, col, depth) == 0 || maze.at(row, col, depth) == 2){
        // cout << "you are not on the path" << endl;
        path.pop_back();
        return false;
    }
    maze.at(row, col, depth) = 2;

    bool forward = find_path(maze, path, row + 1, col, depth);

    bool right = find_path(maze, path, row, col + 1, depth);

    bool up = find_path(maze, path, row, col, depth + 1);
    
    bool backward = find_path(maze, path, row - 1, col, depth);

    bool left = find_path(maze, path, row, col - 1, depth);

    bool down = find_path(maze, path, row, col, depth - 1);

    if(left || right || up || down || forward || backward) {
        // cout << "RL YES\n";
        return true;
    }
    else {
        path.pop_back();
        // cout<< "you are left, right, up , down, forward, etc.\n";
        return false;
    }
}
int main(int argc, char* argv[]) {
    // Write your code here]
    //    //Import Maze
    Grid maze;
    vector<string> path;
    string input_file = argv[1];
    string output_file = argv[2];
    ifstream fin(input_file);
    ofstream end(output_file);

    fin >> maze;

    bool solved_maze = find_path(maze, path, 0, 0, 0);

    if(solved_maze == true) {
        end << "SOLUTION\n";
        for(auto step : path) {
            end << step << endl;
    }
    }

    else {
        end << "NO SOLUTION\n";
        // end << maze.width();
    }














//    cout << argv[1] << std::endl;
//    cout << argv[2] << std::endl;
//    string inputfile_name = argv[1];
//    string outputfile_name = argv[2];
//    ifstream inputFile(inputfile_name);
//    ofstream outputFile(outputfile_name);
//
//    int width_count = 0;
//    int height_count = 0;
//    int depth_count = 0;
//
//    int width = 5;
//    int height = 5;
//    int depth = 5;
//    int your_maze[width][height][depth];
//    stringstream maze;



//    fin >> maze;
//
//    //making a Random Maze
//    for(int i = 0; i < depth; i++) {
//        //counting the width, the height, and the depth in order to make it solveable
//        width_count++;
//        height_count++;
//        depth_count++;
//        for(int j = 0; j < height; j++) {
//            for(int k = 0; k < width; k++) {
//                your_maze[i][j][k] = rand()%2;
//                maze << your_maze[i][j][k] << " ";
//            }
//            //add a newline after each row or height
//            maze << endl;
//        }
//        //add a newline after each depth
//        maze << endl;
//    }
////    to make maze solvable
//    your_maze[0][0][0] = 1;
//    your_maze[width_count][height_count][depth_count] = 1;
//
//    cout << maze.str();
//
//
//
//    inputFile.close();
//    outputFile.close();
    return 0;
}
