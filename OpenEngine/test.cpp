#pragma once

#include "Application.h"
#include "Mesh.h"
using namespace OpenEngine;
int main() {
    App::Application app("D:/Project/OETest");
    std::vector<Vertex> testVertexs;
    Vertex temp;
    temp.position = Vec3(0.2f, 0.4f, 0.6f);
    temp.normal = Vec3(0.0f, 1.0f, 0.0f);
    temp.texCoords = Vec2(1.0f, 0.0f);
    testVertexs.push_back(temp);
    testVertexs.push_back(temp);
    testVertexs.push_back(temp);
    std::vector<uint32_t> testElement;
    testElement.push_back(0);
    testElement.push_back(1);
    testElement.push_back(2);
    Mesh testMesh(testVertexs, testElement);
    app.Run();
    return 0;
}