//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DevLopCar/Personagens/Carro/Carro_Base.h"
#include "DevLopCar/Personagens/Enums/Lista_Enums.h"
#include "Interfaces/DanoProjetilInterface.h"
#include "Jogador_Base.generated.h"

UCLASS()
class DEVLOPCAR_API AJogador_Base : public ACharacter, public IDanoProjetilInterface
{
	GENERATED_BODY()

	UPROPERTY()
	USpringArmComponent* SpringArm;
	UPROPERTY()
	UCameraComponent* CameraPrincipal;
	UPROPERTY()
	UStaticMeshComponent* LocalReferenciaCamera;
	
public:

	AJogador_Base();
	
	UPROPERTY()
	AActor* Veiculo = nullptr;
	UPROPERTY()
	TArray<FString> MeshesPlayer;
	UPROPERTY()
	TArray<FString> AnimacaoPlayer;
	UPROPERTY()
	FString CaminhoArma;

	UPROPERTY(BlueprintReadOnly,Category="Variaveis")
	float Vida = 100;
	UPROPERTY()
	float Velocidade;
	UPROPERTY()
	float AnguloCorpo;
	UPROPERTY()
	float AnguloCameraX;
	UPROPERTY()
	float AnguloCameraY;
	UPROPERTY()
	float Direcao;
	UPROPERTY()
	float VelTempAnimacao;
	
	UPROPERTY(meta=(BlueprintProtected = "true"))
	float VelocidadeCombo = 0.2f;
	UPROPERTY(BlueprintReadOnly,Category="Variaveis")
	float ValorAceleracao= 0.0f;
	UPROPERTY()
	float VelocidadeMax = 1000;
	UPROPERTY()
	bool PermiteEntrarCarro = true;
	UPROPERTY()
	bool PermiteSairCarro = false;
	UPROPERTY()
	bool PodeMovimentar = true;
	UPROPERTY()
	bool PodeDirigir = false;


	UPROPERTY()
	TEnumAsByte<LadoEscolhido> LadoEscolhido = Dirigir_Frente;
	UPROPERTY()
	TEnumAsByte<TipoEstado> Estado = NoChaoAndando;
	UPROPERTY()
	TEnumAsByte<TipoAcao> Acao = Nada;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Personagem")
	TEnumAsByte<TipoPersonagem> PersonagemNPC = Estagiario;

	UPROPERTY()
	UClass* Estagiario_Anim;
	UPROPERTY()
	UClass* Pleno_Anim;
	UPROPERTY()
	UClass* Senior_Anim;
	UPROPERTY()
	UClass* Chefe_Anim;

	UPROPERTY()
	bool BloqueiaContador = true;
	UPROPERTY()
	bool PersonagemSeMovimenta;
	
	void VerificaEscolhaPersonagem();
	
	void VerificaMeshPersonagem(float Index);
	
	void LocalAttachPersonagemVeiculo();
	
	void DetachPersonagemVeiculo();

	virtual void AdicionaCarro(AActor* Carro) override;

	virtual void RemoverCarro() override;
protected:
	virtual void BeginPlay() override;
	
	void MoverFrente(float valor);
	
	void MoverLado(float valor);

	void VirarCameraFrente(float valor);
	
	void VirarCameraLado(float valor);

	void DefinePadroesVel(float valor);

	//Botões apertados
	void VerificaPulo_Pressionado();
	void VerificaPulo_Solto();

	void Acelerar_Pressionado();
	void Acelerar_Solto();

	void Re_Pressionado();
	void Re_Solto();
	
	void Interagir_Pressionado();
	void Interagir_Solto();

	//Metodos
	void DefinePadroes();

	void DefineEstadoAtual();
	void CriaCameraConfig();
	void CriaPersonagemConfig();

public:

	virtual void Tick(float DeltaTime) override;
	
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void RecebeDanoNPCMetodo() override;

	virtual void RecebeDanoTeleportMetodo(ETipoColisao TipoColisao,AActor* Alvo) override;

	UFUNCTION()
	void InicioDanoColisao(UPrimitiveComponent* OverlappedComp, AActor* InimigoDetectado,
						   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						   const FHitResult& SweepResult)
	{
		if (Acao == Atacar && InimigoDetectado != this)
		{
			IDanoProjetilInterface* inimigoEncontrado = Cast<IDanoProjetilInterface>(InimigoDetectado);
			if (inimigoEncontrado)
			{
				inimigoEncontrado->DanoMetodo(this);
			}
		}
	}

	UFUNCTION()
	void FimDanoColisao(UPrimitiveComponent* OverlappedComp, AActor* InimigoDetectado,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
	{
		// ResetaSaidaColisao(InimigoDetectado);
	}
};
