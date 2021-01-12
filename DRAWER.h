#pragma once
class SHADER;
class TEXTURE;
class VECTOR2;
class VECTOR3;
class MATRIX;
/*
DRAWER�̃V�X�e���͕`�悪�K�v�ȃI�u�W�F�N�g�Ő������A
�C�e���[�V�����̂��߂̕ʂ̃}�l�[�W���[�N���X�ɈϏ�����B
�}�l�[�W���[�N���X�ł܂Ƃ߂ĕ`�悵�A�ʒu�Ȃǂ̍X�V��
�o�^���̃I�u�W�F�N�g�ōs���B
�o�^���̃I�u�W�F�N�g��delete�����Ƃ�DRAWER���f���[�g���Ȃ��Ƃ����Ȃ���
�}�l�[�W���[�N���X�ɒʒm���K�v�Ȃ���Delete()�ŊԐڂŃf���[�g����B
*/

namespace DRAWER {
	class BASE {
	public:
		BASE() {};
		virtual ~BASE() {};
		virtual void draw(SHADER* shader) = 0;
		bool isDelete()const { return IsDelete; }
		void Delete() { IsDelete = true; }
	private:
		bool IsDelete = false;
	};


	//�p���ł��Ȃ��Ƃ��͂�����g��
	//�����������void draw(SHADER* shader)�������Ă��邱��
	template <class T>
	class SAUCER :public BASE {
	public:
		using type = T;
		SAUCER(T* obj) { Obj = obj; }
		~SAUCER() {};
		void draw(SHADER* shader) override {
			Obj->draw(shader);
		};
	private:
		T* Obj = nullptr;
	};
}