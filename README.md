# nuMI Simulation
-------------------------------------------------------------------
Project nuMI sim					
-------------------------------------------------------------------
This project is a simple application of GEANT4 to simulate the electron/positron
and gamma production process of High Energy proton in Carbon. Modified from 
GEANT4 example B1. 


1- GEOMETRY DEFINITION

The geometry is constructed in the DetectorConstruction class.
The setup consists of a an envelope of box shape containing a block 
of carbon.


2- PHYSICS LIST

The particle's type and the physic processes which will be available
in this example are set in the FTFP physics list. This physics list
requires data files for electromagnetic and hadronic processes.

3- ACTION INITALIZATION

ActionInitialization, instantiates and registers
to Geant4 kernel all user action classes.

While in sequential mode the action classes are instatiated just once,
      via invoking the method:
ActionInitialization::Build()
  in multi-threading mode the same method is invoked for each thread worker
  and so all user action classes are defined thread-local.

  A run action class is instantiated both thread-local
  and global that's why its instance is created also in the method
ActionInitialization::BuildForMaster()
  which is invoked only in multi-threading mode.

  4- PRIMARY GENERATOR

  The primary generator is defined in the PrimaryGeneratorAction class.
  The default kinematics is a 1 GeV Proton, in front of the graphite target.

  5- DETECTOR RESPONSE

  The information about the primary electron track is recorded. The kinetic 
  energy and track length at each step is recored. 

  B- USER INTERFACES

  The user command interface is set via the G4UIExecutive class
  in the main() function in nuMIsim.cc


  C- HOW TO RUN
  - Execute nuMIsim  in the 'batch' mode from macro files
(without visualization)
  ``Bash
  ./Brem -m <macro.mac>  -o <outputfile.root> -s <seed>
  ``
  macro file is required but outputfile and random seed will be assigned in default
