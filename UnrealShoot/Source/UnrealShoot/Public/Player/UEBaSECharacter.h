// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UEBaSECharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class UNREALSHOOT_API AUEBaSECharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AUEBaSECharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForvard(float Amount);
	void MoveRight(float Amount);

};
