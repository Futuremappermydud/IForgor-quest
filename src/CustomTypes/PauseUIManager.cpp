#include "CustomTypes/PauseUIManager.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "HMUI/ImageView.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "Sprites.hpp"
#ifdef CHROMA
#include "conditional-dependencies/shared/main.hpp"
#include "chroma/shared/SaberAPI.hpp"
#endif
using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace il2cpp_utils;

DEFINE_TYPE(IForgor, PauseUIManager);

void IForgor::PauseUIManager::OnEnable()
{
	pauseUIInstance = this;
	CreateUIElements();
}

void IForgor::PauseUIManager::CreateUIElements()
{
	getModLogger().info("1");
	spr_bloq = QuestUI::BeatSaberUI::Base64ToSprite(spr_bloq_base64);
	spr_slider_bloq = QuestUI::BeatSaberUI::Base64ToSprite(spr_slider_bloq_base64);
	spr_arrow = QuestUI::BeatSaberUI::Base64ToSprite(spr_arrow_base64);
	spr_dot = QuestUI::BeatSaberUI::Base64ToSprite(spr_dot_base64);
	spr_slider_dot = QuestUI::BeatSaberUI::Base64ToSprite(spr_slider_dot_base64);
	spr_cut_arrow = QuestUI::BeatSaberUI::Base64ToSprite(spr_cut_arrow_base64);
	spr_saber_bg = QuestUI::BeatSaberUI::Base64ToSprite(spr_saber_bg_base64);
	spr_saber_fg = QuestUI::BeatSaberUI::Base64ToSprite(spr_saber_fg_base64);
	if (_colorScheme == nullptr)
		_colorScheme = Resources::FindObjectsOfTypeAll<GameplayCoreInstaller*>()[0]->sceneSetupData->colorScheme;
    if (_pauseCanvasTransform == nullptr)
	{
		PauseMenuManager* manager = Resources::FindObjectsOfTypeAll<PauseMenuManager*>()[0];
		getModLogger().info("%p", manager);
		_pauseCanvasTransform = manager->get_transform()->Find(newcsstr("Wrapper"))->Find(newcsstr("MenuWrapper"))->Find(newcsstr("Canvas"))->get_transform();
	}
	getModLogger().info("2");

	Sprite* spr_RoundRect10 = _pauseCanvasTransform->Find(newcsstr("MainBar"))->Find(newcsstr("LevelBarSimple"))->Find(newcsstr("BG"))->GetComponent<HMUI::ImageView*>()->get_sprite();
	mat_UINoGlow = QuestUI::ArrayUtil::First(Resources::FindObjectsOfTypeAll<Material*>(), [](Material* x) { return to_utf8(csstrtostr(x->get_name())) == "UINoGlow"; });
	RectTransform* uiContainer = GameObject::New_ctor(newcsstr("IFUIContainer"))->AddComponent<RectTransform*>();
	uiContainer->SetParent(_pauseCanvasTransform, false);
	uiContainer->set_localScale(Vector3::get_one());
	uiContainer->set_localPosition(Vector3::get_zero());
	uiContainer->set_sizeDelta(Vector2(3.0f, 10.0f));
	getModLogger().info("3");

	HMUI::ImageView* background = GameObject::New_ctor(newcsstr("IFUIBackground"))->AddComponent<HMUI::ImageView*>();
	background->get_transform()->SetParent(uiContainer->get_transform(), false);
	background->get_rectTransform()->set_localScale(Vector3(1.0f, 1.0f, 1.0f));
	background->get_rectTransform()->set_localPosition(Vector3(0.0f, 14.0f, 0.0f));
	background->get_rectTransform()->set_sizeDelta(Vector2(40.0f, 10.0f));
	background->set_sprite(spr_RoundRect10);
	background->set_type(Image::Type::Sliced);
	background->set_color(UnityEngine::Color(0.125f, 0.125f, 0.125f, 0.75f));
	background->set_material(mat_UINoGlow);
    background->skew = 0.18f;
	background->SetAllDirty();
	getModLogger().info("4");

	groupA = GameObject::New_ctor(newcsstr("IFUIBloq_TypeA"))->AddComponent<UIGroup*>();
	groupB = GameObject::New_ctor(newcsstr("IFUIBloq_TypeB"))->AddComponent<UIGroup*>();
	getModLogger().info("5");

	groupA->Initialize();
	groupB->Initialize();
	groupA->SetNoteColor(_colorScheme->get_saberAColor());
	groupB->SetNoteColor(_colorScheme->get_saberBColor());
	groupA->SetSaberColor(_colorScheme->get_saberAColor());
	groupB->SetSaberColor(_colorScheme->get_saberBColor());
	groupA->SetSaberXPosition(-9.0f);
	groupB->SetSaberXPosition(9.0f);
	groupA->get_transform()->SetParent(background->get_transform(), false);
	groupB->get_transform()->SetParent(background->get_transform(), false);
	groupA->get_transform()->set_localPosition(Vector3(-5.0f, 0.0f, 0.0f));
	groupB->get_transform()->set_localPosition(Vector3(5.0f, 0.0f, 0.0f));
	getModLogger().info("6");

}

void IForgor::PauseUIManager::OnPause()
{
	#ifdef CHROMA
	static auto getColors = CondDeps::Find<Chroma::SaberAPI::ColorOptPair>("chroma", "getGlobalSabersColorSafe");
	#endif
	auto leftColor = _colorScheme->get_saberAColor();
	auto rightColor = _colorScheme->get_saberBColor();
	#ifdef CHROMA
	if(getColors.has_value()) 
	{
		Chroma::SaberAPI::ColorOptPair colors = getColors.value()();
		bool isLeftColorChroma = colors.first.isSet;
		bool isRightColorChroma = colors.second.isSet;

		auto leftColorChroma = colors.first.getColor();
		auto rightColorChroma = colors.second.getColor();

		leftColor = isLeftColorChroma ? leftColorChroma : leftColor;
		rightColor = isRightColorChroma ? rightColorChroma : rightColor;
	}
	#endif

    if (noteRecorderInstance->noteAData != nullptr) {
		if (_groupANullified && _colorScheme != nullptr) {
			groupA->SetNoteColor(leftColor);
		}
		_groupANullified = false;
		groupA->SetNoteData(noteRecorderInstance->noteAData, this);
	} else {
		if (_colorScheme != nullptr) {
			groupA->SetNoteColor(Color::get_gray());
		}
		_groupANullified = true;
	}
	if (noteRecorderInstance->noteBData != nullptr) {
		if (_groupBNullified && _colorScheme != nullptr) {
			groupB->SetNoteColor(rightColor);
		}
		_groupBNullified = false;
		groupB->SetNoteData(noteRecorderInstance->noteBData, this);
	} else {
		if (_colorScheme != nullptr) {
			groupB->SetNoteColor(Color::get_gray());
		}
		_groupBNullified = true;
	}

	groupA->SetNoteCutInfo(noteRecorderInstance->noteACutInfo);
	groupB->SetNoteCutInfo(noteRecorderInstance->noteBCutInfo);


	saberRecorderInstance->RecordSaberAngles();
	groupA->SetSaberAngle(saberRecorderInstance->saberAAngle);
	groupB->SetSaberAngle(saberRecorderInstance->saberBAngle);
}