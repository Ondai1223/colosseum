// Fill out your copyright notice in the Description page of Project Settings.


#include "Title/TitleMenu.h"
#include "Title/TitleMenuButton.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"


#define BUTTON_LOCAL_NAME     TEXT("WBP_Title_MenuButton_1")
#define BUTTON_ONLINE_NAME     TEXT("WBP_Title_MenuButton_2")
#define BUTTON_PLAYER_NAME     TEXT("WBP_Title_MenuButton_3")
#define BUTTON_HOWTO_NAME     TEXT("WBP_Title_MenuButton_4")
#define BUTTON_HELP_NAME     TEXT("WBP_Title_MenuButton_5")
#define BUTTON_CREDIT_NAME     TEXT("WBP_Title_MenuButton_6")

#define OVERLAY_NAME              TEXT("Overlay_Selected")
#define TEXT_BLOCK_NAME         TEXT("TextBlock_TitleMenu")

#define TEXT_NAME_LOCAL        TEXT("ローカル対戦")
#define TEXT_NAME_ONLINE        TEXT("オンライン対戦")
#define TEXT_NAME_PLAYER        TEXT("プレイヤー名の変更")
#define TEXT_NAME_HOWTO        TEXT("遊び方ガイド")
#define TEXT_NAME_HELP        TEXT("ヘルプ")
#define TEXT_NAME_CREDIT        TEXT("クレジット")

void UTitleMenu::NativeConstruct()
{
	Super::NativeConstruct();

	TObjectPtr<UTitleMenuButton> ButtonLocal = Cast<UTitleMenuButton>(GetWidgetFromName(BUTTON_LOCAL_NAME));
	TObjectPtr<UTitleMenuButton> ButtonOnline = Cast<UTitleMenuButton>(GetWidgetFromName(BUTTON_ONLINE_NAME));
	TObjectPtr<UTitleMenuButton> ButtonPlayer = Cast<UTitleMenuButton>(GetWidgetFromName(BUTTON_PLAYER_NAME));
	TObjectPtr<UTitleMenuButton> ButtonHowto = Cast<UTitleMenuButton>(GetWidgetFromName(BUTTON_HOWTO_NAME));
	TObjectPtr<UTitleMenuButton> ButtonHelp = Cast<UTitleMenuButton>(GetWidgetFromName(BUTTON_HELP_NAME));
	TObjectPtr<UTitleMenuButton> ButtonCredit = Cast<UTitleMenuButton>(GetWidgetFromName(BUTTON_CREDIT_NAME));

	TObjectPtr<UOverlay> LocalOverlay = Cast<UOverlay>(ButtonLocal->GetWidgetFromName(OVERLAY_NAME));
	TObjectPtr<UOverlay> OnlineOverlay = Cast<UOverlay>(ButtonOnline->GetWidgetFromName(OVERLAY_NAME));
	TObjectPtr<UOverlay> PlayerOverlay = Cast<UOverlay>(ButtonPlayer->GetWidgetFromName(OVERLAY_NAME));
	TObjectPtr<UOverlay> HowtoOverlay = Cast<UOverlay>(ButtonHowto->GetWidgetFromName(OVERLAY_NAME));
	TObjectPtr<UOverlay> HelpOverlay = Cast<UOverlay>(ButtonHelp->GetWidgetFromName(OVERLAY_NAME));
	TObjectPtr<UOverlay> CreditOverlay = Cast<UOverlay>(ButtonCredit->GetWidgetFromName(OVERLAY_NAME));

	TitleOverlay.Add(LocalOverlay);
	TitleOverlay.Add(OnlineOverlay);
	TitleOverlay.Add(PlayerOverlay);
	TitleOverlay.Add(HowtoOverlay);
	TitleOverlay.Add(HelpOverlay);
	TitleOverlay.Add(CreditOverlay);

	TObjectPtr<UTextBlock> TextLocal = Cast<UTextBlock>(ButtonLocal->GetWidgetFromName(TEXT_BLOCK_NAME));
	TObjectPtr<UTextBlock> TextOnline = Cast<UTextBlock>(ButtonOnline->GetWidgetFromName(TEXT_BLOCK_NAME));
	TObjectPtr<UTextBlock> TextPlayer = Cast<UTextBlock>(ButtonPlayer->GetWidgetFromName(TEXT_BLOCK_NAME));
	TObjectPtr<UTextBlock> TextHowto = Cast<UTextBlock>(ButtonHowto->GetWidgetFromName(TEXT_BLOCK_NAME));
	TObjectPtr<UTextBlock> TextHelp = Cast<UTextBlock>(ButtonHelp->GetWidgetFromName(TEXT_BLOCK_NAME));
	TObjectPtr<UTextBlock> TextCredit = Cast<UTextBlock>(ButtonCredit->GetWidgetFromName(TEXT_BLOCK_NAME));

	TextLocal->SetText(FText::FromString(TEXT_NAME_LOCAL));
	TextOnline->SetText(FText::FromString(TEXT_NAME_ONLINE));
	TextPlayer->SetText(FText::FromString(TEXT_NAME_PLAYER));
	TextHowto->SetText(FText::FromString(TEXT_NAME_HOWTO));
	TextHelp->SetText(FText::FromString(TEXT_NAME_HELP));
	TextCredit->SetText(FText::FromString(TEXT_NAME_CREDIT));
}

void UTitleMenu::Init()
{
	bool Initial = true;
	for (TArray<TObjectPtr<UOverlay>>::TIterator Ite(TitleOverlay); Ite; ++Ite)
	{
		if (Initial)
		{
			(*Ite)->SetVisibility(ESlateVisibility::Visible);
			Initial = false;
		}
		else
		{
			(*Ite)->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UTitleMenu::MenuButtonSwitch(int index)
{
	for (int i = 0; i < TitleOverlay.Num(); i++)
	{
		if (i == index)
		{
			TitleOverlay[i]->SetVisibility(ESlateVisibility::Visible);
			// UE_LOG(LogTemp, Warning, TEXT("ボタンを切り替えます。"));
		}
		else
		{
			TitleOverlay[i]->SetVisibility(ESlateVisibility::Hidden);
		}
		
	}
}
