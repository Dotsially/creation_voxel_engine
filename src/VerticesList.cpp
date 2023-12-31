#include "vertices_list.h"


f32 VerticesList::verticesCube[6][12] = {
            //front
            {-0.5f,-0.5f,-0.5f, -0.5f,0.5f,-0.5f, 0.5f,0.5f,-0.5f, 0.5f,-0.5f,-0.5f},
            //back
            {-0.5f,-0.5f,0.5f, -0.5f,0.5f,0.5f, 0.5f,0.5f,0.5f, 0.5f,-0.5f,0.5f},
            //left
            {-0.5f,-0.5f,0.5f, -0.5f,0.5f,0.5f, -0.5f,0.5f,-0.5f, -0.5f,-0.5f,-0.5f},
            //right
            {0.5f,-0.5f,0.5f, 0.5f,0.5f,0.5f, 0.5f,0.5f,-0.5f, 0.5f,-0.5f,-0.5f},
            //top
            {-0.5f,0.5f,-0.5f, -0.5f,0.5f,0.5f, 0.5f,0.5f,0.5f, 0.5f,0.5f,-0.5f},
            //bottom
            {-0.5f,-0.5f,-0.5f, -0.5f,-0.5f,0.5f, 0.5f,-0.5f,0.5f, 0.5f,-0.5f,-0.5f}

    };

i32 VerticesList::verticesIntCube[6][12] = {
            //front
            {0,0,0, 0,1,0, 1,1,0, 1,0,0},
            //back
            {0,0,1, 0,1,1, 1,1,1, 1,0,1},
            //left
            {0,0,1, 0,1,1, 0,1,0, 0,0,0},
            //right
            {1,0,1, 1,1,1, 1,1,0, 1,0,0},
            //top
            {0,1,0, 0,1,1, 1,1,1, 1,1,0},
            //bottom
            {0,0,0, 0,0,1, 1,0,1, 1,0,0}

    };

u32 VerticesList::indicesCube[2][6] = 
    {   
        {0,1,2,3,0,2},
        {2,1,0,2,0,3}
    };


f32 VerticesList::verticesEntity1x1[20] = {
    -0.5f,-0.5f, -0.5f,0.5f, 0.5f,0.5f, -0.5f,-0.5f
};

u32 VerticesList::indicesEntity[6] = {
    0,1,2,3,0,2
};