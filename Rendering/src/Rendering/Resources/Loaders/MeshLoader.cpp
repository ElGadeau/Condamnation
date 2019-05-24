#include "stdafx.h"
#include <Rendering/Resources/Loaders/MeshLoader.h>
#include <../assimp/include/assimp/Importer.hpp>
#include <../assimp/include/assimp/scene.h>
#include <../assimp/include/assimp/postprocess.h>

std::shared_ptr<Rendering::Resources::Mesh> Rendering::Resources::Loaders::MeshLoader::Load(const char* pfile)
{

	std::vector<Rendering::Geometry::Vertex> vertices;
	std::vector<uint32_t> indices;

    int offset = 0;

	Assimp::Importer m_importer;
	const aiScene* m_scene = m_importer.ReadFile(pfile,
		aiProcess_OptimizeMeshes 
		| aiProcess_OptimizeGraph
		| aiProcess_Triangulate
		| aiProcess_SortByPType
		| aiProcess_GenNormals
		| aiProcess_FixInfacingNormals
		);


    //Load Meshes
	for (int i = 0; i < m_scene->mNumMeshes; ++i)
	{
		aiMesh* t_mesh = m_scene->mMeshes[i];
		int t_meshFaces = t_mesh->mNumFaces;
		//std::cout << m_scene->mNumMeshes << std::endl;
		//std::cout << t_mesh->mNumVertices << std::endl;


        //Load Vertices
		for (unsigned int vertIdx = 0u; vertIdx < t_mesh->mNumVertices; vertIdx++)
		{
			Rendering::Geometry::Vertex vertex;

			aiVector3D vert = t_mesh->mVertices[vertIdx];
			aiVector3D norm = t_mesh->mNormals[vertIdx];

			vertex.m_position = glm::vec3(vert.x, vert.y , vert.z);
			vertex.m_normal = glm::vec3(norm.x, norm.y , norm.z );

			vertices.push_back(vertex);

            //Load Indices
		}
		for (int faceIdx = 0; faceIdx < t_mesh->mNumFaces; faceIdx++)
		{
			if (t_mesh->mFaces[faceIdx].mNumIndices == 3)
			{
				indices.push_back(t_mesh->mFaces[faceIdx].mIndices[0] + offset);
				indices.push_back(t_mesh->mFaces[faceIdx].mIndices[1] + offset);
				indices.push_back(t_mesh->mFaces[faceIdx].mIndices[2] + offset);
			}
		}
        offset += t_mesh->mNumVertices;
	}
	//std::cout << indices.size() << std::endl;
    return std::shared_ptr<Mesh>(new Mesh{vertices, indices});
}