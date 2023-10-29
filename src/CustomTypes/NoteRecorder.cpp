#include "CustomTypes/NoteRecorder.hpp"
#include "UnityEngine/Resources.hpp"

DEFINE_TYPE(IForgor, NoteRecorder);

void IForgor::NoteRecorder::Start() 
{
    noteAData = nullptr;
	noteBData = nullptr;
}

void IForgor::NoteRecorder::OnNoteWasCut(GlobalNamespace::NoteData* noteData, GlobalNamespace::NoteCutInfo noteCutInfo) 
{
	if (noteData == nullptr || noteData->colorType == GlobalNamespace::ColorType::None) return;
	if (!noteCutInfo.saberTypeOK)
	{
		ProcessNote(noteData, nullptr);
	}
	else
	{
		ProcessNote(noteData, noteCutInfo);
	}
}

void IForgor::NoteRecorder::OnNoteWasMissed(GlobalNamespace::NoteData* noteData) 
{
    ProcessNote(noteData, GlobalNamespace::NoteCutInfo());
}
void IForgor::NoteRecorder::ProcessNote(GlobalNamespace::NoteData* noteData, GlobalNamespace::NoteCutInfo noteCutInfo) 
{
    if (noteData->colorType == GlobalNamespace::ColorType::ColorA)
	{
		noteAData = noteData;
		noteACutInfo = noteCutInfo;
	}
	else if (noteData->colorType == GlobalNamespace::ColorType::ColorB)
	{
		noteBData = noteData;
		noteBCutInfo = noteCutInfo;
	}
}
