//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopCar/Personagens/NPC/NPC_Base.h"
#include "DevLopCar/PlayerStates/Interfaces/AlteraPlayerStateInterface.h"

void ANPC_Base::DanoMetodo(AActor* Inimigo)
{
	AJogador_Base* Jogador_Base = Cast<AJogador_Base>(Inimigo);
	if (Vida > 0 && IsValid(Jogador_Base) && Acao != TomarDano && Acao != Morto)
	{
		if (InimigoEncontrado == NULL)
		{
			InimigoEncontrado = Inimigo;
			IA_Comportamento = Perseguir_NPC;
		}
		Acao = TomarDano;
		Vida -= 40;
		ContadorDano = 0.5;
		LocalFixoGolpe = FVector(((GetRootComponent()->GetComponentToWorld().GetRotation().
													   GetForwardVector()) * -1000) + Jogador_Base->GetActorLocation());
		if (Vida <= 0)
		{
			ContadorApagaNPC();
			Acao = Morto;
			IAlteraPlayerStateInterface* VerPlayerState = Cast<IAlteraPlayerStateInterface>(
				Jogador_Base->GetPlayerState());
			if (VerPlayerState)
			{
				VerPlayerState->AdicionaMortesZumbiMetodo();
			}
		}
	}
}