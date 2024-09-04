// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Boss_001Character.h"

// Sets default values
ABoss_001Character::ABoss_001Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoss_001Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoss_001Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoss_001Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

