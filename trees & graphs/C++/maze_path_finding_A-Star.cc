/**
 * @file maze_path_finding_A-Star.cc
 * @author Hongyu Ding
 * @brief This program finds the shortest path using A Star Algorithm
 * @version 0.1
 * @date 2020-12-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <limits>
#include <math.h>
#include <memory>

// graphical output
namespace Graphics {
    // colors
    const int BLACK =      0;
    const int RED =        1;
    const int GREEN =      2;
    const int YELLOW =     3;
    const int BLUE =       4;
    const int MAGENTA =    5;
    const int CYAN =       6;
    const int WHITE =      7;
    // font settings
    const int FONT_RESET =          0;
    const int FONT_BOLD =           1;
    const int FONT_UNDERLINE =      4;
    const int FONT_INVERSE =        7;
    const int FONT_BOLD_OFF =       21;
    const int FONT_UNDERLINE_OFF =  24;
    const int FONT_INVERSE_OFF =    27;
    
    void renderCh(char ch, int fore, int back, bool bold, bool underline) {
        std::string setting = "\033[3" + std::to_string(fore) + ";4" + std::to_string(back);
        if (bold) {
            setting += (";" + std::to_string(FONT_BOLD));
        }
        if (underline) {
            setting += (";" + std::to_string(FONT_UNDERLINE));
        }
        setting += 'm';
        std::string reset = "\033[" + std::to_string(FONT_RESET) + "m";
        std::string output = setting + ch + reset;
        std::cout << output;
    }

    void draw(int color) {
        renderCh(' ', WHITE, color, false, false);
    }

    class Buffer {
        struct Info {
            int fore;
            int back;
            char ch;
        };
        std::vector<std::vector<Info>> buffer;
    public:
        Buffer(int N, int M) {
            buffer = std::vector<std::vector<Info>>(N);
            for (int i = 0; i < N; i ++) {
                buffer[i] = std::vector<Info>(M);
                for (int j = 0; j < M; j ++) {
                    buffer[i][j] = {BLACK, WHITE, ' '};
                }
            }
        }

        void setCh(int x, int y, char ch, int fore, int back) {
            if (0 <= x && x < buffer.size() && 0 <= y && y < buffer[0].size()) {
                buffer[x][y].ch = ch;
                buffer[x][y].fore = fore;
                buffer[x][y].back = back;
            }
        }

        void setFore(int x, int y, int fore) {
            if (0 <= x && x < buffer.size() && 0 <= y && y < buffer[0].size()) {
                buffer[x][y].fore = fore;
            }
        }

        void setBack(int x, int y, int back) {
            if (0 <= x && x < buffer.size() && 0 <= y && y < buffer[0].size()) {
                buffer[x][y].back = back;
            }
        }

        void clear() {
            for (auto& line : buffer) {
                for (auto& cell : line) {
                    cell.fore = BLACK;
                    cell.back = WHITE;
                    cell.ch = ' ';
                }
            }
        }

        void render() {
            for (auto& line : buffer) {
                for (auto& cell : line) {
                    renderCh(cell.ch, cell.fore, cell.back, false, false);
                }
                std::cout << std::endl;
            }
        }
    };
};

using namespace Graphics;

class Maze {
    struct Coord {
        int x = 0;  // row index
        int y = 0;  // col index
    };

    const std::vector<Coord> dir = {
        {-1, 0},    // up
        {0, -1},    // left
        {1, 0},     // down
        {0, 1}      // right
    };

    struct Node {
        Coord coord;
        bool isWall = false;
        bool visited = false;
        double global_goal;
        double local_goal;
        std::shared_ptr<Node> parent;   // parent in the shortest path
        std::vector<std::shared_ptr<Node>> neighbors;
    };

    int N, M;
    std::vector<std::vector<std::shared_ptr<Node>>> maze;

    double distance(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2) {
        return sqrt((node1->coord.x - node2->coord.x) * (node1->coord.x - node2->coord.x)
                    + (node1->coord.y - node2->coord.y) * (node1->coord.y - node2->coord.y));
    }

    std::shared_ptr<Buffer> buffer;
    std::shared_ptr<Node> start;
    std::shared_ptr<Node> end;

public:
    Maze(int rows, int cols) : N{rows}, M{cols} {
        maze = std::vector<std::vector<std::shared_ptr<Node>>>(N);
        for (int i = 0; i < N; i ++) {
            maze[i] = std::vector<std::shared_ptr<Node>>(M);
            for (int j = 0; j < M; j ++) {
                maze[i][j] = std::make_shared<Node>();
            }
        }
        for (int i = 0; i < N; i ++) {
            for (int j = 0; j < M; j ++) {
                maze[i][j]->coord = {i, j};
                maze[i][j]->isWall = false;
                maze[i][j]->parent = nullptr;
                maze[i][j]->visited = false;
                maze[i][j]->global_goal = INFINITY;
                maze[i][j]->local_goal = INFINITY;
                for (int k = 0; k < 4; k ++) {
                    int x = maze[i][j]->coord.x + dir[k].x;
                    int y = maze[i][j]->coord.y + dir[k].y;
                    if (validCoord({x, y})) {
                        maze[i][j]->neighbors.emplace_back(maze[x][y]);
                    }
                }
            }
        }
        buffer = std::make_shared<Buffer>(N, M);
        start = maze[0][0];
        end = maze[N-1][M-1];
    }

    bool validCoord(Coord coord) {
        return (0 <= coord.x && coord.x < N && 0 <= coord.y && coord.y < M);
    }

    void setWall(int x, int y) {
        if (validCoord({x, y})) {
            maze[x][y]->isWall = true;
        }
    }

    void setPath(int x, int y) {
        if (validCoord({x, y})) {
            maze[x][y]->isWall = false;
        }
    }

    void draw() {
        buffer->clear();
        for (int i = 0; i < N; i ++) {
            for (int j = 0; j < M; j ++) {
                char content = ' ';
                int fore = BLACK;
                int back = WHITE;
                if (maze[i][j]->isWall) {
                    back = MAGENTA;
                }
                if (maze[i][j]->visited) {
                    back = BLUE;
                }
                if (maze[i][j] == start) {
                    content = 'S';
                    fore = BLACK;
                    back = GREEN;
                } else if (maze[i][j] == end) {
                    content = 'E';
                    fore = WHITE;
                    back = RED;
                }
                buffer->setCh(i, j, content, fore, back);
            }
        }
        // draw path
        if (end) {
            std::shared_ptr<Node> node = end->parent;
            while (node && node->parent) {
                buffer->setBack(node->coord.x, node->coord.y, YELLOW);
                node = node->parent;
            }
        }

        buffer->render();
    }

    void setStart(int x, int y) {
        if (validCoord({x, y})) {
            start = maze[x][y];
        }
    }

    void setEnd(int x, int y) {
        if (validCoord({x, y})) {
            end = maze[x][y];
        }
    }

    void clearSolution() {
        for (int i = 0; i < N; i ++) {
            for (int j = 0; j < M; j ++) {
                maze[i][j]->visited = false;
                maze[i][j]->global_goal = INFINITY;
                maze[i][j]->local_goal = INFINITY;
                maze[i][j]->parent = nullptr;
            }
        }
    }

    /**
     * @brief findPath uses A Star Algorithm to 
     * find the shortest path from start to end
     * O(|E|) where |E| is the number of edges
     * 
     */
    void findPath() {
        clearSolution();

        std::shared_ptr<Node> node = start;
        start->local_goal = 0.0f;
        start->global_goal = distance(start, end);

        std::list<std::shared_ptr<Node>> notTested;
        notTested.push_back(start);

        while (!notTested.empty() && node != end) {
            notTested.sort([](const std::shared_ptr<Node> a, const std::shared_ptr<Node> b) 
                            {return a->global_goal < b->global_goal; });
            while (!notTested.empty() && notTested.front()->visited) {
                notTested.pop_front();
            }
            if (notTested.empty()) {
                break;
            }
            node = notTested.front();
            node->visited = true;
            for (auto neighbor : node->neighbors) {
                if (!neighbor->visited && !neighbor->isWall) {
                    notTested.push_back(neighbor);
                }
                double temp = node->local_goal + distance(node, neighbor);
                if (temp < neighbor->local_goal) {
                    neighbor->parent = node;
                    neighbor->local_goal = temp;
                    neighbor->global_goal = neighbor->local_goal + distance(neighbor, end);
                }
            }
        }
    }
};

int main() {
    int N, M;
    std::cout << "How many rows of the maze?" << std::endl;
    std::cin >> N;
    std::cout << "How many columns of the maze?" << std::endl;
    std::cin >> M;
    Maze maze(N, M);
    maze.draw();
    std::cout << "commands:" << std::endl;
    bool loop = true;
    while (loop) {
        char command;
        std::cin >> command;
        switch (command) {
            case 's': {     // set start position
                int x, y;
                std::cin >> x >> y;
                maze.setStart(x, y);
                maze.findPath();
                maze.draw();
                break;
            }
            case 'e': {     // set end position
                int x, y;
                std::cin >> x >> y;
                maze.setEnd(x, y);
                maze.findPath();
                maze.draw();
                break;
            }
            case 'w': {     // set wall
                int x, y;
                std::cin >> x >> y;
                maze.setWall(x, y);
                maze.findPath();
                maze.draw();
                break;
            }
            case 'p': {     // set path
                int x, y;
                std::cin >> x >> y;
                maze.setPath(x, y);
                maze.findPath();
                maze.draw();
                break;
            }
            case 'c': {     // clear solution
                maze.clearSolution();
                maze.draw();
                break;
            }
            case 'q': {     // quit the program
                loop = false;
                break;
            }
        }
    }

    return 0;
}