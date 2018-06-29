#pragma once

struct PRD{
  unsigned int seed;
  unsigned int uDepth;//�������ʼ����ʷ��׷�ٵ���ȣ���������������ߣ������Ϊ0���״��ཻ��ĵ�һ�����ߣ����Ϊ1��
  Pos hp_g;
  Nor n_g;
	
	// radiance use only
	Nor wi_g;
	Color4 color_out;
	Albedo4 albedo;
	float lastMaterialEnvBlend;
	Radiance4 luminance_out;
	int materialIndex;
	float BRDF;
	float PDF;
  bool missed;

	// AO use only
	float AO_intensity;
	bool AO_nextIteration;
	float AO_distancePercent;
};