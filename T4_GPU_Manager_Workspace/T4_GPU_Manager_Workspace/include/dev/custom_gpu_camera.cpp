#include "custom_gpu_camera.h"

EDK3::dev::CustomGPUCamera::CustomGPUCamera() {

}

/*
void DoCullRecursively(const Node* root_node, Mat4 parent) {
	Mat4 model = ;
	Drawable* d = dynamic_cast<Drawable*>(root_node);
	
	if (d && d->visible()) {
		NodeData cmd;
		cmd.geo = d->geometry();
		cmd.mat = d->material();
		cmd.mat_settings = d->material_settings();
		cmd.model = model;
		data_.data.push_back(cmd);
	}

	for (int i = 0; i < root_node->num_children();++i) {
		DoCullRecursively(root_node->child(i), model);
	}
}
*/

void EDK3::dev::CustomGPUCamera::doCull(const Node* root_node) {
	/*
	data_->data.clear();
	DoCullRecursively(root_node, Mat4Identity());
	*/


}

void EDK3::dev::CustomGPUCamera::doRender() const {
	// enable depth test --> // CustomGPUManager::enableDepthTest();
 	// clear --> // CustomGPUManager::clearFrameBuffer();

	/*
	*/
	float view[16] = view_matrix();
	float projection[16] = projection_matrix();

	for (int i = 0; i < data.data.size(); i++) {
		data[i].mat->enable(data[i].mat_settings);		//glUseProgram + material settings uniforms
		data[i].mat->setupCamera(projection, view);		//Camera uniforms
		data[i].mat->setupModel(model);					//Model uniforms
		// More eventual uniforms
		data[i].geo->bindAttributesAndRenderWithCurrentMaterial(data[i].mat);	//bindBuffer();
																				//glDrawElements();
	}
}

EDK3::dev::CustomGPUCamera::~CustomGPUCamera()
{
}

EDK3::dev::CustomGPUCamera& EDK3::dev::CustomGPUCamera::operator=(const CustomGPUCamera&) {
	//return this
}
