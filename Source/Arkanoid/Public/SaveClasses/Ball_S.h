#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Ball_S.generated.h"

UCLASS()
class ARKANOID_API UBall_S : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()	FVector Scale = FVector::OneVector;
	UPROPERTY() FString AttachOwner = " ";
	UPROPERTY()	bool bMovement = false;
	UPROPERTY()	float Speed = 0.0f;
	UPROPERTY()	int32 Power = 0.0f;
	UPROPERTY()	FVector NextDirection;
	UPROPERTY()	FVector PreviousLocation;
	UPROPERTY()	FVector CurrentDirection;
	UPROPERTY()	FVector NextLocation;
	UPROPERTY()	UStaticMesh* StaticMesh;
	UPROPERTY()	UMaterialInterface* Material;
};
