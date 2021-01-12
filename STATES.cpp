#include "STATE_BASE.h"
#include "STATES.h"

STATES::STATES() {
}

STATES::~STATES() {
	for (auto state : States) {
		delete state.second;
	}
}

void STATES::update() {
	CurrentState->update();
}

void STATES::change(const char* name){
	if (CurrentState)CurrentState->onExit();

	CurrentState = States[name];

	if (CurrentState) {
		CurrentState->onEnter();
	}
	else {
		WARNING(1, "‚±‚ÌOBJECT_STATE‚Í‚ ‚è‚Ü‚¹‚ñ", name)
	}
}

void STATES::regist(STATE_BASE* state) {
	States[state->name()] = state;
}
