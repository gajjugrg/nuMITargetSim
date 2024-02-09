#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4Types.hh"
#include "G4VUserActionInitialization.hh"
#include "G4String.hh"

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization();
    ActionInitialization(const G4String* outputFileNamePtr);
    ~ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    const G4String* fOutputFileNamePtr;
};
#endif
