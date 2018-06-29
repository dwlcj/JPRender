#pragma once

#include "geometry\oclgeometry_base.h"

OCL_NAMESPACE_START

class oclMathPlane :public oclGeometryBase{
public:
// ����չ����λ�ã����򡢱߳��ȳ�Ա������
//Ŀǰʹ�õĵط��ǵ��棬λ����ԭ�㣬����y+���������ЩҲ��Ĭ�ϲ���);
	void FetchProxyInfo(SGeometryProxy* proxy)const override;

private:
	friend oclGeometryManager;

	oclMathPlane& operator=(const oclMathPlane&)=delete;
	oclMathPlane(const oclMathPlane&)=delete;
	oclMathPlane()=delete;
	oclMathPlane(oclInt index);
	~oclMathPlane();

private:
	Pos m_pos;//ƽ������ĵ�
	Nor m_normal;
	oclFloat m_width,m_height;
	
};

OCL_NAMESPACE_END
