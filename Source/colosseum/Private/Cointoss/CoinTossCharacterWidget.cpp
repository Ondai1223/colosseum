// Fill out your copyright notice in the Description page of Project Settings.


#include "Cointoss/CoinTossCharacterWidget.h"

#define CHAR_FACE_NAME_1P_1   TEXT("WBP_InGame_CharaFace_1p_1")
#define CHAR_FACE_NAME_1P_2   TEXT("WBP_InGame_CharaFace_1p_2")
#define CHAR_FACE_NAME_1P_3   TEXT("WBP_InGame_CharaFace_1p_3")

#define CHAR_FACE_NAME_2P_1   TEXT("WBP_InGame_CharaFace_2p_1")
#define CHAR_FACE_NAME_2P_2   TEXT("WBP_InGame_CharaFace_2p_2")
#define CHAR_FACE_NAME_2P_3   TEXT("WBP_InGame_CharaFace_2p_3")

void UCoinTossCharacterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	CharactorFace1 = Cast<UCharaFace>(GetWidgetFromName(CHAR_FACE_NAME_1P_1));
	CharactorFace2 = Cast<UCharaFace>(GetWidgetFromName(CHAR_FACE_NAME_1P_2));
	CharactorFace3 = Cast<UCharaFace>(GetWidgetFromName(CHAR_FACE_NAME_1P_3));
	CharactorFace4 = Cast<UCharaFace>(GetWidgetFromName(CHAR_FACE_NAME_2P_1));
	CharactorFace5 = Cast<UCharaFace>(GetWidgetFromName(CHAR_FACE_NAME_2P_2));
	CharactorFace6 = Cast<UCharaFace>(GetWidgetFromName(CHAR_FACE_NAME_2P_3));

	CharactorFace1->SetArrow(false);
	CharactorFace2->SetArrow(false);
	CharactorFace3->SetArrow(false);
	CharactorFace4->SetArrow(false);
	CharactorFace5->SetArrow(false);
	CharactorFace6->SetArrow(false);
}

void UCoinTossCharacterWidget::ChangeFace(AUnitBattleParameter* BattleUnit, int32 index)
{
	switch (index)
	{
		case 0:
			if (BattleUnit->GetTeamID() == EUnitTeamID::EUTID_Team1)
			{
				CharactorFace1->TeamID = BattleUnit->GetTeamID();
				CharactorFace1->JobFaceID = BattleUnit->GetJobID();

				CharactorFace1->ChangeFace();
				UE_LOG(LogTemp, Warning, TEXT("%dの顔を変更しました: TeamID=%d, JobFaceID=%d"), index, CharactorFace1->TeamID, CharactorFace1->JobFaceID);
			}else
			{
				CharactorFace4->TeamID = BattleUnit->GetTeamID();
				CharactorFace4->JobFaceID = BattleUnit->GetJobID();

				CharactorFace4->ChangeFace();
				UE_LOG(LogTemp, Warning, TEXT("%dの顔を変更しました: TeamID=%d, JobFaceID=%d"), index, CharactorFace4->TeamID, CharactorFace4->JobFaceID);
			}
			break;
		case 1:
			if (BattleUnit->GetTeamID() == EUnitTeamID::EUTID_Team1)
			{
				CharactorFace2->TeamID = BattleUnit->GetTeamID();
				CharactorFace2->JobFaceID = BattleUnit->GetJobID();

				CharactorFace2->ChangeFace();
				UE_LOG(LogTemp, Warning, TEXT("%dの顔を変更しました: TeamID=%d, JobFaceID=%d"), index, CharactorFace2->TeamID, CharactorFace2->JobFaceID);
			}else
			{
				CharactorFace5->TeamID = BattleUnit->GetTeamID();
				CharactorFace5->JobFaceID = BattleUnit->GetJobID();

				CharactorFace5->ChangeFace();
				UE_LOG(LogTemp, Warning, TEXT("%dの顔を変更しました: TeamID=%d, JobFaceID=%d"), index, CharactorFace5->TeamID, CharactorFace5->JobFaceID);	
			}
			break;
		case 2:
			if (BattleUnit->GetTeamID() == EUnitTeamID::EUTID_Team1)
			{
				CharactorFace3->TeamID = BattleUnit->GetTeamID(	);
				CharactorFace3->JobFaceID = BattleUnit->GetJobID();

				CharactorFace3->ChangeFace();
				UE_LOG(LogTemp, Warning, TEXT("%dの顔を変更しました: TeamID=%d, JobFaceID=%d"), index, CharactorFace3->TeamID, CharactorFace3->JobFaceID);	
			}else
			{
				CharactorFace6->TeamID = BattleUnit->GetTeamID();
				CharactorFace6->JobFaceID = BattleUnit->GetJobID();

				CharactorFace6->ChangeFace();
				UE_LOG(LogTemp, Warning, TEXT("%dの顔を変更しました: TeamID=%d, JobFaceID=%d"), index, CharactorFace6->TeamID, CharactorFace6->JobFaceID);	
			}
			break;
		default:
			break;
	}
}
