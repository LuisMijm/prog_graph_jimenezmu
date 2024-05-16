/**
 *
 * @brief Basic material header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#ifndef __MATERIAL_CUSTOM_H__
#define __MATERIAL_CUSTOM_H__ 1

#include "ESAT/math.h"
#include "EDK3/ref_ptr.h"
#include "EDK3/material.h"
#include "EDK3/materialsettings.h"
#include "EDK3/dev/program.h"
#include "EDK3/dev/shader.h"
#include "EDK3/texture.h"


namespace EDK3 {

  class MaterialCustom : public Material {
  public:
    MaterialCustom();
    void init(EDK3::scoped_array<char>& error_log,
      const char* vertex_path,
      const char* fragment_path);

    //Indica el uso del material, se llamara frame a frame cada que queramos pintar algo
    virtual bool enable(const EDK3::MaterialSettings* mat) const override;
    virtual void setupCamera(const float projection[16], const float view[16]) const override;
    virtual void setupModel(const float model[16]) const override;

    virtual unsigned int num_attributes_required() const; //Devolver un 3 de momento
    virtual EDK3::Attribute attribute_at_index(const unsigned int attrib_idx) const;
    virtual EDK3::Type attribute_type_at_index(const unsigned int attrib_index) const;

    struct LightConf {
      int type_;
      float pos_[3];
      float dir_[3];
      float diff_color_[3];
      float spec_color_[3];
      float linear_att_;
      float quadratic_att_;
      float constant_att_;
      float shininess_;
      float strength_;
      float camera_pos_[3];
      bool enabled_;
    };

    class LightSettings : public MaterialSettings {
    public:
      LightConf light_confs_[8];
      static float ambient_color_[3];
      EDK3::ref_ptr<EDK3::Texture> texture_;

      LightSettings() {
        memset(light_confs_, 0, sizeof(light_confs_));
      }
      void set_texture(EDK3::ref_ptr<EDK3::Texture> t) { texture_ = t; }
      EDK3::ref_ptr<EDK3::Texture> texture() const { return texture_; }
    protected:
      virtual ~LightSettings() {}
    private:
      LightSettings(const LightSettings& other) {
        memcpy(light_confs_, other.light_confs_, sizeof(light_confs_));
        texture_ = other.texture_;
      }
      LightSettings(LightSettings&& other) {
        memcpy(light_confs_, other.light_confs_, sizeof(light_confs_));
        memset(other.light_confs_, 0, sizeof(light_confs_));
        texture_ = other.texture_;
        other.texture_.release();
      }
      LightSettings& operator=(const LightSettings& other) {
        memcpy(light_confs_, other.light_confs_, sizeof(light_confs_));
        texture_ = other.texture_;
        return *this;
      }
    };

    /*
    class MaterialCustomSettings : public EDK3::MaterialSettings {
     public:
      MaterialCustomSettings() {
        memset(color_, 0, sizeof(color_));
      }
      void set_color(const float v[4]) { memcpy(color_, v, sizeof(color_)); }
      const float* color() const { return color_; }
     protected:
      virtual ~MaterialCustomSettings() {}
     private:
      MaterialCustomSettings(const MaterialCustomSettings& other) {
        memcpy(color_, other.color_, sizeof(color_));
      }
      MaterialCustomSettings(MaterialCustomSettings&& other) {
        memcpy(color_, other.color_, sizeof(color_));
        memset(other.color_, 0, sizeof(color_));
      }
      MaterialCustomSettings& operator=(const MaterialCustomSettings& other) {
        memcpy(color_, other.color_, sizeof(color_));
        return *this;
      }
      float color_[4];
    }; //MaterialCustomSettings

    class MaterialCustomTextureSettings : public EDK3::MaterialSettings {
    public:
        MaterialCustomTextureSettings() {
            memset(color_, 0, sizeof(color_));
        }
        void set_color(const float v[4]) { memcpy(color_, v, sizeof(color_)); }
        const float* color() const { return color_; }
        void set_texture(EDK3::ref_ptr<EDK3::Texture> t, const int i) { texture_[i] = t; }
        EDK3::ref_ptr<EDK3::Texture> texture(const int i) const { return texture_[i]; }
    protected:
        virtual ~MaterialCustomTextureSettings() {}
    private:
        MaterialCustomTextureSettings(const MaterialCustomTextureSettings& other) {
            memcpy(color_, other.color_, sizeof(color_));
            texture_[0] = other.texture_[0];
            texture_[1] = other.texture_[1];
        }
        MaterialCustomTextureSettings(MaterialCustomTextureSettings&& other) {
            memcpy(color_, other.color_, sizeof(color_));
            memset(other.color_, 0, sizeof(color_));
            texture_[0] = other.texture_[0];
            texture_[1] = other.texture_[1];
            other.texture_[0].release();
            other.texture_[1].release();
        }
        MaterialCustomTextureSettings& operator=(const MaterialCustomTextureSettings& other) {
            memcpy(color_, other.color_, sizeof(color_));
            texture_[0] = other.texture_[0];
            texture_[1] = other.texture_[1];
            return *this;
        }
        float color_[4];
        EDK3::ref_ptr<EDK3::Texture> normal_;
        EDK3::ref_ptr<EDK3::Texture> diffuse_;
        EDK3::ref_ptr<EDK3::Texture> specular_;



    }; //MaterialCustomTextureSettings
    */



  protected:
    virtual ~MaterialCustom();

  private:
    EDK3::ref_ptr<EDK3::dev::Program> program_;

    MaterialCustom(const MaterialCustom&);
    //MaterialCustom(MaterialCustom&&);
    MaterialCustom& operator=(const MaterialCustom&);
  };

  class CustomLightMaterial : public Material {
  public:
    int useTexture_;


  public:
    CustomLightMaterial();

    void init(EDK3::scoped_array<char>& error_log,
      const char* vertex_path,
      const char* fragment_path, int useTexture = 0);
    bool enable(const EDK3::MaterialSettings* mat) const;
    void setupCamera(const float projecton[16], const float view[16]) const;
    void setupModel(const float m[16]) const;

    virtual unsigned int num_attributes_required() const override;
    virtual EDK3::Attribute attribute_at_index(const unsigned int attrib_idx) const override;
    virtual EDK3::Type attribute_type_at_index(const unsigned int attrib_index) const override;
    CustomLightMaterial(const CustomLightMaterial&);


    //void init(EDK3::scoped_array<char>& error_log, const char* vertex_path, const char* fragment_path);

    struct LightConf {
      int type_;
      float pos_[3];
      float dir_[3];
      float diff_color_[3];
      float spec_color_[3];
      float linear_att_;
      float quadratic_att_;
      float constant_att_;
      float shininess_;
      float strength_;
      float camera_pos_[3];
      bool enabled_;
    };

    class Settings : public MaterialSettings {

    private:
      EDK3::ref_ptr<EDK3::Texture> texture_;
      EDK3::ref_ptr<EDK3::Texture> specualar_;
      EDK3::ref_ptr<EDK3::Texture> normal_;
    public:
      LightConf lightConf_[10];
      float color_[4];

    private:
      Settings(const Settings&);
      Settings& operator=(const Settings&);


    public:
      Settings();

      void set_texture(EDK3::Texture* tex) { texture_ = tex; }
      EDK3::Texture* texture() { return texture_.get(); }
      const EDK3::Texture* texture() const { return texture_.get(); }

      void set_specular(EDK3::Texture* tex) { specualar_ = tex; }
      EDK3::Texture* specular() { return specualar_.get(); }
      const EDK3::Texture* specular() const { return specualar_.get(); }

      void set_normal(EDK3::Texture* tex) { normal_ = tex; }
      EDK3::Texture* normal() { return normal_.get(); }
      const EDK3::Texture* normal() const { return normal_.get(); }
      void set_color(const float v[4]) {
        memcpy(color_, v, sizeof(color_));
      }

      void init(EDK3::scoped_array<char> &error_log, const char* vertex_path, const char* fragment_path);

      const float* color() const { return color_; }

      ~Settings();

      };


      EDK3::ref_ptr<EDK3::dev::Program> program_;
      //CustomLightMaterial(const CustomLightMaterial&);
      //CustomLightMaterial& operator=(const CustomLightMaterial&);
    };

  } //EDK3


#endif //__MATERIAL_BASIC_H__


