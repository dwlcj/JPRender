#ifndef _MESH_H_
#define _MESH_H_

#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/string_cast.hpp>
#include <string>       
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


// ��ʾһ����������
struct Vertex{
  glm::vec3 position;
  glm::vec2 texCoords;
  glm::vec3 normal;
};

// ��ʾһ��Texture
struct Texture{
  GLuint id;
  aiTextureType type;
  std::string path;
};

// ��ʾһ��������Ⱦ����Сʵ��
class Mesh{
public:
 
  Mesh():VAOId(0),VBOId(0),EBOId(0){}
  Mesh(const std::vector<Vertex>& vertData,
       const std::vector<Texture> & textures,
       const std::vector<GLuint>& indices):VAOId(0),VBOId(0),EBOId(0) // ����һ��Mesh
  {
    setData(vertData,textures,indices);
  }
  void setData(const std::vector<Vertex>& vertData,
               const std::vector<Texture> & textures,
               const std::vector<GLuint>& indices){
    this->vertData=vertData;
    this->indices=indices;
    this->textures=textures;
    if(!vertData.empty()&&!indices.empty()){
      this->setupMesh();
    }
  }
  void setDataPtr(){
  
  }
  void final() const{
    glDeleteVertexArrays(1,&this->VAOId);
    glDeleteBuffers(1,&this->VBOId);
    glDeleteBuffers(1,&this->EBOId);
  }
  ~Mesh(){
    // ��Ҫ�������ͷ�VBO�ȿռ� ��ΪMesh���󴫵�ʱ ��ʱ�������ٺ����������VBO�ȿռ�
  }
  std::vector<Vertex> GetVector(){ return vertData; }
  std::vector<GLuint> GetIndices(){ return indices; }
private:
  std::vector<Vertex> vertData;
  std::vector<GLuint> indices;
  std::vector<Texture> textures;
  GLuint VAOId,VBOId,EBOId;

  void setupMesh()  // ����VAO,VBO�Ȼ�����
  {
    glGenVertexArrays(1,&this->VAOId);
    glGenBuffers(1,&this->VBOId);
    glGenBuffers(1,&this->EBOId);

    glBindVertexArray(this->VAOId);
    glBindBuffer(GL_ARRAY_BUFFER,this->VBOId);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex) * this->vertData.size(),
                 &this->vertData[0],GL_STATIC_DRAW);
    // ����λ������
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,
                          sizeof(Vertex),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    // ������������
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,
                          sizeof(Vertex),(GLvoid*)(3*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);
    // ���㷨��������
    glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,
                          sizeof(Vertex),(GLvoid*)(5*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);
    // ��������
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->EBOId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint)* this->indices.size(),
                 &this->indices[0],GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
  }
};

#endif 