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

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;

private:
	bool WantsToRun;
	bool IsMovingForward = false;

	void MoveForvard(float Amount);
	void MoveRight(float Amount);

	void OnStartRunning();
	void OnStopRunning();
	
};
