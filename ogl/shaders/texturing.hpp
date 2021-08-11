#pragma once

#include "programBase.hpp"

namespace Shaders
{
	namespace Programs
	{
		struct TexturingAccessor : ProgramBase
		{
			using ProgramBase::ProgramBase;

			TexturingAccessor(Shaders::ProgramId program) :
				ProgramBase(program),
				color(program, "color"),
				texture1(program, "texture1"),
				mvp(program, "mvp")
			{
			}

			Uniforms::UniformController4f color;
			Uniforms::UniformController1i texture1;
			Uniforms::UniformControllerMat4f mvp;
		};

		struct Texturing : TexturingAccessor
		{
			Texturing() :
				TexturingAccessor(Shaders::LinkProgram(Shaders::CompileShaders("ogl/shaders/texturing.vs",
					"ogl/shaders/texturing.fs"), { {0, "bPos"}, {1, "bTexCoord"} }))
			{
			}

			Texturing(const Texturing&) = delete;

			~Texturing()
			{
				glDeleteProgram(getProgramId());
			}
		};
	}
}
