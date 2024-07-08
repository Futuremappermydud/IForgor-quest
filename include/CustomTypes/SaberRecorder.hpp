#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "GlobalNamespace/Saber.hpp"

DECLARE_CLASS_CODEGEN(IForgor, SaberRecorder, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(GlobalNamespace::Saber*, _saberA);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::Saber*, _saberB);
    DECLARE_INSTANCE_FIELD(float, saberAAngle);
    DECLARE_INSTANCE_FIELD(float, saberBAngle);
    DECLARE_INSTANCE_METHOD(void, Init);
    DECLARE_INSTANCE_METHOD(void, Start);
    DECLARE_INSTANCE_METHOD(void, RecordSaberAngles);
    DECLARE_INSTANCE_METHOD(void, RecordSaberAngle, GlobalNamespace::Saber* saber);
)

inline IForgor::SaberRecorder* saberRecorderInstance;