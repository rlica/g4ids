#ifndef __TERMINATOR_HH__
#define __TERMINATOR_HH__

#include <TROOT.h>
#include <TApplication.h>

class Terminator : public TObject {
public:
  Terminator() {;}
  ~Terminator() {;}
  inline void Terminate() { //*SIGNAL*
     if (gROOT->GetListOfCanvases()->GetEntries() < 1)
       gApplication->Terminate();
  }
private:
  int count;

 ClassDef(Terminator,1)
};
#endif
