#include "CustomTypes/SaberRecorder.hpp"
#include "UnityEngine/Resources.hpp"
#include "GlobalNamespace/SaberManager.hpp"
#include "UnityEngine/Mathf.hpp"
#include "UnityEngine/zzzz__Vector3_def.hpp"

DEFINE_TYPE(IForgor, SaberRecorder);

void IForgor::SaberRecorder::Init() 
{
    if (saberRecorderInstance != nullptr) {
		Destroy(saberRecorderInstance);
	}
	saberRecorderInstance = this;
}

void IForgor::SaberRecorder::Start() 
{
    auto sabManager = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::SaberManager*>()[0];
    _saberA = sabManager->leftSaber;
    _saberB = sabManager->rightSaber;
}

void IForgor::SaberRecorder::RecordSaberAngles() 
{
    RecordSaberAngle(_saberA);
    RecordSaberAngle(_saberB);
}

void IForgor::SaberRecorder::RecordSaberAngle(GlobalNamespace::Saber* saber) 
{
    auto saberVector = UnityEngine::Vector3::op_Subtraction(saber->get_saberBladeTopPos(), saber->get_saberBladeBottomPos());
	saberVector.z = 0;
	saberVector.Normalize();
	float saberAngle = UnityEngine::Mathf::Atan2(saberVector.y, saberVector.x) * 57.29578f;
    if(saber->get_saberType() == GlobalNamespace::SaberType::SaberA) saberAAngle = saberAngle;
    if(saber->get_saberType() == GlobalNamespace::SaberType::SaberB) saberBAngle = saberAngle;
}