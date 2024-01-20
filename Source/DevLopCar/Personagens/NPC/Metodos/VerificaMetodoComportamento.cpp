//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "UObject/ConstructorHelpers.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "BehaviorTree/BlackboardComponent.h"
#include "DevLopCar/Personagens/NPC/NPC_Base.h"

void ANPC_Base::VerificaMetodoComportamento()
{
	if (IsValid(ControleNPC) && Acao != TomarDano)
	{
		if (Estado == NoChaoAndando)
		{
			if (IA_Comportamento == Patrulha_NPC)
			{
				MoverPersonagemPatrulha(VariaveisIA_BlackBoard->GetValueAsVector("LocalObjetivo"));
			}
			if (IA_Comportamento == Perseguir_NPC)
			{
				if (IsValid(InimigoEncontrado))
				{
					MoverPersonagemPatrulha(InimigoEncontrado->GetActorLocation());
				}
			}
		}
		else
		{
			ControleNPC->ClearFocus(EAIFocusPriority::Gameplay);
			GetCharacterMovement()->StopActiveMovement();
			ControleNPC->StopMovement();
			Acao = Nada;
		}
	}
}