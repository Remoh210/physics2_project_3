#include "globalOpenGLStuff.h"
#include "globalStuff.h"	
#include "cAABB.h"// for g_pRogerRabbit

#include "cVAOMeshManager.h"
#include "cMeshObject.h"

#include "DebugRenderer/cDebugRenderer.h"

#include <iostream>

// Loading models was moved into this function
void LoadModelTypes( cVAOMeshManager* pTheVAOMeshManager, GLuint shaderProgramID )
{


	sModelDrawInfo sphereInfo;
	sphereInfo.meshFileName = "Sphere_320.ply";			// "Sphere_320_faces_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(sphereInfo, shaderProgramID);

	sModelDrawInfo sphereInvertedNormalsInfo;
	sphereInvertedNormalsInfo.meshFileName = "Sphere_320_faces_xyz_n_GARBAGE_uv_INVERTED_NORMALS.ply";			// "Sphere_320_faces_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(sphereInvertedNormalsInfo, shaderProgramID);


	sModelDrawInfo mig;
	mig.meshFileName = "mig.ply";			// "Sphere_320_faces_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(mig, shaderProgramID);



	//for debug draw only ***********************
	sModelDrawInfo cube1x1x1;
	cube1x1x1.meshFileName = "cube_flat_shaded_xyz_n_uv.ply";			// "cube_flat_shaded_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(cube1x1x1, shaderProgramID);



	// At this point, mesh in in GPU
	std::cout << "Mesh was loaded OK" << std::endl;

	::g_pTheTextureManager->SetBasePath("assets/textures/cubemaps");
	std::string errorString;
	if (::g_pTheTextureManager->CreateCubeTextureFromBMPFiles("CityCubeMap",
		"city_lf.bmp", "city_rt.bmp",				// reverse these
		"city_dn.bmp", "city_up.bmp",				// Rotate the image "right 90 degrees")
		"city_ft.bmp", "city_bk.bmp", true, errorString))
	{
		std::cout << "Loaded the city cube map OK" << std::endl;
	}
	else
	{
		std::cout << "Error: city cube map DIDN't load. On no!" << std::endl;
	}



	return;
}

	
// Loads the models we are drawing into the vector
void LoadModelsIntoScene( std::vector<cMeshObject*> &vec_pObjectsToDraw )
{

	//SkyBoxObject
	{	
		cMeshObject* pSkyBoxObject = new cMeshObject();
		pSkyBoxObject->setDiffuseColour(glm::vec3(1.0f, 105.0f / 255.0f, 180.0f / 255.0f));
		pSkyBoxObject->bUseVertexColour = false;
		pSkyBoxObject->friendlyName = "SkyBoxObject";
		float scale = 5000.0f;
		pSkyBoxObject->nonUniformScale = glm::vec3(scale, scale, scale);
		pSkyBoxObject->meshName = "Sphere_320_faces_xyz_n_GARBAGE_uv_INVERTED_NORMALS.ply";			// "Sphere_320_faces_xyz.ply";
		pSkyBoxObject->bIsDebug = true;
		pSkyBoxObject->bIsVisible = false;
		vec_pObjectsToDraw.push_back(pSkyBoxObject);
	}

	{	
		cMeshObject* pPlayerSphere = new cMeshObject();
		pPlayerSphere->setDiffuseColour(glm::vec3(1.0f, 105.0f / 255.0f, 180.0f / 255.0f));
		pPlayerSphere->friendlyName = "DebugSphere";
		float scale = 1.0f;
		pPlayerSphere->nonUniformScale = glm::vec3(scale, scale, scale);
		pPlayerSphere->meshName = "Sphere_320.ply";
		pPlayerSphere->bIsWireFrame = true;
		pPlayerSphere->position = glm::vec3(-100.0f, 10.0f, 0.0f);
		pPlayerSphere->bIsUpdatedByPhysics = true;
		pPlayerSphere->bIsDebug = true;
		pPlayerSphere->pDebugRenderer = ::g_pDebugRenderer;
		vec_pObjectsToDraw.push_back(pPlayerSphere);
	}




	return;
}