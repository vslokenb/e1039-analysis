## Fun4AllVectEventInputManager
The `Fun4AllVectEventInputManager` is an input file manager in the Fun4All framework, designed to manage and register various types of input data from a simple vector-based ROOT file, such as triggers, hits, and event information, into the framework's event processing system.

## Fun4AllVectEventOutputManager
The `Fun4AllVectEventOutputManager` is an output file manager in the Fun4All framework, designed to store triggers, hits, and event information in a vector-based file format.

## Goal
The Fun4All framework does not support random indexing in the Fun4All event processing server. Therefore, translating the data into a convenient format enables us to perform pre- and post-processing using the input/output managers.

### Registered Branches
- `EventID`
- `RunID`
- `SpillID`
- `fpga_triggers`
- `nim_triggers`
- `Intensity`
- `DetectorID`
- `ElementID`
- `DriftDistance`
- `TdcTime`
- `hit_in_time`
- `Trig_DriftDistance`
- `Trig_ElementID`
- `Trig_TdcTime`
- `Trig_hit_in_time`

``` Compilation
source Fun4AllVectFileManager ../setup.sh
cmake-this
make-this
```

### Uses

1. **Convert the DST file to a vector file**  
   If you'd like to convert the DST file to a vector format for easier event processing, use the following commands:

   ```bash
   cd Convert
   root -b ConvertToVect.C
   ```
2. **Run the Pre- or Post-Process Data in the Fun4All Server**

   After completing the event processing, if you would like to add the triggers, hits, and event information into the Fun4All framework's event processing server, follow these steps:

   Go to the `work_reco` directory, where you will find two subdirectories:

   - **(i) Reco_DST_in**:  
     Run `Fun4Sim.C` and make sure to use the correct input file in DST format. (This directory was created to verify that both input file systems yield the same results in the output.)

   - **(ii) Vect_DST_in**:  
     Run `Fun4Sim.C` and make sure to use the correct input file in vector format, which you obtained from the Convert directory. You can definitely perform preprocessing as required for your analysis before registering the data into the Fun4All framework and running reconstruction and vertexing.

