#pragma once
#include "oclmaterial_common.h"

struct SData_Material;

OCL_NAMESPACE_START

class oclBuffer;
class oclTexture;
class oclMaterial;

class oclMaterialLibrary final{
public:
	oclMaterialLibrary(RTcontext ctx);
  ~oclMaterialLibrary();

	oclBool Init(const SMaterialLibraryDescription& param);

  /**
	*���ز��ʿ������в��ʵ�id
	*/
  void GetMaterialIDs(std::vector<oclID>* v)const;

  oclMaterial* GetMaterial(oclID ID);

  const oclMaterial* GetMaterial(oclID ID)const;

  oclMaterial* GetMaterialByIndex(oclInt index);

  oclInt GetMaterialCount()const{ return m_mapMaterials.size(); };

	void DestroyMaterials();

	oclInt GetID()const{ return m_nLibID; }

	oclStr GetLibName()const{ return m_sName; }

	/**
	* ɾ��������ָ�������в��ʣ�������Ϊ����ID
	*/
  oclBool DestroyMaterials(const std::vector<oclInt>& vecIds);

	//oclBool DestroyUnusedMaterials();

  /**
	* ����һ������ģ�ͺ���������øýӿڴ������ʣ����ģ����Ҫn�����ʣ��ýӿڻᱻ����n�飻
  */
	oclMaterial* CreateMaterial(SMaterialDescription desp);

  /**
  *delete material library config data which exist in tab page tabindex, item number itemindex.
  * this function will not delete current using material instance. They are different
  * material instance essentially.
  * return true if item exist.
  *delete material library config data which exist in tab page tabindex, item number itemindex.
  * @param[in]	 ID �ò��ʿ��еĲ���ID��Ҳ��ȫ��ΨһID��
  */
	oclBool DestroyMaterial(oclID ID);

	/**
	* ��ȡ���ʿ���ַ�������������������ʿ⣬libraryҲ���Դ���������Ĳ��ʿ������������ʿ�
	*/
  SMaterialLibraryDescription GetDescription()const;

  void FetchTextures(std::vector<const oclTexture*>*)const;

	void Upload();

private:
  RTcontext m_ctx;
  std::map<oclID,oclMaterial*> m_mapMaterials;
  oclStr m_sName="no-library-name-assigned";
  oclStr m_sLibFilePath="";//���ʿ��ļ���Ӳ���ϵĵ�ַ���½��Ĳ��ʿ��ֵ��ȻΪ""�����صĲ��ʿ�ͻ��¼�ļ�URL��
	oclInt m_nLibID=-1;//���ʿ�ID��
	oclBuffer* m_pBufMaterialData;//����ò��ʿ����в������ݵĻ�������
	oclUint m_nNextMaterialDataBufOffset=0u;//��һ������������buffer�е�ƫ�ƣ�
	oclInt m_nBufID=-1;
};

OCL_NAMESPACE_END

