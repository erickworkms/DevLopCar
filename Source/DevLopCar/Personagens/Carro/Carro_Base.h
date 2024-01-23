//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "Components/BoxComponent.h"
#include "Perception/AISightTargetInterface.h"
#include "Components/StaticMeshComponent.h"
#include "DevLopCar/Personagens/Jogador/Jogador_Base.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animacao)
	float Velocidade = 0;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* LocalPorta;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Components")
	TArray<UStaticMeshComponent*> LocalEntrada;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	AJogador_Base* Jogador;

	UPROPERTY()
	FString AnimacaoCarro;
	
	void MovimentaVeiculoFrente();
	void MovimentaVeiculoDirecao(float Direcao);
	void PararVeiculo();
	void MovimentaVeiculoRe();
	void MudancaConfigFisicaVeiculo();
	void VerificaVelocidadeCarro(float valor);
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

	virtual void Tick(float DeltaSeconds) override;
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
			Velocidade = 0;
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
				if (IsValid(Jogador) && Velocidade > 300)
				{
					inimigoEncontrado->DanoMetodo(Jogador);
				}
			}
		}
	}
};
