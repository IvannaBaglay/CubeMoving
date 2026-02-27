// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeSpecificController/CubePlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Pawn.h"

#include "InputActionValue.h"

void ACubePlayerController::BeginPlay()
{
    Super::BeginPlay();
}

void ACubePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Add Input Mapping Context
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }

    // Cast the default InputComponent to EnhancedInputComponent
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        // Bind the Action A input to the C++ function HandleActionA
        if (ActionA)
        {
            // Bind the "Triggered" event of the Input Action
            EnhancedInputComponent->BindAction(ActionA, ETriggerEvent::Triggered, this, &ACubePlayerController::Moving);
        }
    }
}
UE_DISABLE_OPTIMIZATION

void ACubePlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bIsMoving)
        return;

    APawn* ControlledPawn = GetPawn();
    if (!ControlledPawn)
        return;

    CurrentRollTime += DeltaTime;

    float Alpha = FMath::Clamp(CurrentRollTime / RollDuration, 0.f, 1.f);
    float Angle = 90.f * Alpha;

    FVector Offset = StartLocation - RollPivot;
    FVector RotatedOffset = Offset.RotateAngleAxis(Angle, RollAxis);

    FVector NewLocation = RollPivot + RotatedOffset;

    FQuat DeltaQuat = FQuat(RollAxis, FMath::DegreesToRadians(Angle));
    FQuat NewRotation = DeltaQuat * StartRotation.Quaternion();


    ControlledPawn->SetActorLocation(NewLocation);
    ControlledPawn->SetActorRotation(NewRotation);

    if (Alpha >= 1.f)
    {
        bIsMoving = false;
    }
}

ACubePlayerController::ACubePlayerController()
{
    bIsMoving = false;
}


void ACubePlayerController::Moving()
{
    if (bIsMoving)
    {
        return;
    }

    APawn* ControlledPawn = GetPawn();
    if (!ControlledPawn)
        return;

    bIsMoving = true;
    CurrentRollTime = 0.f;

    StartLocation = ControlledPawn->GetActorLocation();
    StartRotation = ControlledPawn->GetActorRotation();

    FVector Direction = FVector::LeftVector;

    RollAxis = FVector::CrossProduct(FVector::UpVector, Direction);

    RollPivot = StartLocation
        + (Direction * CubeSize * 0.5f)
        - (FVector::UpVector * CubeSize * 0.5f);
}

UE_ENABLE_OPTIMIZATION
