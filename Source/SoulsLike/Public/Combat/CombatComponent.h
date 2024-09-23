// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

UENUM(BlueprintType)
enum class EAttackState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Windup UMETA(DisplayName = "Windup"),
	Active UMETA(DisplayName = "Active"),
	Recovering UMETA(DisplayName = "Recovering")
};

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnAttackPerformedSignature,
	UCombatComponent, OnAttackPerformedDelegate,
	float, Amount
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOULSLIKE_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> AttackAnimations;

	ACharacter* Character;

	UPROPERTY(VisibleAnywhere)
	int ComboCounter{ 0 };
	
	UPROPERTY(EditAnywhere)
	float StamiaCost{ 5.0f };
public:	
	// Sets default values for this component's properties
	UCombatComponent();

	UPROPERTY(BlueprintAssignable)
	FOnAttackPerformedSignature OnAttackPerformedDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere)
	EAttackState AttackState{ EAttackState::Idle };

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ComboAttack();
	
	UFUNCTION(BlueprintCallable)
	void SetAttackState(EAttackState NewState);
};
