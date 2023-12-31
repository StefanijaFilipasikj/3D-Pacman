//
// Created by drist on 8/28/2023.
//

#ifndef OPENGLPRJ_GHOST_H
#define OPENGLPRJ_GHOST_H
#include <OpenGLPrj.hpp>
#include "Bfs.h"
#include "cmath"

class Ghost{
private:
    BFS algorithm;
    float moved;
    glm::vec3 moveToPosition;
    glm::vec3 positionBeforeMove;
    vector<int> path;

public:
    glm::vec3 position;
    bool isScared;
    float rotation;

    Ghost(glm::vec3 pos, int V){
        positionBeforeMove = pos;
        moveToPosition = pos;
        moved = 1;
        position = pos;
        algorithm = BFS(V);
        isScared=false;
    }

    void move(float deltaTime, int dest){
        if(path.size()!=0){

            moveToPosition.x = path[0]%cols;
            moveToPosition.z = path[0]/cols;
            moved += deltaTime;

            position.x += (moveToPosition.x - positionBeforeMove.x)*deltaTime;
            position.z += (moveToPosition.z - positionBeforeMove.z)*deltaTime;

            if(moveToPosition.x - positionBeforeMove.x != 0){
                if(moveToPosition.x - positionBeforeMove.x > 0)
                    rotation = 90.0f;
                else rotation = 270.0f;
            }
            if(moveToPosition.z - positionBeforeMove.z != 0){
                if(moveToPosition.z - positionBeforeMove.z > 0)
                    rotation = 0.0f;
                else rotation = 180.0f;
            }
        }else{
            moved = 1;
        }
        if(moved >= 1){
            positionBeforeMove = moveToPosition;
            position = moveToPosition;
            moved = 0;
            if(!isScared){
                path = algorithm.get_path(positionBeforeMove.x + positionBeforeMove.z*cols, dest);
            }else{
                path = vector<int>();
                path.push_back(algorithm.getRunningPath(positionBeforeMove.x + positionBeforeMove.z*cols,dest));
            }

        }
    }
};

#endif //OPENGLPRJ_GHOST_H
