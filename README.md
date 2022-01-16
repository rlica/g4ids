# g4ids
 Geant4 simulation package for the [ISOLDE Decay Station](https://isolde-ids.web.cern.ch/)

##
The G4IDS (Geant4 IDS) code was created for the IDS detection system
as part of my [PhD Thesis](https://cds.cern.ch/record/2292847?ln=en), based on the GEANT4 framework.
The present version represents a joint effort together with C. Sotty (KU Leuven, IFIN-HH) and having as a starting
point a previous code developed by F. Rotaru (IFIN-HH). The geometries
of the supporting frame and detectors were carefully defined, using CAD models and imported into Geant4 using [CADMesh](https://github.com/christopherpoole/CADMesh).

The main purpose of the code was to evaluate the detection efficiency of the
IDS detectors, starting with the HPGe detectors. As the IDS system became more
versatile, other detectors and implantation chambers were included in the simulations,
such that the latest iteration of the code contains the following geometries:
 * HPGe Clovers
 * LaBr3(Ce) detectors
 * Plastic scintillators
 * The T-shaped implantation chamber for fast-timing studies
 * The IS530 implantation chamber for beta-gamma spectroscopy
 * The IDS polyhedron frame

## Prerequisites:
Geant4, ROOT, CADMesh
