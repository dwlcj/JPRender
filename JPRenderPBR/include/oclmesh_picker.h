#pragma once

#include <optixu\optixu_math_namespace.h>
#include "core\oclcore.h"

OCL_NAMESPACE_START

class oclBuffer;
class oclRenderer;

/**
 * meshʰȡ���ǽ���Ҫ����ʰȡ��������Ϣ������һ��float4��
 * ��ǰ3���ֶ��Ƿ��򣬵��ĸ�ʰȡ����meshID����
 * Ȼ��ͨ��һ��buffer�ύ��OptiX�������Ȼ��ͨ����buffer��ȡ��MeshID
 */
class oclMeshPicker final{
public:
  oclMeshPicker(const oclMeshPicker&)=delete;
  oclMeshPicker operator=(const oclMeshPicker&)=delete;
	oclMeshPicker(RTcontext ctx);
  ~oclMeshPicker();

  /**
   * mousePosInRenderScreen_x|y   �������Ⱦ�������Ͻǵ�������ꣻ
   */
  oclInt GetPickedMeshID(const oclRenderer* renderer,oclInt mousePosInRenderScreen_x,oclInt mousePosInRenderScreen_y);

	oclInt GetPickBufferID()const;

private:
  oclBuffer* m_bufferPicker=nullptr;
  RTcontext m_ctx;
  Nor m_dir;


};

OCL_NAMESPACE_END
