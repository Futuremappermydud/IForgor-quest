#pragma once

#include "main.hpp"
#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "GlobalNamespace/NoteData.hpp"
#include "GlobalNamespace/NoteCutInfo.hpp"
#include "GlobalNamespace/ScoreController.hpp"

DECLARE_CLASS_CODEGEN(IForgor, NoteRecorder, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(GlobalNamespace::NoteData*, noteAData);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::NoteData*, noteBData);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::NoteCutInfo, noteACutInfo);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::NoteCutInfo, noteBCutInfo);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::ScoreController*, scoreController);
    DECLARE_INSTANCE_METHOD(void, Start);
    DECLARE_INSTANCE_METHOD(void, OnNoteWasCut, GlobalNamespace::NoteData* noteData, GlobalNamespace::NoteCutInfo noteCutInfo);
    DECLARE_INSTANCE_METHOD(void, OnNoteWasMissed, GlobalNamespace::NoteData* noteData);
    DECLARE_INSTANCE_METHOD(void, ProcessNote, GlobalNamespace::NoteData* noteData, GlobalNamespace::NoteCutInfo noteCutInfo);
)

inline IForgor::NoteRecorder* noteRecorderInstance;