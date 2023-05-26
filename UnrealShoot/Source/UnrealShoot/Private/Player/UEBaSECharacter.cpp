// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UEBaSECharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/UECharacterMovementComponent.h"

AUEBaSECharacter::AUEBaSECharacter(const FObjectInitializer& Object) 
	:Super(Object.SetDefaultSubobjectClass<UUECharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AUEBaSECharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUEBaSECharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUEBaSECharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForvard", this, &AUEBaSECharacter::MoveForvard);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUEBaSECharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AUEBaSECharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &AUEBaSECharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AUEBaSECharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AUEBaSECharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run",IE_Released, this, &AUEBaSECharacter::OnStopRunning);

}

bool AUEBaSECharacter::IsRunning() const
{
	return WantsToRun && !GetVelocity().IsZero() && IsMovingForward;
}

void AUEBaSECharacter::MoveForvard(float Amount)
{
	IsMovingForward = Amount > 0.0f;

	AddMovementInput(GetActorForwardVector(), Amount);
}

void AUEBaSECharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void AUEBaSECharacter::OnStartRunning()
{
	
	WantsToRun= true;
}

void AUEBaSECharacter::OnStopRunning()
{
	WantsToRun = false;
}

