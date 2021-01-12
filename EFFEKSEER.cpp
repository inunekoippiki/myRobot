#include <filesystem>
#include "EFFEKSEER.h"
#include "../Library/GRAPHIC.h"
#include "../Library/MATRIX.h"
#include "../Library/VECTOR3.h"

namespace EFFEKSEER {

	MANAGER::MANAGER() {
		GRAPHIC* g = GRAPHIC::instance();
		Renderer = ::EffekseerRendererDX11::Renderer::Create(g->device(), g->immediateContext(), 4096);
		Manager = ::Effekseer::Manager::Create(1024);
		// �`����@�̎w��A�Ǝ��Ɋg�����Ȃ������`���ł��B
		Manager->SetSpriteRenderer(Renderer->CreateSpriteRenderer());
		Manager->SetRibbonRenderer(Renderer->CreateRibbonRenderer());
		Manager->SetRingRenderer(Renderer->CreateRingRenderer());
		// �e�N�X�`���摜�̓Ǎ����@�̎w��(�p�b�P�[�W������ǂݍ��ޏꍇ�g������K�v������܂��B)
		Manager->SetTextureLoader(Renderer->CreateTextureLoader());
		// ���W�n�̎w��(RH�ŉE��n�ALH�ō���n)
		Manager->SetCoordinateSystem(::Effekseer::CoordinateSystem::LH);
		// �G�t�F�N�g�̓Ǎ�
		for (auto& i : std::filesystem::directory_iterator("Assets/effect/")) {
			size_t idx = i.path().filename().string().find_last_of(".");
			Effect[i.path().filename().string().substr(0, idx)]= Effekseer::Effect::Create(Manager, (i.path().u16string().c_str()));
		}
	}

	MANAGER::~MANAGER() {
		// �G�t�F�N�g��������܂��B�Đ����̏ꍇ�́A�Đ����I��������A�����I�ɉ������܂��B
		for (auto& i : Effect) {
			ES_SAFE_RELEASE(i.second);
		}
		// �G�t�F�N�g�Ǘ��p�C���X�^���X��j��
		Manager->Destroy();
		// �`��p�C���X�^���X��j��
		Renderer->Destroy();
	}

	void MANAGER::updateProj(const MATRIX& pjoj) {
		// ���e�s��̍X�V
		Renderer->SetProjectionMatrix(cvtMatrix(pjoj));
	}

	void MANAGER::updateView(const MATRIX& view) {
		// �J�����s��̍X�V
		Renderer->SetCameraMatrix(cvtMatrix(view));
	}

	Effekseer::Handle MANAGER::play(const char* name, const VECTOR3& pos) {
		WARNING(!Effect.contains(name), "�G�t�F�N�g�f�[�^��������܂���", name);
		return Manager->Play(Effect[name], cvtVector3D(pos));
	}

	Effekseer::Handle MANAGER::play(const char* name, const VECTOR3& pos, float scale) {
		WARNING(!Effect.contains(name), "�G�t�F�N�g�f�[�^��������܂���", name);
		Effekseer::Handle handle = Manager->Play(Effect[name], Effekseer::Vector3D());
		Effekseer::Matrix43 m;
		m.Translation(pos.x, pos.y, pos.z);
		m.Scaling(scale, scale, scale);
		Manager->SetBaseMatrix(handle, m);
		return handle;
	}

	Effekseer::Handle MANAGER::play(const char* name, const VECTOR3& pos, const VECTOR3 scale) {
		WARNING(!Effect.contains(name), "�G�t�F�N�g�f�[�^��������܂���", name);
		Effekseer::Handle handle = Manager->Play(Effect[name], Effekseer::Vector3D());
		Effekseer::Matrix43 m;
		m.Translation(pos.x, pos.y, pos.z);
		m.Scaling(scale.x, scale.y, scale.z);
		Manager->SetBaseMatrix(handle, m);
		return handle;
	}

	Effekseer::Handle MANAGER::play(const char* name, const VECTOR3& pos, const VECTOR3& rad, const VECTOR3 scale) {
		WARNING(!Effect.contains(name), "�G�t�F�N�g�f�[�^��������܂���", name);
		Effekseer::Handle handle = Manager->Play(Effect[name], Effekseer::Vector3D());
		Effekseer::Matrix43 mR;
		Effekseer::Matrix43 mL;
		mL.Scaling(scale.x, scale.y, scale.z);
		mR.RotationY(rad.y);
		Effekseer::Matrix43::Multiple(mL, mL, mR);
		mR.Translation(pos.x, pos.y, pos.z);
		Effekseer::Matrix43::Multiple(mL, mL, mR);
		Manager->SetBaseMatrix(handle, mL);
		return handle;
	}

	void MANAGER::setPos(Effekseer::Handle handle, const VECTOR3& pos) {
		Manager->SetLocation(handle, pos.x, pos.y, pos.z);
	}

	void MANAGER::setRotation(Effekseer::Handle handle, const VECTOR3& rad) {
		Manager->SetRotation(handle, rad.x, rad.y, rad.z);
	}

	void MANAGER::setScale(Effekseer::Handle handle, const VECTOR3& scale) {
		Manager->SetScale(handle, scale.x, scale.y, scale.z);
	}

	void MANAGER::setPaused(Effekseer::Handle handle, bool paused) {
		Manager->SetPaused(handle, paused);
	}

	void MANAGER::stopRoot(Effekseer::Handle handle) {
		Manager->StopRoot(handle);
	}

	void MANAGER::update() {
		// �S�ẴG�t�F�N�g�̍X�V
		Manager->Update();
	}

	void MANAGER::draw() {
		Renderer->BeginRendering();
		Manager->Draw();
		Renderer->EndRendering();
	}

}



namespace EFFEKSEER {
	::Effekseer::Matrix44 cvtMatrix(const MATRIX& m) {
		::Effekseer::Matrix44 ret;
		ret.Values[0][0] = m._11;ret.Values[0][1] = m._12;ret.Values[0][2] = m._13;ret.Values[0][3] = m._14;
		ret.Values[1][0] = m._21;ret.Values[1][1] = m._22;ret.Values[1][2] = m._23;ret.Values[1][3] = m._24;
		ret.Values[2][0] = m._31;ret.Values[2][1] = m._32;ret.Values[2][2] = m._33;ret.Values[2][3] = m._34;
		ret.Values[3][0] = m._41;ret.Values[3][1] = m._42;ret.Values[3][2] = m._43;ret.Values[3][3] = m._44;
		ret.Transpose();
		return ret;
	}

	::Effekseer::Vector3D cvtVector3D(const VECTOR3& vector3) {
		return ::Effekseer::Vector3D(vector3.x, vector3.y, vector3.z);
	}
	MATRIX uncvtMatrix(const::Effekseer::Matrix44& m){
		MATRIX ret;
		ret._11 = m.Values[0][0];ret._12 = m.Values[0][1];ret._13 = m.Values[0][2];ret._14 = m.Values[0][3];
		ret._21 = m.Values[1][0];ret._22 = m.Values[1][1];ret._23 = m.Values[1][2];ret._24 = m.Values[1][3];
		ret._31 = m.Values[2][0];ret._32 = m.Values[2][1];ret._33 = m.Values[2][2];ret._34 = m.Values[2][3];
		ret._41 = m.Values[3][0];ret._42 = m.Values[3][1];ret._43 = m.Values[3][2];ret._44 = m.Values[3][3];
		ret.transpose();
		return ret;
	}
	VECTOR3 uncvtVector3D(const::Effekseer::Vector3D& vector3){
		return VECTOR3(vector3.X, vector3.Y, vector3.Z);
	}
	MATRIX inverseMatrix(const MATRIX& m){
		::Effekseer::Matrix44 ret;
		::Effekseer::Matrix44::Inverse(ret, cvtMatrix(m));
		return uncvtMatrix(ret);
	}
}