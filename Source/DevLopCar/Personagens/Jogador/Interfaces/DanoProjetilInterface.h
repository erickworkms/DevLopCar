#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DanoProjetilInterface.generated.h"

UINTERFACE(MinimalAPI)
class UDanoProjetilInterface : public UInterface
{
	GENERATED_BODY()
};

class DEVLOPCAR_API IDanoProjetilInterface
{
	GENERATED_BODY()
public:
	UFUNCTION()
	virtual void DanoMetodo(AActor* Inimigo);
	UFUNCTION()
	virtual void RecebeDanoNPCMetodo();
	UFUNCTION()
	virtual void AdicionaCarro(AActor* Carro);
	UFUNCTION()
	virtual void RemoverCarro();
};
