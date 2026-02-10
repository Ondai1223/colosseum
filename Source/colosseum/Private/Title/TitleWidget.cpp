// Fill out your copyright notice in the Description page of Project Settings.


#include "Title/TitleWidget.h"
#include "Title/TitleGameMode.h"

#define TitleMenu TEXT("WBP_Title_Menu")

void UTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TitleView = Cast<UTitleMenu>(GetWidgetFromName(TitleMenu));
	TitleController = Cast<ATitleController>(GetWorld()->GetFirstPlayerController());

	if (TitleController)
	{
		// コントローラーのデリゲートに自分の関数をバインドする（購読開始）
		TitleController->OnInputChanged.AddDynamic(this, &UTitleWidget::HandleInputChanged);
		// UE_LOG(LogTemp, Warning, TEXT("登録します"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TitleControllerの取得に失敗しました"));
	}
	if(TitleView)
	{
		TitleView->Init();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TitleViewの取得に失敗しました"));
	}
}

void UTitleWidget::ChangeButton()
{
	FVector2D cursor = TitleController->GetLeftAxis();
	if (cursor.Size() > 0.0f)
	{
		if (FMath::Abs(cursor.X) < FMath::Abs(cursor.Y))
		{
			if (cursor.Y > 0.0f)
			{
				DecrementCursor();
				
			}
			else if (cursor.Y < 0.0f)
			{
				IncrementCursor();
			}
			TitleView->MenuButtonSwitch(SelectCursor);
		}
	}

}

void UTitleWidget::HandleInputChanged()
{
	ChangeButton();
	// UE_LOG(LogTemp, Warning, TEXT("スティックの入力がありました"));
}

void UTitleWidget::IncrementCursor()
{
	SelectCursor++;
	if (SelectCursor > 5)
	{
		SelectCursor = 0;
	}
	
}

void UTitleWidget::DecrementCursor()
{
	SelectCursor--;
	if (SelectCursor < 0)
	{
		SelectCursor = 5;
	}
}
