#pragma once

#include "IAssetImporter.h"
#include "Texture.h"
#include "stb_image.h"

namespace OpenEngine::Importer {

	class TextureImporter : public IAssetImporter {
	public:
		TextureImporter() {
			supported_extensions.push_back(".png");
			supported_extensions.push_back(".jpg");
		}
		std::vector<int> Import(std::string path, const Setting::ImportSetting& importSetting) {
			int width, height, nrChannels;
			unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
			TextureFormat format = RGB;
			if (nrChannels == 1) {
				format = GRAY;
			}
			else if (nrChannels == 3) {
				format = RGB;
			}
			else if (nrChannels == 4){
				format = RGBA;
			}
			else {
				OE_ERROR("Import " + path + " error : unknown format");
				return std::vector<int>();
			}
			Texture* tex = new Texture(width, height, format, importSetting.GetPropertyBool("useMipmap"));
			tex->name = importSetting.GetProperty("name");
			tex->wrapU = (TextureWrapMode)importSetting.GetPropertyInt("wrapU");
			tex->wrapV = (TextureWrapMode)importSetting.GetPropertyInt("wrapV");
			tex->minFilter = (TextureFilterMode)importSetting.GetPropertyInt("minFilter");
			tex->minFilter = (TextureFilterMode)importSetting.GetPropertyInt("magFilter");
			tex->m_raw = data;
			tex->Apply();
			OE_INFO(path + " imported");
			stbi_image_free(data);
			std::vector<int> ret;
			ret.push_back(tex->GetInstanceID());
			return ret;
		}
		Setting::ImportSetting GetDefaultSetting() {
			Setting::ImportSetting setting;
			setting.SetProperty("type", "Texture");
			setting.SetProperty("maxWidth", 4096);
			setting.SetProperty("maxHeight", 4096);
			setting.SetProperty("wrapU", REPEAT);
			setting.SetProperty("wrapV", REPEAT);
			setting.SetProperty("minFilter", LINEAR_MIPMAP_LINEAR);
			setting.SetProperty("magFilter", LINEAR);
			setting.SetProperty("useMipmap", "true");
			return setting;
		}
	};
}