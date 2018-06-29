#ifndef VIRTUALBASEPROCESS_H_
#define VIRTUALBASEPROCESS_H_
#include "RenderMath.h"
#include <OAIdl.h>
#include <functional>
#include <set>
#include "VegetationValueChanger.h"
#include "DataType.h"
#include <list>
//#include "ITmaxSystem.h"

namespace OPENNP{
class OPENFuncs;
struct Material;
}
typedef std::function<void(int nodeIndex, int meshIndex)> NotifyMeshIndexChange;
namespace RenderMax {
	class IBaseProcess {
	public:
		virtual ~IBaseProcess() {};

		//virtual bool CreateViewport(void* pHwnd) { return false; }
		//��ʼ��
		virtual void ImportFile(RM_FileInfo) = 0;
		virtual void ImportResources(const char*) = 0;
		virtual void SaveFile(RM_FileInfo) = 0;
		virtual void initObjBase() = 0;

		//��Ⱦ����
		virtual bool RenderAsync() = 0;
		virtual bool RenderMatBall() = 0;

		//�ͷŶ���
		virtual void ReleaseObject() = 0;
		virtual void removeAllMesh() = 0;

		//light method
		virtual void removeLight(unsigned int lightIndex) = 0;
		virtual void createLight(int lightIndex, const char* lightType) = 0;
		virtual void setLightProperty(unsigned int lightIndex, const char* propName, VARIANT* v, int count) = 0;
		virtual void getLightProperty(unsigned int lightIndex, const char* propName, float*) = 0;
		virtual bool getLightProperty(unsigned int lightIndex, const char* propName, VARIANT* v, int count) = 0;

		virtual void setLightPreDelete(int, bool) = 0;
		virtual std::list<int> GetlightShowList() = 0;
		virtual std::string getLightBuffer(unsigned int lightIndex) = 0;
		virtual std::string getLightBuffer(std::vector<int>) = 0; //�˺���Ӧ��Ϊ���麯��
		virtual std::string getAllLightBuffer(int saveMode) = 0;
		virtual void createAllLight(std::string buf, int offset) = 0;
		virtual void setLightAllProperty(int index, std::string json) = 0;
		virtual void setEulerAngle(int, float, float, float, int nodeType) = 0;
		//virtual void ImportLightResources() = 0;
		//set the path of the environment
		virtual bool setEnvPath(std::string path) = 0;
		virtual void createSurroundLight(int surroundid, int lightIndex, const char* lightType) = 0;
		virtual void createSurroundAllLight(int surroundid, std::string buf, int offset) = 0;
		virtual void SetViewProMat(UINT* pData) {}
		//clip
		virtual void deleteSectionPlane() = 0;
		virtual bool removeClip(int nNodeIndex) = 0;

		//mesh��ز���:
		//����mesh������ͷ�������
		virtual void setMeshRUVAndNormal(int index, float* textures, float* normals) = 0;

		//����mesh������ͷ�������Ͷ���
		virtual void UpdateVecInfo(int index, int nVexSize, const float* pVex, const float* pNormal, const float* pUV, int nIndexSize, const unsigned int* pIndex) = 0;
		virtual void CopyNode(int srcNodeid, int newNodeId, TreeObject_Type nodeType) = 0;
		virtual void UpdateMeshForCutPlane(int meshIndex, int nVexSize, int nIndexSize, const VERTEX_P3F_CU_T2F* vers, const float* normals, const unsigned int* indices) {}
		virtual void getMeshDataForCutPlane(int meshIndex, VERTEX_P3F_CU_T2F* vers, float* normals, unsigned int* indices) {}

		virtual void InitMatballRenderWnd(void * hWnd) {}
		virtual void GetMatballBuffer(int matID, int libID, int width, int height, void* pbuf) {}
		virtual void GetSpecularMapBuffer(void* pbuf) {}
		virtual void GetNormalMapBuffer(void* pbuf) {}
		/**
		* @param[in] meshName              mesh����
		* @param[in] materialName          ��������
		* @param[in] nodeIndex             �ڵ�����
		* @param[in] mateiralIndex         ��������
		* @param[in] iVertexCount          ��������
		* @param[in] indexCount            ��������
		* @param[in] pInVex                ��������
		* @param[in] normals               ��������
		* @param[in] indices               ��������
		* @param[in] textures              ��������
		* @param[in] Tangents              ��������
		* @param[in] Bitangent             ��δʹ��
		* @param[in] worldMat              �����������
		* @param[in] maxbox                ��Χ�����Ͻ�x,y,z����
		* @param[in] minbox                ��Χ�����Ͻ�x,y,z����
		* @param[in] meshCount             mesh����
		* @param[in] materialCount         ��������
		*/
		virtual void processMesh(bool isSurround,int surroundid, const char* meshName, const char* materialName, int nodeIndex, int mateiralIndex, int vertexSize, int indexCount, const float* pInVex, const float* normals,
			const unsigned int* indices, const float* textures, const float* Tangents, const float* Bitangent, float* worldMat, const float* maxbox, const float* minbox, int meshCount, int materialCount, const char* entityParams) = 0;//��ģ�Ͷ�ȡmesh

		virtual void writeMesh(int index, char* meshName, std::string& materialName, int& mateiralIndex, float* pInVex, float* normals,
			unsigned int* indices, float* textures, float* Tangents, float* Bitangents, float* maxbox, float* minbox, std::string& entityparams) = 0;//��optix��ȡmesh

		virtual void getMeshVertexIndexCount(int i, int& indexCount, int& vertexCount, int& meshNameLen) = 0;//���mesh��������������ֵĳ���

		virtual void getMeshNormalAndTexture(int index, float* normals, float* textures) = 0; //���mesh�ķ��ߺ�����

		virtual void getVertexAndIndexOfMesh(int index, float* vertex, unsigned int* indices) = 0;//��ȡmesh�Ķ������������

		virtual int getMeshCount() = 0;//���mesh��Ŀ
		virtual void setMeshCount(int count) = 0;
		virtual void updateWorldMat(float* mat, int instanceIndex, int nodeType) = 0;//����mesh�����ݾ���
		virtual void setCenter(float*, int, int) = 0;
		virtual void setCenter(int, float, float, float) = 0;;
		virtual void Init() = 0;//���ó����е�����

		virtual void deleteObjBase(int key) = 0;//mesh�����������Ӧmesh

		virtual void ShowUnSelectMesh(int* index, int size, bool bShow) = 0;
		virtual void HideSelectMesh(int index, bool bHide, int type) = 0;
		virtual void HideSelectLight(int index, bool bShow) = 0;

		//surround����
		virtual void removeSurroundChild(int surroundid)=0;//ɾ��optix�ж�Ӧ��mesh����
		virtual int getSurroundInstanceCount()=0;//��ȡsurround��mesh����
		virtual void setBackScene(int index,bool isShow)=0;
		virtual void setAllBackScene(bool isShow)=0;
		virtual bool processSurroundCamera()=0;
		virtual void HideSurroundLight(int surroundid, bool bShow) = 0;
		virtual void HideSurroundMesh(int surroundid, bool bHide) = 0;
		virtual void deleteSurroundLight(int surroundid) = 0;

		//opengl����		
		//��ȡ���buf��С
		virtual size_t GetOutBufSize() = 0;

		//�������buf
		virtual void CreateOutPutBuf(unsigned int/*glvboid*/,
			unsigned int/*width*/, unsigned int/*height*/) = 0;

		//�������buf��С
		virtual void SetOutputBufReSize(unsigned int/*width*/, unsigned int/*height*/, void* hwnd =nullptr) = 0;
		virtual void SetMatBallOutputBufSize(unsigned int/*width*/, unsigned int/*height*/) = 0;

		//��ע��GLBUF
		virtual void UnregisterGLBuffer() = 0;

		//��ȡGLID
		virtual unsigned int/*glvboid*/GetGLBOId() = 0;

		//��ȡ��С
		virtual unsigned int GetElementSize() = 0;

		//ע��GLBUF
		virtual void RegisterGLBuffer() = 0;

		virtual void* OutPutMap() = 0;
		virtual void OutPutUnMap() = 0;
		virtual void* OutPutMatBallMap() = 0;
		virtual void* OutPutLayerBuffer(unsigned int layerType, unsigned int quality = 100) = 0;
		virtual void AddLayer(unsigned int layerType) = 0;
		virtual void RemoveLayer(unsigned int layerType) = 0;

		//CameraInfo����ͷ����
		//get pickout ID
		virtual bool GetPickOutID(int x, int y, int& nOutID) = 0;
		virtual void GetHitPos(float& x, float& y, float& z) = 0;
		virtual void GetWorldRay(float* srcRay, float* rayDir) = 0;
		//htc handle
		virtual void GetHandleRayPoint(float* HTCHandleViveInfo) = 0;
		virtual std::map<int, float> GetHTCHandleButtonState() = 0;
		virtual void GetPickOutIDByHTCHandle(Vector3D srcPos, Vector3D dir, bool bNetLeader, Vector3D& t_hitPos, int& nOutID) = 0;
		virtual void SetOperateHandleShow(bool isShow) = 0;
		virtual void SetHTCHandle(Vector3D pos, Vector3D up, Vector3D dir, bool isRight) = 0;
		virtual void SetHTCHandle(Vector3D Lpos, Vector3D Lup, Vector3D Ldir, Vector3D Rpos, Vector3D Rup, Vector3D Rdir) = 0;
		virtual void SetHTCHandle(bool isShow, bool MetaHandIsShow) =0;
		virtual void SetHTCHandlePosOffset(float x, float y, float z,bool isMeta) = 0;
		virtual void SetHTCCameraOffset(float x, float y, float z,bool isMeta) = 0;
		virtual void SetHTCCameraScale(float t_scale) = 0;
		virtual void GetHtcHandleViveMat(float* mat) = 0;
		virtual void SetHTCVive(bool b,bool isMeta) = 0;
		virtual void SetIsSplitScreen(bool b) = 0;
		virtual void GetHTCCameraInfo(int t_eye, float& t_fov, float& eye_x, float& eye_y, float& eye_z,
			float& up_x, float& up_y, float& up_z,
			float& dir_x, float& dir_y, float& dir_z, float& t_modulatedHalfIpd, float& aspectRatio, float& transfAsymH, float& transfAsymV) = 0;
		virtual void SetHTCSelectFeedback() = 0;
		virtual void SetHTCNetPeoplePos(int SelfClientID, HTC_PosMessage* t_mess, bool Allshow) = 0;
		virtual void SetHTCLeftHandleRayMat(Vector3D t_pos) = 0;
		//htc end

		//��ȡ�����Ϣ
		virtual void getCameraInfo(Vector3D& eye, Vector3D& lookat, Vector3D& up, float& fov) = 0;
		virtual	void UpdatePinholeCamera(Vector3D eye, Vector3D lookat, Vector3D up, float HFOV, float VFOV) = 0;
		virtual void GetOrthographicWith(float &with) = 0;
		virtual	void SetOrthographicWith(float with) = 0;
		virtual	void SetCameraType(CameraType camtype) = 0;
		virtual void UpdateBindBox(Vector3D vMin, Vector3D vMax) = 0;
		virtual RenderAABBV3& GetLocalBBOX(int index) = 0;
		virtual RenderAABBV3& GetWorldBBOX(int index) = 0;
		virtual RenderAABBV3& GetSceneBBOX() = 0;

		virtual void updateAABB() = 0;
		virtual void updateAABB(RenderAABBV3 aabb, int index) = 0;
		virtual void GetRootworld(float* rootworld) = 0;
		virtual int GetMeshNodeIndex(int meshIndex) = 0;
		virtual void SetStereo(bool b) = 0;
		virtual void SetActiveStereo(bool b) = 0;
		virtual void SetEyeDist(float dist) = 0;
		virtual void SetScreenDist(float dist) = 0;
		virtual bool GetStereo() = 0;
		virtual float GetEyeDist() = 0;
		virtual float GetScreenDist() = 0;
		virtual bool GetVRMode() = 0;
		virtual void SetFarPlane(float t_far) = 0;
		virtual void SetNearPlane(float t_near) = 0;
		virtual void setGroundPositionMin() = 0;
		virtual void GetSuperSampling(int& t_supersampling) = 0;

		//����mesh��Χ�еĸ����������Сֵ�����õ��棨��ʱֻ�������õ��棬���������б���ô���
		virtual bool calWorldMinXYZ(float& minX, float& minY, float& minZ) = 0;
		virtual bool calWorldMaxXYZ(float& maxX, float& maxY, float& maxZ) = 0;
		virtual bool getAABBLength(float& Length) = 0;

		virtual void setMeshIndex(int meshIndex) = 0;
		//��ȡ�µĿ���meshIndex
		virtual int GetNewMeshIndex() = 0;
		virtual void setMeshChangeCallBack(NotifyMeshIndexChange func) { this->meshIndexChange = func;}

		virtual void processClipPlane(int nNodeIndex, float* pMat, bool bLight) = 0;
		virtual void ChangeClipLight(int nInstanceIndex, bool bLight) = 0;
		virtual bool GetClipLight(int nInstanceIndex) = 0;


		virtual void SetRenderLevel(int nLevel) = 0;//0-2Ĭ����0
		virtual void  SetRayDepthReflect(int type, int value) = 0;
		virtual int GetRenderLevel() = 0;//0-2Ĭ����0
		virtual void SetTexturePackagePath(std::string path) = 0;
		virtual void SetTexturePackage(int saveMode) = 0;
		//HsessionView

		virtual	std::string GetHsessionViewOptionsBuff() = 0;
		virtual	bool GetHsessionViewOptionsBuff(VARIANT *v) = 0;
		virtual bool SetHsessionViewOption(const char* propertyName, VARIANT* v) = 0;
		virtual void SetAllHsessionViewOption(std::string jsonbuff) = 0;

		virtual bool ExportCurrentRenderLayer(const std::string& fileName, const unsigned int layerType = 0, unsigned int quality = 100) = 0;

		//Environment
		virtual	std::string GetEnvironmentOptionsBuff() = 0;
		virtual bool GetEnvironmentOptionsBuff(VARIANT *v) = 0;
		virtual bool SetEnvironmentType(const char* EnvType) = 0;
		virtual bool SetEnvironmentOption(const char* propertyName, VARIANT* v) = 0;
		virtual void SetAllEnvironmentOption(std::string jsonbuff) = 0;


		virtual	std::string GetEnvFunctionBuff() = 0;
		virtual bool GetEnvFunctionBuff(VARIANT *v) = 0;
		virtual bool SetEnvFunction(const char* propertyName, VARIANT* v) = 0;
		virtual bool SetEnvFunctionType(const char* type) = 0;
		virtual void SetAllEnvFunOption(std::string jsonbuff) = 0;

		//set baclpate
		virtual	std::string GetBackplateOptionsBuff() = 0;
		virtual bool GetBackplateOptionsBuff(VARIANT *v) = 0;
		virtual void SetBackplateType(const char* EnvType) = 0;
		virtual bool SetBackplateOption(const char* propertyName, VARIANT* v) = 0;
		virtual void SetAllBackplateOption(std::string jsonbuff) = 0;


		virtual void ExportScene() = 0;		//set ToneMapper

		virtual	std::string GetToneMapperOptionsBuff() = 0;
		virtual bool GetToneMapperOptionsBuff(VARIANT *v) = 0;
		virtual bool SetToneMapperOption(const char* propertyName, VARIANT* v) = 0;
		virtual void SetToneMapperType(std::string m_ToneMapper) = 0;
		virtual void SetAllToneMapperOption(std::string jsonbuff) = 0;
		virtual void TestInterface() = 0;

#pragma region **********<Material>**********
		/////�������

		virtual void CreateMaterial(int matindex, OPENNP::Material* pMat) = 0;

		/**
		* �������ʿ��е�material;
		* �ڶ���������Ҫ��ȷ���壻
		* matlibIndex          ���ʿ�����
		* matlibItemIndex      �´����Ĳ����ڲ��ʿ��е�����
		*
		* ���ز���ΨһID
		*/
		virtual int CreateMaterial(unsigned int matlibIndex, int *matlibItemIndex) = 0;

		virtual int GetMatIndex(int meshIndex) = 0;
		virtual bool ChangeMatType(int matIndex, const char* typeName) = 0;
		virtual int GetSceneMatCount() = 0; //��ȡ��������
		virtual void destroySceneMaterial() = 0; //�ͷų����еĲ���
		virtual void SetMatToBall(int matIndex) = 0;
		virtual bool SetMatProperty(int meshIndex, const char* propName, VARIANT* v, int count) = 0;
		virtual bool GetMatProperty(int meshIndex, const char* propName, VARIANT* v, int count) = 0;
		virtual bool GetMatProperty(int matIndex, const char* propName, float* pv) = 0;
		virtual int GetMatOffset() = 0;
		virtual void setMaterialRes(std::string jsonbuffs, std::map<std::string, int>& fileGuidIndexMap, std::map<std::string, int>&allGuidIndexMap) = 0;
		virtual std::string GetMatTypes() = 0;
		virtual std::string GetMatType(int matIndex) = 0;
		virtual std::string GetMatBuff(int matIndex) = 0;
		virtual std::string GetAllMaterialBuf() = 0;
		virtual std::string GetSceneMatList() = 0;

		virtual std::string MakeUniqMatName(std::string srcName) = 0;
		virtual bool SetMatDefinitionName(int matIndex, const char*  matName) = 0;
		virtual std::string GetMatDefinitionName(int matIndex) = 0;
		virtual std::string GetMatUniqueName(int matIndex) = 0;

		virtual std::string GetMatLibrary(int matlibIndex) = 0;
		virtual int OpenMatLibrary(const char* path, bool isNew) = 0;
		virtual bool SaveMatLibrary(const char* path, int matllibIndex) = 0;
		virtual bool CloseMatLibrary(int matllibIndex) = 0;

		virtual bool AssignlookToSelection(std::vector<int> meshes, int matlibIndex, int matIndex, int assignMode, int& NewMatIndex) = 0;
		virtual bool CreateMatForVariant(int mat, int oldMatId, int& newMatIndex) = 0;
		virtual bool AssignlookToSingleMesh(int meshindex, int matindex) = 0;
		virtual bool AssignlookToMat(int oldmatindex, int newmatindex, int& outmatindex, bool beCopy) = 0;

		virtual	std::string GetMatLibItem(int matlibIndex, int matitemIndex) = 0;
		virtual	bool SetUserLevel(int matindex, int level) = 0;
		virtual bool DeleteMatItem(int tabindex, int itemindex) = 0;
		virtual bool CopyMatItem(int srcMat, int desMatlib, int& newItemIndex) = 0;
		virtual int GetMatLibIndex(int matindex) = 0;

#pragma region MaterialCollections
		virtual bool AssignCollection(int matlibindex, int* matitems, int num, const char* collection, bool isadd) = 0;
		virtual bool ModifyCollection(int matlibindex, const char* oldname, const char* newname) = 0;
		virtual bool RemoveCollection(int matlibindex, const char* name) = 0;
		virtual bool AddCollection(int matlibindex, const char* name) = 0;
#pragma endregion MaterialCollections
#pragma endregion  **********<Material>**********

		virtual void CancelRender() = 0;
		virtual void SetViewMatCallBack(std::function<void(float[3], float[3], float[3], float)>) = 0;
		virtual void UnLockBuffer() = 0;
		virtual bool RenderBegin(void* hwnd = nullptr) = 0;
		virtual bool Render(void* hwnd = nullptr) = 0;
		virtual bool RenderEnd(void* hwnd = nullptr) = 0;
		virtual bool GetViewPort(void*hwnd, int&x, int&y, int&width, int&hight) = 0;
		virtual void SetNodeParams(int meshindex, NodeParams nodepar) = 0;
		virtual void GetNodeParams(int meshindex, NodeParams& nodepar) = 0;

		virtual unsigned char * GetImageBuf() = 0;
		virtual bool ChangeMatShader(int matindex, const char* propName, int type) = 0;
		virtual bool GetMatShader(int matindex, const char* propName, int& shaderType) = 0;

		virtual bool SetTextureSpaceType(int meshIndex, std::string tsm) = 0;
		virtual bool SetTextureSpaceProp(int meshIndex, const char* propName, VARIANT* v) = 0;
		virtual std::string GetMatTextureSpaceBuff(int meshIndex) = 0;
		virtual bool ClearSceneUnusedMats(std::vector<int> usedmatindexs) = 0;


		// for uv editor
		virtual bool GetUVMatImagePath(std::string &imagepath, int meshindex) = 0;
		virtual void * GetD3DDevice() = 0;
		virtual void * GetFactory() = 0;
		virtual void * GetD3DDeviceContext() = 0;
		virtual void EngineOnIdle() = 0;

		virtual bool TestConsoleVar_RT(const char* param, int value) = 0;
		virtual bool GetConsoleVar_RT(const char* param, VARIANT& value) = 0;
		virtual std::string GetConsoleData() = 0;
		virtual void SetConsoleVal(std::string bug) = 0;

		virtual void SetEnvProperty(const char* propName, VARIANT* v, int argCount, EnviromentType t) = 0;
		virtual void GetEnvProperty(const char* propname, VARIANT* v, int count, EnviromentType t) = 0;
		virtual void GetEnvironmentJsonData(VARIANT* v, EnviromentType t) = 0;
		virtual float GetTerrainSize() = 0;

        virtual void SetVideoTextureFilePath(std::string filePath) = 0;
        virtual void BegineEncodeVideoTexture() = 0;
        virtual void EndEncodeVideoTexture() = 0;

		//Vegetation start
		virtual void LoadVegetationFile(bool isSurround, const char* meshName, const char* materialName, int nodeIndex, int mateiralIndex, int vertexSize, int indexCount, const float* pInVex, const float* normals,
			const unsigned int* indices, const float* textures, const float* Tangents, const float* Bitangent, float* worldMat, const float* maxbox, const float* minbox, int meshCount, int materialCount, int nodeid) = 0;
		virtual void SetVegetationToolMode(int toolmode) = 0;
		virtual int GetVegetationToolMode() = 0;
		virtual std::shared_ptr<InstanceValueMap> VegetationButtonDown(Vector3D worldPoint, size_t instanceId, size_t nodeindex) = 0;
		virtual Vector3D VeiwToWorldTerrain(int x, int y) = 0;
		virtual void GetVegetationNodeBufferByNodeMeshid(int nodeid, int & indexCount, int & vertexCount, float ** vertex, unsigned int ** index, float ** normals, float ** textrues, int meshindex) = 0;
		virtual void MoveSelectedVegetation(const Vector3D & offset, bool bFollowTerrain) = 0;
		virtual void RotateSelectedVegetation(const Vector3D & rot) = 0;
		virtual void ScaleSelected(float fScale) = 0;
		virtual void SetSelectInstance(std::set<size_t> & selectedInstance) = 0;
		virtual void SetVegetationPosCallBack(void * callBack) = 0;
		virtual void SetVegetationRoteCallBack(void * callBack) = 0;
		virtual void SetVegetationScaleCallBack(void * callBack) = 0;
		virtual void SetVegetationRemoveCallBack(void * callBack) = 0;
		virtual float GetVegetationBrushRadius() = 0;
		virtual int GetMaterialIndexByNodeIndex(int nodeindex) = 0;
		virtual void FinishProcessVegetationProcess(int nodeId) = 0;
		virtual void RemoveNode(size_t nodeid) = 0;
		virtual void * GetVegetationValueChangerByNodeId(size_t nodeid) = 0;
		virtual void SetVegetationBrushRadius(float radius) = 0;
		virtual EngineBlock * SaveVegetation(size_t & EngineBlockLength) = 0;
		virtual void LoadVegetation(std::vector<int> & nodeIndex, EngineBlock * block, size_t EngineBlockLength) = 0;
        virtual void BeginRecordVegetationEvent(int eventType) = 0;
        virtual void EndRecordVegetationEvent() = 0;
        virtual void VegetationUnDo() = 0;
        virtual void VegetationReDo() = 0;
        virtual void SetVegetationAddCallBack(void * callBack) = 0;
		virtual void SetVegetationHiddenByNodeId(size_t nodeid, bool hidden) = 0;
        virtual void DeleteSelectVegetationInstance() = 0;
		virtual std::string MatIndex2Id(std::string oldid) = 0;
		//Vegetation end
		virtual void SetNormalSaveSign(bool bSave) = 0;
		virtual bool RenderComplete() = 0;
		//��ʱ
		virtual bool GetIsPkFromMaterial(const char* buf) { return false; }
		protected:
			NotifyMeshIndexChange meshIndexChange = nullptr;

	};
}

typedef RenderMax::IBaseProcess* (*PCREATEENGINEPROCESSINTERFACE)();
#endif
