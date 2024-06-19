#include "dev/custom_gpu_program.h"
#include "EDK3/dev/opengl.h"


namespace EDK3{


	namespace dev {

		CustomGPUProgram::CustomGPUProgram() {
			internal_id_ = glCreateProgram();
		}

		CustomGPUProgram::CustomGPUProgram(const CustomGPUProgram& other) {
			internal_id_ = other.internal_id_;
		}

		CustomGPUProgram& CustomGPUProgram::operator=(const CustomGPUProgram& other) {
			internal_id_ = other.internal_id_;
			return *this;
		}

		CustomGPUProgram::~CustomGPUProgram() {
			GLint params;
			glDeleteProgram(internal_id_);
			glGetProgramiv(internal_id_, GL_DELETE_STATUS, &params);
			if (GL_TRUE != params) {
				GLenum error = glGetError();
				switch (error) {
				case GL_INVALID_VALUE:
					printf("Delete program error: GL_INVALID_VALUE\n");
					break;
				case GL_INVALID_OPERATION:
					printf("Delete program error: GL_INVALID_OPERATION\n");
					break;
				case GL_INVALID_ENUM:
					printf("Delete program error: GL_INVALID_ENUM\n");
					break;
				default:
					printf("Delete program error: Unknown error\n");
					break;
				}
			}
		}


		unsigned int CustomGPUProgram::internal_id() const {
			return internal_id_;
		}

		/*
		void CustomGPUProgram::set_uniform_value(const int uniform_pos,
			const EDK3::Type uniform_type,
			const float* number) const {
			GLenum error;
			switch (uniform_type) {
			case EDK3::Type::T_FLOAT_1:
				glUniform1f(uniform_pos, number[0]);
				break;
			case EDK3::Type::T_FLOAT_2:
				glUniform2f(uniform_pos, number[0], number[1]);
				break;
			case EDK3::Type::T_FLOAT_3:
				glUniform3f(uniform_pos, number[0], number[1], number[2]);
				break;
			case EDK3::Type::T_FLOAT_4:
				glUniform4f(uniform_pos, number[0], number[1], number[2], number[3]);
				break;
			}

			error = glGetError();
			if (error != GL_NO_ERROR) {
				switch (error) {
				case GL_INVALID_OPERATION:
					printf("Set float uniform value error: GL_INVALID_OPERATION\n");
					break;
				case GL_INVALID_VALUE:
					printf("Set float uniform value error: GL_INVALID_VALUE\n");
					break;
				default:
					printf("Set float uniform value error: Unknown error\n");
					break;
				}

			}
		}
		*/


		
		void CustomGPUProgram::set_uniform_value(const int uniform_pos,
			const EDK3::Type uniform_type,
			const int* number) const {
			GLenum error;
			switch (uniform_type) {
			case EDK3::Type::T_INT_1:
			case EDK3::Type::T_BYTE_1:
			case EDK3::Type::T_SHORT_1:
				glUniform1i(uniform_pos, number[0]);
				break;
			case EDK3::Type::T_INT_2:
			case EDK3::Type::T_BYTE_2:
			case EDK3::Type::T_SHORT_2:
				glUniform2i(uniform_pos, number[0], number[1]);
				break;
			case EDK3::Type::T_INT_3:
			case EDK3::Type::T_BYTE_3:
			case EDK3::Type::T_SHORT_3:
				glUniform3i(uniform_pos, number[0], number[1], number[2]);
				break;
			case EDK3::Type::T_INT_4:
			case EDK3::Type::T_BYTE_4:
			case EDK3::Type::T_SHORT_4:
				glUniform4i(uniform_pos, number[0], number[1], number[2], number[3]);
				break;
			}

			error = glGetError();
			if (error != GL_NO_ERROR) {
				switch (error) {
				case GL_INVALID_OPERATION:
					printf("Set int uniform value error: GL_INVALID_OPERATION\n");
					break;
				case GL_INVALID_VALUE:
					printf("Set int uniform value error: GL_INVALID_VALUE\n");
					break;
				default:
					printf("Set int uniform value error: Unknown error\n");
					break;
				}

			}
		}
		
		void CustomGPUProgram::set_uniform_value(const int uniform_pos,
			const EDK3::Type uniform_type,
			const float* number) const {
		
			switch (uniform_type) {
			case T_DOUBLE_1:
			case T_FLOAT_1:
				glUniform1f(uniform_pos, number[0]);
				break;
			case T_DOUBLE_2:
			case T_FLOAT_2:
				glUniform2f(uniform_pos, number[0], number[1]);
				break;
			case T_DOUBLE_3:
			case T_FLOAT_3:
				glUniform3f(uniform_pos, number[0], number[1], number[2]);
				break;
			case T_DOUBLE_4:
			case T_FLOAT_4:
				glUniform4f(uniform_pos, number[0], number[1], number[2], number[3]);
				break;
			case T_MAT_2x2:
				glUniformMatrix2fv(uniform_pos, 1,false, number);
				break;
			case T_MAT_3x3:
				glUniformMatrix3fv(uniform_pos, 1, false, number);
				break;
			case T_MAT_4x4:
				glUniformMatrix4fv(uniform_pos, 1, false, number);
				break;
			}
		}



		void CustomGPUProgram::set_uniform_value(const int uniform_pos,
			const EDK3::Type uniform_type,
			const unsigned int* number) const {
			GLenum error;
			switch (uniform_type) {
			case EDK3::Type::T_UINT_1:
			case EDK3::Type::T_UBYTE_1:
			case EDK3::Type::T_USHORT_1:
				glUniform1ui(uniform_pos, number[0]);
				break;
			case EDK3::Type::T_UINT_2:
			case EDK3::Type::T_UBYTE_2:
			case EDK3::Type::T_USHORT_2:
				glUniform2ui(uniform_pos, number[0], number[1]);
				break;
			case EDK3::Type::T_UINT_3:
			case EDK3::Type::T_UBYTE_3:
			case EDK3::Type::T_USHORT_3:
				glUniform3ui(uniform_pos, number[0], number[1], number[2]);
				break;
			case EDK3::Type::T_UINT_4:
			case EDK3::Type::T_UBYTE_4:
			case EDK3::Type::T_USHORT_4:
				glUniform4ui(uniform_pos, number[0], number[1], number[2], number[3]);
				break;
			}

			error = glGetError();
			if (error != GL_NO_ERROR) {
				switch (error) {
				case GL_INVALID_OPERATION:
					printf("Set uint uniform value error: GL_INVALID_OPERATION\n");
					break;
				case GL_INVALID_VALUE:
					printf("Set uint uniform value error: GL_INVALID_VALUE\n");
					break;
				default:
					printf("Set uint uniform value error: Unknown error\n");
					break;
				}

			}


		}

		int CustomGPUProgram::get_attrib_location(const char* name) const {
			//glGetAttribLocation
			GLint attrib_location;
			attrib_location = glGetAttribLocation(internal_id_, name);
			if (-1 == attrib_location) {
				GLenum error;
				error = glGetError();
				switch (error) {
				case GL_INVALID_OPERATION:
					printf("Get attribute location error: GL_INVALID_OPERATION\n");
					break;
				default:
					printf("Get attribute location error: Unknown error\n");
					break;
				}
				return -1;
			}
			return attrib_location;
		}

		int CustomGPUProgram::get_uniform_position(const char* name) const {
			GLint uniform_location;
			uniform_location = glGetUniformLocation(internal_id_, name);
			if (-1 == uniform_location) {
				GLenum error;
				error = glGetError();
				switch (error) {
				case GL_INVALID_OPERATION:
					printf("Get uniform location error: GL_INVALID_OPERATION\n");
					break;
				case GL_INVALID_VALUE:
					printf("Get uniform location error: GL_INVALID_VALUE\n");
					break;
				default:
					printf("Get uniform location error: Unknown error\n");
					break;
				}
				return -1;
			}
			return uniform_location;
		}


		void CustomGPUProgram::attach(EDK3::dev::Shader* shader) {
			GLenum error;
			glAttachShader(internal_id_, shader->internal_id());
			error = glGetError();
			if (error != GL_NO_ERROR) {
				switch (error) {
				case GL_INVALID_VALUE:
					printf("Attach shader error: GL_INVALID_VALUE\n");
					break;
				case GL_INVALID_OPERATION:
					printf("Attach shader error: GL_INVALID_OPERATION\n");
					break;
				default:
					printf("Attach shader error: Unknown error\n");
					break;
				}
			}

		}
		bool CustomGPUProgram::link(EDK3::scoped_array<char>* link_log) {
			glLinkProgram(internal_id_);
			GLint params;
			glGetProgramiv(internal_id_, GL_LINK_STATUS, &params);

			if (GL_FALSE == params) {
				if (link_log) {
					GLint length = 0;
					glGetProgramiv(internal_id_, GL_INFO_LOG_LENGTH, &length);
					link_log->alloc(length + 1);
					glGetProgramInfoLog(internal_id_, length, nullptr, link_log->get());
					link_log->get()[length] = '\0';
				}
				return false;

			}

			if (link_log) {
				link_log->alloc(1);
				link_log->get()[0] = '\0';
			}
			return true;
			/*
			if (GL_TRUE != params) {
				GLenum error = glGetError();
				switch (error) {
				case GL_INVALID_VALUE:
					printf("Link program error: GL_INVALID_VALUE\n");
					break;
				case GL_INVALID_OPERATION:
					printf("Link program error: GL_INVALID_OPERATION\n");
					break;
				default:
					printf("Delete shader error: Unknown error\n");
					break;
				}
				GLint info_length;
				glGetProgramiv(internal_id_, GL_INFO_LOG_LENGTH, &info_length);
				glGetShaderInfoLog(internal_id_, info_length, NULL, link_log->get());
				return false;
			}
			*/


		}
		void CustomGPUProgram::use() const {
			//glUseProgram
			GLenum error;
			glUseProgram(internal_id_);
			error = glGetError();
			if (error != GL_NO_ERROR) {
				switch (error) {
				case GL_INVALID_VALUE:
					printf("Use program error: GL_INVALID_VALUE\n");
					break;
				case GL_INVALID_OPERATION:
					printf("Use program error: GL_INVALID_OPERATION\n");
					break;
				default:
					printf("Delete shader error: Unknown error\n");
					break;
				}
			}
		}
	}
}