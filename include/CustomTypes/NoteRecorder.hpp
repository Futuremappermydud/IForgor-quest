#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "GlobalNamespace/NoteData.hpp"
#include "GlobalNamespace/NoteCutInfo.hpp"
#include "GlobalNamespace/ScoreController.hpp"
#include <optional>

DECLARE_CLASS_CODEGEN(IForgor, NoteRecorder, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(GlobalNamespace::NoteData*, noteAData);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::NoteData*, noteBData);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::ScoreController*, scoreController);
    DECLARE_INSTANCE_METHOD(void, Start);
    DECLARE_INSTANCE_METHOD(void, OnNoteWasCut, GlobalNamespace::NoteData* noteData, GlobalNamespace::NoteCutInfo noteCutInfo);
    DECLARE_INSTANCE_METHOD(void, OnNoteWasMissed, GlobalNamespace::NoteData* noteData);
public:
    void ProcessNote(GlobalNamespace::NoteData* noteData, std::optional<GlobalNamespace::NoteCutInfo> noteCutInfo);
    std::optional<GlobalNamespace::NoteCutInfo> noteBCutInfo;
    std::optional<GlobalNamespace::NoteCutInfo> noteACutInfo;

)

inline IForgor::NoteRecorder* noteRecorderInstance;