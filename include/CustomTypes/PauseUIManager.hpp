#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Material.hpp"
#include "UIGroup.hpp"
#include "GlobalNamespace/ColorScheme.hpp"

DECLARE_CLASS_CODEGEN(IForgor, PauseUIManager, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, _pauseCanvasTransform);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::ColorScheme*, _colorScheme);

    DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, spr_bloq);
    DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, spr_slider_bloq);
    DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, spr_arrow);
    DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, spr_dot);
    DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, spr_slider_dot);
    DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, spr_cut_arrow);
    DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, spr_saber_bg);
    DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, spr_saber_fg);
    DECLARE_INSTANCE_FIELD(UnityEngine::Material*, mat_UINoGlow);

    DECLARE_INSTANCE_FIELD(bool, _groupANullified);
    DECLARE_INSTANCE_FIELD(bool, _groupBNullified);

    DECLARE_INSTANCE_FIELD(IForgor::UIGroup*, groupA);
    DECLARE_INSTANCE_FIELD(IForgor::UIGroup*, groupB);

    DECLARE_INSTANCE_METHOD(void, OnEnable);
    DECLARE_INSTANCE_METHOD(void, CreateUIElements);
    DECLARE_INSTANCE_METHOD(void, OnPause);
)

inline IForgor::PauseUIManager* pauseUIInstance;