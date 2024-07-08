#include "CustomTypes/PauseUIManager.hpp"
#include "CustomTypes/UIGroup.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "HMUI/ImageView.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Mathf.hpp"


DEFINE_TYPE(IForgor, UIGroup);

void IForgor::UIGroup::Initialize()
{
	pauseUIInstance = UnityEngine::Resources::FindObjectsOfTypeAll<IForgor::PauseUIManager*>()[0];
    bloqImage = UnityEngine::GameObject::New_ctor("IFBloqImage")->AddComponent<HMUI::ImageView*>();
	bloqImage->get_transform()->SetParent(get_transform(), false);
	bloqImage->get_rectTransform()->set_localScale({0.075f, 0.075f, 0.075f});
	bloqImage->get_rectTransform()->set_localPosition(UnityEngine::Vector3::get_zero());
	bloqImage->set_sprite(pauseUIInstance->spr_bloq);
	bloqImage->set_type(UnityEngine::UI::Image::Type::Simple);
	bloqImage->set_color(UnityEngine::Color::get_red());
	bloqImage->set_material(pauseUIInstance->mat_UINoGlow);
	directionImage = UnityEngine::GameObject::New_ctor("IFDirectionImage")->AddComponent<HMUI::ImageView*>();
	directionImage->get_transform()->SetParent(bloqImage->get_transform(), false);
	directionImage->get_rectTransform()->set_localScale(UnityEngine::Vector3::get_one());
	directionImage->get_rectTransform()->set_localPosition(UnityEngine::Vector3::get_zero());
	directionImage->set_sprite(pauseUIInstance->spr_dot);
	directionImage->set_type(UnityEngine::UI::Image::Type::Simple);
	directionImage->set_color(UnityEngine::Color::get_white());
	directionImage->set_material(pauseUIInstance->mat_UINoGlow);
	cutAngleImage = UnityEngine::GameObject::New_ctor("IFCutAngleImage")->AddComponent<HMUI::ImageView*>();
	cutAngleImage->get_transform()->SetParent(bloqImage->get_transform(), false);
	cutAngleImage->get_rectTransform()->set_localScale({1.2f, 1.2f, 1.2f});
	cutAngleImage->get_rectTransform()->set_localPosition(UnityEngine::Vector3::get_zero());
	cutAngleImage->set_sprite(pauseUIInstance->spr_cut_arrow);
	cutAngleImage->set_type(UnityEngine::UI::Image::Type::Simple);
	cutAngleImage->set_color(UnityEngine::Color(1.0f, 1.0f, 1.0f, 0.75f));
	cutAngleImage->set_material(pauseUIInstance->mat_UINoGlow);
	cutAngleImage->set_enabled(false);
	saberBgImage = UnityEngine::GameObject::New_ctor("IFSaberBGImage")->AddComponent<HMUI::ImageView*>();
	saberBgImage->get_transform()->SetParent(get_transform(), false);
	saberBgImage->get_rectTransform()->set_localScale({0.075f, 0.075f, 0.075f});
	saberBgImage->get_rectTransform()->set_localPosition(UnityEngine::Vector3(0.0f, 10.0f, 0.0f));
	saberBgImage->set_sprite(pauseUIInstance->spr_saber_bg);
	saberBgImage->set_type(UnityEngine::UI::Image::Type::Simple);
	saberBgImage->set_color(UnityEngine::Color::get_white());
	saberBgImage->set_material(pauseUIInstance->mat_UINoGlow);
	saberFgImage = UnityEngine::GameObject::New_ctor("IFSaberFGImage")->AddComponent<HMUI::ImageView*>();
	saberFgImage->get_transform()->SetParent(saberBgImage->get_transform(), false);
	saberFgImage->get_rectTransform()->set_localScale(UnityEngine::Vector3::get_one());
	saberFgImage->get_rectTransform()->set_localPosition(UnityEngine::Vector3::get_zero());
	saberFgImage->set_sprite(pauseUIInstance->spr_saber_fg);
	saberFgImage->set_type(UnityEngine::UI::Image::Type::Simple);
	saberFgImage->set_color(UnityEngine::Color::get_white());
	saberFgImage->set_material(pauseUIInstance->mat_UINoGlow);
}

void IForgor::UIGroup::SetNoteData(GlobalNamespace::NoteData* noteData, void* ye)
{
	auto pauseUI = reinterpret_cast<IForgor::PauseUIManager*>(ye);
	this->noteData = noteData;

	directionImage->set_sprite(pauseUIInstance->spr_arrow);
	bloqImage->set_sprite(pauseUIInstance->spr_bloq);

	auto bloqRootTransform = bloqImage->get_rectTransform();
	switch (noteData->cutDirection) {
		case GlobalNamespace::NoteCutDirection::Down:
			bloqRootTransform->set_localRotation(UnityEngine::Quaternion::Euler(UnityEngine::Vector3(0.0f, 0.0f, 0.0f)));
			break;
		case GlobalNamespace::NoteCutDirection::Up:
			bloqRootTransform->set_localRotation(UnityEngine::Quaternion::Euler(UnityEngine::Vector3(0.0f, 0.0f, 180.0f)));
			break;
		case GlobalNamespace::NoteCutDirection::Left:
			bloqRootTransform->set_localRotation(UnityEngine::Quaternion::Euler(UnityEngine::Vector3(0.0f, 0.0f, 270.0f)));
			break;
		case GlobalNamespace::NoteCutDirection::Right:
			bloqRootTransform->set_localRotation(UnityEngine::Quaternion::Euler(UnityEngine::Vector3(0.0f, 0.0f, 90.0f)));
			break;
		case GlobalNamespace::NoteCutDirection::DownLeft:
			bloqRootTransform->set_localRotation(UnityEngine::Quaternion::Euler(UnityEngine::Vector3(0.0f, 0.0f, 315.0f)));
			break;
		case GlobalNamespace::NoteCutDirection::DownRight:
			bloqRootTransform->set_localRotation(UnityEngine::Quaternion::Euler(UnityEngine::Vector3(0.0f, 0.0f, 45.0f)));
			break;
		case GlobalNamespace::NoteCutDirection::UpLeft:
			bloqRootTransform->set_localRotation(UnityEngine::Quaternion::Euler(UnityEngine::Vector3(0.0f, 0.0f, 225.0f)));
			break;
		case GlobalNamespace::NoteCutDirection::UpRight:
			bloqRootTransform->set_localRotation(UnityEngine::Quaternion::Euler(UnityEngine::Vector3(0.0f, 0.0f, 135.0f)));
			break;
		case GlobalNamespace::NoteCutDirection::None: //??
		case GlobalNamespace::NoteCutDirection::Any:
			bloqRootTransform->set_localRotation(UnityEngine::Quaternion::Euler(UnityEngine::Vector3(0.0f, 0.0f, noteData->cutDirectionAngleOffset)));
			if (noteData->gameplayType == GlobalNamespace::NoteData::GameplayType::BurstSliderElement)
			{
				bloqImage->set_sprite(pauseUIInstance->spr_slider_bloq);
				directionImage->set_sprite(pauseUIInstance->spr_slider_dot);
			}
			else
			{
				directionImage->set_sprite(pauseUIInstance->spr_dot);
			}
			break;
	}
}

void IForgor::UIGroup::SetNoteCutInfo(std::optional<GlobalNamespace::NoteCutInfo> noteCutInfo)
{
	this->noteCutInfo = noteCutInfo;
	if (noteCutInfo.has_value() && noteCutInfo.value().get_allIsOK()) {
		// Maffs from SliceVisualizer bc I cant even pass calc 2 (https://github.com/m1el/BeatSaber-SliceVisualizer/blob/master/Core/NsvSlicedBlock.cs)
		auto cutDirection = UnityEngine::Vector3(-noteCutInfo.value().cutNormal.y, noteCutInfo.value().cutNormal.x, 0.0f);
		float cutAngle = UnityEngine::Mathf::Atan2(cutDirection.y, cutDirection.x) *  57.29578f + 270.0f;
		cutAngleImage->set_enabled(true);
		cutAngleImage->get_rectTransform()->set_rotation(UnityEngine::Quaternion::Euler(UnityEngine::Vector3(0.0f, 0.0f, cutAngle)));
	} else {
		cutAngleImage->set_enabled(false);
	}	
}

void IForgor::UIGroup::SetSaberAngle(float angle)
{
	saberBgImage->get_rectTransform()->set_localRotation(UnityEngine::Quaternion::Euler(UnityEngine::Vector3(0.0f, 0.0f, angle - 90.0f)));
}
void IForgor::UIGroup::SetSaberXPosition(float xpos)
{
	saberBgImage->get_rectTransform()->set_localPosition(UnityEngine::Vector3(xpos, 0.0f, 0.0f));
}

void IForgor::UIGroup::SetNoteColor(UnityEngine::Color color)
{
	noteColor = color;
	bloqImage->set_color(color);
}

void IForgor::UIGroup::SetSaberColor(UnityEngine::Color color)
{
	saberColor = color;
	saberBgImage->set_color(color);
}
