// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TraceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOULSLIKE_API UTraceComponent : public UActorComponent
{
	GENERATED_BODY()

	class USkeletalMeshComponent* SkeletalComp;

	UPROPERTY(EditAnywhere)
	FName StartSocketName;

	UPROPERTY(EditAnywhere)
	FName EndSocketName;

	UPROPERTY(EditAnywhere)
	FName SocketRotation;

	UPROPERTY(EditAnywhere)
	float WeaponWidth{ 30.f };

	UPROPERTY(EditAnywhere)
	float WeaponHeight{ 30.f };
public:	
	// Sets default values for this component's properties
	UTraceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
