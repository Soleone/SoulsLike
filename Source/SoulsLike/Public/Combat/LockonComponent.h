// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockonComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOULSLIKE_API ULockonComponent : public UActorComponent
{
	GENERATED_BODY()

	ACharacter* OwnerRef;

	APlayerController* Controller;

	class UCharacterMovementComponent* MovementComp;

	class USpringArmComponent* SpringArmComp;

	FVector PlayerLocation;
	
	FVector TargetLocation;

	void StartLockon(float Radius = 750.f);

	void EndLockon();

	void UpdateLockonRotation();

	bool HandleLockonBreak();

public:	
	// Sets default values for this component's properties
	ULockonComponent();

	AActor* CurrentTargetActor;

	UPROPERTY(EditAnywhere)
	double BreakDistance{ 1000.f };

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ToggleLockon(float Radius = 750.f);
};
