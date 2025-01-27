//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DevLopCar/Personagens/Enums/Lista_Enums.h"
#include "Jogador_AnimBlueprint.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPCAR_API UJogador_AnimBlueprint : public UAnimInstance
{
	GENERATED_BODY()

public:
	UJogador_AnimBlueprint();
	
	FVector LocalArma;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	float Vida;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	float Velocidade;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	TEnumAsByte<TipoEstado> Estado = NoChaoAndando;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	TEnumAsByte<TipoAcao> Acao = Nada;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animacao")
	TEnumAsByte<LadoEscolhido> LadoEscolhido = Dirigir_Frente;
		
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds);

private:
	UPROPERTY()
	APawn* Personagem = NULL;
};
