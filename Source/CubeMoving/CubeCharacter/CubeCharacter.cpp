// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeCharacter/CubeCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACubeCharacter::ACubeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACubeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACubeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACubeCharacter::GetComponentOrientedBoundingBox(USceneComponent* Component, FVector& Origin, FVector& Extent)
{
	// Calculate the right world origin
	FVector ComponentExtent;
	float ComponentRadius;
	UKismetSystemLibrary::GetComponentBounds(Component, Origin, ComponentExtent, ComponentRadius);

	// Calculate the right extent
	auto Box = Component->GetOwner()->CalculateComponentsBoundingBoxInLocalSpace();
	Extent = Box.GetExtent();
}
