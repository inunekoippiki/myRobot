#pragma once
#include "DRAWERS.h"
class SHADER;
namespace DRAWER {
	class DRAWERS_SHADER :public DRAWERS {
	public:
		DRAWERS_SHADER(SHADER* shader);
		DRAWERS_SHADER();
		~DRAWERS_SHADER();
		void setShader(SHADER* shader) { Shader = shader; };
		SHADER* shader() { return Shader; }
		void draw() override;
		void draw(SHADER* shader);
		void add(BASE* drawer);
	private:
		SHADER* Shader = nullptr;
		std::vector<BASE*> Drawers;
	};
}