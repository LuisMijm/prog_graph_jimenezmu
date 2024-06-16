#include "EDK3/dev/opengl.h"
#include "EDK3/node.h"
#include "EDK3/drawable.h"
#include "dev/custom_gpu_camera.h"
#include <EDK3/dev/gpumanager.h>


namespace EDK3{


  namespace dev {
	  CustomGPUCamera::CustomGPUCamera()
	  {
	  }

	  void CustomGPUCamera::doCull(const Node* root_node)
	  {
          static Mat4 child_transform = child_transform.Identity();
          CamData current_node;


          if (nullptr == root_node->parent()) {
              data_.clear();
              current_node.transform = Mat4(root_node->local_transform());
          }
          else {
              current_node.transform = child_transform.Multiply(Mat4(root_node->local_transform()));
          }

          const EDK3::Drawable* draw = dynamic_cast<const EDK3::Drawable*>(root_node);

          if (draw != nullptr) {
              if (draw->visible()) {
                  current_node.geometry = draw->geometry();
                  current_node.material = draw->material();
                  current_node.material_setting = draw->material_settings();
                  current_node.should_render = true;
                  data_.push_back(current_node);
              }
              else {
                  current_node.should_render = false;
              }
          }

          for (int i = 0; i < root_node->num_children(); ++i)
          {
              child_transform = current_node.transform;
              doCull(root_node->child(i));
          }
	  }

	  void CustomGPUCamera::doRender() const
	  {
          float rgba[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
          EDK3::dev::GPUManager::Instance()->clearFrameBuffer(rgba);

          for (int i = 0; i < data_.size(); ++i)
          {
              if (data_[i].should_render) {
                  if (data_[i].material->enable(data_[i].material_setting))
                  {
                      data_[i].material->setupCamera(projection_matrix(), view_matrix());
                      data_[i].material->setupModel(data_[i].transform.m);
                      data_[i].geometry->bindAttributesAndRenderWithCurrentMaterial(data_[i].material);
                  }
              }
          }
	  }

	  CustomGPUCamera::~CustomGPUCamera()
	  {
	  }
  }
}