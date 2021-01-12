#if( _DEBUG  )
#include"../Library/CONVERT.h"
#include"../Library/CONVERT_MA.h"
#include"../Library/fileUtil.h"
#include"listsFile.h"
#endif
#include"createAssets.h"

/*
完成したらDebugモードにしてFINALを定義後、実行する。
するとdata.txtはAssets.txtに追加される。
addDataToContainer()は実行されなくなる。
*/

//#define FINAL

void convertPrimitiveAssets() {
#if( _DEBUG )
	CONVERT_MA convert;
	convert.fbxToTree( "AssetsOrigin/primitive/box.fbx",  "AssetsOrigin/primitive/box.txt", "Assets/primitive/textures/box/" );
	convert.fbxToTree("AssetsOrigin/primitive/cylinder.fbx", "AssetsOrigin/primitive/cylinder.txt", "Assets/primitive/textures/cylinder/");
	convert.fbxToTree("AssetsOrigin/primitive/plane.fbx", "AssetsOrigin/primitive/plane.txt", "Assets/primitive/textures/plane/");
    convert.fbxToTree("AssetsOrigin/primitive/sphere.fbx", "AssetsOrigin/primitive/sphere.txt", "Assets/primitive/textures/sphere/");
    convert.fbxToTree("AssetsOrigin/primitive/floor.fbx", "AssetsOrigin/primitive/floor.txt", "Assets/primitive/textures/floor/");
#endif
}
void createPrimitiveAssets() {
#if( _DEBUG )
	const char* filename = "Assets/primitive/Assets.txt";
	delFile( filename );
	addFile( filename, "AssetsOrigin/primitive/box.txt" );
	addFile( filename, "AssetsOrigin/primitive/cylinder.txt" );
	addFile(filename, "AssetsOrigin/primitive/plane.txt");
    addFile(filename, "AssetsOrigin/primitive/sphere.txt");
    addFile(filename, "AssetsOrigin/primitive/floor.txt");
#endif
}

void convertMenuIconAssets() {
#if( _DEBUG )
	listsFile('x', "Assets/images/Menu/Icon", "AssetsOrigin/MenuIcon.txt");
#endif
}
void createMenuIconAssets() {
#if( _DEBUG )

#endif
}

void convertCommonAssets() {
#if( _DEBUG )
    listsFile('x', "Assets/COMMON/images", "AssetsOrigin/commonImages.txt");
#endif
}
void createCommonAssets() {
#if( _DEBUG )
    const char* filename;
    filename = "Assets/COMMON/Assets.txt";
    delFile(filename);
    addFile(filename, "AssetsOrigin/commonImages.txt");
    addFile(filename, "Assets/ROUND/Assets.txt");
    addFile(filename, "AssetsOrigin/MenuIcon.txt");
    addFile(filename, "AssetsOrigin/data/commonData.txt");

#ifdef FINAL
    addFile(filename, "assetsOrigin/data/commonData.txt");
#endif
#endif

}


void convertGameAssets(){
#if( _DEBUG )
    //CONVERT convert;
    //convert.fbxToTree( "AssetsOrigin/unitychan/unitychan.fbx",  "AssetsOrigin/unitychan.txt", "Assets/GAME/textures/unitychan/" );
    //convert.fbxToAnim( "AssetsOrigin/unitychan/unitychanWait00.fbx",  "AssetsOrigin/unitychanWait00.txt" );
    //convert.fbxToAnim( "AssetsOrigin/unitychan/unitychanWait02.fbx",  "AssetsOrigin/unitychanWait02.txt" );
    //convert.fbxToAnim( "AssetsOrigin/unitychan/unitychanRun.fbx",     "AssetsOrigin/unitychanRun.txt" );
    //convert.fbxToAnim( "AssetsOrigin/unitychan/unitychanJump00.fbx",  "AssetsOrigin/unitychanJump00.txt" );
#endif
}
void createGameAssets(){
#if( _DEBUG )
    //const char* filename = "Assets/GAME/Assets.txt";
    //delFile( filename );
    //addFile( filename, "AssetsOrigin/unitychan.txt" );
    //addFile( filename, "AssetsOrigin/unitychanWait00.txt" );
    //addFile( filename, "AssetsOrigin/unitychanWait02.txt" );
    //addFile( filename, "AssetsOrigin/unitychanRun.txt" );
    //addFile( filename, "AssetsOrigin/unitychanJump00.txt" );
#endif
}

void convertTitleAssets(){
#if( _DEBUG )
    listsFile( 'x', "Assets/TITLE/images", "AssetsOrigin/titleImages.txt" );
#endif
}
void createTitleAssets(){
#if( _DEBUG )
    const char* filename;
    filename = "Assets/TITLE/Assets.txt";
    delFile( filename );
    addFile( filename, "AssetsOrigin/titleImages.txt" );
#ifdef FINAL
    addFile( filename, "AssetsOrigin/data/titleData.txt" );
#endif
#endif
}

void convertRoundAssets() {
#if( _DEBUG )
    CONVERT_MA convert;
    convert.fbxToTree( "AssetsOrigin/robot/robot.fbx",  "AssetsOrigin/robot.txt", "Assets/ROUND/textures/robot/" );
    convert.fbxToTree("AssetsOrigin/robot/robotCanon.fbx", "AssetsOrigin/robotCanon.txt", "Assets/ROUND/textures/robot/");
    convert.fbxToTree("AssetsOrigin/robot/robotLeftWheel.fbx", "AssetsOrigin/robotLeftWheel.txt", "Assets/ROUND/textures/robot/");
    convert.fbxToTree("AssetsOrigin/robot/robotRightWheel.fbx", "AssetsOrigin/robotRightWheel.txt", "Assets/ROUND/textures/robot/");

    convert.fbxToTree("AssetsOrigin/enemy/enemy.fbx", "AssetsOrigin/enemy.txt", "Assets/ROUND/textures/enemy/");
    convert.fbxToTree("AssetsOrigin/enemy/enemyCanon.fbx", "AssetsOrigin/enemyCanon.txt", "Assets/ROUND/textures/enemy/");
    convert.fbxToTree("AssetsOrigin/enemy/enemyLeftWheel.fbx", "AssetsOrigin/enemyLeftWheel.txt", "Assets/ROUND/textures/enemy/");
    convert.fbxToTree("AssetsOrigin/enemy/enemyRightWheel.fbx", "AssetsOrigin/enemyRightWheel.txt", "Assets/ROUND/textures/enemy/");

    convert.fbxToTree("AssetsOrigin/target/target.fbx", "AssetsOrigin/target.txt", "Assets/ROUND/textures/target/");
    listsFile('s', "Assets/sounds", "AssetsOrigin/sounds.txt");
#endif
}
void createRoundAssets() {
#if( _DEBUG )
    const char* filename = "Assets/ROUND/Assets.txt";
    delFile( filename );
    addFile( filename, "AssetsOrigin/enemy.txt" );
    addFile(filename, "AssetsOrigin/enemyCanon.txt");
    addFile(filename, "AssetsOrigin/enemyLeftWheel.txt");
    addFile(filename, "AssetsOrigin/enemyRightWheel.txt");

    addFile(filename, "AssetsOrigin/robot.txt");
    addFile(filename, "AssetsOrigin/robotCanon.txt");
    addFile(filename, "AssetsOrigin/robotLeftWheel.txt");
    addFile(filename, "AssetsOrigin/robotRightWheel.txt");

    addFile(filename, "AssetsOrigin/target.txt");
    addFile(filename, "AssetsOrigin/primitive/box.txt");
    addFile(filename, "AssetsOrigin/primitive/cylinder.txt");
    addFile(filename, "AssetsOrigin/primitive/plane.txt");
    addFile(filename, "AssetsOrigin/primitive/sphere.txt");
    addFile(filename, "AssetsOrigin/primitive/floor.txt");
    addFile(filename, "AssetsOrigin/sounds.txt");
    addFile(filename, "AssetsOrigin/MenuIcon.txt");

    addFile(filename, "AssetsOrigin/data/sceneRoundData.txt");

#endif
}

void convertStageAssets(){
#if( _DEBUG )
    //CONVERT_MA convertMa;
    //convertMa.fbxToTree( "AssetsOrigin/map/map.fbx",  "AssetsOrigin/map.txt", "Assets/STAGE01/textures/map/" );
    /*元のマップをそのままコリジョンマップにする場合*/
    //convertMa.fbxToCollisionData( "AssetsOrigin/map/map.fbx",  "Assets/STAGE01/collisionData.txt" );
    /*コリジョンマップを別に作った場合*/
    //convertMa.fbxToCollisionData( "AssetsOrigin/map/collisionMap.fbx",  "Assets/STAGE01/collisionData.txt" );

    listsFile( 'x', "Assets/STAGE01/images/num", "AssetsOrigin/stage01Images.txt" );
#endif
}
void createStageAssets(){
#if( _DEBUG )
    const char* filename = "assets/STAGE01/assets.txt";
    delFile( filename );
    addFile( filename, "AssetsOrigin/map.txt" );
    addFile( filename, "AssetsOrigin/stage01Images.txt" );
#ifdef FINAL
    addFile( filename, "assetsOrigin/data/stage01Data.txt" );
#endif
#endif
}

void createAssets(){
#if( _DEBUG )

    //convertGameAssets();
    //createGameAssets();

    convertTitleAssets();
    createTitleAssets();

    //convertStageAssets();
    //createStageAssets();

	convertPrimitiveAssets();
	createPrimitiveAssets();

    convertRoundAssets();
    createRoundAssets();

	convertMenuIconAssets();
	createMenuIconAssets();

    convertCommonAssets();
    createCommonAssets();

#endif
}

void addDataToContainer( class CONTAINER* c, const char* dataFile ){
#ifndef FINAL
    c->addData( dataFile );
#endif
}
