#include "World/Projectile.h"
#include "Components/LifeBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "World/Block.h"

AProjectile::AProjectile()
{
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	SetRootComponent(ProjectileMesh);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(Timer, this, &AProjectile::Move, GetWorld()->DeltaTimeSeconds, true);
}

void AProjectile::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
                            bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
                            const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (auto Block = Cast<ABlock>(Other))
	{
		Block->LifeComponent->Damage(Power);
		if (!Block->LifeComponent->IsAlive())
		{
			Block->Exterminate();
		}
		else
		{
			const float Alpha = static_cast<float>(Block->LifeComponent->GetLife() - 1) /
				(Block->LifeComponent->MaxLife - 1);
			Block->Material->SetVectorParameterValue(
				"Color", UKismetMathLibrary::LinearColorLerp(FLinearColor::Red, FLinearColor::Green, Alpha));
		}
	}
	Destroy();
}

void AProjectile::Move()
{
	AddActorLocalOffset(FVector(Speed * GetWorld()->DeltaTimeSeconds, 1.f, 1.f), true);
}
