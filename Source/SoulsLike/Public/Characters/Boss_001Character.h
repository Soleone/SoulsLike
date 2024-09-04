// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Enemy.h"
#include "Boss_001Character.generated.h"

UCLASS()
class SOULSLIKE_API ABoss_001Character : public ACharacter, public IEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABoss_001Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
