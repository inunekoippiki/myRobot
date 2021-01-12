#include "UI.h"
#include "NODE_LINE.h"
#include "NODE_LINE_DATA.h"

NODE_LINE_DATA::NODE_LINE_DATA(){
}

NODE_LINE_DATA::NODE_LINE_DATA(NODE_LINE* nodeLine){
	Num = nodeLine->num();
	Points = nodeLine->localPoints();
}


void NODE_LINE_DATA::set(NODE_LINE* nodeLine){
	nodeLine->pointsUpdate(Num, Points);
}

NODE_LINE_DATA::~NODE_LINE_DATA() {
}