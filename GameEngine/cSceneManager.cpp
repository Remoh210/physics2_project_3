#include "cSceneManager.h"
#include <cstdio>
#include <fstream>
#include <iostream>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

#include <rapidjson/writer.h>
#include <cstdio>


cSceneManager::cSceneManager() {};



bool cSceneManager::saveScene(std::string filename) {

	rapidjson::Document doc;
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
	doc.SetObject();
	rapidjson::Value MeshArray(rapidjson::kArrayType);
	
	//Camera Output
	rapidjson::Value CameraObj(rapidjson::kObjectType);
	rapidjson::Value CameraSpeed(camera.MovementSpeed);
	rapidjson::Value CameraPosArray(rapidjson::kArrayType);

	for (int i = 0; i < 3; i++)
	{
		rapidjson::Value temp(camera.Position[i]);
		CameraPosArray.PushBack(temp, allocator);
	}
	CameraObj.AddMember("Speed", CameraSpeed, allocator);
	CameraObj.AddMember("Position", CameraPosArray, allocator);
	//camera.Position
	//camera
	//doc.AddMember("Camera", )


	/*or rapidjson::Value myArray; ;
	     myArray.SetArray() */
	for (std::vector<cMeshObject*>::iterator it = vec_pObjectsToDraw.begin(); it != vec_pObjectsToDraw.end(); ++it) {
		cMeshObject* CurModel = *it;
		rapidjson::Value ObjValue(rapidjson::kObjectType);
		rapidjson::Value FriendlyName(CurModel->friendlyName.c_str(), allocator);
		rapidjson::Value MeshName(CurModel->meshName.c_str(), allocator);
		rapidjson::Value PositionArray(rapidjson::kArrayType);
		rapidjson::Value DiffuseRGBArray(rapidjson::kArrayType);
		rapidjson::Value SpecularRGBArray(rapidjson::kArrayType);
		rapidjson::Value Rotation(rapidjson::kArrayType);
		rapidjson::Value Scale(rapidjson::kArrayType);
		rapidjson::Value Visible(CurModel->bIsVisible);
		rapidjson::Value UsePhysics(CurModel->bIsUpdatedByPhysics);
		rapidjson::Value WireFrame(CurModel->bIsWireFrame);
		rapidjson::Value TexArray(rapidjson::kArrayType);
		

		for(int i = 0; i < 3; i ++) {
			rapidjson::Value temp(CurModel->position[i]);
			PositionArray.PushBack(temp, allocator);
		}

		for (int i = 0; i < 4; i++) {
			rapidjson::Value temp(CurModel->materialDiffuse[i]);
			DiffuseRGBArray.PushBack(temp, allocator);
		}

		for (int i = 0; i < 4; i++) {
			rapidjson::Value temp(CurModel->materialSpecular[i]);
			SpecularRGBArray.PushBack(temp, allocator);
		}

		for (int i = 0; i < 4; i++) {
			rapidjson::Value temp(CurModel->m_meshQOrientation[i]);
			Rotation.PushBack(temp, allocator);
		}
		for (int i = 0; i < 3; i++) {
			rapidjson::Value temp(CurModel->nonUniformScale[i]);
			Scale.PushBack(temp, allocator);
		}

		ObjValue.AddMember("Name", FriendlyName, allocator);
		ObjValue.AddMember("Mesh", MeshName, allocator);
		ObjValue.AddMember("Visible", Visible, allocator);
		ObjValue.AddMember("Use_Physics", UsePhysics, allocator);
		ObjValue.AddMember("Wireframe", WireFrame, allocator);
		ObjValue.AddMember("Position", PositionArray, allocator);
		ObjValue.AddMember("DiffuseRGB_Alpha", DiffuseRGBArray, allocator);
		ObjValue.AddMember("SpecularRGB_Alpha", SpecularRGBArray, allocator);
		ObjValue.AddMember("Rotation", Rotation, allocator);
		ObjValue.AddMember("Scale", Scale, allocator);

		//Textures
		if (CurModel->vecTextures.size() > 0) {
			for (int i = 0; i < CurModel->vecTextures.size(); i++) {
				rapidjson::Value TexObjValue(rapidjson::kObjectType);
				rapidjson::Value TexName(CurModel->vecTextures[i].name.c_str(), allocator);
				rapidjson::Value TexStrength(CurModel->vecTextures[i].strength);
				TexObjValue.AddMember("Name", TexName, allocator);
				TexObjValue.AddMember("Strength", TexStrength, allocator);
				TexArray.PushBack(TexObjValue, allocator);
			}
			ObjValue.AddMember("Textures", TexArray, allocator);
		}
		


		MeshArray.PushBack(ObjValue, allocator);
		

	}
	doc.AddMember("Camera", CameraObj, allocator);
	doc.AddMember("GameObjects", MeshArray, allocator);

	//TODO: Lights

	


	FILE* fp = fopen("output.json", "wb"); // non-Windows use "w"
	char writeBuffer[65536];
	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
	doc.Accept(writer);
	fclose(fp);
	return true;
}




bool cSceneManager::loadScene(std::string filename) {

	rapidjson::Document doc;
	FILE* fp = fopen("output.json", "rb"); // non-Windows use "r"
	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	doc.ParseStream(is);
	fclose(fp);


	//Camera
	float Speed;
	glm::vec3 CameraPos;
	rapidjson::Value& CameraPosArray = doc["Camera"]["Position"];

	Speed = doc["Camera"]["Speed"].GetFloat();
	for (rapidjson::SizeType i = 0; i < CameraPosArray.Size(); i++) {
		CameraPos[i] = CameraPosArray[i].GetFloat();
		std::cout << "CameraPos: [ " << CameraPos[i] << " ]" << std::endl;
	}

	std::cout << Speed << std::endl;
	

	//Game Objects
	const rapidjson::Value& GameObject = doc["GameObjects"];
	std::string MeshName;
	glm::vec3 Position;

	for (rapidjson::SizeType i = 0; i < GameObject.Size(); i++) {

		MeshName = GameObject[i]["Name"].GetString();
		
		std::cout << "Name: " << MeshName << std::endl;
		const rapidjson::Value& PositionArray = GameObject[i]["Position"];
		for (rapidjson::SizeType i = 0; i < PositionArray.Size(); i++) {
			Position[i] = PositionArray[i].GetFloat();
			std::cout << "Position: [ " << Position[i] << " ]" <<std::endl;
		}
		
		
	}

	return true;
}