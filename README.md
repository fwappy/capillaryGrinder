## Dependencies:

TcMenu by The Coders Corner


## Pseudocode:
```
Main menu:
    • Calibrate
    • Grind Capillary
    • Face Capillary 
    • Face Chip

Calibrate:
    • Manual movement
        ◦ Jog up/down
            ▪ 1 micron
            ▪ 10 micron
            ▪ 100 micron
            ▪ 1000 micron
    • Zero: user gets capillary somewhat close to plate manually
            ▪ Software travels down at 10 micron per second until sound signal digital output of “1” is received. 
                • Stops
                • Moves up 10 microns
                • Lowers at 1 micron a second until sound signal “1” is sent.
                    ◦ Stops
Grind Capillary
    • Set parameters
        ◦ Inner diameter - resolution of 0.1 micron
            ▪ ID = “user entry”
        ◦ Outer diameter - resolution of 0.1 micron
            ▪ OD = “User entry”
        ◦ Angle degrees
            ▪ Angle = “user entry”
            ▪ //angle of capillary to grinding plate
        ◦ Face width
            ▪ FaceWidth = “user entry”
            ▪ // width of face at pointed circular face at sharpened capillary end
    • Grind is initiated
        ◦ Did you calibrate/zero grinder?
            ▪ Yes/no
                • Yes - begin grind
                • No - begin grind but run Zero code from above first
        ◦ Grind?
            ▪ Yes/no
                • No - exit to main menu
            ▪ Yes
                • Calculate GrindDepthRemaining 
                    ◦ double AngleRad = Angle * M_PI / 180;
                    ◦ int R = (OD - ID) / 2;
                    ◦ GrindDepthRemaining = R * cos(AngleRad) - FaceWidth;
                • Turn on capillary motor
                • Wait GrindDelayTime (default value is 20 seconds)
                • If (GrindDepthRemaining/GrindStepDistance > 1)
                    ◦ StepDistance = GrindStepDistance
                    ◦ //(default value is 10 microns)
                    ◦ Move down StepDistance
                    ◦ At GrindSpeed rate 
                    ◦ //(default is 100 microns/second)
                    ◦ GrindDepthRemaining = GrindDepthRemaining - StepDistance
                    ◦ Wait GrindDelayTime
                • Else if (GrindDepthRemaining/GrindStepDistance < 1)
                    ◦ StepDistance = GrindDepthRemaining
                    ◦ Move down StepDistance
                    ◦ At GrindSpeed rate 
                    ◦ //(default is 100 microns/second)
                    ◦ GrindDepthRemaining = GrindDepthRemaining - StepDistance
                    ◦ Wait GrindDelayTime
                    ◦ Move up 20,000 microns At TravelSpeed
                        ▪ //default value is 2500 microns/second
                    ◦ Give Grind complete message
                        ▪ OK
                            • Return to main menu
                • Else
                    ◦ Printscreen = “error grind distance”
Face Capillary
    • Set Parameters:
        ◦ Amount to face off?
            ▪ FaceDepthRemaining = “user entry”
        ◦ //in microns
        ◦ Capillary motor on or off?
            ▪ If yes
                • CapillaryRun = True
            ▪ If no
                • CapillaryRun = False
    • Grind
        ◦ Did you calibrate/zero grinder?
            ▪ Yes/no
                • Yes - continue
                • No - continue but run Zero code from above first
        ◦ Grind?
            ▪ Yes/no
                • No - exit to main menu
            ▪ Yes
                • If CapillaryRun = True
                    ◦ Turn on Capillary motor
                • Wait FaceDelayTime
                • //default value is 60 seconds
                • If (FaceDepthRemaining/FaceStepDistance > 1)
                    ◦ StepDistance = FaceStepDistance
                    ◦ //(default value is 1 microns)
                    ◦ Move down StepDistance
                    ◦ At FaceSpeed rate 
                    ◦ //(default is 1 microns/second)
                    ◦ FaceDepthRemaining = FaceDepthRemaining - StepDistance
                    ◦ Wait FaceDelayTime
                • Else if (FaceDepthRemaining/FaceStepDistance < 1)
                    ◦ StepDistance = FaceDepthRemaining
                    ◦ Move down StepDistance
                    ◦ At FaceSpeed rate 
                    ◦ //(default is 1 microns/second)
                    ◦ FaceDepthRemaining = FaceDepthRemaining - StepDistance
                    ◦ Wait GrindDelayTime
                    ◦ Move up 20,000 microns At TravelSpeed
                        ▪ //default value is 2500 microns/second
                    ◦ Give Grind complete message
                        ▪ OK
                            • Return to main menu
                • Else
                    ◦ Printscreen = “error face distance”
Face Chip:
    • Set Parameters:
        ◦ SmallestWidth
        ◦ //resolution 0.1 microns
        ◦ //width at the face of the chip
        ◦ LargestWidth
        ◦ //width at the end of the chip taper
        ◦ //resolution 0.1 microns
        ◦ TaperAngle
        ◦ //resolution 0.1 degrees
        ◦ //angle of taper on chip
        ◦ TaperHeight
        ◦ //resolution 0.1 microns
        ◦ //Height perpendicular to the chip face from the beginning of taper to the end
        ◦ FlatChannelDepth
        ◦ //Depth of face channel along which there is not taper
        ◦ //resolution 1 micron
    • Amount to face off?
        ◦ FaceDepthRemaining = “user entry”
        ◦ //resolution of up to 0.1 microns
        ◦ //values range 0 - 500 micron
    • Desired Final Channel Width
        ◦ Requested = “user entry”
            ▪ If (Requested > LargestWidth)
                • Too large
                    ◦ Ok
                • Return to Desired Final Channel Width question
            ▪ Else if (Requested < SmallestWidth)
                • Too small
                    ◦ Ok
                • Return to Desired Final Channel Width
            ▪ Else
                • Adjacent = Requested - SmallestWidth
                • FaceDepthRemaining = Adjacent*(tan(TaperAngle))
        ◦ If (FaceDepthRemaining > TaperHeight)
            ▪ Printscreen = “Error in Height Calculation”
        ◦ Did you calibrate/zero grinder?
            ▪ Yes/no
                • Yes - continue
                • No - continue but run Zero code from above first
        ◦ Begin Facing?
            ▪ Yes/no
                • No
                    ◦ Return to main menu
                • Yes
                    ◦ Wait ChipDelayTime
                    ◦ //Default is 30 seconds
                    ◦ Move down FlatChannelDepth
                    ◦ Wait ChipDelayTime
                    ◦ If (ChipDepthRemaining/ChipStepDistance > 1)
                        ▪ StepDistance = ChipStepDistance
                        ▪ //(default value is 5 microns)
                        ▪ Move down StepDistance
                        ▪ At ChipSpeed rate 
                        ▪ //(default is 1 microns/second)
                        ▪ ChipDepthRemaining = ChipDepthRemaining - StepDistance
                        ▪ Wait ChipDelayTime
                    ◦ Else if (ChipDepthRemaining/ChipStepDistance < 1)
                        ▪ StepDistance = ChipDepthRemaining
                        ▪ Move down StepDistance
                        ▪ At ChipSpeed rate 
                        ▪ //(default is 1 microns/second)
                        ▪ ChipDepthRemaining = ChipDepthRemaining - StepDistance
                        ▪ Wait ChipDelayTime
                        ▪ Move up 20,000 microns At TravelSpeed
                            • //default value is 2500 microns/second
                        ▪ Give Grind complete message
                            • OK
                                ◦ Return to main menu
                    ◦ Else
                        ▪ Printscreen = “error chip distance”
```
