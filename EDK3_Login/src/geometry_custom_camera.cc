/**
 *
 * @brief Custom quad source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */

#include "camera_custom.h"

#include "ESAT/math.h"
#include "EDK3/dev/gpumanager.h"
#include "EDK3/dev/gpumanager.h"
#include "Perlin/SimplexNoise.h"
#include "ESAT/input.h"
#include "math_helpers.h"
#include "EDK3/drawable.h"



//#define STB_IMAGE_IMPLEMENTATION
#include "stbi_image.h"

namespace EDK3 {

  //IMPORTANT!!!
  //TODO constructors, destructor and =operator here!!!
  CameraCustom::CameraCustom(){}
  CameraCustom::~CameraCustom(){}
  
  /*
    mesh_elements_pointer[j + i * (num_revs_ + 1)].pos = {
                    cosf(0) * cosf(i * alpha - 1.57f) ,
                    sinf(alpha * i - 1.57f) ,
                    sinf(0) * cosf(i * alpha - 1.57f) 
    };
  */
  void CameraCustom::initViewTarget(const float window_width,
    const float window_height) {
    window_size_ = { window_width, window_height };
    view_dir_ = {0.0f,0.0f,1.0f};
    last_wheel_value_ = 0.0;
    set_view_direction(&view_dir_.x);
  }

  ESAT::Vec2 CameraCustom::window_size() const{
    return window_size_;
  }

  void CameraCustom::doCull(const Node* root_node)
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

  void CameraCustom::doRender() const
  {
      float rgba[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
      EDK3::dev::GPUManager::Instance()->clearFrameBuffer(rgba);

      for (int i = 0; i < data_.size(); ++i)
      {
          if (data_[i].should_render) {
              if (data_[i].material->enable(data_[i].material_setting))
              {
                  //EDK3::dev::GPUManager::Instance()->disableCullFaces();
                  data_[i].material->setupCamera(projection_matrix(), view_matrix());
                  data_[i].material->setupModel(data_[i].transform.m);
                  data_[i].geometry->bindAttributesAndRenderWithCurrentMaterial(data_[i].material);
              }
          }
      }
  }

  void CameraCustom::setSpeed(const float speed) {
    speed_ = speed;
  }

  void CameraCustom::setSpeedModifier(const float speed_modifier){
    speed_modifier_ = speed_modifier;
  }

  void CameraCustom::setSensitibity(const float sensitivity){
    sensitivity_ = sensitivity;
  }

  void CameraCustom::update(const double dt, const float window_width,
      const float window_height){
    float alpha;
    float omega;

    
    if(ESAT::MouseWheelY() > last_wheel_value_){
      speed_ += speed_modifier_;
    }else if(ESAT::MouseWheelY() < last_wheel_value_){
      speed_ -= speed_modifier_;
    }
    speed_ = speed_ < 0.0 ? 0.0 : speed_;
    last_wheel_value_ = ESAT::MouseWheelY();


    if (ESAT::MouseButtonPressed(1)) {
      const float* position_ = position();
      ESAT::Vec3 new_position;
      if (ESAT::IsKeyPressed('W')) {
        new_position = {position_[0] + view_dir_.x * speed_,
                      position_[1] + view_dir_.y * speed_,
                      position_[2] + view_dir_.z * speed_ };
        set_position(&new_position.x);
      }
      if (ESAT::IsKeyPressed('S')) {
        new_position = {position_[0] - view_dir_.x * speed_,
                      position_[1] - view_dir_.y * speed_,
                      position_[2] - view_dir_.z * speed_ };
        set_position(&new_position.x);
      }
      if (ESAT::IsKeyPressed('A')) {
        ESAT::Vec3 right = Vec3CrossProduct(view_dir_,{0.0f,1.0f,0.0f});
        new_position = {position_[0] - right.x * speed_,
                        position_[1] - right.y * speed_,
                        position_[2] - right.z * speed_};
        set_position(&new_position.x);
      }
      if (ESAT::IsKeyPressed('D')) {
        ESAT::Vec3 right = Vec3CrossProduct(view_dir_,{0.0f,1.0f,0.0f});
        new_position = {position_[0] + right.x * speed_,
                        position_[1] + right.y * speed_,
                        position_[2] + right.z * speed_};
        set_position(&new_position.x);
      }
      if (ESAT::IsKeyPressed('Q')) {
        new_position = {position_[0],
                        position_[1] - speed_,
                        position_[2]};
        set_position(&new_position.x);
      }

      if (ESAT::IsKeyPressed('E')) {
        new_position = {position_[0],
                        position_[1] + speed_,
                        position_[2] };
        set_position(&new_position.x);
      }
      

      alpha = ((window_size_.y-(float)ESAT::MousePositionY()) / window_height) * 3.14f;
      omega = ((float)ESAT::MousePositionX() / window_width) * 6.28f;

      ESAT::Vec3 camera_pos = {
        cosf(omega) * cosf(alpha - 1.57) * sensitivity_,
        sinf(alpha - 1.57f) ,
        sinf(omega) * cosf(alpha - 1.57f) * sensitivity_
      };

      view_dir_ = Vec3Normalize(camera_pos);

      set_view_direction(&view_dir_.x);
    }
  }
} //EDK3
