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

	void Moving();
	
private:
	/** Mapping Context */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Input Action for Action A */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ActionA;

	UPROPERTY(EditAnywhere)
	float RollDuration = 0.25f;

	UPROPERTY(EditAnywhere)
	float CubeSize = 100.f;

	bool bIsMoving = false;
	float CurrentRollTime = 0.f;

	FVector RollPivot;
	FVector RollAxis;
	FVector StartLocation;
	FRotator StartRotation;
};
