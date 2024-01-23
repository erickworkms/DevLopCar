//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "DevLopCar/Controles/GamePlayController.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopCar/PlayerStates/DevOpPlayerState.h"


void AJogador_Base::RecebeDanoNPCMetodo()
{
	if (Vida > 0 && Veiculo == nullptr)
	{
		Vida -= 10;
		Acao = TomarDano;
		if (Vida <= 0)
		{
			Acao = Morto;
			ADevOpPlayerState* VerPlayerState = Cast<ADevOpPlayerState>(this->GetPlayerState());
			FTimerHandle ContadorReviver;
			GetWorldTimerManager().SetTimer(ContadorReviver, Cast<AGamePlayController>(GetController()),
											&AGamePlayController::ReviveJogador, 5, false);
			if (VerPlayerState)
			{
				VerPlayerState->AdicionaMortesJogadorMetodo();
			}
		}
	}
}

