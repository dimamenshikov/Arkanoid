#include "Bonuses/BonusInfinitive/BonusCannon.h"
#include "EnhancedInputComponent.h"
#include "Bonuses/SaveClasses/BonusInfinitive_S.h"
#include "Framework/ArkanoidPC.h"
#include "Framework/Paddle.h"
#include "Kismet/GameplayStatics.h"
#include "World/Cannon.h"

void ABonusCannon::Activate()
{
	for (int32 i = -1; i <= 1; i += 2)
	{
		auto Cannon = Cast<ACannon>(GetWorld()->SpawnActor<ACannon>(CannonClass));
		Cannon->AttachToComponent(Paddle->StaticMesh, FAttachmentTransformRules::KeepRelativeTransform);
		Cannon->CannonMesh->SetAbsolute(false, false, true);
		Cannon->SetActorRelativeLocation(FVector(0.f, (Paddle->GetActorScale3D().Y * 50 - 5) * i, 0.f));
		Cannons.Add(Cannon);
	}
	Cast<UEnhancedInputComponent>(Paddle->GameplayClasses->ArkanoidPC->InputComponent)->BindAction(
		Paddle->GameplayClasses->ArkanoidPC->IA_Action, ETriggerEvent::Started, this, &ABonusCannon::Shoot);
}

void ABonusCannon::DeleteBonus()
{
	for (auto& Cannon : Cannons)
	{
		Cannon->Destroy();
	}

	Super::DeleteBonus();
}

void ABonusCannon::Shoot()
{
	if (CanShoot)
	{
		UGameplayStatics::PlaySound2D(this, ShootSound);
		CanShoot = false;
		for (auto& Cannon : Cannons)
		{
			Cannon->Shoot();
		}
		--QuantityProjectile;
		if (QuantityProjectile == 0)
		{
			DeleteBonus();
		}
		auto AllowShoot = [this]()-> void
		{
			CanShoot = true;
		};
		GetWorldTimerManager().SetTimer(Timer, AllowShoot, 0.2f, false);
	}
}

void ABonusCannon::Update()
{
	QuantityProjectile = 10;
}

USaveGame* ABonusCannon::Save(USaveGame* BaseSaveObject)
{
	INIT_SAVE_OBJECT(UBonusInfinitive_S, BonusInfinitive_S);
	BonusInfinitive_S->Value = QuantityProjectile;
	return Super::Save(BonusInfinitive_S);
}

void ABonusCannon::Load(const USaveGame*& SaveGameObject)
{
	Super::Load(SaveGameObject);
	QuantityProjectile = Cast<UBonusInfinitive_S>(SaveGameObject)->Value;
}
