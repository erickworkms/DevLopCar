//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Containers/UnrealString.h" 
#include "DevLopCar/GameInstance/DevLopCarGameInstance.h"
#include "DevLopCar/Huds/BaseHudMenuPrincipal.h"
#include "MenuPrincipalGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPCAR_API AMenuPrincipalGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AMenuPrincipalGameMode();
public:
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite)
	ABaseHudMenuPrincipal* hudDetectada;

	UFUNCTION(BlueprintCallable)
	void IniciarJogo();

private:
	UPROPERTY()
	UDevLopCarGameInstance* SeuGameInstance;
};
