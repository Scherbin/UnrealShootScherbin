// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/MyAnimInstance.h"
#include "Player/UEBaSECharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimInstance::ApdateAnimationProperties(float DeltaTime)
{
	if (BaseCharacter == nullptr)
	{
		BaseCharacter = Cast<AUEBaSECharacter>(TryGetPawnOwner());
	}
	if (BaseCharacter)
	{
		//get yhe speed of the character from velocity
		FVector Velocity{ BaseCharacter->GetVelocity() };
		Velocity.Z = 0;
		Speed = Velocity.Size();

		//is the character in the air?
		IsInAir = BaseCharacter->GetCharacterMovement()->IsFalling();

		//is the character accelerating?
		if (BaseCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.0f)
		{
			IsAccelerating = true;
		}
		else
		{
			IsAccelerating = false;
		}
	}
}

void UMyAnimInstance::NativeInitializeAnimation()
{
	BaseCharacter = Cast<AUEBaSECharacter>(TryGetPawnOwner());
}