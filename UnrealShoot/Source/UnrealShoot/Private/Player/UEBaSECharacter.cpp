// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UEBaSECharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

AUEBaSECharacter::AUEBaSECharacter()
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

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}

void AUEBaSECharacter::MoveForvard(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AUEBaSECharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

