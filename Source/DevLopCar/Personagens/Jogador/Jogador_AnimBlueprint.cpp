//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.
#include "Jogador_AnimBlueprint.h"
#include "Jogador_Base.h"
#include "GameFramework/CharacterMovementComponent.h"

UJogador_AnimBlueprint::UJogador_AnimBlueprint()
{
	Vida = 100.f;
	Velocidade = 0.f;
}

void UJogador_AnimBlueprint::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Personagem = TryGetPawnOwner();
}

void UJogador_AnimBlueprint::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Personagem)
	{
		return;
	}
	if (Personagem->IsA(AJogador_Base::StaticClass()))
	{
		AJogador_Base* PersonagemReferencia = Cast<AJogador_Base>(Personagem);
		
		if (PersonagemReferencia)
		{
			Vida = PersonagemReferencia->Vida;
			Velocidade = PersonagemReferencia->Velocidade;
	
			Estado = PersonagemReferencia->Estado;
			Acao = PersonagemReferencia->Acao;
			LadoEscolhido = PersonagemReferencia->LadoEscolhido;
		}
	}
}


