//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "NPC_Base.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Delegates/DelegateSignatureImpl.inl"


void ANPC_Base::DanoAtropelamento()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow,"Bateu");
}

ANPC_Base::ANPC_Base()
{
	VerificaPadroes();
}


void ANPC_Base::BeginPlay()
{
	Super::BeginPlay();
	InicializaNPC();
}

void ANPC_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetController())
	{
		DefineEstadoAtual();
		DefinePadroesVel(DeltaTime);
		VerificaLocalDano(DeltaTime);
		VerificaVida();
		GerenciaVisaoPersonagemIA();
		if (Vida > 0 && Acao != Queda && Estado == NoChaoAndando)
		{
			VerificaMetodoComportamento();
		}
		if (Acao == Morto && Estado != Caindo)
		{
			GetCharacterMovement()->SetCanEverAffectNavigation(false);
			GetCharacterMovement()->SetAvoidanceEnabled(false);
			GetController()->bBlockInput = true;
			GetController()->UnPossess();

			if (IsValid(InimigoEncontrado))
			{
				InimigoEncontrado = NULL;
			}
			SetActorTickEnabled(false);
		}
	}
}

void ANPC_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
