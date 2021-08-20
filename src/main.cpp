#include "main.hpp"
#include "UnityEngine/SceneManagement/SceneManager.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/SceneManagement/Scene.hpp"
#include "UnityEngine/SceneManagement/LoadSceneMode.hpp"
#include "UnityEngine/Events/UnityAction_2.hpp"
#include "GlobalNamespace/ScoreController.hpp"
#include "GlobalNamespace/NoteController.hpp"
#include "GlobalNamespace/GameSongController.hpp"
#include "GlobalNamespace/GameScenesManager.hpp"
#include "GlobalNamespace/GamePause.hpp"
#include "custom-types/shared/coroutine.hpp"

using UnityEngine::SceneManagement::SceneManager;
using UnityEngine::GameObject;
using UnityEngine::Resources;
using UnityEngine::SceneManagement::Scene;
using UnityEngine::SceneManagement::LoadSceneMode;
using UnityEngine::Events::UnityAction_2;
using GlobalNamespace::ScoreController;
using GlobalNamespace::GamePause;
using GlobalNamespace::GameScenesManager;
using GlobalNamespace::GameSongController;

static ModInfo modInfo;

Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load();
}

MAKE_HOOK_MATCH(GameSongController_StartSong, &GameSongController::StartSong, void, GameSongController* self, float songTimeOffset) {
    GameSongController_StartSong(self, songTimeOffset);
    IForgor::SaberRecorder* s = GameObject::New_ctor(il2cpp_utils::createcsstr("IFSaberRecorder"))->AddComponent<IForgor::SaberRecorder*>();
	IForgor::NoteRecorder* n = GameObject::New_ctor(il2cpp_utils::createcsstr("IFNoteRecorder"))->AddComponent<IForgor::NoteRecorder*>();
	IForgor::PauseUIManager* p = GameObject::New_ctor(il2cpp_utils::createcsstr("IFPauseUIManager"))->AddComponent<IForgor::PauseUIManager*>();

    pauseUIInstance = p;
    saberRecorderInstance = s;
    noteRecorderInstance = n;
    getLogger().info("%p", noteRecorderInstance);
    getLogger().info("%p", saberRecorderInstance);
    getLogger().info("%p", pauseUIInstance);
}

MAKE_HOOK_MATCH(ScoreController_HandleNoteWasCut, &ScoreController::HandleNoteWasCut, void, ScoreController* self, GlobalNamespace::NoteController* noteController, ByRef<GlobalNamespace::NoteCutInfo> noteCutInfo) {
    ScoreController_HandleNoteWasCut(self, noteController, noteCutInfo);
    noteRecorderInstance->OnNoteWasCut(noteController->noteData, noteCutInfo.heldRef);
}

MAKE_HOOK_MATCH(ScoreController_HandleNoteWasMissed, &ScoreController::HandleNoteWasMissed, void, ScoreController* self, GlobalNamespace::NoteController* noteController) {
    ScoreController_HandleNoteWasMissed(self, noteController);
    noteRecorderInstance->OnNoteWasMissed(noteController->noteData);
}

MAKE_HOOK_MATCH(GamePause_Resume, &GamePause::Resume, void, GamePause* self) {
    GamePause_Resume(self);
    pauseUIInstance->OnPause();
}

MAKE_HOOK_MATCH(GamePause_Pause, &GamePause::Pause, void, GamePause* self) {
    GamePause_Pause(self);
    pauseUIInstance->OnPause();
}

extern "C" void load() {
    il2cpp_functions::Init();

    INSTALL_HOOK(getLogger(), GameSongController_StartSong);
    INSTALL_HOOK(getLogger(), ScoreController_HandleNoteWasCut);
	INSTALL_HOOK(getLogger(), ScoreController_HandleNoteWasMissed);
    INSTALL_HOOK(getLogger(), GamePause_Resume);
	INSTALL_HOOK(getLogger(), GamePause_Pause);

	custom_types::Register::AutoRegister();
}