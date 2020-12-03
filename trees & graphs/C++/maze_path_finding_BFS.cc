/**
 * @file maze_path_finding.cc
 * @author Hongyu Ding
 * @brief This program finds a path in a maze using BFS
 * @version 0.1
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using Maze = std::vector<std::string>;
using Coor = std::pair<int, int>;
using Path = std::vector<Coor>;

const Path dir = {
    {-1, 0},    // up
    {0, -1},    // left
    {1, 0},     // down
    {0, 1}      // right
};

Path findPath(Maze maze, Coor start, Coor end) {
    Path path;
    Path queue;
    std::vector<int> from;
    int front = 0, tail = 1;
    queue.push_back(start);
    from.push_back(-1);
    maze[start.first][start.second] = '#';
    while (front < tail) {
        if (queue[front] == end) {
            int index = front;
            while (index != -1) {
                path.push_back(queue[index]);
                index = from[index];
            }
            std::reverse(path.begin(), path.end());
            break;
        } 
        for (int i = 0; i < 4; i ++) {
            int x = queue[front].first + dir[i].first;
            int y = queue[front].second + dir[i].second;
            if (0 <= x && x < maze.size() && 0 <= y && y < maze[0].size() && maze[x][y] != '#') {
                queue.push_back({x, y});
                from.push_back(front);
                tail ++;
            }
        }
        front ++;
    }
    return path;
}

int main() {
    int N, M;
    Maze maze;
    std::string line;
    std::cout << "How many rows of the maze?" << std::endl;
    std::getline(std::cin, line);
    N = std::stoi(line);
    std::cout << "How many columns of the maze?" << std::endl;
    std::getline(std::cin, line);
    M = std::stoi(line);
    std::cout << "Please input the maze:" << std::endl;
    std::cout << "# for wall\n- for path\nS for start\nE for end" << std::endl;
    Coor start, end;
    for (int i = 0; i < N; i ++) {
        std::getline(std::cin, line);
        maze.push_back(line);
        for (int j = 0; j < M; j ++) {
            if (maze[i][j] == 'S') {
                start = {i, j};
            } else if (maze[i][j] == 'E') {
                end = {i, j};
            }
        }
    }

    Path path = findPath(maze, start, end);

    if (path.empty()) {
        std::cout << "cannot reach the end" << std::endl;
    } else {
        std::cout << "(" << path[0].first << ", " << path[0].second << ")";
        for (int i = 1; i < path.size(); i ++) {
            std::cout << " -> (" << path[i].first << ", " << path[i].second << ")";
        }
        std::cout << std::endl;
    }

    return 0;
}