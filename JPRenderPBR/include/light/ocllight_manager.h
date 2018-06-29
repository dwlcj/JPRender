#pragma once

#include <comutil.h>
#include <map>
#include <optixu\optixu_matrix_namespace.h>
#include "json.h"
#include "core\oclcore.h"
#include "../../host_device/data_light.h"

namespace Json{
class Value;
};

OCL_NAMESPACE_START

class oclBuffer;
class oclTexture;
class oclLightSource;
class oclLightSourceEnvironment;

class oclLightManager final{
public:
  oclLightManager()=delete;
  oclLightManager(const oclLightManager&)=delete;
  oclLightManager& operator=(const oclLightManager&)=delete;
  oclLightManager(RTcontext ctx);
  ~oclLightManager();

  oclLightSource* CreateLight(oclUint id,const oclChar* lightType);

  oclStr GetLightJsonString(const std::vector<oclInt>& nodeIndexes)const;

  Json::Value GetLightsJson()const;

  /**
  *��ѡ�еƹ�����json�����л�ȡ��ͬ������
  * @param[in] fstV	 һ���ƹ�����json
  * @param[in] SecV	 һ���ƹ�����json
  */
  Json::Value GetSameBuffer(Json::Value fstV,Json::Value SecV)const;

  /**
  *���ƹ���Ϣ����GPU�ˣ��ж��Ƿ�ʹ��Ĭ�ϵ�HDR�����û��Լ�����HDR�ƹ⣬Ĭ�ϵƹ�رգ�ʹ�����´�����HDR�ƹ�
  */
  void Upload();

  /**
  *����֮ǰ����ĵƹ⣻
  * @param[in] buf	�Ա���ƹ����������
  * @param[in] offset �ƹ�����
  * @param[in] packagePath ���ر���ƹ�ĵ�·��
  */
  oclBool SetLightsProperty(oclStr buf,oclInt offset,oclStr packagePath);

  void DestroyLights();

  oclLightSource* GetLight(oclUint index)const;

	oclInt GetBufferID_lights()const;

	oclInt GetBufferID_materialBallLights()const;

  void FetchTextures(std::vector<const oclTexture*>*)const;

private:
  void Init_();

private:
  RTcontext m_ctx=0;
  std::map<oclUint,oclLightSource*> m_mapLights;
  oclBuffer* m_bufferLights=nullptr;
  oclBuffer* m_bufferMaterialBallLights=nullptr;
	oclLightSourceEnvironment* m_materialBallLight=nullptr;

};

OCL_NAMESPACE_END