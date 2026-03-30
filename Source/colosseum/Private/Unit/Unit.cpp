// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/Unit.h"
#include "Battle/BattleGameMode.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Unit/UnitTankAnimInstance.h"

#define FACE_MATERIAL_INDEX 1 //  顔のマテリアルインデックス
#define TANK_MODEL_PLAYER1    TEXT("/Game/Unit/tank/Charactor/BP_UnitTank1.BP_UnitTank1_C") //  タンクプレーヤー１
#define TANK_MODEL_PLAYER2    TEXT("/Game/Unit/tank/Charactor/BP_UnitTank2.BP_UnitTank2_C") //  タンクプレーヤー２
#define HEALER_MODEL_PLAYER1  TEXT("/Game/Unit/healer/Charactor/BP_UnitHealer1.BP_UnitHealer1_C") //  ヒーラープレーヤー１
#define HEALER_MODEL_PLAYER2  TEXT("/Game/Unit/healer/Charactor/BP_UnitHealer2.BP_UnitHealer2_C") //  ヒーラープレーヤー２
#define ROUNDER_MODEL_PLAYER1   TEXT("/Game/Unit/rounder/Charactor/BP_Rounder_P1.BP_Rounder_P1_C") //  ラウンダープレーヤー１
#define ROUNDER_MODEL_PLAYER2   TEXT("/Game/Unit/rounder/Charactor/BP_Rounder_P2.BP_Rounder_P2_C") //  ラウンダープレーヤー２
#define MAGITION_MODEL_PLAYER1    TEXT("/Game/Unit/mazishan/Charactor/BP_Mazishan_P1.BP_Mazishan_P1_C") //  マジシャンプレーヤー１
#define MAGITION_MODEL_PLAYER2    TEXT("/Game/Unit/mazishan/Charactor/BP_Mazishan_P2.BP_Mazishan_P2_C") //  マジシャンプレーヤー２


#define FACE_U_ID   TEXT("FaceU")
#define FACE_V_ID   TEXT("FaceV")


// Sets default values
AUnit::AUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
#if 1
    USkeletalMeshComponent* scene = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UnitScene"));
    if (scene)
    {
        RootComponent = scene;
    }
#else
    UnitMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UnitMesh"));
    if (UnitMesh)
    {
        RootComponent = UnitMesh; // メッシュコンポーネントをルートコンポーネントに設定
    }
#endif

}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//  ユニットデータの設定
void AUnit::SetUnitData(const FUnitData& UnitData)
{
    // ユニットデータを設定
    UnitBaseData = UnitData;
}


void AUnit::CreateUnitData()
{
    FSoftObjectPath SkeletalMeshPath;
    bool AnimeSetup = false;

    switch (UnitBaseData.Job)
    {
    case EUnitJob::EUJ_Tank:    // タンク
    default:
        
        if (UnitBaseData.TeamID == EUnitTeamID::EUTID_Team1)
        {
            SkeletalMeshPath = FSoftObjectPath(TANK_MODEL_PLAYER1);
        }
        else
        {
            SkeletalMeshPath = FSoftObjectPath(TANK_MODEL_PLAYER2);
        }

        AnimeSetup = true;

        {
            TSubclassOf<class AUnitModel> CharBP = TSoftClassPtr<class AUnitModel >(SkeletalMeshPath).LoadSynchronous();
            if (CharBP)
            {
                UnitModel = GetWorld()->SpawnActor<AUnitModel>(CharBP);
                if (UnitModel)
                {
                    UnitModel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

                    UnitModel->SetMasterUnit(this);

                    UnitMesh = Cast<USkeletalMeshComponent>(UnitModel->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

                    UnitAnimInstanceObject = Cast<UUnitAnimInstance>(UnitMesh->GetAnimInstance());
                }
            }
        }
        break;
    case EUnitJob::EUJ_Rounder: // ラウンダー
        if (UnitBaseData.TeamID == EUnitTeamID::EUTID_Team1)
        {
            SkeletalMeshPath = FSoftObjectPath(ROUNDER_MODEL_PLAYER1);
        }
        else
        {
            SkeletalMeshPath = FSoftObjectPath(ROUNDER_MODEL_PLAYER2);
        }
        {
            TSubclassOf<class AUnitModel> CharBP = TSoftClassPtr<class AUnitModel >(SkeletalMeshPath).LoadSynchronous();
            if (CharBP)
            {
                UnitModel = GetWorld()->SpawnActor<AUnitModel>(CharBP);
                if (UnitModel)
                {
                    UnitModel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

                    UnitModel->SetMasterUnit(this);

                    UnitMesh = Cast<USkeletalMeshComponent>(UnitModel->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

                    UnitAnimInstanceObject = Cast<UUnitAnimInstance>(UnitMesh->GetAnimInstance());
                    FaceMaterialInstance = UnitMesh->CreateAndSetMaterialInstanceDynamic(FACE_MATERIAL_INDEX);
                    ChangeUnitFace(EUnitFace::EUF_Normal);
                }
            }
        }

        break;
    case EUnitJob::EUJ_Healer:  // ヒーラー
        if (UnitBaseData.TeamID == EUnitTeamID::EUTID_Team1)
        {
            SkeletalMeshPath = FSoftObjectPath(HEALER_MODEL_PLAYER1);
        }
        else
        {
            SkeletalMeshPath = FSoftObjectPath(HEALER_MODEL_PLAYER2);
        }
        {
            TSubclassOf<class AUnitModel> CharBP = TSoftClassPtr<class AUnitModel >(SkeletalMeshPath).LoadSynchronous();
            if (CharBP)
            {
                UnitModel = GetWorld()->SpawnActor<AUnitModel>(CharBP);
                if (UnitModel)
                {
                    UnitModel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

                    UnitModel->SetMasterUnit(this);

                    UnitMesh = Cast<USkeletalMeshComponent>(UnitModel->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

                    UnitAnimInstanceObject = Cast<UUnitAnimInstance>(UnitMesh->GetAnimInstance());
                    FaceMaterialInstance = UnitMesh->CreateAndSetMaterialInstanceDynamic(FACE_MATERIAL_INDEX);
                    ChangeUnitFace(EUnitFace::EUF_Normal);
                }
            }
        }


        break;
    case EUnitJob::EUJ_Magician:    // マジシャン
        if (UnitBaseData.TeamID == EUnitTeamID::EUTID_Team1)
        {
            SkeletalMeshPath = FSoftObjectPath(MAGITION_MODEL_PLAYER1);
        }
        else
        {
            SkeletalMeshPath = FSoftObjectPath(MAGITION_MODEL_PLAYER2);
        }
        {
            TSubclassOf<class AUnitModel> CharBP = TSoftClassPtr<class AUnitModel >(SkeletalMeshPath).LoadSynchronous();
            if (CharBP)
            {
                UnitModel = GetWorld()->SpawnActor<AUnitModel>(CharBP);
                if (UnitModel)
                {
                    UnitModel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

                    UnitModel->SetMasterUnit(this);

                    UnitMesh = Cast<USkeletalMeshComponent>(UnitModel->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

                    UnitAnimInstanceObject = Cast<UUnitAnimInstance>(UnitMesh->GetAnimInstance());
                    FaceMaterialInstance = UnitMesh->CreateAndSetMaterialInstanceDynamic(FACE_MATERIAL_INDEX);
                    ChangeUnitFace(EUnitFace::EUF_Normal);
                }
            }
        }
        
        break;
    }

    USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(SkeletalMeshPath.TryLoad());
    if (SkeletalMesh)
    {
        UnitMesh->SetSkeletalMesh(SkeletalMesh); // メッシュを設定
        UnitMesh->SetVisibility(true);
        if (AnimeSetup)
        {
            // アニメーションブループリントの設定

            //  テストで書かれているので、ちょっと考える
            FSoftObjectPath Path(TEXT("/Game/Unit/tank/Animation/AnimationBlueprints/ABP_Tank.ABP_Tank_C"));

            TSubclassOf<class UUnitTankAnimInstance> AnimBPClass = TSoftClassPtr<class UUnitTankAnimInstance > (Path).LoadSynchronous();
            if (AnimBPClass)
            {
                UnitAnimInstanceObject = Cast<UUnitAnimInstance>(AnimBPClass->GetDefaultObject());
                UnitMesh->SetAnimInstanceClass(AnimBPClass);

                UnitMesh->bEnableAnimation = true; // アニメーションを有効にする
                UnitMesh->SetSimulatePhysics(true);
                UnitAnimInstanceObject->PlayAnimationWait();
            }
        }
        UnitMesh->SetSimulatePhysics(true);
        UnitMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load SkeletalMesh!"));
    }
}


//  ユニットデータの取得
FUnitData& AUnit::GetUnitData()
{
    // ユニットデータを返す
    return UnitBaseData;
}


void AUnit::Set3DScale(const FVector& scale)
{
    UnitMesh->SetRelativeScale3D(scale);
}

// 回転設定
void AUnit::Set3DRotation(const FRotator& rotation)
{
    UnitMesh->SetRelativeRotation(rotation);
}

// 回転取得
FRotator AUnit::Get3DRotation() const
{
    return UnitMesh->GetRelativeRotation();
}

// クォータニオン取得
FQuat AUnit::GetQuaternion() const
{
    return UnitMesh->GetRelativeRotation().Quaternion();
}

//  クォータニオン設定
void AUnit::SetQuaternion(const FQuat& quat)
{
    UnitMesh->SetRelativeRotation(quat);
}



void AUnit::Set3DLocation(const FVector& location)
{
    UnitMesh->SetRelativeLocation(location);
}

FVector AUnit::Get3DLocation() const
{
    return UnitMesh->GetRelativeLocation();
}



void AUnit::SetVisible(bool flag)
{
    UnitMesh->SetVisibility(flag);
}


bool AUnit::IsVisible() const
{ 
    return UnitMesh->IsVisible();
}


void AUnit::PlayAnimationWait(float ShiftTime)
{
    if (UnitAnimInstanceObject)
    {
        UnitAnimInstanceObject->PlayAnimationWait(ShiftTime);
    }
}
void AUnit::PlayAnimationMove(float ShiftTime)
{
    if (UnitAnimInstanceObject)
    {
        UnitAnimInstanceObject->PlayAnimationMove(ShiftTime);
    }
}
void AUnit::PlayAnimationAttack(float ShiftTime )
{
    if (UnitModel)
    {
        UnitModel->OnAttackRunEvent();
    }
}


void AUnit::PlayAnimationDamage(float ShiftTime)
{
    if (UnitModel)
    {
        UnitModel->OnDamageRunEvent();
    }
}


void AUnit::PlayAnimationDeath(float ShiftTime)
{
    if (UnitModel)
    {
        UnitModel->OnDownRunEvent();

    }
}

void AUnit::PlayAnimationGuard(float ShiftTime)
{
    if (UnitAnimInstanceObject)
    {
        UnitAnimInstanceObject->PlayAnimationGuard(ShiftTime);
    }
}

void AUnit::PlayAnimationSkillAttack(float ShiftTime)
{
    if (UnitModel)
    {
        UnitModel->OnSkillAttackRunEvent    ();
    }
}

void AUnit::PlayAnimationBuf(float ShiftTime)
{
    if (UnitModel)
    {
        UnitModel->OnBufRunEvent();
    }
}





bool AUnit::IsEndOfAnime() const
{
    if (UnitModel) {
        return UnitModel->IsEndOfAnime();
    }
    return true;
}


void AUnit::ChangeUnitFace(EUnitFace FaceID)
{
    if (FaceMaterialInstance)
    {
        //  表情に応じたテクスチャを設定
        FVector2D   uv = FVector2D::ZeroVector;
        UTexture* FaceTexture = nullptr;
        switch (FaceID)
        {
        case EUnitFace::EUF_Normal:
        default:
            uv = FVector2D::ZeroVector;
            break;
        }

        FaceMaterialInstance->SetScalarParameterValue(FACE_U_ID, uv.X);
        FaceMaterialInstance->SetScalarParameterValue(FACE_V_ID, uv.Y);

    }
}