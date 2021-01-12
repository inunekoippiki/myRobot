#pragma once
#include <unordered_map>
#include <string>
#include "../Effekseer/Effekseer.h"
#include "../include/EffekseerRendererDX11.h"
#include "../include/Effekseer.h"

class MATRIX;
class VECTOR3;
namespace EFFEKSEER {
	class MANAGER {
	public:
		MANAGER();
		~MANAGER();
		void updateProj(const MATRIX& pjoj);
		void updateView(const MATRIX& view);
		Effekseer::Handle play(const char* name, const VECTOR3& pos);
		Effekseer::Handle play(const char* name, const VECTOR3& pos, float scale);
		Effekseer::Handle play(const char* name, const VECTOR3& pos, const VECTOR3 scale);
		Effekseer::Handle play(const char* name, const VECTOR3& pos, const VECTOR3& rad, const VECTOR3 scale);
		void setPos(Effekseer::Handle handle, const VECTOR3& pos);
		void setRotation(Effekseer::Handle handle, const VECTOR3& rad);
		void setScale(Effekseer::Handle handle, const VECTOR3& scale);
		void setPaused(Effekseer::Handle handle, bool paused);
		void stopRoot(Effekseer::Handle handle);
		void update();
		void draw();
		::Effekseer::Manager* manager() { return Manager; }
	private:
		::EffekseerRenderer::Renderer* Renderer = nullptr;
		::Effekseer::Manager* Manager = nullptr;
		std::unordered_map<std::string, Effekseer::Effect*> Effect;
	};
	static constexpr Effekseer::Handle initialHandle() { return -1; }
	::Effekseer::Matrix44 cvtMatrix(const MATRIX& m);
	::Effekseer::Vector3D cvtVector3D(const VECTOR3& vector3);
	MATRIX uncvtMatrix(const ::Effekseer::Matrix44& m);
	VECTOR3 uncvtVector3D(const ::Effekseer::Vector3D& vector3);
	MATRIX inverseMatrix(const MATRIX& m);
}