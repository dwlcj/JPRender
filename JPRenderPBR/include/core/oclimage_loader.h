#pragma once

#include "core\oclcore.h"

OCL_NAMESPACE_START


class oclImageLoader{
public:
  oclImageLoader(const oclImageLoader&)=delete;
  oclImageLoader operator=(const oclImageLoader&)=delete;
  oclImageLoader();
  ~oclImageLoader();

  /**
   * ֻ�гɹ����زŷ���true��
   * ���ظ�����ʹ�ã�
   */
  oclBool Load(oclStr fileURL);

  oclFloat4* GetImageData()const{
    return m_data;
  }

  oclUint GetWidth()const{
    return m_uWidth;
  }

  oclUint GetHeight()const{
    return m_uHeight;
  }


private:
  oclFloat4* m_data;
  oclUint m_uWidth,m_uHeight;
  oclBool m_bDown=false;
};

OCL_NAMESPACE_END
