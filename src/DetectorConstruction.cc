#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

/*
#include "G4FieldManager.hh"
#include "G4EqMagElectricField.hh"
#include "G4UniformElectricField.hh"
#include "G4DormandPrince745.hh"
#include "G4TransportationManager.hh"
#include "G4ChordFinder.hh"
#include "G4IntegrationDriver.hh"
*/

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()					
{ }


DetectorConstruction::~DetectorConstruction()
{ }

G4VPhysicalVolume* DetectorConstruction::Construct(){
  
  G4NistManager* nist = G4NistManager::Instance();
  
  // World Material

  G4Material* Air = nist->FindOrBuildMaterial("G4_AIR");

  // Detector Material

  G4Material* lAr = nist->FindOrBuildMaterial("G4_lAr");
  
  const G4int NUMENTRIES = 2;
  G4double lAr_SCAT_ENERGIES[NUMENTRIES] = {9.68*eV, 9.69*eV};
  G4double lAr_SCAT[NUMENTRIES_SCAT_RINDEX] = {99.9*cm, 99.9*cm};

  G4MaterialPropertiesTable* lAr_MPT = new G4MaterialPropertiesTable();
 
  lAr_MPT -> AddProperty("RAYLEIGH", lAr_SCAT_ENERGIES, lAr_SCAT, NUMENTRIES_SCAT_RINDEX);
  
  lAr-> SetMaterialPropertiesTable(lAr_MPT);
  
  G4bool checkOverlaps = true;

       
  // World and Detector Volume Parameters
  double detectorX = 57.5*m, detectorY = 12*m, detectorZ = 7*m;

  G4double worldX = 1.2*detectorX;
  G4double worldY = 1.2*detectorY;
  G4double worldZ = 1.2*detectorZ;
  
  // World

  G4Box* solidWorld =    
    new G4Box("sWorld",                    	
       0.5*worldX, 0.5*worldY, 0.5*worldZ);	
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          
                        Air,           	     
                        "lWorld");   	    
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     
                      G4ThreeVector(),       
                      logicWorld,            
                      "pWorld",              
                      0,                    
                      false,                 
                      0,                     
                      checkOverlaps);        
      
  // Detector
   
  G4Box* solidDetector =    
    new G4Box("sDetector",                     			
        0.5*detectorX, 0.5*detectorY, 0.5*detectorZ);		
      
  G4LogicalVolume* logicDetector =                         
    new G4LogicalVolume(solidDetector,         
                        lAr,                   
                        "lDetector");        
  
  G4VPhysicalVolume* physDetector =
    new G4PVPlacement(0,                     
                    G4ThreeVector(),         
                    logicDetector,            
                    "pDetector",             
                    logicWorld,              
                    false,                   
                    0,                      
                    checkOverlaps);            
  
  /* Uniform Electric Field ( if needed )

  G4ElectricField* electricField = new G4UniformElectricField(G4ThreeVector(0.0,500.0*kilovolt/cm,0.0));

  // Create an equation of motion for this field
  G4EqMagElectricField* equation = new G4EqMagElectricField(electricField);

  G4int nvar = 9;

  // Create the Runge-Kutta 'stepper' using the efficient 'DoPri5' method
  auto stepper = new G4DormandPrince745( equation, nvar );

  // Get the global field manager
  auto fieldManager= G4TransportationManager::GetTransportationManager()->GetFieldManager();

  // Set this field to the global field manager
  fieldManager->SetDetectorField( electricField );

  G4double minStep     = 0.010*mm ; // minimal step of 10 microns

  // The driver will ensure that integration is control to give
  //   acceptable integration error
  auto integrationDriver =
     new G4IntegrationDriver<G4DormandPrince745>(minStep,
                                                 stepper,
                                                 nvar);

  G4ChordFinder* chordFinder = new G4ChordFinder(integrationDriver);
  fieldManager->SetChordFinder( chordFinder );

  logicDetector->SetFieldManager(fieldManager, true);
  */
  
  
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
