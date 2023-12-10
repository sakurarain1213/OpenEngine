#pragma once

#include "Application.h"
#include "Material.h"
#include <iostream>
using namespace OpenEngine;
int main() {
    App::Application app("D:/Project/OETest");
    
    Material* mat = OESERVICE(Editor::AssetDatabase).GetAsset<Material>(GUID("f41e3dd0-fce5-4043-b723-1eea0f9fa823"), 0);
    
    app.Run();
    return 0;
}