//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "UObject/ConstructorHelpers.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopCar/Personagens/NPC/NPC_Base.h"

void ANPC_Base::DefinePadroesVel(float valor)
{
	if (IA_Comportamento == Perseguir_NPC && Acao != Atacar && PodeMovimentar == true)
	{
		VelocidadeMax = 400;
	}
	else if (PodeMovimentar == false || (Acao == TomarDano || Acao == Morto))
	{
		VelocidadeMax = 0;
	}
	else
	{
		VelocidadeMax = 100;
	}
	GetCharacterMovement()->MaxWalkSpeed = VelocidadeMax;
	Velocidade = GetCapsuleComponent()->GetComponentVelocity().GetAbs().X
		+ GetCapsuleComponent()->GetComponentVelocity().GetAbs().Y;
	Velocidade = FMath::FInterpTo(GetCapsuleComponent()->GetComponentVelocity().Size(),
								  Velocidade, valor, 10.f);
	if (Vida <= 0.0f)
	{
		Acao = Morto;
		VelocidadeMax = 0;
		GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
		GetCapsuleComponent()->SetCollisionObjectType(ECC_WorldDynamic);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
		ControleNPC->ClearFocus(EAIFocusPriority::Gameplay);
	}
}