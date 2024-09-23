// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "Combat/CombatComponent.h"
#include "Interfaces/MainPlayer.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Character = GetOwner<ACharacter>();
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::ComboAttack()
{
	if (Character->Implements<UMainPlayer>())
	{
		IMainPlayer* MainPlayer = Cast<IMainPlayer>(Character);
		if (MainPlayer && !MainPlayer->HasEnoughStamina(StaminaCost))
		{
			return;
		}
	}

	if (AttackState == EAttackState::Windup || AttackState == EAttackState::Active)
	{
		return;
	}

	Character->PlayAnimMontage(AttackAnimations[ComboCounter]);
	
	ComboCounter = UKismetMathLibrary::Wrap(++ComboCounter, -1, AttackAnimations.Num() - 1);

	OnAttackPerformedDelegate.Broadcast(StaminaCost);
}

void UCombatComponent::SetAttackState(EAttackState NewState)
{
	AttackState = NewState;
}

