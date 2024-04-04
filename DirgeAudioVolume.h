// This game is copywritten with any and all content associated with it are exclusively owned by NonNobis Games LLC.

#pragma once

#include "CoreMinimal.h"
#include "Sound/AudioVolume.h"
#include "GameplayTagContainer.h"
#include "DirgeAudioVolume.generated.h"


UCLASS()
class DIRGECPLUS_API ADirgeAudioVolume : public AAudioVolume
{
	GENERATED_BODY()

public:
	ADirgeAudioVolume();

	UPROPERTY(EditAnywhere, Category = "Soundscape") FGameplayTag TagsInside;
	UPROPERTY(EditAnywhere, Category = "Soundscape") FGameplayTag LevelDefault;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
	
};
