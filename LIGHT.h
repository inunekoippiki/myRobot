#pragma once
#include "../Library/COLOR.h"
#include "../Library/VECTOR3.h"
#include "../Library/MATRIX.h"
class STRING_TREE;
class SHADER;
class LIGHT{
public:
	LIGHT();
	~LIGHT();
    void init(const STRING_TREE& dataTree);
    //シェーダーのライトの情報を更新する
    void shaderUpdate(SHADER* shader);
private:
    VECTOR3 Pos;
    VECTOR3 Lookat;
    COLOR Diffuse;
    float Ambient = 0;
    MATRIX View;
    MATRIX Proj;
};

