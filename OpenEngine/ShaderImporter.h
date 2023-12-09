#include "IAssetImporter.h"
#include "Shader.h"
#include <fstream>
#include <sstream>

namespace OpenEngine::Importer {
	class ShaderImporter : public IAssetImporter {
	public:
		ShaderImporter() {
			supported_extensions.push_back(".shader");
		}
		std::vector<int> Import(std::string path, const Setting::ImportSetting& importSetting) {
			std::ifstream ist(path);
			std::string line;
			std::stringstream frag, vert;
			int tag = -1;
			while (std::getline(ist, line)) {
				if (line.find("#shader") != std::string::npos) {
					if (line.find("vert") != std::string::npos) tag = 0;
					else if (line.find("frag") != std::string::npos) tag = 1;
				}
				else if (tag != -1) {
					if (tag == 0) vert << line << '\n';
					else frag << line << '\n';
				}
			}
			Shader* shader = new Shader(vert.str(), frag.str());
			shader->name = importSetting.GetProperty("name");
			OE_INFO(path + " imported");
			std::vector<int> ret;
			ret.push_back(shader->GetInstanceID());
			return ret;
		}
		Setting::ImportSetting GetDefaultSetting() {
			Setting::ImportSetting setting;
			setting.SetProperty("type", "Shader");
			return setting;
		}
	};
}