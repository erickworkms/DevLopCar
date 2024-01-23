//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "WheeledVehicle.h"
#include "DevLopCar/Personagens/Carro/Carro_Base.h"
#include "NavAreas/NavArea_Null.h"


void ACarro_Base::PadroesVeiculo()
{
	AbrirPorta = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshContainer(
			TEXT("SkeletalMesh'/Game/Personagens/Carro/Brasilia.Brasilia'"));
	if (MeshContainer.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshContainer.Object);
	}
	//Blueprints de animação
	AnimacaoCarro = "AnimBlueprint'/Game/Personagens/Carro/Brasilia_AnimBlueprint.Brasilia_AnimBlueprint_C'";
	static ConstructorHelpers::FObjectFinder<UClass> AnimacaoEncontrada(*AnimacaoCarro);
	GetMesh()->SetAnimInstanceClass(AnimacaoEncontrada.Object);


	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	GetMesh()->SetCollisionObjectType(ECC_Vehicle);
	GetMesh()->SetWorldScale3D(FVector(0.70f, 0.70f, 0.70f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		ReferenciaContainer(
			TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (ReferenciaContainer.Succeeded())
	{
		LocalPorta = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Referencia"));
		LocalPorta->SetStaticMesh(ReferenciaContainer.Object);
		LocalPorta->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		LocalPorta->SetupAttachment(GetMesh());
		LocalPorta->SetRelativeLocation(FVector(-28, -125, 100), false, nullptr,
		                                ETeleportType::None);
		LocalPorta->SetRelativeRotation(FRotator(0.000000, 90, 0), false, nullptr, ETeleportType::None);
		LocalPorta->SetHiddenInGame(true);
	}
	GetMesh()->bNavigationRelevant = true;
	GetMesh()->SetCanEverAffectNavigation(true);
	LimpaNavMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("LimpaNavMesh"));
	LimpaNavMesh->SetCanEverAffectNavigation(true);
	LimpaNavMesh->SetWorldScale3D(FVector(7.048013, 2.168754, 4.817287));
	LimpaNavMesh->SetRelativeLocation(FVector(-15.000000, 3.000000, 142.000000));
	LimpaNavMesh->AreaClass = UNavArea_Null::StaticClass();
	LimpaNavMesh->bDynamicObstacle = true;
	LimpaNavMesh->bFillCollisionUnderneathForNavmesh = true;
	LimpaNavMesh->SetupAttachment(GetMesh());
	ConfigFisicaVeiculo();

	DetectaPersonagem = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectaColisao"));
	DetectaPersonagem->SetCanEverAffectNavigation(true);
	DetectaPersonagem->SetWorldScale3D(FVector(1.25, 2.75, 1.5));
	DetectaPersonagem->SetRelativeLocation(FVector(5, -47.000000, 80));
	DetectaPersonagem->SetRelativeRotation(FRotator(0, 0, 0));
	DetectaPersonagem->SetupAttachment(GetMesh());
	DetectaPersonagem->bHiddenInGame = false;
	DetectaPersonagem->OnComponentBeginOverlap.AddDynamic(this, &ACarro_Base::InicioColisaoEntrada);
	DetectaPersonagem->OnComponentEndOverlap.AddDynamic(this, &ACarro_Base::FimColisaoEntrada);

	DetectaDanoFrente = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectaDanoFrente"));
	DetectaDanoFrente->SetCanEverAffectNavigation(false);
	DetectaDanoFrente->SetWorldScale3D(FVector(1.75, 2.55, 1.5));
	DetectaDanoFrente->SetRelativeLocation(FVector(190, 10, 80));
	DetectaDanoFrente->SetRelativeRotation(FRotator(0, 0, 0));
	DetectaDanoFrente->SetupAttachment(GetMesh());
	DetectaDanoFrente->bHiddenInGame = false;
	DetectaDanoFrente->OnComponentBeginOverlap.AddDynamic(this, &ACarro_Base::InicioDanoColisao);

	DetectaDanoAtras = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectaDanoAtras"));
	DetectaDanoAtras->SetCanEverAffectNavigation(false);
	DetectaDanoAtras->SetWorldScale3D(FVector(1.75, 2.55, 1.5));
	DetectaDanoAtras->SetRelativeLocation(FVector(-180, 10, 80));
	DetectaDanoAtras->SetRelativeRotation(FRotator(0, 0, 0));
	DetectaDanoAtras->SetupAttachment(GetMesh());
	DetectaDanoAtras->bHiddenInGame = false;
	DetectaDanoAtras->OnComponentBeginOverlap.AddDynamic(this, &ACarro_Base::InicioDanoColisao);
}