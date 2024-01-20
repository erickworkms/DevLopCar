//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ADevLopCarGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPCAR_API ADevLopCarGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	float GetTempoJogo();
	UFUNCTION()
	void SetTempoJogo(float TempoJogoSet);
	UFUNCTION()
	void DescontaTempoJogo();

private:

	UPROPERTY()
	float TempoJogo = 0;
};
