#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LifeBlock.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARKANOID_API ULifeBlock : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE bool IsAlive() const { return Life > 0; }
	FORCEINLINE int32 GetLife() const { return Life; }
	void Damage(const int32 Damage = 1);
	void SetLife(int32 NewLife);
	
	UPROPERTY(EditDefaultsOnly)	int32 MaxLife = 0;
	UPROPERTY(EditDefaultsOnly)	int32 Life = 0;
};
