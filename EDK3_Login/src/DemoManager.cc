#include "DemoManager.h"


DemoManager::DemoManager()
{
}

DemoManager::~DemoManager()
{
}

/*void DemoManager::LightManager() {
	static float directional_light_dir[]{ -1.0f, 0.2f, 0.0f };
	static float directional_light_color[]{ 0.8f, 0.7f, 0.1f };

	ImGui::Begin("LIGHT MANAGER");

	ImGui::Text("Directional Light");
	ImGui::DragFloat3("Direction", directional_light_dir, 0.01f, -1.0, 1.0f);
	ImGui::ColorEdit3("Color", directional_light_color);

	memcpy(Materials.matSettings->lightConf_[light].dir_, pos, sizeof(dir));
	memcpy(Materials.matSettings->lightConf_[light].diff_color_, pos, sizeof(diff_color));

	memcpy(Materials.matSettings_water->lightConf_[light].dir_, pos, sizeof(dir));
	memcpy(Materials.matSettings_water->lightConf_[light].diff_color_, pos, sizeof(diff_color));
}*/
