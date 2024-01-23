//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "DetectarComecoAtaque.h"
#include "DevLopCar/Personagens/NPC/NPC_Base.h"

void UDetectarComecoAtaque::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	ANPC_Base* NPC = Cast<ANPC_Base>(MeshComp->GetOwner());

	if (IsValid(NPC))
	{
		NPC->PodeMovimentar = false;
		NPC->PermiteDano = true;
	}
}
