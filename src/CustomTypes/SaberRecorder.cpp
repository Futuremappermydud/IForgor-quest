#include "CustomTypes/SaberRecorder.hpp"
#include "UnityEngine/Resources.hpp"
#include "GlobalNamespace/SaberManager.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

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
    auto sabManager = Resources::FindObjectsOfTypeAll<SaberManager*>()[0];
    _saberA = sabManager->leftSaber;
    _saberB = sabManager->rightSaber;
}

void IForgor::SaberRecorder::RecordSaberAngles() 
{
    RecordSaberAngle(_saberA);
    RecordSaberAngle(_saberB);
}

void IForgor::SaberRecorder::RecordSaberAngle(Saber* saber) 
{
    getLogger().info("%p", saber);
    Vector3 saberVector = saber->get_saberBladeTopPos() - saber->get_saberBladeBottomPos();
	saberVector.z = 0;
	saberVector.Normalize();
	float saberAngle = Mathf::Atan2(saberVector.y, saberVector.x) * 57.29578f;
    if(saber->get_saberType() == SaberType::SaberA) saberAAngle = saberAngle;
    if(saber->get_saberType() == SaberType::SaberB) saberBAngle = saberAngle;
}