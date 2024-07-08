#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/ImageView.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Color.hpp"
#include "GlobalNamespace/NoteData.hpp"
#include "GlobalNamespace/NoteCutInfo.hpp"

DECLARE_CLASS_CODEGEN(IForgor, UIGroup, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, bloqImage);
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, directionImage);
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, cutAngleImage);
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, saberBgImage);
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, saberFgImage);

    DECLARE_INSTANCE_FIELD(GlobalNamespace::NoteData*, noteData);
    DECLARE_INSTANCE_FIELD(UnityEngine::Color, noteColor);
    DECLARE_INSTANCE_FIELD(UnityEngine::Color, saberColor);

    DECLARE_INSTANCE_METHOD(void, Initialize);
    DECLARE_INSTANCE_METHOD(void, SetNoteData, GlobalNamespace::NoteData* noteData, void* ye);
    DECLARE_INSTANCE_METHOD(void, SetSaberAngle, float angle);
    DECLARE_INSTANCE_METHOD(void, SetSaberXPosition, float xpos);
    DECLARE_INSTANCE_METHOD(void, SetNoteColor, UnityEngine::Color color);
    DECLARE_INSTANCE_METHOD(void, SetSaberColor, UnityEngine::Color color);
    
public:
    void SetNoteCutInfo(std::optional<GlobalNamespace::NoteCutInfo> noteCutInfo);
    std::optional<GlobalNamespace::NoteCutInfo> noteCutInfo;
)