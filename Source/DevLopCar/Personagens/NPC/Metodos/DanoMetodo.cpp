//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.
#include "DevLopCar/Personagens/NPC/NPC_Base.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopCar/Personagens/Jogador/Jogador_Base.h"
#include "DevLopCar/PlayerStates/DevOpPlayerState.h"

void ANPC_Base::DanoMetodo(AActor* Inimigo)
{
	if (Vida > 0 && Acao != Morto)
	{
		AJogador_Base* VerificaJogador = Cast<AJogador_Base>(Inimigo);
		if (IsValid(VerificaJogador))
		{
			ADevOpPlayerState* VerPlayerState = Cast<ADevOpPlayerState>(
				VerificaJogador->GetPlayerState());
			if (VerPlayerState)
			{
				VerPlayerState->AdicionaMortesZumbiMetodo();
			}
		}
		Acao = TomarDano;
		Vida -= 1000;
		ContadorDano = 0.5;
		GetMesh()->SetCollisionResponseToAllChannels(ECR_Block);
		GetMesh()->SetAllBodiesSimulatePhysics(true);
		ContadorApagaNPC();
		Acao = Morto;
	}
}