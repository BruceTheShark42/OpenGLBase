#include "BasicModel.h"

BasicModel::BasicModel(unsigned int vertexCount, unsigned int indexCount)
	: vertexCount(vertexCount), indexCount(indexCount)
{
	vertices = new BasicVertex[vertexCount];
	indices = new unsigned int[indexCount];
}

BasicModel::~BasicModel()
{
	delete[] vertices;
	delete[] indices;
}
