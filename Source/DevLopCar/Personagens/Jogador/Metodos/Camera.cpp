//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DevLopCar/Personagens/Jogador/Jogador_Base.h"

void AJogador_Base::VirarCameraFrente(float valor)
{
	float RotacaoCamera = CameraPrincipal->GetSocketRotation("none").Pitch * -1;
	
	//Este é o valor maximo para cima e para baixo da camera
	if (RotacaoCamera >= 49 && RotacaoCamera <= -15)
	{
		AddControllerPitchInput(valor);
	}
	else if (RotacaoCamera < 49 && valor > 0)
	{
		AddControllerPitchInput(valor);
	}
	else if (RotacaoCamera > -15 && valor < 0)
	{
		AddControllerPitchInput(valor);
	}
}

void AJogador_Base::VirarCameraLado(float valor)
{
	AddControllerYawInput(valor);
}

void AJogador_Base::CriaCameraConfig()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->MaxSwimSpeed = 1000.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->bAllowPhysicsRotationDuringAnimRootMotion = true;

	//Cria e attacha a camera ao objeto root
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);

	SpringArm->bUsePawnControlRotation = true;

	CameraPrincipal = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraPrincipal->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	CameraPrincipal->bUsePawnControlRotation = false;

	SpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 20.0f;

	SpringArm->bDoCollisionTest = false;
	SpringArm->ProbeSize = 15;
	SpringArm->ProbeChannel = ECC_Camera;

	AutoPossessPlayer = EAutoReceiveInput::Disabled;
}
