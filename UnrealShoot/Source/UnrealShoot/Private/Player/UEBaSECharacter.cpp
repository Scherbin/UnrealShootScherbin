// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UEBaSECharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/UECharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Engine/SkeletalMeshSocket.h"

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

	PlayerInputComponent->BindAction("FireButton", IE_Pressed, this, &AUEBaSECharacter::FireWeapon);

	//dont rotate when the controller rotates. Let that just affect the camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

}

bool AUEBaSECharacter::IsRunning() const
{
	return WantsToRun && !GetVelocity().IsZero() && IsMovingForward;
}

void AUEBaSECharacter::MoveForvard(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	if(Amount == 0.0f) return;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AUEBaSECharacter::MoveRight(float Amount)
{
	if(Amount== 0.0f) return;
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

float AUEBaSECharacter::GetMovementDirection() const
{
	if(GetVelocity().IsZero()) return 0.0f;

	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z);
}

void AUEBaSECharacter::FireWeapon()
{
	if (FireSound)
	{
		UGameplayStatics::PlaySound2D(this, FireSound);
	}
	const USkeletalMeshSocket* BarrelSocket = GetMesh()->GetSocketByName("Muzzle");
	if (BarrelSocket)
	{
		const FTransform SocketTransform = BarrelSocket->GetSocketTransform(GetMesh());
	
		if (MuzzleFlash)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, SocketTransform);
		}
	}
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && HipFireMontage)
	{
		AnimInstance->Montage_Play(HipFireMontage);
		AnimInstance->Montage_JumpToSection(FName("StartFire"));
	}
}