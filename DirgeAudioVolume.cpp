// This game is copywritten with any and all content associated with it are exclusively owned by NonNobis Games LLC.

#include "DirgeAudioVolume.h"
#include "DirgeCppCharacter.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogDirgeAudioVolume, Log, All);

ADirgeAudioVolume::ADirgeAudioVolume()
{
    OnActorBeginOverlap.AddDynamic(this, &ADirgeAudioVolume::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &ADirgeAudioVolume::OnOverlapEnd);
}

void ADirgeAudioVolume::BeginPlay()
{
    Super::BeginPlay();
}

void ADirgeAudioVolume::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    if(OtherActor && (OtherActor != this))
    {
        UE_LOG(LogDirgeAudioVolume, VeryVerbose, TEXT("%s is entering %s."), *FString(OtherActor->GetName()), *FString(*GetName()));
    }
    
    // if TagsInside or LevelDefault is null, print error message
    if (TagsInside.IsValid() && LevelDefault.IsValid())
    {
        ADirgeCppCharacter* AsDirgeCppCharacter = Cast<ADirgeCppCharacter>(OtherActor);
        if (IsValid(AsDirgeCppCharacter))
        {
            UE_LOG(LogDirgeAudioVolume, Verbose, TEXT("Assinging %s soundscapes TagInside %s LevelDefault %s"), *FString(AsDirgeCppCharacter->GetName()), *TagsInside.ToString(), *LevelDefault.ToString());

            AsDirgeCppCharacter->AssignSoundscapeStates(TagsInside, LevelDefault);
            AsDirgeCppCharacter->EnterSoundVolume();
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Define TagsInside and LevelDefault in the editor");
    }
}

void ADirgeAudioVolume::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
    if(OtherActor && (OtherActor != this))
    {
        UE_LOG(LogDirgeAudioVolume, VeryVerbose, TEXT("%s is exiting %s."), *FString(OtherActor->GetName()), *FString(*GetName()));
    }
    if (TagsInside.IsValid() && LevelDefault.IsValid())
    {
        ADirgeCppCharacter* AsDirgeCppCharacter = Cast<ADirgeCppCharacter>(OtherActor);
        if (IsValid(AsDirgeCppCharacter))
        {
            UE_LOG(LogDirgeAudioVolume, Verbose, TEXT("Unassinging %s soundscapes TagInside %s LevelDefault %s"), *FString(AsDirgeCppCharacter->GetName()), *TagsInside.ToString(), *LevelDefault.ToString());

            AsDirgeCppCharacter->AssignSoundscapeStates(LevelDefault, TagsInside);
            AsDirgeCppCharacter->ExitSoundVolume();
        }       
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Define TagsInside and LevelDefault in the editor");
    }
   
}