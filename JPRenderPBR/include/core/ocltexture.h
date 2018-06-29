#pragma once

#include "oclcore.h"

OCL_NAMESPACE_START

struct STextureDescription {
  oclStr fileURL;
  RTwrapmode wrapModeX;
  RTwrapmode wrapModeY;
  RTwrapmode wrapModeZ;
  RTfiltermode filterModeX;
  RTfiltermode filterModeY;
  RTfiltermode filterModeZ;
  oclUint type;
  RTformat format;
  oclUint mipmapCount;
};

class oclBuffer;

/**
 * texture����������ע�⣺oclBuffer�ǹ���ģ�
 */
class oclTexture {
public:
  oclTexture() = delete;
  oclTexture(const oclTexture&) = delete;
  oclTexture& operator=(const oclTexture&) = delete;
  oclTexture(RTcontext ctx);
  ~oclTexture();
  oclInt GetTextureSamplerID()const{ return m_uTSID; }
  const oclStr GetURL()const{ return m_sFileURL; }
	const oclStr GetFileNewName()const{ return m_sFileNewName; };
  void GetSize(oclInt* width, oclInt* height)const;

  // �ýӿڿ��Զ�ε��ã�
  oclBool Reset(const STextureDescription& param);

private:
  RTtexturesampler m_textureSampler = nullptr;
  oclBuffer* m_poclBuffer=nullptr;

  oclStr m_sFileURL="";
  oclInt m_uTSID;
	oclStr m_sFileNewName;
};

OCL_NAMESPACE_END
