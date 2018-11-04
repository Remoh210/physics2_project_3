#include "globalOpenGLStuff.h"
#include "globalStuff.h"		// for g_pRogerRabbit

#include "cVAOMeshManager.h"
#include "cMeshObject.h"

#include "DebugRenderer/cDebugRenderer.h"

#include <iostream>

// Loading models was moved into this function
void LoadModelTypes( cVAOMeshManager* pTheVAOMeshManager, GLuint shaderProgramID )
{

	sModelDrawInfo tableInfo;
	tableInfo.meshFileName = "table.ply";					// "mig29_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(tableInfo, shaderProgramID);



	sModelDrawInfo teapotInfo;
	teapotInfo.meshFileName = "Utah_Teapot_xyz_n_GARBAGE_uv.ply";			// "Utah_Teapot_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(teapotInfo, shaderProgramID);

	sModelDrawInfo terrainInfo;
	terrainInfo.meshFileName = "MeshLab_Fractal_Terrain_xyz_n.ply";	// "MeshLab_Fractal_Terrain_xyz.ply";
	// Will alow me to update the vertex data in the mesh
	terrainInfo.bVertexBufferIsDynamic = true;
	pTheVAOMeshManager->LoadModelIntoVAO(terrainInfo, shaderProgramID);
	
	sModelDrawInfo sphereInfo;
	sphereInfo.meshFileName = "Sphere_320_faces_xyz_n.ply";			// "Sphere_320_faces_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(sphereInfo, shaderProgramID);

	sModelDrawInfo roomInfo;
	roomInfo.meshFileName = "roomUV.ply";			// "Sphere_320_faces_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(roomInfo, shaderProgramID);

	sModelDrawInfo skullInfo;
	skullInfo.meshFileName = "skull.ply";	// "MeshLab_Fractal_Terrain_xyz.ply";
	// Will alow me to update the vertex data in the mesh
	skullInfo.bVertexBufferIsDynamic = true;
	pTheVAOMeshManager->LoadModelIntoVAO(skullInfo, shaderProgramID);

	// At this point, mesh in in GPU
	std::cout << "Mesh was loaded OK" << std::endl;


	::g_pTheTextureManager->SetBasePath("assets/textures");

	if (!::g_pTheTextureManager->Create2DTextureFromBMPFile("roomTex.bmp", true))
	{
		std::cout << "Didn't load texture" << std::endl;
	}
	::g_pTheTextureManager->Create2DTextureFromBMPFile("grass.bmp", true);
	::g_pTheTextureManager->Create2DTextureFromBMPFile("brick-wall.bmp", true);
	::g_pTheTextureManager->Create2DTextureFromBMPFile("220px-Emma_Watson_2013.bmp", true);



	return;
}

	
// Loads the models we are drawing into the vector
void LoadModelsIntoScene( std::vector<cMeshObject*> &vec_pObjectsToDraw )
{

	{
		cMeshObject* pTeapot = new cMeshObject();
		pTeapot->position = glm::vec3(40.0f, 0.0f, 0.0f);
		pTeapot->setMeshOrientationEulerAngles(glm::vec3(-90.0f, 0.0f, 0.0f), true);
		//		pTeapot->objColour = glm::vec3( 1.0f, 0.0f, 0.0f );
		pTeapot->setDiffuseColour(glm::vec3(0.0f, 0.0f, 0.0f));

		// Make the terrain really shinny...
		pTeapot->setSpecularPower(100.0f);

		pTeapot->meshName = "Utah_Teapot_xyz_n_GARBAGE_uv.ply";		// "Utah_Teapot_xyz.ply";
		// Note scale...
//		pTeapot->nonUniformScale = glm::vec3(0.005f,0.005f,0.005f);
		pTeapot->setUniformScale(0.5f);
		// Set the debug renderer here

		// Texture on the teapot
		sTextureInfo grassTexture;
		grassTexture.name = "grass.bmp";
		grassTexture.strength = 1.0f;
		pTeapot->vecTextures.push_back(grassTexture);

		pTeapot->pDebugRenderer = ::g_pDebugRenderer;

		vec_pObjectsToDraw.push_back(pTeapot);
	}

	{
		cMeshObject* pSkull = new cMeshObject();
		pSkull->position = glm::vec3(0.0f, 50.0f, 0.0f);
		//pSkull->setSpecularColour(glm::vec3(1.0f, 0.4f, 0.1f));
		pSkull->setDiffuseColour(glm::vec3(1.0f, 0.4f, 0.1f));
		pSkull->setSpecularPower(100.0f);
		pSkull->friendlyName = "skull";
	//	pSkull->bIsInteractable = true;
		pSkull->meshName = "skull.ply";		
		pSkull->setUniformScale(1.5f);
		vec_pObjectsToDraw.push_back(pSkull);
	}



	{
		cMeshObject* pRoom = new cMeshObject();
		pRoom->position = glm::vec3(0.0f, 0.0f, 300.0f);
		//pSpider->postRotation = glm::vec3(0.0f, glm::radians(-20.0f), 0.0f);
		pRoom->setDiffuseColour(glm::vec3(0.0f, 0.0f, 0.0f));
		pRoom->friendlyName = "room";
		pRoom->setSpecularPower(100.0f);
		pRoom->meshName = "roomUV.ply";
		pRoom->setUniformScale(100.0f);
		pRoom->bIsVisible = true;
		sTextureInfo roomTexture;
		roomTexture.name = "grass.bmp";
		roomTexture.strength = 1.0f;
		pRoom->vecTextures.push_back(roomTexture);
		vec_pObjectsToDraw.push_back(pRoom);
	}


	{
		cMeshObject* pTable = new cMeshObject();
		pTable->position = glm::vec3(0.0f, 0.0f, 0.0f);
	//	pTable->objColour = glm::vec3(85 / 255.0f, 33 / 255.0f, 18 / 255.0f);
		//pTable->setUniformScale(0.9f);
		pTable->friendlyName = "table";
		pTable->meshName = "table.ply";
		vec_pObjectsToDraw.push_back(pTable);
	}






	//cMeshObject* pRogerRabbit = NULL;





	{	// This sphere is the tiny little debug sphere
		cMeshObject* pDebugSphere = new cMeshObject();
		pDebugSphere->position = glm::vec3(0.0f, 0.0f, 0.0f);
	//	pDebugSphere->objColour = glm::vec3(0.0f, 1.0f, 0.0f);
		float scale = 30.0f;
		pDebugSphere->friendlyName = "DebugSphere";
		pDebugSphere->nonUniformScale = glm::vec3(scale, scale, scale);
		pDebugSphere->meshName = "Sphere_320_faces_xyz_n.ply";		
		pDebugSphere->bIsWireFrame = true;
		pDebugSphere->bIsVisible = false;
		pDebugSphere->pDebugRenderer = ::g_pDebugRenderer;

		vec_pObjectsToDraw.push_back(pDebugSphere);
	}


	// ENDOF: Updated physics object





	return;
}