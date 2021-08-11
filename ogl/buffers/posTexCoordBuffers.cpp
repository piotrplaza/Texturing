#include "posTexCoordBuffers.hpp"

#include <cassert>

namespace Buffers
{
	PosTexCoordBuffers::PosTexCoordBuffers()
	{
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &positionBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &texCoordBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(1);
	}

	PosTexCoordBuffers::PosTexCoordBuffers(PosTexCoordBuffers&& other) noexcept:
		vertexArray(other.vertexArray),
		positionBuffer(other.positionBuffer),
		texCoordBuffer(other.texCoordBuffer)
	{
		other.expired = true;
	}

	PosTexCoordBuffers::~PosTexCoordBuffers()
	{
		if (expired) return;

		glDeleteBuffers(1, &positionBuffer);
		glDeleteBuffers(1, &texCoordBuffer);
		glDeleteVertexArrays(1, &vertexArray);
	}

	void PosTexCoordBuffers::setPositionBuffer(const glm::vec3& data, size_t numOfPositions, GLenum positionsDataUsage)
	{
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
		if (numOfAllocatedPositions < numOfPositions || this->positionsDataUsage != positionsDataUsage)
		{
			glBufferData(GL_ARRAY_BUFFER, numOfPositions * sizeof(data), &data, positionsDataUsage);
			this->numOfAllocatedPositions = numOfPositions;
			this->positionsDataUsage = positionsDataUsage;
		}
		else
		{
			glBufferSubData(GL_ARRAY_BUFFER, 0, numOfPositions * sizeof(data), &data);
		}
		this->numOfPositions = numOfPositions;
		this->positionsDataUsage = positionsDataUsage;
	}

	void PosTexCoordBuffers::setTexCoordBuffer(const glm::vec2& data, size_t numOfTexCoords, GLenum texCoordsDataUsage)
	{
		glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
		if (numOfAllocatedTexCoords < numOfTexCoords || this->texCoordsDataUsage != texCoordsDataUsage)
		{
			glBufferData(GL_ARRAY_BUFFER, numOfTexCoords * sizeof(data), &data, texCoordsDataUsage);
			this->numOfAllocatedTexCoords = numOfTexCoords;
			this->texCoordsDataUsage = texCoordsDataUsage;
		}
		else
		{
			glBufferSubData(GL_ARRAY_BUFFER, 0, numOfTexCoords * sizeof(data), &data);
		}
		this->numOfTexCoords = numOfTexCoords;
		this->texCoordsDataUsage = texCoordsDataUsage;
	}

	void PosTexCoordBuffers::bindVertexArray() const
	{
		glBindVertexArray(vertexArray);
	}

	size_t PosTexCoordBuffers::getNumOfVertices() const
	{
		assert(numOfPositions == numOfTexCoords);
		return numOfPositions;
	}
}
