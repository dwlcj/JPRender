#include "core\ocltexture.h"
#include <time.h>
#include "core\oclbuffer_manager.h"
#include "core\oclimage_loader.h"
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include "boost\filesystem.hpp"

OCL_NAMESPACE_START

oclTexture::oclTexture(RTcontext ctx){
  OCL_TRY;
  OCL_CHECK_ERROR(rtTextureSamplerCreate(ctx,&m_textureSampler));
  OCL_CHECK_ERROR(rtTextureSamplerGetId(m_textureSampler,&m_uTSID));
  OCL_CATCH;
}

oclTexture::~oclTexture(){
	F_DBG_INFO("[DESTRUCT] -> oclTexture,m_sFileURL["+oclStr(m_sFileURL.c_str())+"]");
  OCL_TRY;
  OCL_CHECK_ERROR(rtTextureSamplerDestroy(m_textureSampler));
  OCL_CATCH;
  oclBufferManager::S()->Destroy(m_poclBuffer);
  m_poclBuffer=nullptr;
}

void oclTexture::GetSize(oclInt* width,oclInt* height)const{
  if(m_poclBuffer) m_poclBuffer->GetSize(width,height);
  else{
    width=height=0;
  }
}

oclBool oclTexture::Reset(const STextureDescription & param){
  m_sFileURL=param.fileURL;

  /// 1. ���Դ����µ����������� ʧ�ܱ�ʾ�Ѿ����ڣ���ȡ���ɣ�
  oclBuffer* buf=oclBufferManager::S()->Create(m_sFileURL,RT_BUFFER_INPUT,RT_FORMAT_FLOAT4);
  if(buf){
    /// 1.1. �����ɹ�����ʾ��һ��ȫ�µĻ���������Ҫ����image���ݣ�
    oclImageLoader loader;
    if(loader.Load(m_sFileURL)){
      buf->SetSize(loader.GetWidth(),loader.GetHeight());
      buf->SetData(loader.GetImageData(),loader.GetWidth()*loader.GetHeight());
    } else{
      oclBufferManager::S()->Destroy(buf);
      buf=nullptr;
      m_sFileURL="";
      F_DBG_ERROR("image��ȡʧ�ܣ�������⣻");
      F_DBG_ASSERT(false);
      return false;
    }
  } else{
    buf=oclBufferManager::S()->Get(m_sFileURL);
  }

  /// 2. ���پ�buffer����Destroy���жϲ����Ĵ����ԣ���������Ҫ�ڴ���֮��
  oclBufferManager::S()->Destroy(m_poclBuffer);
  m_poclBuffer=buf;

  /// 3. �������������������ԣ�
  oclBufferManager::SetoclBufferToRTtexturesampler(m_poclBuffer,m_textureSampler);
  OCL_TRY;
  OCL_CHECK_ERROR(rtTextureSamplerSetWrapMode(m_textureSampler,0,param.wrapModeX));
  OCL_CHECK_ERROR(rtTextureSamplerSetWrapMode(m_textureSampler,1,param.wrapModeY));
  OCL_CHECK_ERROR(rtTextureSamplerSetWrapMode(m_textureSampler,2,param.wrapModeZ));
  OCL_CHECK_ERROR(rtTextureSamplerSetIndexingMode(m_textureSampler,RT_TEXTURE_INDEX_NORMALIZED_COORDINATES));
  OCL_CHECK_ERROR(rtTextureSamplerSetFilteringModes(m_textureSampler,param.filterModeX,param.filterModeY,param.filterModeZ));
  OCL_CHECK_ERROR(rtTextureSamplerSetReadMode(m_textureSampler,RT_TEXTURE_READ_NORMALIZED_FLOAT));
  OCL_CHECK_ERROR(rtTextureSamplerSetMaxAnisotropy(m_textureSampler,1.f));
  // �������߱�optix�ٷ����ϣ�3.9�Ժ�
  //OCL_CHECK_ERROR(rtTextureSamplerSetMipLevelCount(m_textureSampler,1u));
  //OCL_CHECK_ERROR(rtTextureSamplerSetArraySize(m_textureSampler,1u));
  OCL_CATCH;

	/// 4. �ı��ļ��������ⲻͬĿ¼�µĲ�ͬ�ļ���������ͬ����ɸ��ǣ�
	/// �ı�Ĳ����Ǹ�stem���_<ʱ��>��׺����չ������.tmaxp��
	boost::filesystem::path filePath(m_sFileURL);
	if(strcmp(filePath.extension().string().c_str(),".tmaxp")==0){
		m_sFileNewName=filePath.filename().string();
	} else{
		oclStr fileOldStem=filePath.stem().string();
		time_t t=time(NULL);
		m_sFileNewName=fileOldStem+"_"+std::to_string(uintmax_t(t))+".tmaxp";
	}
  return true;
}

OCL_NAMESPACE_END
