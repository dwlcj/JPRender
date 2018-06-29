#pragma once

/**
* ע�⣺
* ��Ҫ��data�ļ��а�������ͷ�ļ�
* �����д���Ҳ��Ҫ��᣻
*/

/****************************************************************************************************/
// �������в������Եĺ꣬������������
/*****************************************************************************************************/
// geometry
#define M_MPROP_GE_BUMPTEXTUREPATH GE_BumpTexturePath
#define M_MPROP_GE_BUMPSCALE GE_BumpScale
#define M_MPROP_GE_ROTATION GE_Rotation
#define M_MPROP_GE_UVREPEAT GE_UVRepeat
#define M_MPROP_GE_REPEAT GE_Repeat
#define M_MPROP_GE_INDENSITY GE_Indensity
#define M_MPROP_GE_ITERATORTIMES GE_IteratorTimes
#define M_MPROP_GE_LAYERSCOUNT GE_LayersCount
#define M_MPROP_GE_USEBUMPMAPTS GE_UseBumpMapTS


// clearcoat
#define M_MPROP_CC_ORANGEPEELTEXTUREPATH CC_OrangePeelTexturePath
#define M_MPROP_CC_COLOR CC_Color
#define M_MPROP_CC_EXPONENT CC_Exponent
#define M_MPROP_CC_FMAX CC_Fmax
#define M_MPROP_CC_FMIN CC_Fmin
#define M_MPROP_CC_USEORANGEPEELNORMALMAPTS CC_UseOrangePeelNormalMapTS
#define M_MPROP_CC_BUMPSCALE CC_BumpScale
#define M_MPROP_CC_ROTATION CC_Rotation
#define M_MPROP_CC_UVREPEAT CC_UVRepeat
#define M_MPROP_CC_WEIGHT CC_Weight


// flake
#define M_MPROP_CF_COLOR CF_Color
#define M_MPROP_CF_IRREGULARITY CF_Irregularity
#define M_MPROP_CF_REFLECTIVITY CF_Reflectivity
#define M_MPROP_CF_DENSITY CF_Density
#define M_MPROP_CF_ROUGHNESS CF_Roughness
#define M_MPROP_CF_SIZE CF_Size


// base
#define M_MPROP_BS_CHECKBOARDSIZE BS_CheckBoardSize
#define M_MPROP_BS_EXPONENT BS_Exponent
#define M_MPROP_BS_FMIN BS_Fmin
#define M_MPROP_BS_FMAX BS_Fmax
#define M_MPROP_BS_DIFFUSECOLOR BS_DiffuseColor 
#define M_MPROP_BS_GLOSSYCOLOR BS_GlossyColor   
#define M_MPROP_BS_REFLECTCOLOR BS_ReflectColor 
#define M_MPROP_BS_UVREPEAT BS_UVRepeat
#define M_MPROP_BS_IOR BS_IOR
#define M_MPROP_BS_GAMMA BS_Gamma
#define M_MPROP_BS_AOINTENSITY BS_AOIntensity
#define M_MPROP_BS_INTENSITY BS_Intensity
#define M_MPROP_BS_SIGMA BS_Sigma
#define M_MPROP_BS_ROTATION BS_Rotation
#define M_MPROP_BS_ROUGHNESS BS_Roughness
#define M_MPROP_BS_CENTER_X BS_CenterX
#define M_MPROP_BS_CENTER_Y BS_CenterY
#define M_MPROP_BS_CENTER_Z BS_CenterZ
#define M_MPROP_BS_DIFFUSEREFLECTANCE BS_DiffuseReflectance
#define M_MPROP_BS_SPECULARREFLECTANCE BS_SpecularReflectance
#define M_MPROP_BS_USEDIFFUSEMAPTS BS_UseDiffuseMapTS
#define M_MPROP_BS_USEGLOSSYMAPTS BS_UseGlossyMapTS
#define M_MPROP_BS_ANISOTROPYU BS_AnisotropyU
#define M_MPROP_BS_ANISOTROPYV BS_AnisotropyV
#define M_MPROP_BS_DIFFUSETEXTUREPATH BS_DiffuseTexturePath
#define M_MPROP_BS_GLOSSYTEXTUREPATH BS_GlossyTexturePath

#define M_MPROP_SHADOW_ATTENUATION ShadowAttenuation
#define M_MPROP_INDEX material_index;


struct SData_Texture{
	optix::float4 color;

	optix::float2 UVrepeat;
	float rotation;
	float bumpscale;

	float invGamma;
	float place_holder;
	int TSID;
	int enable;
};//48 bytes

struct SData_Fresnel{
	float exponent;
	float fmin;
	float fmax;
	float place_holder;
};// 16 bytes;

struct SData_Material{
	//float GE_indensity;
	//int GE_iteratortimes;
	//int GE_layerscount;
	//float BS_sigma;              //sigma ONģ�͵�΢����������ֵΪ0���˻�ΪLamberianģ�ͣ�
	//float BS_absorption;         //����������


	SData_Texture CC_texture;
	SData_Texture BS_textureDiffuse;
	SData_Texture BS_textureGlossy;
	SData_Texture GE_texture;
	SData_Fresnel CC_fresnel;
	SData_Fresnel BS_fresnel;
	union{
		optix::float4 BS_colorReflect;
		optix::float4 CF_color;
	};
	optix::float4 BS_center;

	float CC_weight;
	float CF_irregularity;
	float CF_reflectivity;
	float CF_roughness;

	float CF_size;
	float CF_density;
	float BS_ior;
	float BS_roughness;

	float BS_reflectanceSpecular;//specular�����
	float BS_reflectanceDiffuse; //diffuse�����
	float BS_anisotropyU;
	float BS_anisotropyV;

	float BS_AOIntensity;
	float BS_checkboardSize;
	float GE_shadowAttenuation;
	int materialIndex;
};

/*
���ֽṹ���������ǵ�ģ��ģ�顣
struct SData_Vertex{
	optix::float3 pos;
	optix::float3 normal;
	optix::float3 tangent;
	optix::float3 bitangent;
	optix::float2 uv;
};
*/

struct SData_Instance{
	/// mesh
	int vertexBufferID;//float3
	int norBufferID;//float3
	int tanBufferID;//float3�����ܻ�û��ֵ��
	int biTanBufferID;//float3�����ܻ�û��ֵ��
	int uvBufferID;//float2
	int indexBufferID;//mesh�����������������id��Ԫ���Ǹ�int3�����buffer�漸��Ԫ�أ�����ζ���м��������棻
  int tanBufferSize;
	int biTanBufferSize;

	/// material
	int materialBufferID;//����SData_Material������id��Ԫ���Ǹ��Զ���ṹ�壬�������������Ҫ���������ݣ�
	int materialBufferOffset;//��mesh����ʹ�õĲ��������ڻ������е�ƫ�ƣ�

	/// instance
	int nodeIndex;//mesh��ģ�Ͳ㼶�ṹ�еĽڵ�id������ʰȡ��
	int worldMatrixBufferID;//���������Դ����mesh��������������ꣻ

};
