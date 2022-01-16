# g4ids
 Geant4 simulation package for the [ISOLDE Decay Station](https://isolde-ids.web.cern.ch/)
 Created in 2014-2015 (R. Lica, C. Sotty)

##
The G4IDS (Geant4 IDS) code was developed for the IDS detection system
as part of my [PhD Thesis](https://cds.cern.ch/record/2292847?ln=en), based on the GEANT4 framework.
The present version represents a joint effort together with C. Sotty (KU Leuven, IFIN-HH) and having as a starting
point a previous Geant4 code for HPGe detectors developed by F. Rotaru (IFIN-HH). The geometries
of the supporting frame and detectors were carefully defined, using CAD models and imported into Geant4 using [CADMesh](https://github.com/christopherpoole/CADMesh).

The main purpose of the code was to evaluate the detection efficiency of the
IDS detectors, starting with the HPGe detectors. As the IDS system became more
versatile, other detectors and implantation chambers were included in the simulations,
such that the present version of the code contains the following geometries:
 * CANBERRA HPGe Clovers (Euroball type)
 * Conical LaBr3(Ce) detectors
 * Square Plastic scintillators
 * The T-shaped IDS implantation chamber used for fast-timing studies
 * The IFIN-HH implantation chamber of IDS used for the first time during the IS530 experiment
 * The IDS polyhedron frame

Aditional simulation codes were developed by other colleagues, dedicated to different types of detectors (neutron, Si, fast-timing). An updated version of the
G4IDS code should be made available once it is finalized.  

## Prerequisites:
Geant4, ROOT, CADMesh
