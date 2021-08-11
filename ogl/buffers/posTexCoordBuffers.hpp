#pragma once

#include <GL/glew.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace Buffers
{
	class PosTexCoordBuffers
	{
	public:
		PosTexCoordBuffers();
		PosTexCoordBuffers(const PosTexCoordBuffers&) = delete;
		PosTexCoordBuffers(PosTexCoordBuffers&& other) noexcept;
		~PosTexCoordBuffers();

		void setPositionBuffer(const glm::vec3& data, size_t numOfPositions, GLenum positionsDataUsage);
		void setTexCoordBuffer(const glm::vec2& data, size_t numOfTexCoords, GLenum texCoordsDataUsage);
		void bindVertexArray() const;

		size_t getNumOfVertices() const;

	private:
		GLuint vertexArray;
		GLuint positionBuffer;
		GLuint texCoordBuffer;

		size_t numOfPositions = 0;
		size_t numOfTexCoords = 0;

		size_t numOfAllocatedPositions = 0;
		size_t numOfAllocatedTexCoords = 0;

		GLenum positionsDataUsage = GL_STATIC_DRAW;
		GLenum texCoordsDataUsage = GL_STATIC_DRAW;

		bool expired = false;
	};
}
