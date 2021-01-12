#pragma once
#include <string>
#include "INTERFACE.h"
namespace PROCESS_NODE_COMMAND {
	//�m�[�h�̕������ݒ肷��R�}���h
	template<class T>
	class INPUT:public BASE {
	public:
		INPUT(T* inputObj,const std::string& newString) :
			InputObj(inputObj),
			NewString(newString) {
		};
		~INPUT() {};
		void execute()override {
			OldString = InputObj->string();
			InputObj->setString(NewString);
		};
		void undo()override {
			InputObj->setString(OldString);
		};

	private:
		std::string NewString;
		std::string OldString;
		T* InputObj = nullptr;
	};
}