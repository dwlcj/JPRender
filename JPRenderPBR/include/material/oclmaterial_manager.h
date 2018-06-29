#pragma once

#include "oclmaterial_common.h"

OCL_NAMESPACE_START

class oclBuffer;
class oclMaterial;
class oclMaterialLibrary;

class oclMaterialManager final{

public:
  oclMaterialManager()=delete;
  oclMaterialManager(const oclMaterialManager&)=delete;
	oclMaterialManager(RTcontext ctx);
  ~oclMaterialManager();

	/**
	* ���ʿⴴ��ʧ�ܷ���nullptr
	*/
	oclMaterialLibrary* CreateLibrary(SMaterialLibraryDescription desp);

	/**
	* �ɹ����٣�����true������false
	*/
	oclBool DestroyLibrary(oclMaterialLibrary* lib);

	/**
	* ��ȡ���������Ĳ��ʿ⣬�����ڵĻ�����nullptr����ʱ�������Ҫ����CreateLibrary�������ʿ�
	*/
	oclMaterialLibrary* GetLibrary(oclInt libIndex);

	const oclMaterialLibrary* GetLibrary(oclInt libIndex)const;

	/**
	* �������еĲ��ʿ⣬���Ҳ���ID��Ӧ�Ĳ��ʣ�
	* ���������ҵ��Ĳ������ڵĲ��ʿ⣻
	*/
	oclMaterial* GetMaterial(oclID ID,oclMaterialLibrary** lib);

  /**
  *�ɲ���ID��ȡ���ڲ��ʿ��е�����
  */
	oclInt GetLibraryIndex(oclID ID)const;

  /**
  *
  * @param[in] definitionName       �����������Զ��������
  * @param[in] matindex             �����еĲ��ʺͲ��ʿ��еĲ�����m_mapMaterials�е�����
  * @param[in] type                 �������ʵ�����Default Metal ��
  * @param[in] isAddMatToScene      �����Ĳ����Ƿ���ӵ�������
  * @param[in] jsonString           �������Ĭ�ϲ���str=""ʱ���ڴ���Ĭ�ϲ��ʣ���Ϊ��ʱ���ڴ����Ѿ�������Ĳ��ʣ�str��Ϊ����Ĳ�������
  * @param[in] path                 �ѱ���Ĳ��ʿ�·��
  */
  //oclMaterial* CreateMaterialAndExchangeMaterialIndex(oclStr definitionName,oclInt matindex,oclStr type,oclBool isAddMatToScene=true,oclStr jsonString="",oclStr path="./texture/");

private:
  /**
  * create necessary oclbuffers;
  * load disk material type file(*.dat).
  * If exist and load successfully return true;
  * else return false;
  */
  oclBool Init_();

  /**
  *����������ʻ�����ͼ·��
  *@param[in] topath               Ҫ�������ͼ·��
  *@param[in] oldEnvPath           ��ͼԭʼ·��
  */
  oclBool SaveMaterialEnvTexPath(oclStr topath,oclStr oldEnvPath);

private:
  RTcontext m_ctx;
  std::map<oclInt,oclMaterialLibrary*> m_mapLibs; 
};

OCL_NAMESPACE_END
