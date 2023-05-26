// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UECharacterMovementComponent.h"
#include "Player/UEBaSECharacter.h"

float UUECharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const AUEBaSECharacter* Player = Cast<AUEBaSECharacter>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier: MaxSpeed;
}