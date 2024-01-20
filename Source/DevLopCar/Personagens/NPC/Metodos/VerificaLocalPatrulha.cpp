//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "AIController.h"
#include "UObject/ConstructorHelpers.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "BehaviorTree/BlackboardComponent.h"
#include "DevLopCar/Personagens/NPC/NPC_Base.h"

void ANPC_Base::VerificaLocalPatrulha()
{
	if (IsValid(VariaveisIA_BlackBoard))
	{
		VariaveisIA_BlackBoard->SetValueAsVector("LocalObjetivo", Objetivos[IndexObjetivo]->GetActorLocation());
	}
}

void ANPC_Base::MoverPersonagemPatrulha(FVector LocalPatrulha)
{
	if (IA_Comportamento == Patrulha_NPC)
	{
		VerificaLocalPatrulha();
		if (FVector::Dist(LocalPatrulha, GetActorLocation()) >= DistanciaCombate)
		{
			ControleNPC->MoveToLocation(LocalPatrulha, 25, true, false,
										false, false, 0, false);
			if (FVector::Dist(LocalPatrulha, GetActorLocation()) <= 130 && PodeMovimentar == true)
			{
				PodeMovimentar = false;
				if (IndexObjetivo == 0)
				{
					IndexObjetivo = 1;
				}
				else
				{
					IndexObjetivo = 0;
				}
				FTimerHandle ContadorLocal;
				GetWorldTimerManager().SetTimer(ContadorLocal, this, &ANPC_Base::AtualizaObjetivo, 2, false);
			}
		}
	}
	else if (IA_Comportamento == Perseguir_NPC)
	{
		if (FVector::Dist(InimigoEncontrado->GetActorLocation(), GetActorLocation()) >= DistanciaCombate)
		{
			Acao = Nada;
			VariaveisIA_BlackBoard->SetValueAsEnum("Acao", Acao);
			ControleNPC->MoveToLocation(InimigoEncontrado->GetActorLocation(), 25, false, false,
										false, false, 0, false);
			ControleNPC->ClearFocus(EAIFocusPriority::Default);
		}
		else if (FVector::Dist(InimigoEncontrado->GetActorLocation(), GetActorLocation()) <= DistanciaCombate && Acao !=
			Atacar && PodeMovimentar == true)
		{
			PodeMovimentar = false;
			Acao = Atacar;
			VariaveisIA_BlackBoard->SetValueAsEnum("Acao", Acao);
			ControleNPC->SetFocus(InimigoEncontrado);
			FTimerHandle ContadorLocal;
			GetWorldTimerManager().SetTimer(ContadorLocal, this, &ANPC_Base::ResetaNPC, 2, false);
		}
	}
}
void ANPC_Base::AtualizaObjetivo()
{
	PodeMovimentar = true;
}