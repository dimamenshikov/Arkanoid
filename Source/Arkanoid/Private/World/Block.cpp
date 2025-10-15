#include "Arkanoid/Public/World/Block.h"
#include "Arkanoid/Public/Bonuses/Bonus.h"
#include "Arkanoid/Public/Components/LifeBlock.h"
#include "Arkanoid/Public/Framework/ArkanoidPS.h"
#include "Arkanoid/Public/World/Ball.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

//					Parent:

ABlock::ABlock()
{
	PrimaryActorTick.bCanEverTick = false;

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

//					Gameplay:

void ABlock::Exterminate()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EffectDestroy, GetActorTransform());
	UGameplayStatics::PlaySound2D(this, SoundDestroy);

	if (const auto World = GetWorld(); BonusClass && World)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		World->SpawnActor<ABonus>(BonusClass, GetActorLocation(), GetActorRotation());
	}

	if (const auto Pawn = Cast<APawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		Cast<AArkanoidPS>(Pawn->GetPlayerState())->ChangePlayerScore(Score);
	}
	Destroy();
}
