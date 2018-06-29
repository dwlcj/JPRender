#pragma once

#include <vector>
#include <map>
#include <optixu\optixu_aabb_namespace.h>
#include "core\oclcore.h"
#include "../../host_device/data_instance.h"

OCL_NAMESPACE_START

class oclMesh;
class oclMathPlane;
class oclMathSphere;
class oclGeometryManager;

struct SGeometryCreateInfo{
	oclStr name="geometry-name";
	oclID ID;
	EGeometryTypes type;
};

class oclGeometryBase{
public:
	oclGeometryBase& operator=(const oclGeometryBase&)=delete;
	oclGeometryBase(const oclGeometryBase&)=delete;
	oclGeometryBase()=delete;
	oclGeometryBase(EGeometryTypes t,oclInt ID):m_type(t),m_nID(ID){};
	~oclGeometryBase(){
		F_DBG_INFO("[DESTRUCT] -> oclGeometry");
	};

	virtual void FetchProxyInfo(SGeometryProxy* proxy)const=0;

	oclStr GetName()const{ return m_sName; }

	void SetName(oclStr s){ m_sName=s; }

	oclInt GetID()const{ return m_nID; }

	EGeometryTypes GetType()const{ return m_type; }

private:
	const EGeometryTypes m_type;
	const oclInt m_nID;
	oclStr m_sName;
};

class oclGeometryManager final{
public:
	oclGeometryManager(const oclGeometryManager&)=delete;
	oclGeometryManager& operator=(const oclGeometryManager&)=delete;
	oclGeometryManager();
	~oclGeometryManager();

	/**
	 * ����oldMeshID���Ҷ�Ӧmesh�������ڣ��򿽱�һ���µ�mesh�����أ���û�У��򷵻�nullptr
	 * @param[in] oldMeshID ԭmesh��ID
	 */
	oclMesh* CopyMesh(oclInt oldMeshID);

	/**
	 * �ú����϶�����һ��ȫ�µ�Geometry����
	 */
	oclGeometryBase* CreateGeometry(const SGeometryCreateInfo& info);

	/**
	 * �����ڷ���nullptr
	 * @param[in] ID  mesh��map�е�ID
	 */
	oclGeometryBase* GetGeometry(oclInt ID);

	const oclGeometryBase* GetGeometry(oclInt ID)const;

	void DestroyGeometries();

	/**
	 * ����ɾ��ID��������զ������false�����ڵĻ�ɾ��mesh��������true��
	 */
	oclBool DestroyGeometry(oclInt ID)noexcept;

	oclGeometryBase* GetMaterialBall()const{
		return m_pMaterialBall;
	}

	oclGeometryBase* GetGroundPlane()const{
		return m_pGroundPlane;
	}

private:
	void Init_();

private:
	std::map<oclInt,oclGeometryBase*> m_mapGeometries;
	oclGeometryBase* m_pMaterialBall=nullptr;
	oclGeometryBase* m_pGroundPlane=nullptr;
};

OCL_NAMESPACE_END
