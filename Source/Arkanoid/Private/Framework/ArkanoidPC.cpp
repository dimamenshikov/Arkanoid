#include "Framework/ArkanoidPC.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Framework/ArkanoidGameplayClasses.h"
#include "Framework/ArkanoidGM.h"
#include "Framework/Paddle.h"
#include "Kismet/KismetMathLibrary.h"
#include "World/Ball.h"

void AArkanoidPC::BeginPlay()
{
	Super::BeginPlay();

	GameplayClasses->ArkanoidPC = this;

	ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())->AddMappingContext(Management, 0);
}

void AArkanoidPC::LevelLoad()
{
	Paddle = GameplayClasses->ArkanoidP;
}

void AArkanoidPC::StartGame()
{
	const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(IA_StartMove, ETriggerEvent::Started, this, &AArkanoidPC::StartMove);
	EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AArkanoidPC::Move);
	EnhancedInputComponent->BindAction(IA_Pause, ETriggerEvent::Started, this, &AArkanoidPC::PauseGame);
}

void AArkanoidPC::Move(const FInputActionValue& Value)
{
	FVector VectorMove = FVector(Value.Get<FVector2D>().Y, Value.Get<FVector2D>().X, 0.0f);

	VectorMove = UKismetMathLibrary::Quat_RotateVector(FQuat(FRotator(0.0f, Paddle->CameraRotationYaw, 0.0f)),
	                                                   VectorMove);

	Paddle->AddActorLocalOffset(
		FVector(0.0f, Paddle->PaddleSpeed * FVector::DotProduct(VectorMove, Paddle->GetActorRightVector()), 0.0f),
		true);
}

void AArkanoidPC::PauseGame()
{
	GameplayClasses->ArkanoidGM->SetGamePause();
}

void AArkanoidPC::StartMove()
{
	Paddle->SpawnBall();
	if (Paddle->CurrentBall && Paddle->CurrentBall->bMovement == false)
	{
		Paddle->CurrentBall->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Paddle->CurrentBall->ActiveMove(true);
	}
	else
	{
		OnStartMove.Broadcast();
	}
}
