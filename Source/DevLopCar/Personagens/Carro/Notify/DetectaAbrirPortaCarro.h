//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "DetectaAbrirPortaCarro.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPCAR_API UDetectaAbrirPortaCarro : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp,
					UAnimSequenceBase* Animation) override;
};

