#pragma once

#include <vector>
#include <map>
#include "json.h"
#include "core\oclcore.h"

OCL_NAMESPACE_START

struct SMaterialDescription{
	oclID ID;//���ʵ�ȫ��ΨһID������Լ�������ظ������Ը�ֵ���ɶԽӲ����(rmprocessor.cpp)��PBR����ID��ά����
	oclInt itemIndex=-1;//�����ڲ��ʿ��е���������ֵ�ɾ���Ĳ��ʿ⸳ֵ���û����ع��ĸ�ֵ��ʹ�ü��ɣ�
	oclInt libID=-1;//���ʿ�ID����ֵ�ɾ���Ĳ��ʿ⸳ֵ���û����ع��ġ�
	oclStr definitionName="NewMaterial";
	oclStr type="";
	oclStr jsonString="";
	oclStr texturePath="./texture/";
	oclStr thumbnailPath="";
	oclStr group="";
   std::map<oclStr,oclStr> textureMap;//1.��һ��Ԫ��Ϊԭʼ�������ƣ��ڶ���Ϊ�޸ĺ����������
};

struct SMaterialLibraryDescription{
	oclInt ID;
	oclStr libName="NewLibrary";
	oclStr filePath="";//���ʿ��ⲿ�ļ�·�����յĻ���ʾ����һ��ȫ�µĲ��ʿ⡣
	std::vector<SMaterialDescription> vecMaterial;
};


/**
* Returns oclStr witch is combined by type names of all material types.
* Used for combo box of UI.
*/
oclStr GetTypeNames();
const Json::Value& GetTypeJson(oclStr type);
const void LoadMaterialConfigFile(const oclStr& URL);
void DestroyDefaultTextures();

OCL_NAMESPACE_END
