#pragma once  

enum class LIGHT_TYPE {
	POINT = 0,
	AREA,
	SPOT,
	DISTANT,
	ENVIRONMENTPROBE,
	NO_LIGHT,
};

struct SData_Light {
	/*ͨ������*/
	unsigned int lightFuncIndex;
	Pos pos;                               //λ��
	Color4 diffuse;                           //��Դ��ɫ
	Dir dir;                               //��Դ����ƽ�й⣬�۹�����ã�must be normalized
	float intensity;                  //��Դ��ɫ�Ŵ�����
	float radius;                             //���հ뾶���ڴ˰뾶��������岻�����������Դ��۹��ʹ�ã�
  float totalTheta;                         //�۹���Žǣ�
  float fullLightTheta;                     //�۹����ȫ�����Ƕ�,ע��totalTheta>fullLightTheta

	/*�Է���Դ������⣩���ר������*/
	float meshAreaIntegration;
	float sumArea;
	int nodeIndex;
	int meshAreaCDFBufferID;
	int meshAreaBufferID;
	int meshCount;
	int bufferID_index;
	int bufferID_vertex;
	int bufferID_worldMatrix;// ���������Ĳ�����HDR����ת��
	int bufferID_materials;
	int bufferOffset_materials;

	/*�������������*/
	optix::uint2 HDR_size;
	float energyBalance;                       
	float HDR_inv_gamma;                       
	float HDR_exposure;                       // �������ع���         
	float HDR_Intensity;	                    // �߹��ع���                     
	float HDR_contrast;                     
	float HDR_saturation;                  
  int HDR_textureSamplerID;
	int HDR_LuminanceBufferID;           
	int HDR_CDFBufferID;                      //��ά�����������buffer�Ŀ�ȱ�image��ȴ�1�����أ��߶���imageһ��
	int HDR_MarginalCDFBufferID;              //һά�����������buffer�Ŀ�ȱ�image�߶ȴ�һ�����أ�
	int HDR_IntegrationBufferID;              //һά�����������buffer�Ŀ�ȱ�image�߶ȴ�һ�����أ������Ŀ�ȼ�¼ԭʼͼ��ÿһ�еĻ���ֵ���������һλ��¼�������ֵ�Ļ��֣���
	int SH_lmax;                              //��г��������band���˲�����ʱ���ã�
	int SH_cBufferID;		                      //��г������ϵ��buffer


};

