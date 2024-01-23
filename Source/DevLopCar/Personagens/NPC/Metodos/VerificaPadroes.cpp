//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopCar/Personagens/NPC/IAControle.h"
#include "DevLopCar/Personagens/NPC/NPC_Base.h"

void ANPC_Base::VerificaPadroes()
{
	GetCapsuleComponent()->InitCapsuleSize(29.0f, 76.0f);

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -75));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	GetMesh()->SetWorldScale3D(FVector(0.70f, 0.70f, 0.70f));


	//BaseMesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshContainer(TEXT("SkeletalMesh'/Game/Personagens/Clientes/Mremireh_O_Desbiens.Mremireh_O_Desbiens'"));
	if (MeshContainer.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshContainer.Object);
	}
	AnimacaoPlayer = "AnimBlueprint'/Game/Personagens/Clientes/Clientes_AnimBlueprint.Clientes_AnimBlueprint_C'";
	//AnimBlueprint
	static ConstructorHelpers::FObjectFinder<UClass> AnimacaoEncontrada(*AnimacaoPlayer);
	GetMesh()->SetAnimInstanceClass(AnimacaoEncontrada.Object);
	
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	
	//floats
	Vida = 100;
	DistanciaCombate = 100;

	//Structs
	Acao = Nada;
	Estado = NoChaoAndando;
	IA_Comportamento = Patrulha_NPC;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AIAControle::StaticClass();

	DanoAtaque = CreateDefaultSubobject<UBoxComponent>(TEXT("ColisaoAtaque"));
	DanoAtaque->bFillCollisionUnderneathForNavmesh = false;
	DanoAtaque->bHiddenInGame = false;
	DanoAtaque->SetVisibility(true);
	DanoAtaque->SetCanEverAffectNavigation(false);
	DanoAtaque->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));
	DanoAtaque->SetRelativeRotation(FRotator(0, 0, 0));
	DanoAtaque->SetWorldScale3D(FVector(1, 0.5, 2));
	DanoAtaque->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DanoAtaque->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	DanoAtaque->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	DanoAtaque->OnComponentBeginOverlap.AddDynamic(this, &ANPC_Base::InicioDanoColisao);
	DanoAtaque->OnComponentEndOverlap.AddDynamic(this, &ANPC_Base::FimDanoColisao);
}