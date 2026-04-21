// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/MyGameInstance.h"
#include "Runtime/Slate/Public/Widgets/Layout/SDPIScaler.h" // 追加
#include "Engine/UserInterfaceSettings.h"
#include "MoviePlayer.h"

#define LOADING_SCREEN_PATH TEXT("/Game/UI/Widgets/Common/WBP_Loading.WBP_Loading_C")
#define LOADING_BACK_PATH TEXT("/Game/UI/Widgets/Title/WBP_Common_OutGame.WBP_Common_OutGame_C")

void UMyGameInstance::Init()
{
	Super::Init();

	Loading = false;
	bIsStartup = true;
    CreateWidgets(); // ウィジェットを作成
    if (BGWidget && TempWidget)
    {
        CurrentLoadingWidget = TempWidget; // ロード中のウィジェットを保持
        LoadingWidgetSlate = SNew(SOverlay)
            + SOverlay::Slot()
            .HAlign(HAlign_Fill)
            .VAlign(VAlign_Fill)
            [
                BGWidget->TakeWidget() // 背景を下に敷く
            ]
            + SOverlay::Slot()
            .HAlign(HAlign_Fill)
            .VAlign(VAlign_Fill)
            [
                TempWidget->TakeWidget() // バーを上に重ねる
            ];
        UE_LOG(LogTemp, Warning, TEXT("WBPの取得に成功しました。: %s"), LOADING_SCREEN_PATH);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("WBPの取得に失敗しました。: %s"), LOADING_SCREEN_PATH);
    }
    if (StartupWidget) {
        StartupWidgetSlate = StartupWidget->TakeWidget();
    }
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMyGameInstance::BeginLoadingScreen);
}

void UMyGameInstance::BeginLoadingScreen(const FString& MapName)
{
    float TargetScale = 1.0f;
    if (GEngine && GEngine->GameViewport)
    {
        FVector2D ViewportSize;
        GEngine->GameViewport->GetViewportSize(ViewportSize);
        // 指定した解像度におけるスケール値を計算
        TargetScale = GetDefault<UUserInterfaceSettings>()->GetDPIScaleBasedOnSize(FIntPoint(ViewportSize.X, ViewportSize.Y));
    }

    FLoadingScreenAttributes LoadingScreen;
    if(bIsStartup)
    {
        LoadingScreen.bAutoCompleteWhenLoadingCompletes = true; // 終わったらすぐタイトルへ
        LoadingScreen.MinimumLoadingScreenDisplayTime = 5.0f;   // 起動ロゴ等は少し長めに

        LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

        bIsStartup = false; 
	}else if (LoadingWidgetSlate.IsValid())
    {
        LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
        LoadingScreen.MinimumLoadingScreenDisplayTime = 6.0f;
        LoadingScreen.WidgetLoadingScreen = SNew(SDPIScaler)
            .DPIScale(TargetScale)
            [
                LoadingWidgetSlate.ToSharedRef()
            ];
		Loading = true;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ロードスレートの取得に失敗しました。"));
    }

    if(LoadingScreen.WidgetLoadingScreen.IsValid())
    {
        GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
}

void UMyGameInstance::CreateWidgets()
{

    UClass* BGClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, LOADING_BACK_PATH);
    UClass* WidgetClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, LOADING_SCREEN_PATH);
    // ↓ここをUEデフォルトの起動ロゴ等のウィジェットに変更
    UClass* StartupClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, TEXT("/Game/UI/Widgets/Common/WBP_Startup.WBP_Startup_C"));
    if (BGClass && WidgetClass)
    {
        BGWidget = CreateWidget<UUserWidget>(this, BGClass);
        TempWidget = CreateWidget<UUserWidget>(this, WidgetClass);
    }
    if(StartupClass)
    {
        StartupWidget = CreateWidget<UUserWidget>(this, StartupClass);
        if (StartupWidget) {
            StartupWidgetSlate = StartupWidget->TakeWidget();
        }
	}
}

void UMyGameInstance::Shutdown()
{
    // Slateポインタをリセットして参照カウントを正しく減らす
    if (LoadingWidgetSlate.IsValid())
    {
        LoadingWidgetSlate.Reset();
    }

    if (StartupWidgetSlate.IsValid())
    {
        StartupWidgetSlate.Reset();
    }

    Super::Shutdown();
}
