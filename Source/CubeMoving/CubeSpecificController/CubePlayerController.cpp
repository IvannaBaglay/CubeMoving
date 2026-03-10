// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeSpecificController/CubePlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Pawn.h"
#include "CubeCharacter/CubeCharacter.h"

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
        check(ActionLeftMove);
        check(ActionRigthMove);
        check(ActionForwardMove);
        check(ActionBackwardMove);
        check(ActionDiagonalBackLeftMove);

        // Bind the "Triggered" event of the Input Action
        EnhancedInputComponent->BindAction(ActionLeftMove, ETriggerEvent::Triggered, this, &ACubePlayerController::LeftMove);
        EnhancedInputComponent->BindAction(ActionRigthMove, ETriggerEvent::Triggered, this, &ACubePlayerController::RightMove);
        EnhancedInputComponent->BindAction(ActionForwardMove, ETriggerEvent::Triggered, this, &ACubePlayerController::ForwardMove);
        EnhancedInputComponent->BindAction(ActionBackwardMove, ETriggerEvent::Triggered, this, &ACubePlayerController::BackwardMove);
        EnhancedInputComponent->BindAction(ActionDiagonalBackLeftMove, ETriggerEvent::Triggered, this, &ACubePlayerController::DiagonalBackLeftMove);
    }
}
UE_DISABLE_OPTIMIZATION

void ACubePlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    APawn* ControlledPawn = GetPawn();
    if (!ControlledPawn)
        return;

    if (!bIsMoving)
            return;


    // Check if position in 90 degree angle is reached
    // Looks like it works ok if I do it in one step
    // Then issue can be in interpolation
    FQuat DeltaQuat = FQuat(RollAxis, FMath::DegreesToRadians(90.f));
    FQuat NewRotation = DeltaQuat * StartRotation.Quaternion();

    FVector Offset = StartLocation - RollPivot;
    FVector RotatedOffset = Offset.RotateAngleAxis(90.f, RollAxis); /*rotating around start vector point(in my case pivot)*/

    // Zero location
    DrawDebugLine(GetWorld(), FVector::ZeroVector, Offset, FColor::Yellow, false, 0.01f, 1, 2.f);
    DrawDebugLine(GetWorld(), FVector::ZeroVector, RotatedOffset, FColor::Orange, false, 0.01f, 1, 2.f);



    FVector NewLocation = RollPivot + RotatedOffset;

    FTransform NewTransform;
    NewTransform.SetLocation(NewLocation);
    NewTransform.SetRotation(NewRotation);

    ControlledPawn->SetActorTransform(NewTransform);

    //
    DrawCubeVertex();

    const FVector ActorLocation = ControlledPawn->GetActorLocation();
    const FVector ActorForwardVector = ControlledPawn->GetActorForwardVector();
    const FVector ActorRightVector = ControlledPawn->GetActorRightVector();
    const FVector ActorUpVector = ControlledPawn->GetActorUpVector();

    //const UWorld* InWorld, FVector const& LineStart, FVector const& LineEnd, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f
    // Global Actor vectors 
    DrawDebugLine(GetWorld(), ActorLocation, ActorLocation + 100 * ActorForwardVector, FColor::Red, false, 0.01f, 0, 2.f);
    DrawDebugLine(GetWorld(), ActorLocation, ActorLocation + 100 * ActorRightVector, FColor::Green, false, 0.01f, 0, 2.f);
    DrawDebugLine(GetWorld(), ActorLocation, ActorLocation + 100 * ActorUpVector, FColor::Blue, false, 0.01f, 0, 2.f);

    // RollAxis
    DrawDebugLine(GetWorld(), ActorLocation, ActorLocation + 100 * RollAxis, FColor::Cyan, false, 0.01f, 1, /*Thickness*/ 2.f);
    //RollPivot
    DrawDebugPoint(GetWorld(), RollPivot, /*Size*/ 5.f, FColor::Cyan, false, 5.f, 1);

    //bIsMoving = false;

    //if (!bIsMoving)
    //    return;
    //
    //
    //CurrentRollTime = FMath::Min(CurrentRollTime + DeltaTime, RollDuration);;
    //
    //float Alpha = CurrentRollTime / RollDuration;
    //float Angle = 90.f * Alpha;
    //
    //// Debug info
    //const FString AlphaString = FString::Printf(TEXT("Alpha: %f"), Alpha);
    //UE_LOG(LogTemp, Warning, TEXT("Alpha: %f"), Alpha);
    //const FString AngleString = FString::Printf(TEXT("Angle: %f"), Angle);
    //UE_LOG(LogTemp, Warning, TEXT("Angle: %f"), Angle);
    //DrawDebugString(GetWorld(), ActorLocation, *AlphaString, nullptr, FColor::Cyan, 0.01f, false, 2.f);
    //DrawDebugString(GetWorld(), ActorLocation + FVector::UpVector * 20, *AngleString, nullptr, FColor::Cyan, 0.01f, false, 2.f);
    ////
    //
    //// Get a vector which will be rotating
    //FVector Offset = StartLocation - RollPivot; /*vector in pivot start and direction to start location(cube center). Vector direction is important*/ 
    //DrawDebugLine(GetWorld(), StartLocation, RollPivot, FColor::Yellow, false, 0.01f, 1, 2.f);
    //
    //
    //
    //FVector RotatedOffset = Offset.RotateAngleAxis(Angle, RollAxis); /*rotating around start vector point(in my case pivot)*/
    //
    //// Zero location
    //DrawDebugLine(GetWorld(), FVector::ZeroVector, Offset, FColor::Yellow, false, 0.01f, 1, 2.f);
    //DrawDebugLine(GetWorld(), FVector::ZeroVector, RotatedOffset, FColor::Orange, false, 0.01f, 1, 2.f);
    //
    //
    //
    //FVector NewLocation = RollPivot + RotatedOffset;
    //
    //DrawDebugLine(GetWorld(), RollPivot, RollPivot + RotatedOffset, FColor::Orange, false, 0.01f, 1, 2.f);
    //
    //DrawDebugPoint(GetWorld(), NewLocation, /*Size*/ 25.f, FColor::Orange, false, 0.01f, 2);
    //
    //FQuat DeltaQuat = FQuat(RollAxis, FMath::DegreesToRadians(Angle));
    //FQuat NewRotation = DeltaQuat * StartRotation.Quaternion();
    //
    //
    //FTransform NewTransform;
    //NewTransform.SetLocation(NewLocation);
    //NewTransform.SetRotation(NewRotation);
    //
    //ControlledPawn->SetActorTransform(NewTransform);
    //
    ////ControlledPawn->SetActorLocation(NewLocation);
    ////ControlledPawn->SetActorRotation(NewRotation);
    //
    //if (FMath::IsNearlyZero((Alpha - 1.f), UE_SMALL_NUMBER))
    //{
    //    bIsMoving = false;
    //
    //    //DeltaQuat = FQuat(RollAxis, FMath::DegreesToRadians(90.f));
    //    //NewRotation = DeltaQuat * StartRotation.Quaternion();
    //    //ControlledPawn->SetActorRotation(NewRotation);
    //}
}

ACubePlayerController::ACubePlayerController()
{
    bIsMoving = false;
}

void ACubePlayerController::LeftMove()
{
    FVector Direction = FVector::LeftVector;
    Moving(Direction);
}

void ACubePlayerController::RightMove()
{
    FVector Direction = FVector::RightVector;
    Moving(Direction);
}

void ACubePlayerController::ForwardMove()
{
    FVector Direction = FVector::ForwardVector;
    Moving(Direction);
}

void ACubePlayerController::BackwardMove()
{
    FVector Direction = FVector::BackwardVector;
    Moving(Direction);
}

void ACubePlayerController::DiagonalBackLeftMove()
{
    DiagonalMoving(FVector::BackwardVector, FVector::LeftVector);
}

void ACubePlayerController::Moving(const FVector& Direction)
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


    RollAxis = FVector::CrossProduct(FVector::UpVector, Direction).GetSafeNormal();


    // Get Real Actor Size
    
    AActor* Actor = GetPawn();
    ACubeCharacter* CubeCharacter = CastChecked<ACubeCharacter>(Actor);

    FVector ActorCubeSize;
    FVector OriginLocation;

    CubeCharacter->GetComponentOrientedBoundingBox(OriginLocation, ActorCubeSize); // Actor cube size from bound is a half of full size

    // Botton Middle point
    RollPivot = StartLocation
        + (Direction * ActorCubeSize)
        - (FVector::UpVector * ActorCubeSize);
}

void ACubePlayerController::DiagonalMoving(const FVector& DirectionA, const FVector& DirectionB)
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

    FVector Direction = (DirectionA + DirectionB).GetSafeNormal();

    RollAxis = FVector::CrossProduct(FVector::UpVector, Direction).GetSafeNormal();;


    // Get Real Actor Size

    AActor* Actor = GetPawn();
    ACubeCharacter* CubeCharacter = CastChecked<ACubeCharacter>(Actor);

    FVector ActorCubeSize;
    FVector OriginLocation;

    CubeCharacter->GetComponentOrientedBoundingBox(OriginLocation, ActorCubeSize); // Actor cube size from bound is a half of full size

    // Botton Middle point
    RollPivot =
        StartLocation
        + DirectionA * ActorCubeSize
        + DirectionB * ActorCubeSize
        - FVector::UpVector * ActorCubeSize;
}

void ACubePlayerController::DrawCubeVertex()
{
    AActor* Actor = GetPawn();
    ACubeCharacter* CubeCharacter = CastChecked<ACubeCharacter>(Actor);

    FVector ActorCubeSize;
    FVector OriginLocation;

    CubeCharacter->GetComponentOrientedBoundingBox(OriginLocation, ActorCubeSize); // Actor cube size from bound is a half of full size

    FVector PivotBottonLeft = OriginLocation + (-FVector::UpVector * ActorCubeSize) + FVector::LeftVector * ActorCubeSize + FVector::BackwardVector * ActorCubeSize;


    DrawDebugPoint(GetWorld(), PivotBottonLeft, /*Size*/ 5.f, FColor::Black, false, 0.01f, 1);

    DrawDebugLine(GetWorld(), OriginLocation, PivotBottonLeft, FColor::Black, false, 0.01f, 1, 2.f);


}

UE_ENABLE_OPTIMIZATION
