#pragma once

#include "Application.h"
#include "Material.h"
#include <iostream>
using namespace OpenEngine;
int main() {
    App::Application app("D:\\Project\\OETest");

    //Editor::AssetDatabase& assets = OESERVICE(Editor::AssetDatabase);
    
    //assets.CreateAsset("standard.material");
    //Material* mat = assets.GetAsset<Material>("standard.material", 0);
    //Shader* shader = assets.GetAsset<Shader>("standard.shader", 0);
    //Texture* tex = assets.GetAsset<Texture>(GUID("5403deab-728c-4a70-8aa2-f66433b8e237"), 0);
    //mat->SetShader(shader);
    //mat->SetUniform("diffuseMap", tex);
    //assets.Save(mat);

    app.Run();
    return 0;
}