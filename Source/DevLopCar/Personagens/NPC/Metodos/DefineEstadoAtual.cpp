//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopCar/Personagens/NPC/NPC_Base.h"

void ANPC_Base::DefineEstadoAtual()
{
	if (GetCharacterMovement()->MovementMode == MOVE_Falling)
	{
		Estado = Caindo;
	}
	else if (GetCharacterMovement()->MovementMode == MOVE_Flying)
	{
		Estado = Voando;
	}
	else if (GetCharacterMovement()->MovementMode == MOVE_Walking)
	{
		Estado = NoChaoAndando;
	}
	else
	{
		Estado = NoChaoAndando;
	}
}
