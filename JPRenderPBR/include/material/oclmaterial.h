#pragma once

#include "OAIDL.h"
#include <comutil.h>
#include <optixu\optixu_math_namespace.h>
#include "oclmaterial_common.h"
#include "../../host_device/data_instance.h"

OCL_NAMESPACE_START

class oclTexture;

class oclMaterial final{
public:
	oclMaterial(RTcontext ctx,oclInt bufID,oclUint bufOffset,oclID ID);
  ~oclMaterial();

  inline void SetMaterialInUse(oclBool value){ m_bIsMaterialInUse=value; };

  inline void SetGroupName(oclStr name){ m_sGroupName=name; }

  void SetDefinitionName(const oclStr& name);

	inline oclInt GetBufferOffset()const{ return m_nBufferOffset; }

	inline const SData_Material& GetMaterialData()const{ return *m_materialData; }

  /**
  *�޸Ĳ�������ֵ
  *@param[in] propName        ����������
  *@param[in] v               �޸ĺ������ֵ
  *@param[in] count           ���Ը���
  */
  oclBool SetProperty(const oclChar* propName,VARIANT* v,oclInt count);

	inline oclID GetID()const{ return m_nID; }
	
	inline oclInt GetIndex()const{ return m_nItemIndex; }

	inline oclInt GetLibID()const{ return m_nLibID; }

	inline oclStr GetDefinitionName()const{ return m_sDefinitionName; }

  inline oclStr GetGroupName()const{ return m_sGroupName; }

  inline oclStr GetType()const{ return m_sMaterialType; }

  inline oclBool GetMaterialInUse()const{ return m_bIsMaterialInUse; };

  oclBool GetProperty(const oclChar* propName,VARIANT* v,oclInt count)const;

	SMaterialDescription GetDescription()const;

	/**
	* ��վ��������ò������ԣ�
	*/
	oclBool Reset(const SMaterialDescription& d);

	void FetchProxy(SMaterialProxy* proxy)const;

	/**
	* ��ȡ�ò������е��������ڱ�������ʹ��
	*/
  void FetchTextures(std::vector<const oclTexture*>*)const;

private:
  oclMaterial()=delete;
  oclMaterial(const oclMaterial&)=delete;
  oclMaterial& operator=(const oclMaterial&)=delete;

  oclTexture* CreateTexture_(const oclStr& fileURL,const oclStr& propName);

  void ClearTextures_();

  void SetTextureSamplerID_(const oclStr& propName,oclInt TSID);

private:
	const oclInt m_nBufferID=-1;//��ֵ�ǲ�����������RTbuffer��ID��
	const oclInt m_nBufferOffset=-1;//��ֵ�ǲ���������RTbuffer�е�ƫ�ƣ����ύ��OptiXʹ�õı�����
	const oclID m_nID;//���ʵ�ȫ��ΨһID��

  oclStr m_sMaterialType;
  oclStr m_sTexturePath="./texture/";
  oclStr m_sGroupName="no-group-name-assigned";
	oclStr m_sDefinitionName="";
	oclInt m_nItemIndex;//�����ڲ��ʿ��е�������
	oclInt m_nLibID;//�������ڲ��ʿ�ı�ţ�
  oclBool m_bIsMaterialInUse=false;
  SData_Material* m_materialData=nullptr;
  RTcontext m_ctx=0;//optix��Ⱦ�����ģ��������õ�ΨһĿ���Ǵ���RTtextureʱʹ�ã�
  Json::Value m_JsonMaterial;//�ύ���棬������ȾGUIʹ�ã�
  std::map<oclStr,oclTexture*> m_mapTextures;
  std::map<oclStr,oclStr> m_mapTexuresName;//��һ��Ԫ��Ϊԭʼ�������ƣ��ڶ���Ϊ�޸ĺ����������
};

OCL_NAMESPACE_END
