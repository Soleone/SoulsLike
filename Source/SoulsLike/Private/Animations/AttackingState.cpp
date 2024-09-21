// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/AttackingState.h"
#include "Combat/TraceComponent.h"

void UAttackingState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	UTraceComponent* TraceComp{ MeshComp->GetOwner()->FindComponentByClass<UTraceComponent>() };

	if (!IsValid(TraceComp)) { return; }

	TraceComp->bIsAttacking = true;
}

void UAttackingState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UTraceComponent* TraceComp{ MeshComp->GetOwner()->FindComponentByClass<UTraceComponent>() };

	if (!IsValid(TraceComp)) { return; }

	TraceComp->bIsAttacking = false;
}
