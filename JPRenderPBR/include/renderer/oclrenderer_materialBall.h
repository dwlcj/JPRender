#pragma once

#include "oclrenderer_radiance.h"
#include <queue>

OCL_NAMESPACE_START

class oclBuffer;
class oclMaterialManager;
class oclInstance;

class oclRendererMaterialBall:public oclRendererRadiance{
public:
	oclRendererMaterialBall& operator=(oclRendererMaterialBall& o)=delete;
	oclRendererMaterialBall(oclRendererMaterialBall& o)=delete;
	oclRendererMaterialBall(RTcontext);
  ~oclRendererMaterialBall();

  oclBool IsContinueToRender()const override;

  void PreRender()override;

  void PostRender()override;

  oclBool Init()override;

	void SetCamera(oclCameraBase* camera)override;

	void PushMaterialID(oclID id);

	void SetMaterialManager(oclMaterialManager* mgr){
		m_ref_pMaterialMgr=mgr;
	}

	void SetMaterialBallInstance(oclInstance* ins){
		m_ref_pIns=ins;
	}

private:
	/*
	���ڻ��潫Ҫ��Ⱦ�Ĳ���ID����Ϊ������һ��һ����Ⱦ�ģ�ǰ��δ��Ⱦ��ɣ����水��Ŀǰ�����ֻ�ܵȴ���
	��Ⱦ���ָ����һ����Ҫ��Ⱦ��֡�����ڼȶ�֡����
	��vecΪ�յĻ���������Ⱦ����ͣ������
	ÿ��Ⱦ���һ��popһ��ID��
	����û���������Ⱦ�Ĳ������Ա䶯�Ļ������ø���Ⱦ��framecount
	������Ⱦ�Ĳ���id���Ѿ�pop����vector�ģ�
	*/
	std::queue<oclID> m_queMateerialIDCacher;
	oclMaterialManager* m_ref_pMaterialMgr=nullptr;
	oclID m_nCurrentRenderingMaterialID=M_MATERIAL_ID_NONE;
	oclInstance* m_ref_pIns=nullptr;
};

OCL_NAMESPACE_END

