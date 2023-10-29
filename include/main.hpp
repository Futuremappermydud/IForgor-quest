#pragma once

#include "CustomTypes/SaberRecorder.hpp"
#include "CustomTypes/NoteRecorder.hpp"
#include "CustomTypes/UIGroup.hpp"
#include "CustomTypes/PauseUIManager.hpp"

#include "modloader/shared/modloader.hpp"

#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"

Logger& getLogger();
#define CHROMA