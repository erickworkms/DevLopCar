//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopCar/Personagens/NPC/IAControle.h"
#include "DevLopCar/Personagens/NPC/NPC_Base.h"

void ANPC_Base::InicializaNPC()
{
	VariaveisIA_BlackBoard = UAIBlueprintHelperLibrary::GetBlackboard(GetController());
	ControleNPC = Cast<AIAControle>(GetController());
	VerificaLocalPatrulha();
	InicializaAttachPersonagem();

	for (FConstControllerIterator it = GetWorld()->GetControllerIterator(); it; ++it)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(*it))
			if (IsValid(PlayerController))
			{
				AJogador_Base* JogadorEncontrado = Cast<AJogador_Base>(PlayerController->GetPawn());
				if (IsValid(JogadorEncontrado))
				{
					InimigoEncontrado = JogadorEncontrado;
					IA_Comportamento = Perseguir_NPC;
				}					
			}
	}
	
}

void ANPC_Base::InicializaAttachPersonagem()
{
	DanoAtaque->AttachToComponent(GetMesh(),
								  FAttachmentTransformRules::SnapToTargetIncludingScale, "MaoEsqSoquete");
	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->AvoidanceConsiderationRadius = 500;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->MaxSwimSpeed = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->SetAvoidanceEnabled(true);
}
