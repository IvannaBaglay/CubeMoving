// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h" // Required for FInputActionValue
#include "CubePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class CUBEMOVING_API ACubePlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override; // PlayerController uses SetupInputComponent, not SetupPlayerInputComponent
	virtual void Tick(float DeltaTime) override;
private:
	ACubePlayerController();

	void LeftMove();
	void RightMove();
	void ForwardMove();
	void BackwardMove();
	void DiagonalBackLeftMove();
	void Moving(const FVector& Direction);
	void DiagonalMoving(const FVector& DirectionA, const FVector& DirectionB);
	
private:
	void DrawCubeVertex();
	void DrawActorCoordinates();
	void QuickDiagonalRotation(float DeltaTime);
	void CooldownkDiagonalRotation(float DeltaTime);
	void Rolling(float DeltaTime);
    void TransformRolling(float DeltaTime);

	/** Mapping Context */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Input Action for Action A */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ActionLeftMove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ActionRigthMove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ActionForwardMove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ActionBackwardMove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ActionDiagonalBackLeftMove;


	UPROPERTY(EditAnywhere)
	float RollDuration = 0.25f;
	UPROPERTY(EditAnywhere)
	float RollCooldown = 0.25f;

	bool bIsMoving = false;
	float CurrentRollTime = 0.f;
	float CurrentRollCooldown = 0.f;

	UPROPERTY(EditAnywhere)

	float TargetAngle = 360.f;

	FQuat TargetQuat;
	FVector FinalLocation;

	FVector RollPivot;
	FVector RollAxis;
	FVector StartLocation;
	FRotator StartRotation;
};
