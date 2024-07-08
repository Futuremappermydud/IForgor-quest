#include "main.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Events/UnityAction_2.hpp"
#include "GlobalNamespace/ScoreController.hpp"
#include "GlobalNamespace/NoteController.hpp"
#include "GlobalNamespace/GameSongController.hpp"
#include "GlobalNamespace/GameScenesManager.hpp"
#include "GlobalNamespace/GamePause.hpp"
#include "custom-types/shared/coroutine.hpp"

MAKE_HOOK_MATCH(GameSongController_StartSong, &GlobalNamespace::GameSongController::StartSong, void, GlobalNamespace::GameSongController* self, float songTimeOffset) {
    GameSongController_StartSong(self, songTimeOffset);
    
    auto s = UnityEngine::GameObject::New_ctor("IFSaberRecorder")->AddComponent<IForgor::SaberRecorder*>();
	auto n = UnityEngine::GameObject::New_ctor("IFNoteRecorder")->AddComponent<IForgor::NoteRecorder*>();
	auto p = UnityEngine::GameObject::New_ctor("IFPauseUIManager")->AddComponent<IForgor::PauseUIManager*>();

    pauseUIInstance = p;
    saberRecorderInstance = s;
    noteRecorderInstance = n;
}

MAKE_HOOK_MATCH(ScoreController_HandleNoteWasCut, &GlobalNamespace::ScoreController::HandleNoteWasCut, void, GlobalNamespace::ScoreController* self, GlobalNamespace::NoteController* noteController, ByRef<GlobalNamespace::NoteCutInfo> noteCutInfo) {
    ScoreController_HandleNoteWasCut(self, noteController, noteCutInfo);
    noteRecorderInstance->OnNoteWasCut(noteController->noteData, noteCutInfo.heldRef);
}

MAKE_HOOK_MATCH(ScoreController_HandleNoteWasMissed, &GlobalNamespace::ScoreController::HandleNoteWasMissed, void, GlobalNamespace::ScoreController* self, GlobalNamespace::NoteController* noteController) {
    ScoreController_HandleNoteWasMissed(self, noteController);
    noteRecorderInstance->OnNoteWasMissed(noteController->noteData);
}

MAKE_HOOK_MATCH(GamePause_Resume, &GlobalNamespace::GamePause::Resume, void, GlobalNamespace::GamePause* self) {
    GamePause_Resume(self);
    pauseUIInstance->OnPause();
}

MAKE_HOOK_MATCH(GamePause_Pause, &GlobalNamespace::GamePause::Pause, void, GlobalNamespace::GamePause* self) {
    GamePause_Pause(self);
    pauseUIInstance->OnPause();
}

extern "C" __attribute__((visibility("default"))) void setup(CModInfo* info) {
  info->id =MOD_ID;
  info->version = VERSION;
  info->version_long = 0;
}

extern "C" __attribute__((visibility("default"))) void late_load() {
    il2cpp_functions::Init();

    INSTALL_HOOK(IForgor::Logger, GameSongController_StartSong);
    INSTALL_HOOK(IForgor::Logger, ScoreController_HandleNoteWasCut);
    INSTALL_HOOK(IForgor::Logger, ScoreController_HandleNoteWasMissed);
    INSTALL_HOOK(IForgor::Logger, GamePause_Resume);
    INSTALL_HOOK(IForgor::Logger, GamePause_Pause);

    custom_types::Register::AutoRegister();
}