#include "cSceneManager.h"
#include <cstdio>
#include <fstream>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>




#include <rapidjson/writer.h>
#include <cstdio>



cSceneManager::cSceneManager() {};



bool cSceneManager::saveScene(std::string filename) 

{

	rapidjson::Document doc;
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
	doc.SetObject();
	rapidjson::Value MeshArray(rapidjson::kArrayType);

	/*or rapidjson::Value myArray; ;
	     myArray.SetArray() */
	for (std::vector<cMeshObject*>::iterator it = vec_pObjectsToDraw.begin(); it != vec_pObjectsToDraw.end(); ++it)
	{
		cMeshObject* CurModel = *it;
		rapidjson::Value objValue(rapidjson::kObjectType);
		rapidjson::Value friendlyName(CurModel->friendlyName.c_str(), doc.GetAllocator());
		rapidjson::Value meshName(CurModel->meshName.c_str(), doc.GetAllocator());
		objValue.AddMember("friendly name", friendlyName, allocator);
		objValue.AddMember("mesh name", meshName, allocator);
		MeshArray.PushBack(objValue, allocator);

	}

	doc.AddMember("GameObjects", MeshArray, allocator);

	FILE* fp = fopen("output.json", "wb"); // non-Windows use "w"
	char writeBuffer[65536];
	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
	doc.Accept(writer);
	fclose(fp);
	return true;
}