#pragma once
#include <array>
#include "../Library/VECTOR2.h"
#include "DRAWER.h"
class TEXTURE;
class SHADER;
class COLOR;
//�܂������`�悷��N���X
namespace DRAWER {
	class ARROW :public BASE {
	public:
		ARROW(std::array<VECTOR2, 6>* points, size_t* num) :
			Points(points),
			Num(num) {
		}
		void draw(SHADER* shader);
		//���̑�����ݒ肷��B�e�N�X�`���T�C�Y�ŉ�
		void setLineWidth(float lineWidth) { LineWidth = lineWidth; }
		//���̐��̕����̃e�N�X�`����ݒ肷��
		void setTexture(TEXTURE* texture) { Texture = texture; }
		//���̐�[�̃e�N�X�`����ݒ肷��
		void setTextureEnd(TEXTURE* textureEnd) { TextureEnd = textureEnd; }
		void setColor(const COLOR& color) { Color = color; }
		void setIsInvisible(bool isInvisible) { IsInvisible = isInvisible; }
		//�f�o�b�N�p
		static int drawCallCnt;
	private:
		//���̓_����ʏ�ɂ��邩��Ԃ�
		bool isNecessaryDraw(const VECTOR2& p1, const VECTOR2& p2);
		std::array<VECTOR2, 6>* Points = nullptr;
		size_t* Num = nullptr;
		float LineWidth = 0.0f;
		TEXTURE* Texture = nullptr;
		TEXTURE* TextureEnd = nullptr;
		COLOR Color;
		bool IsInvisible = false;
	};
}
