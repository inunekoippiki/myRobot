#include "../Library/common.h"
#include "../Library/SHADER.h"
#include "DRAWER.h"
#include "DRAWERS_SHADER.h"
namespace DRAWER {
	DRAWERS_SHADER::DRAWERS_SHADER(SHADER* shader):
		Shader(shader) {
	}

	DRAWERS_SHADER::DRAWERS_SHADER(){
	}

	DRAWERS_SHADER::~DRAWERS_SHADER() {
		for (auto& i : Drawers) {
			delete i;
		}
	}
	void DRAWERS_SHADER::draw(){
		SHADER* shader = Shader;
		BEGIN_PATH_
			draw(shader);
		END_PATH_
	}
	void DRAWERS_SHADER::draw(SHADER* shader){
		for (int i = 0;i < Drawers.size();) {
			if (Drawers[i]->isDelete()) {
				delete Drawers[i];
				Drawers[i] = Drawers[Drawers.size() - 1];
				Drawers.pop_back();
				continue;
			}
			Drawers[i]->draw(shader);
			i++;
		}
	}
	void DRAWERS_SHADER::add(BASE* drawer){
		Drawers.push_back(drawer);
	}
}