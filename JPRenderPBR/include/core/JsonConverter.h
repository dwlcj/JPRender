#pragma once
#include <map>
#include <comutil.h>
#include <optixu\optixu_math_namespace.h>
#include "json.h"
#include "core\oclcore.h"
#include "../../host_device/data_instance.h"

/**
* This is a global helper funcs. header file
*/

OCL_NAMESPACE_START

struct SMaterialDescription;
struct SMaterialLibraryDescription;

namespace jsonconvertor{

/**
* ����json���ݵ����ʿ��Ӧ������
* �ɹ���������true
* json��ʽ���£�
{
"name":"your material library's name",
"index":10,
"list":[
		<materialJson>,
		<materialJson>,
		...
	]
}
*/
oclBool ConvertJsonToMaterialLibraryDescription(const oclStr& jsonString,SMaterialLibraryDescription* out);
oclBool ConvertMaterialLibraryDescriptionToJson(const SMaterialLibraryDescription& desp,oclStr* out);

oclBool ConvertMaterialLibraryDescriptionToJson_scene(const SMaterialLibraryDescription& desp,oclStr* out);

/**
* ����ģ��ʱ��д�����Ĳ������ԣ���ͬ�ڲ��ʿⱣ��ʱ��ĸ�ʽ
* ���һ����Ҫע����ǣ�������û��ʹ�õĲ��ʣ�
* json��ʽ���£�
{
// 0��3��4�ǲ���ȫ��ID��
"0":<dataJson>,
"3":<dataJson>,
"4":<dataJson>,
...
}
*/
oclBool ConvertMaterialLibraryDescriptionToJson_save(const SMaterialLibraryDescription& desp,oclStr* out);
oclBool ConvertJsonToMaterialLibraryDescription_save(const oclStr& jsonString,SMaterialLibraryDescription* out);

/**
* <materialJson>
* json��ʽ���£�
{
	"itemindex":1,
	"matdata":<dataJson>.toStyleString();
	"matdefinitionName":"defName",
	"matindex":0,
	"type":"Default",
	"thumbnail":"./your/path/to/store/thumbnail/pics/",
	"group":"your group name"
}
*/
oclBool ConvertJsonToMaterialDescription(const Json::Value& value,SMaterialDescription* desp);
oclBool ConvertMaterialDescriptionToJson(const SMaterialDescription& desp,Json::Value* j);
oclBool ConvertMaterialDescriptionToJson(const SMaterialDescription& desp,oclStr* out);

/**
* <dataJson>
*json ��ʽ����:
{
	"NorProperty" : {
		"Base" : [
			"BS_Exponent",
			"BS_Fmin",
		]
	},
	"Prop" : {
		"BS_AOIntensity" : {
			"max" : 1,
			"min" : 0,
			"name" : "AOIntensity",
			"step" : 0.01,
			"type" : 10,
			"value" : 1
		}
	},
	"TexProperty" : {
		"DiffuseTexture" : [
		"BS_UseDiffuseMapTS",
		"BS_DiffuseTexturePath",
		"BS_Rotation",
		"BS_UVRepeat"
		],
		"GlossyTexture" : [ "BS_UseGlossyMapTS", "BS_GlossyTexturePath", "BS_Gamma" ]
	},
	"env_Texture" : "./texture/env/Default.hdr",
	"guid" : " ",
	"matdefinitionName" : "",
	"type" : "M_Rubber"
}
*/
oclBool ConvertJsonToDataMaterial(const Json::Value& value,SData_Material* p,std::map<oclStr,oclStr>* names);

oclBool GetTypesTextureFileNames(const std::map<oclStr,Json::Value>& mapTypes,std::vector<oclStr>* out);

void SetMaterialProperty(const oclStr& propName,const VARIANT& v,Json::Value* value,SData_Material* p);
void SetMaterialProperty(const oclStr& propName,const VARIANT& v,const VARIANT& v2,Json::Value* value,SData_Material* p);
void SetMaterialProperty(const oclStr& propName,const VARIANT& v,const VARIANT& v2,const VARIANT& v3,Json::Value* value,SData_Material* p);
void GetMaterialProperty(const oclStr& propName,const Json::Value& value,VARIANT* v);
void GetMaterialProperty(const oclStr& propName,const Json::Value& value,VARIANT* v,VARIANT* v2);
void GetMaterialProperty(const oclStr& propName,const Json::Value& value,VARIANT* v,VARIANT* v2,VARIANT* v3);
/**
����������·����ת��Ϊ�µ�������
*/
oclStr ConvertMaterialTexURLNameToNewName(const SMaterialDescription desp);
}

OCL_NAMESPACE_END