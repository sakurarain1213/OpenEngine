#pragma once

#include "Application.h"
#include "Material.h"
#include <iostream>
using namespace OpenEngine;
int main() {
    App::Application app("D:\\Project\\OETest");

    GLint uniformBufferOffsetAlign = 0;
    glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &uniformBufferOffsetAlign);
    OE_LOG(std::to_string(uniformBufferOffsetAlign));

    Editor::AssetDatabase& assets = OESERVICE(Editor::AssetDatabase);
    
    //assets.CreateAsset("standard.material");
    //Material* mat = assets.GetAsset<Material>("standard.material", 0);
    //Shader* shader = assets.GetAsset<Shader>("standard.shader", 0);
    //Texture* tex = assets.GetAsset<Texture>(GUID("5403deab-728c-4a70-8aa2-f66433b8e237"), 0);
    //mat->SetShader(shader);
    //mat->SetUniform("diffuseMap", tex);
    //assets.Save(mat);
    Entity* model = assets.GetAsset<Entity>(GUID("f083afbb-ef5c-496c-bfb7-d1575868d447"), 0);
    OE_LOG(std::to_string((size_t)model));
    model->SetWorld(&OESERVICE(World));
    app.Run();
    return 0;
}