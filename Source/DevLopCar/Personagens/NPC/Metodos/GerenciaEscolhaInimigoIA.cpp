//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "AIController.h"
#include "UObject/ConstructorHelpers.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "BehaviorTree/BlackboardComponent.h"
#include "DevLopCar/Personagens/NPC/NPC_Base.h"

void ANPC_Base::GerenciaEscolhaInimigoIA()
{
	AJogador_Base* JogadorPadrao = Cast<AJogador_Base>(InimigoEncontrado);

	if (IsValid(JogadorPadrao))
	{
		VariaveisIA_BlackBoard->SetValueAsObject("Inimigo", JogadorPadrao);
	}
}

void ANPC_Base::GerenciaVisaoPersonagemIA()
{
	if (Vida > 0 && Acao != Queda && Estado == NoChaoAndando)
	{
		if (InimigoEncontrado)
		{
			float AuxDistancia = GetDistanceTo(InimigoEncontrado);
			if (AuxDistancia < 3000)
			{
				VariaveisIA_BlackBoard->SetValueAsFloat("DistanciaObjetivo", AuxDistancia);
				IA_Comportamento = Perseguir_NPC;
				VariaveisIA_BlackBoard->SetValueAsEnum("IA_Comportamento", IA_Comportamento);
			}
			else
			{
				InimigoEncontrado = NULL;
				VariaveisIA_BlackBoard->ClearValue("Inimigo");
				IA_Comportamento = Patrulha_NPC;
				VariaveisIA_BlackBoard->SetValueAsEnum("IA_Comportamento", IA_Comportamento);
			}
		}
	}
	if (IsValid(InimigoEncontrado))
	{
		AJogador_Base* JogadorPadrao = Cast<AJogador_Base>(InimigoEncontrado);
		if (IsValid(JogadorPadrao))
		{
			if (JogadorPadrao->Vida <= 0)
			{
				InimigoEncontrado = NULL;
				ControleNPC->ClearFocus(EAIFocusPriority::Gameplay);
				VariaveisIA_BlackBoard->ClearValue("Inimigo");
				Acao = Nada;
				VariaveisIA_BlackBoard->SetValueAsEnum("Acao", Acao);
				IA_Comportamento = Patrulha_NPC;
				VariaveisIA_BlackBoard->SetValueAsEnum("IA_Comportamento", IA_Comportamento);
			}
		}
	}
}