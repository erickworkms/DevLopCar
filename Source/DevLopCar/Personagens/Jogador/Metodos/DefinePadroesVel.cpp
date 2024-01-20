//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "DevLopCar/Personagens/Jogador/Jogador_Base.h"
#include "GameFramework/CharacterMovementComponent.h"

void AJogador_Base::DefinePadroesVel(float valor)
{
	if (Acao == TomarDano || Acao == Morto)
	{
		VelocidadeMax = 0;
	}
	else
	{
		VelocidadeMax = 600;
	}
	
	GetCharacterMovement()->MaxWalkSpeed = VelocidadeMax;
	PersonagemSeMovimenta = (GetCapsuleComponent()->GetComponentVelocity().GetAbs().X
		+ GetCapsuleComponent()->GetComponentVelocity().GetAbs().Y) > 0;
	Velocidade = GetCapsuleComponent()->GetComponentVelocity().GetAbs().X
		+ GetCapsuleComponent()->GetComponentVelocity().GetAbs().Y;
	Velocidade = FMath::FInterpTo(GetCapsuleComponent()->GetComponentVelocity().Size(),
	                              Velocidade, valor, 10.f);
	if (Vida <= 0.0f)
	{
		Acao = Morto;
	}
}