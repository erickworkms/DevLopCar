//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "Jogador_Base.h"
#include "Components/SkeletalMeshComponent.h"
#include "Delegates/DelegateSignatureImpl.inl"

AJogador_Base::AJogador_Base()
{
	CriaPersonagemConfig();
	CriaCameraConfig();
}

void AJogador_Base::BeginPlay()
{
	Super::BeginPlay();
	DefinePadroes();
	VerificaEscolhaPersonagem();
}

void AJogador_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DefineEstadoAtual();
	DefinePadroesVel(DeltaTime);
}

void AJogador_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoverFrente"), this, &AJogador_Base::MoverFrente);
	PlayerInputComponent->BindAxis(TEXT("MoverLado"), this, &AJogador_Base::MoverLado);

	PlayerInputComponent->BindAxis(TEXT("VirarCameraLado"), this, &AJogador_Base::VirarCameraLado);
	PlayerInputComponent->BindAxis(TEXT("VirarCameraFrente"), this, &AJogador_Base::VirarCameraFrente);

	PlayerInputComponent->BindAction(TEXT("Pulo"), IE_Pressed, this, &AJogador_Base::VerificaPulo_Pressionado);
	PlayerInputComponent->BindAction(TEXT("Pulo"), IE_Released, this, &AJogador_Base::VerificaPulo_Solto);

	PlayerInputComponent->
		BindAction(TEXT("Acelerar"), IE_Pressed, this, &AJogador_Base::Acelerar_Pressionado);
	PlayerInputComponent->BindAction(TEXT("Acelerar"), IE_Released, this, &AJogador_Base::Acelerar_Solto);

	PlayerInputComponent->
		BindAction(TEXT("Re"), IE_Pressed, this, &AJogador_Base::Re_Pressionado);
	PlayerInputComponent->BindAction(TEXT("Re"), IE_Released, this, &AJogador_Base::Re_Solto);
	
	PlayerInputComponent->BindAction(TEXT("Interagir"), IE_Pressed, this,
	                                 &AJogador_Base::Interagir_Pressionado);
	PlayerInputComponent->BindAction(TEXT("Interagir"), IE_Released, this,
	                                 &AJogador_Base::Interagir_Solto);
}



void AJogador_Base::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	VerificaEscolhaPersonagem();
}
