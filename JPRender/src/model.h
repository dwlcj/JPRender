#ifndef _MODEL_H_
#define _MODEL_H_

#include <map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"


/*
* ����һ��ģ�� ģ�Ϳ��԰���һ������Mesh
*/
class Model{
public:
  bool loadModel(const std::string& filePath){
    Assimp::Importer importer;
    if(filePath.empty()){
      std::cerr<<"Error:Model::loadModel, empty model file path."<<std::endl;
      return false;
    }
    const aiScene* sceneObjPtr=importer.ReadFile(filePath,
                                                 aiProcess_Triangulate|
                                                 aiProcess_FlipUVs);
    if(!sceneObjPtr
       ||sceneObjPtr->mFlags==AI_SCENE_FLAGS_INCOMPLETE
       ||!sceneObjPtr->mRootNode){
      std::cerr<<"Error:Model::loadModel, description: "
        <<importer.GetErrorString()<<std::endl;
      return false;
    }
    this->modelFileDir=filePath.substr(0,filePath.find_last_of('/'));
    if(!this->processNode(sceneObjPtr->mRootNode,sceneObjPtr)){
      std::cerr<<"Error:Model::loadModel, process node failed."<<std::endl;
      return false;
    }
    return true;
  }
  ~Model(){
    for(std::vector<Mesh>::const_iterator it=this->meshes.begin(); this->meshes.end()!=it; ++it){
      it->final();
    }
  }

  /*
  * �ݹ鴦��ģ�͵Ľ��
  */
  bool processNode(const aiNode* node,const aiScene* sceneObjPtr){
    if(!node||!sceneObjPtr){
      return false;
    }
    // �ȴ���������
    for(size_t i=0; i<node->mNumMeshes; ++i){
      // ע��node�е�mesh�Ƕ�sceneObject��mesh������
      const aiMesh* meshPtr=sceneObjPtr->mMeshes[node->mMeshes[i]];
      if(meshPtr){
        Mesh meshObj;
        if(this->processMesh(meshPtr,sceneObjPtr,meshObj)){
          this->meshes.push_back(meshObj);
        }
      }
    }
    // �����ӽ��
    for(size_t i=0; i<node->mNumChildren; ++i){
      this->processNode(node->mChildren[i],sceneObjPtr);
    }
    return true;
  }
  bool processMesh(const aiMesh* meshPtr,const aiScene* sceneObjPtr,Mesh& meshObj){
    if(!meshPtr||!sceneObjPtr){
      return false;
    }
    std::vector<Vertex> vertData;
    std::vector<Texture> textures;
    std::vector<GLuint> indices;
    // ��Mesh�õ��������ݡ�����������������
    for(size_t i=0; i<meshPtr->mNumVertices; ++i){
      Vertex vertex;
      // ��ȡ����λ��
      if(meshPtr->HasPositions()){
        vertex.position.x=meshPtr->mVertices[i].x;
        vertex.position.y=meshPtr->mVertices[i].y;
        vertex.position.z=meshPtr->mVertices[i].z;
      }
      // ��ȡ�������� Ŀǰֻ����0������
      if(meshPtr->HasTextureCoords(0)){
        vertex.texCoords.x=meshPtr->mTextureCoords[0][i].x;
        vertex.texCoords.y=meshPtr->mTextureCoords[0][i].y;
      } else{
        vertex.texCoords=glm::vec2(0.0f,0.0f);
      }
      // ��ȡ����������
      if(meshPtr->HasNormals()){
        vertex.normal.x=meshPtr->mNormals[i].x;
        vertex.normal.y=meshPtr->mNormals[i].y;
        vertex.normal.z=meshPtr->mNormals[i].z;
      }
      vertData.push_back(vertex);
    }
     //��ȡ��������
    for(size_t i=0; i<meshPtr->mNumFaces; ++i){
      aiFace face=meshPtr->mFaces[i];
      if(face.mNumIndices!=3){
        return false;
      }
      for(size_t j=0; j<face.mNumIndices; ++j){
        indices.push_back(face.mIndices[j]);
      }
    }
    meshObj.setData(vertData,textures,indices);
    return true;
  }
  std::vector<Mesh> GetMeshVector(){ return meshes; }
public:
  std::vector<Mesh> meshes; // ����Mesh
private:
  std::string modelFileDir; // ����ģ���ļ����ļ���·��
  typedef std::map<std::string,Texture> LoadedTextMapType; // key = texture file path
  LoadedTextMapType loadedTextureMap; // �����Ѿ����ص�����
  float* m_pv;
  float* m_puv;
  float* m_pn;
  unsigned int* m_pi;
  int poSize=0;
  int txSize=0;
  int noSize=0;
  int inSize=0;
};



#endif