//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopCar/Personagens/NPC/NPC_Base.h"

void ANPC_Base::ContadorApagaNPC()
{
	FTimerHandle ContadorMorte;
	PontoSpawn->ContadorSpawnAtivos--;
	GetWorldTimerManager().SetTimer(ContadorMorte, this, &ANPC_Base::ApagaNPC, 5, false);
}
void ANPC_Base::ApagaNPC()
{
	Destroy();
}

void ANPC_Base::ResetaNPC()
{
	PodeMovimentar = true;
	Acao = Nada;
}
