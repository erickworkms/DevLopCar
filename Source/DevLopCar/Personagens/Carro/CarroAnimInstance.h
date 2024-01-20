// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VehicleAnimInstance.h"
#include "CarroAnimInstance.generated.h"
/**
 * 
 */
PRAGMA_DISABLE_DEPRECATION_WARNINGS
UCLASS()
class DEVLOPCAR_API UCarroAnimInstance : public UVehicleAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animacao)
	bool AbrirPorta = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animacao)
	bool FecharPorta = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animacao)
	bool DirecaoDireita = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animacao)
	bool DirecaoEsquerda = false;
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	
	UPROPERTY()
	APawn* Carro = NULL;
};
