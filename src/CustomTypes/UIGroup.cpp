#include "CustomTypes/PauseUIManager.hpp"
#include "CustomTypes/UIGroup.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "HMUI/ImageView.hpp"
#include "main.hpp"
using namespace GlobalNamespace;
using namespace HMUI;
using il2cpp_utils::newcsstr;
using namespace UnityEngine;
using namespace UnityEngine::UI;

DEFINE_TYPE(IForgor, UIGroup);

void IForgor::UIGroup::Initialize()
{
	pauseUIInstance = Resources::FindObjectsOfTypeAll<IForgor::PauseUIManager*>()[0];
	getLogger().info("%p", pauseUIInstance);
	getLogger().info("%p", pauseUIInstance->spr_bloq);
    getLogger().info("%p", pauseUIInstance->spr_dot);
    getLogger().info("%p", pauseUIInstance->spr_cut_arrow);
	getLogger().info("%p", pauseUIInstance->spr_saber_bg);
    getLogger().info("%p", pauseUIInstance->spr_saber_fg);
    getLogger().info("%p", pauseUIInstance->spr_arrow);
    bloqImage = GameObject::New_ctor(newcsstr("IFBloqImage"))->AddComponent<ImageView*>();
	bloqImage->get_transform()->SetParent(get_transform(), false);
	bloqImage->get_rectTransform()->set_localScale(Vector3::get_one() * 0.075f);
	bloqImage->get_rectTransform()->set_localPosition(Vector3::get_zero());
	bloqImage->set_sprite(pauseUIInstance->spr_bloq);
	bloqImage->set_type(Image::Type::Simple);
	bloqImage->set_color(Color::get_red());
	bloqImage->set_material(pauseUIInstance->mat_UINoGlow);
	directionImage = GameObject::New_ctor(newcsstr("IFDirectionImage"))->AddComponent<ImageView*>();
	directionImage->get_transform()->SetParent(bloqImage->get_transform(), false);
	directionImage->get_rectTransform()->set_localScale(Vector3::get_one());
	directionImage->get_rectTransform()->set_localPosition(Vector3::get_zero());
	directionImage->set_sprite(pauseUIInstance->spr_dot);
	directionImage->set_type(Image::Type::Simple);
	directionImage->set_color(Color::get_white());
	directionImage->set_material(pauseUIInstance->mat_UINoGlow);
	cutAngleImage = GameObject::New_ctor(newcsstr("IFCutAngleImage"))->AddComponent<ImageView*>();
	cutAngleImage->get_transform()->SetParent(bloqImage->get_transform(), false);
	cutAngleImage->get_rectTransform()->set_localScale(Vector3::get_one() * 1.2f);
	cutAngleImage->get_rectTransform()->set_localPosition(Vector3::get_zero());
	cutAngleImage->set_sprite(pauseUIInstance->spr_cut_arrow);
	cutAngleImage->set_type(Image::Type::Simple);
	cutAngleImage->set_color(Color(1.0f, 1.0f, 1.0f, 0.75f));
	cutAngleImage->set_material(pauseUIInstance->mat_UINoGlow);
	cutAngleImage->set_enabled(false);
	saberBgImage = GameObject::New_ctor(newcsstr("IFSaberBGImage"))->AddComponent<ImageView*>();
	saberBgImage->get_transform()->SetParent(get_transform(), false);
	saberBgImage->get_rectTransform()->set_localScale(Vector3::get_one() * 0.075f);
	saberBgImage->get_rectTransform()->set_localPosition(Vector3(0.0f, 10.0f, 0.0f));
	saberBgImage->set_sprite(pauseUIInstance->spr_saber_bg);
	saberBgImage->set_type(Image::Type::Simple);
	saberBgImage->set_color(Color::get_white());
	saberBgImage->set_material(pauseUIInstance->mat_UINoGlow);
	saberFgImage = GameObject::New_ctor(newcsstr("IFSaberFGImage"))->AddComponent<ImageView*>();
	saberFgImage->get_transform()->SetParent(saberBgImage->get_transform(), false);
	saberFgImage->get_rectTransform()->set_localScale(Vector3::get_one());
	saberFgImage->get_rectTransform()->set_localPosition(Vector3::get_zero());
	saberFgImage->set_sprite(pauseUIInstance->spr_saber_fg);
	saberFgImage->set_type(Image::Type::Simple);
	saberFgImage->set_color(Color::get_white());
	saberFgImage->set_material(pauseUIInstance->mat_UINoGlow);
}

void IForgor::UIGroup::SetNoteData(GlobalNamespace::NoteData* noteData, void* ye)
{
	auto pauseUI = reinterpret_cast<IForgor::PauseUIManager*>(ye);
	this->noteData = noteData;

	directionImage->set_sprite(pauseUIInstance->spr_arrow);
	bloqImage->set_sprite(pauseUIInstance->spr_bloq);

	RectTransform* bloqRootTransform = bloqImage->get_rectTransform();
	switch (noteData->cutDirection) {
		case NoteCutDirection::Down:
			bloqRootTransform->set_localRotation(Quaternion::Euler(Vector3(0.0f, 0.0f, 0.0f)));
			break;
		case NoteCutDirection::Up:
			bloqRootTransform->set_localRotation(Quaternion::Euler(Vector3(0.0f, 0.0f, 180.0f)));
			break;
		case NoteCutDirection::Left:
			bloqRootTransform->set_localRotation(Quaternion::Euler(Vector3(0.0f, 0.0f, 270.0f)));
			break;
		case NoteCutDirection::Right:
			bloqRootTransform->set_localRotation(Quaternion::Euler(Vector3(0.0f, 0.0f, 90.0f)));
			break;
		case NoteCutDirection::DownLeft:
			bloqRootTransform->set_localRotation(Quaternion::Euler(Vector3(0.0f, 0.0f, 315.0f)));
			break;
		case NoteCutDirection::DownRight:
			bloqRootTransform->set_localRotation(Quaternion::Euler(Vector3(0.0f, 0.0f, 45.0f)));
			break;
		case NoteCutDirection::UpLeft:
			bloqRootTransform->set_localRotation(Quaternion::Euler(Vector3(0.0f, 0.0f, 225.0f)));
			break;
		case NoteCutDirection::UpRight:
			bloqRootTransform->set_localRotation(Quaternion::Euler(Vector3(0.0f, 0.0f, 135.0f)));
			break;
		case NoteCutDirection::Any:
			bloqRootTransform->set_localRotation(Quaternion::Euler(Vector3(0.0f, 0.0f, noteData->cutDirectionAngleOffset)));
			if (noteData->gameplayType == NoteData::GameplayType::BurstSliderElement)
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

void IForgor::UIGroup::SetNoteCutInfo(GlobalNamespace::NoteCutInfo noteCutInfo)
{
	this->noteCutInfo = noteCutInfo;
	if (noteCutInfo.get_allIsOK()) {
		// Maffs from SliceVisualizer bc I cant even pass calc 2 (https://github.com/m1el/BeatSaber-SliceVisualizer/blob/master/Core/NsvSlicedBlock.cs)
		Vector3 cutDirection = Vector3(-noteCutInfo.cutNormal.y, noteCutInfo.cutNormal.x, 0.0f);
		float cutAngle = Mathf::Atan2(cutDirection.y, cutDirection.x) *  57.29578f + 270.0f;
		cutAngleImage->set_enabled(true);
		cutAngleImage->get_rectTransform()->set_rotation(Quaternion::Euler(Vector3(0.0f, 0.0f, cutAngle)));
	} else {
		cutAngleImage->set_enabled(false);
	}	
}

void IForgor::UIGroup::SetSaberAngle(float angle)
{
	saberBgImage->get_rectTransform()->set_localRotation(Quaternion::Euler(Vector3(0.0f, 0.0f, angle - 90.0f)));
}
void IForgor::UIGroup::SetSaberXPosition(float xpos)
{
	saberBgImage->get_rectTransform()->set_localPosition(Vector3(xpos, 0.0f, 0.0f));
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
