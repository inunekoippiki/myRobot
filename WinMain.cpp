#include <Windows.h>
#include <string>
#include"../Library/common.h"
#include"../Library/WINDOW.h"
#include"../Library/GRAPHIC.h"
#include"../Library/INDEV.h"
#include"../Library/DSOUND.h"
#include"../Library/DEBUG_STR.h"
#include"../Library/Thread/THREAD_MANAGER.h"
#include "../Library/TIME_COUNTER.h"

#include "SCENE_MANAGER.h"
#include "SOUND_MANAGER.h"
#include "START_DEBUG_RUN.h"
#include"createAssets.h"

int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR, INT nShow)
{
    CONTAINER* c = new CONTAINER("Assets/WINMAIN/Assets.txt");
    WINDOW* w = 0;
    int fullscreen = c->data("fullscreen");
    if (fullscreen)
        w = new WINDOW(
            c->data("caption"),
            c->data("baseWidth"),
            c->data("baseHeight"),
            MODE_FULLSCREEN);
    else
        w = new WINDOW(
            c->data("caption"),
            c->data("baseWidth"),
            c->data("baseHeight"),
            c->data("dispWidth"),
            c->data("dispHeight"));
    SAFE_DELETE(c);
    GRAPHIC* g = new GRAPHIC;
    INDEV* in = new INDEV;
    DSOUND* s = new DSOUND;
    DEBUG_STR* ds = new DEBUG_STR;
    THREAD_MANAGER* th = new THREAD_MANAGER( 0 );
    SOUND_MANAGER* Sm = new SOUND_MANAGER();
    //-----------------------------------------------
    createAssets();
	//DebugRun();
    TIME_COUNTER timeCounter;
    SCENE_MANAGER* sceneManager = new SCENE_MANAGER();
    sceneManager->create();
	while( w->msgProc() ){
        if( w->active() ){
            timeCounter.start();
            sceneManager->proc();
            timeCounter.end();
            ds->instance()->set("fps;%d", (int)(1000 / timeCounter.ms()));
        }
    }
    SAFE_DELETE(sceneManager);
    //-----------------------------------------------

    SAFE_DELETE(Sm);
    SAFE_DELETE( th );
    SAFE_DELETE( ds );
    SAFE_DELETE( s );
    SAFE_DELETE( in );
    SAFE_DELETE( g );
    SAFE_DELETE( w );
    return 0;
}

