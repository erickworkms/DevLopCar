// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "Components/BoxComponent.h"
#include "Perception/AISightTargetInterface.h"
#include "Components/StaticMeshComponent.h"
#include "DevLopCar/Personagens/Jogador/Interfaces/DanoProjetilInterface.h"
#include "Carro_Base.generated.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
/**
 * 
 */
//Lembrar: Sempre exportar carros baseando-se na camera em Z com a frente do carro apontando para X, o importante é sempre para onde o root aponta
UCLASS()
class DEVLOPCAR_API ACarro_Base : public AWheeledVehicle,public IAISightTargetInterface
{
	GENERATED_BODY()
	
public:
	ACarro_Base();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animacao)
	bool AbrirPorta = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animacao)
	bool FecharPorta = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animacao)
	bool DirecaoDireita = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animacao)
	bool DirecaoEsquerda = false;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* LocalPorta;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Components")
	TArray<UStaticMeshComponent*> LocalEntrada;

	void MovimentaVeiculoFrente();
	void MovimentaVeiculoDirecao(float Direcao);
	void PararVeiculo();
	void MovimentaVeiculoRe();
	void MudancaConfigFisicaVeiculo();
private:
	
	FString CaminhoMesh;
	FString CaminhoAnimacao;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* LimpaNavMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* DetectaPersonagem;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* DetectaDanoFrente;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* DetectaDanoAtras;
	
	void PadroesVeiculo();
	void ConfigFisicaVeiculo();
	
	virtual void BeginPlay() override;
	virtual bool CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor, const bool* bWasVisible, int32* UserData) const override;

	UFUNCTION()
	void InicioColisaoEntrada(UPrimitiveComponent* OverlappedComp, AActor* InimigoDetectado,
						   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						   const FHitResult& SweepResult)
	{
		if (InimigoDetectado != this)
		{
			IDanoProjetilInterface* inimigoEncontrado = Cast<IDanoProjetilInterface>(InimigoDetectado);
			if (inimigoEncontrado)
			{
				inimigoEncontrado->AdicionaCarro(this);
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow,"entrou");
			}
		}
	}

	UFUNCTION()
	void FimColisaoEntrada(UPrimitiveComponent* OverlappedComp, AActor* InimigoDetectado,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
	{
		IDanoProjetilInterface* inimigoEncontrado = Cast<IDanoProjetilInterface>(InimigoDetectado);
		if (inimigoEncontrado)
		{
			inimigoEncontrado->RemoverCarro();
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow,"falhou");
		}
	}

	UFUNCTION()
	void InicioDanoColisao(UPrimitiveComponent* OverlappedComp, AActor* InimigoDetectado,
						   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						   const FHitResult& SweepResult)
	{
		if (InimigoDetectado != this)
		{
			IDanoProjetilInterface* inimigoEncontrado = Cast<IDanoProjetilInterface>(InimigoDetectado);
			if (inimigoEncontrado)
			{
				inimigoEncontrado->DanoAtropelamento();
			}
		}
	}
};
