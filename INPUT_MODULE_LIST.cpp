#include "INPUT_MODULE_LIST.h"
INPUT_MODULE_LIST::INPUT_MODULE_LIST(){
}
INPUT_MODULE_LIST::INPUT_MODULE_LIST(LIST&& list) {
	List = list;
}

INPUT_MODULE_LIST::~INPUT_MODULE_LIST() {
}