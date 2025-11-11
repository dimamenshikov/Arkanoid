#include "Arkanoid/Public/World/Block.h"
#include "Arkanoid/Public/Bonuses/Bonus.h"
#include "Arkanoid/Public/Components/LifeBlock.h"
#include "Arkanoid/Public/Framework/ArkanoidPS.h"
#include "Arkanoid/Public/World/Ball.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SaveClasses/LifeBlock_S.h"

ABlock::ABlock()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block"));
	SetRootComponent(StaticMesh);

	LifeComponent = CreateDefaultSubobject<ULifeBlock>(TEXT("Lives"));
}

void ABlock::BeginPlay()
{
	Super::BeginPlay();

	Material = StaticMesh->CreateDynamicMaterialInstance(0);
	const float Alpha = static_cast<float>(LifeComponent->GetLife() - 1) / (LifeComponent->MaxLife - 1);
	Material->SetVectorParameterValue(
		"Color", UKismetMathLibrary::LinearColorLerp(FLinearColor::Red, FLinearColor::Green, Alpha));
}

void ABlock::Interaction(ABall* Ball, const FHitResult& HitResult)
{
	if (Ball && LifeComponent)
	{
		LifeComponent->Damage(Ball->Power);
		if (!LifeComponent->IsAlive())
		{
			Exterminate();
		}
		else
		{
			const float Alpha = static_cast<float>(LifeComponent->GetLife() - 1) / (LifeComponent->MaxLife - 1);
			Material->SetVectorParameterValue(
				"Color", UKismetMathLibrary::LinearColorLerp(FLinearColor::Red, FLinearColor::Green, Alpha));
		}
	}
}

void ABlock::Exterminate()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EffectDestroy, GetActorTransform());
	UGameplayStatics::PlaySound2D(this, SoundDestroy);

	if (const auto World = GetWorld(); BonusClass && World)
	{
		World->SpawnActor<ABonus>(BonusClass, GetActorLocation(), FRotator::ZeroRotator);
	}

	if (const auto Pawn = Cast<APawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		Cast<AArkanoidPS>(Pawn->GetPlayerState())->ChangePlayerScore(Score);
	}
	Destroy();
}

USaveGame* ABlock::Save(USaveGame* BaseSaveObject)
{
	INIT_SAVE_OBJECT(ULifeBlock_S, LifeBlock_S);
	SET_VAL_2(LifeBlock_S, BonusClass, Score, SAVE);
	LifeBlock_S->Life = LifeComponent->Life;
	LifeBlock_S->MaxLife = LifeComponent->MaxLife;
	return ISaveAndLoadGame::Save(LifeBlock_S);
}

void ABlock::Load(const USaveGame*& SaveGameObject)
{
	ISaveAndLoadGame::Load(SaveGameObject);
	auto LifeBlock_S = Cast<ULifeBlock_S>(SaveGameObject);
	SET_VAL_2(LifeBlock_S, BonusClass, Score, LOAD);
	LifeComponent->Life = LifeBlock_S->Life;
	LifeComponent->MaxLife = LifeBlock_S->MaxLife;
	const float Alpha = static_cast<float>(LifeComponent->GetLife() - 1) / (LifeComponent->MaxLife - 1);
	Material->SetVectorParameterValue(
		"Color", UKismetMathLibrary::LinearColorLerp(FLinearColor::Red, FLinearColor::Green, Alpha));
}
