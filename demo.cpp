#include "demo.hpp"

#include "tools/utility.hpp"

void Demo()
{
	for (int x = 0; x < texCoordBuffer.getRes().x; ++x)
	{
		texCoordBuffer.putColor({ x, 0 }, { Tools::Random(-10.0f, 10.0f), Tools::Random(-10.0f, 10.0f), Tools::Random(-5.0f, 5.0f) });
	}

	for (int y = 1; y < texCoordBuffer.getRes().y; ++y)
	{
		for (int x = 1; x < texCoordBuffer.getRes().x - 1; ++x)
		{
			glm::vec3 newColor = (texCoordBuffer.getColor({ x - 1, y - 1 }) + texCoordBuffer.getColor({ x, y - 1 }) + texCoordBuffer.getColor({ x + 1, y - 1 }) + texCoordBuffer.getColor({ x, y })) / 4.03f;
			texCoordBuffer.putColor({ x, y }, newColor);
		}
	}
}
