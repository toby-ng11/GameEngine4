#include "MaterialHandler.h"

unique_ptr<MaterialHandler> MaterialHandler::materialInstance = nullptr;
vector<Material> MaterialHandler::materials = vector<Material>();

MaterialHandler::MaterialHandler()
{
    materials.reserve(20);
}

MaterialHandler::~MaterialHandler()
{
    OnDestroy();
}

MaterialHandler* MaterialHandler::GetInstance()
{
    if (materialInstance.get() == nullptr) {
        materialInstance.reset(new MaterialHandler);
    }
    return materialInstance.get();
}

void MaterialHandler::AddMaterial(Material mat_)
{
    materials.push_back(mat_);
}

const Material MaterialHandler::GetMaterial(const string& matName_) const
{
    for (auto mat : materials) {
        if (mat.name == matName_) { // check if mat exist
            return mat;
        }
    }
    return Material();
}

void MaterialHandler::OnDestroy()
{
    if (materials.size() > 0) {
        materials.clear();
    }
}


