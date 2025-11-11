#include "World/Cannon.h"
#include "World/Projectile.h"

ACannon::ACannon()
{
	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon"));
	SetRootComponent(CannonMesh);
	ShootPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnProjectile"));
	ShootPoint->SetupAttachment(CannonMesh);
}

void ACannon::Shoot()
{
	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ShootPoint->GetComponentTransform());
}
