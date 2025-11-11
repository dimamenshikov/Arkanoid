#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusTemporary.h"
#include "BonusShuriken.generated.h"

class ABall;

UCLASS(Abstract)
class ARKANOID_API ABonusShuriken : public ABonusTemporary
{
	GENERATED_BODY()

protected:
	UFUNCTION()	void Shuriken(const FHitResult& Hit);

	virtual void Activate() override;
	virtual void DeleteBonus() override;
	
	virtual USaveGame* Save(USaveGame* BaseSaveObject = nullptr) override;
	virtual void FindReferences(const USaveGame*& SaveGameObject, const TMap<FString, AActor*>& ExistActors) override;
	virtual void Load(const USaveGame*& SaveGameObject) override;
	
private:
	UStaticMesh* OldStaticMesh = nullptr;
	UMaterialInterface* OldMaterial = nullptr;
	FVector OldScale;
};
