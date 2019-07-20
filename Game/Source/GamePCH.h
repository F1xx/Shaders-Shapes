#ifndef __GamePCH_H__
#define __GamePCH_H__

#include "../../Libraries/Framework/Source/FrameworkPCH.h"

#include <queue>

//include everything because we are bad coders :)
#include "Game/Game.h"
#include "Game/Mesh.h"
#include "Game/PlayerController.h"
#include "Game/Color.h"
#include "GameConstants.h"
#include "Game/Camera.h"
#include "Game/Timer.h"

#include "Game/GameObject.h"
#include "Game/Player.h"
#include "Game/HUDObject.h"
#include "Game/Enemy.h"
#include "Game/ObjectiveObject.h"

#if WIN32
#else
#include "../Android-NativeActivity/Source/android_native_app_glue.h"
#include "../Android-NativeActivity/Source/UtilityAndroid.h"
#endif

#endif //__GamePCH_H__
