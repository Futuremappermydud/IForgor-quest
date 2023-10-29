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
#include "assets.hpp"
#ifdef CHROMA
#include "conditional-dependencies/shared/main.hpp"
#include "chroma/shared/SaberAPI.hpp"
#endif

DEFINE_TYPE(IForgor, PauseUIManager);

void IForgor::PauseUIManager::OnEnable()
{
	pauseUIInstance = this;
	CreateUIElements();
}

void IForgor::PauseUIManager::CreateUIElements()
{
	spr_bloq = QuestUI::BeatSaberUI::ArrayToSprite(IncludedAssets::bloq_png);
	spr_slider_bloq = QuestUI::BeatSaberUI::ArrayToSprite(IncludedAssets::slider_png);
	spr_arrow = QuestUI::BeatSaberUI::ArrayToSprite(IncludedAssets::arrow_png);
	spr_dot = QuestUI::BeatSaberUI::ArrayToSprite(IncludedAssets::dot_png);
	spr_slider_dot = QuestUI::BeatSaberUI::ArrayToSprite(IncludedAssets::slider_dots_png);
	spr_cut_arrow = QuestUI::BeatSaberUI::ArrayToSprite(IncludedAssets::cut_arrow_png);
	spr_saber_bg = QuestUI::BeatSaberUI::ArrayToSprite(IncludedAssets::saber_bg_png);
	spr_saber_fg = QuestUI::BeatSaberUI::ArrayToSprite(IncludedAssets::saber_fg_png);
	if (_colorScheme == nullptr)
		_colorScheme = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::GameplayCoreInstaller*>()[0]->sceneSetupData->colorScheme;
    if (_pauseCanvasTransform == nullptr)
	{
		auto manager = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::PauseMenuManager*>()[0];
		_pauseCanvasTransform = manager->get_transform()->Find("Wrapper")->Find("MenuWrapper")->Find("Canvas")->get_transform();
	}

	UnityEngine::Sprite* spr_RoundRect10 = _pauseCanvasTransform->Find("MainBar")->Find("LevelBarSimple")->Find("BG")->GetComponent<HMUI::ImageView*>()->get_sprite();
	mat_UINoGlow = QuestUI::ArrayUtil::First(UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::Material*>(), [](UnityEngine::Material* x) { return x->get_name() == "UINoGlow"; });
	UnityEngine::RectTransform* uiContainer = UnityEngine::GameObject::New_ctor("IFUIContainer")->AddComponent<UnityEngine::RectTransform*>();
	uiContainer->SetParent(_pauseCanvasTransform, false);
	uiContainer->set_localScale(UnityEngine::Vector3::get_one());
	uiContainer->set_localPosition(UnityEngine::Vector3::get_zero());
	uiContainer->set_sizeDelta(UnityEngine::Vector2(3.0f, 10.0f));

	HMUI::ImageView* background = UnityEngine::GameObject::New_ctor("IFUIBackground")->AddComponent<HMUI::ImageView*>();
	background->get_transform()->SetParent(uiContainer->get_transform(), false);
	background->get_rectTransform()->set_localScale(UnityEngine::Vector3(1.0f, 1.0f, 1.0f));
	background->get_rectTransform()->set_localPosition(UnityEngine::Vector3(0.0f, 14.0f, 0.0f));
	background->get_rectTransform()->set_sizeDelta(UnityEngine::Vector2(40.0f, 10.0f));
	background->set_sprite(spr_RoundRect10);
	background->set_type(UnityEngine::UI::Image::Type::Sliced);
	background->set_color(UnityEngine::Color(0.125f, 0.125f, 0.125f, 0.75f));
	background->set_material(mat_UINoGlow);
    background->skew = 0.18f;
	background->SetAllDirty();

	groupA = UnityEngine::GameObject::New_ctor("IFUIBloq_TypeA")->AddComponent<UIGroup*>();
	groupB = UnityEngine::GameObject::New_ctor("IFUIBloq_TypeB")->AddComponent<UIGroup*>();

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
	groupA->get_transform()->set_localPosition(UnityEngine::Vector3(-5.0f, 0.0f, 0.0f));
	groupB->get_transform()->set_localPosition(UnityEngine::Vector3(5.0f, 0.0f, 0.0f));

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
			groupA->SetNoteColor(UnityEngine::Color::get_gray());
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
			groupB->SetNoteColor(UnityEngine::Color::get_gray());
		}
		_groupBNullified = true;
	}

	groupA->SetNoteCutInfo(noteRecorderInstance->noteACutInfo);
	groupB->SetNoteCutInfo(noteRecorderInstance->noteBCutInfo);


	saberRecorderInstance->RecordSaberAngles();
	groupA->SetSaberAngle(saberRecorderInstance->saberAAngle);
	groupB->SetSaberAngle(saberRecorderInstance->saberBAngle);
}