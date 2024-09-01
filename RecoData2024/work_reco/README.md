# e1039-analysis/RecoData2024/work_reco

Te spill-level data files are stored in `/pnfs/e1039/persistent/users/kenichi/dst`.
These data are used in this directory, as selected by `DIR_DST` in `gridsub.sh`.


## Test of Reconstruction Using a Few Runs

The procedure below will analyze the 4th good run to draw basic dimuon variables.

```
./gridsub.sh -j 4-4
root -b 'AnaEventTree.C("scratch/reco")'
display result/h1_m.png &
```

Here are what happens in each step:
- `gridsub.sh` sets up a subdirectory (per run) to analyze DST files of the given run(s).
    - The option `-j 4-4` selects the 4th run (listed in `list_run_spill.txt`).
    - Analyzing one run is directed by `gridrun.sh` and `Fun4All.C`.
    - A SubsysReco module, `AnaDimuon`, is registered by default.
    - The analysis runs on local computer by default (i.e. when `-g` is not given).
    - Extracted dimuon parameters are stored in `scratch/default/run_*/out/output.root` as TTree.
- `AnaEventTree.C` reads the TTree files to draw histograms.
    - Histograms are saved under `result/`.


## Reconstruction of All Runs

You can process all runs/spills by adjusting the `-j` option of `gridsub.sh`.
The `-g` option let you use the Grid computing.
You first submit jobs for the first 10 spills;
```
kinit
./gridsub.sh -g -j 1-10
```

You might execute `jobsub_q --group spinquest --user=$USER` to monitor the job status.
Once you confirm that the jobs are running fine, you submit more jobs for the remaining runs;
```
./gridsub.sh -g -j 11-200
./gridsub.sh -g -j 201-1000
./gridsub.sh -g -j 1001-
```

The output files are stored under `data/` in case Grid is used.
You can analyze them once (almost) all jobs finish;
```
root -b AnaEventTree.C
display result/h1_m.png &
```


## Reconstruction Condition

The reconstruction condition is programmed in `Fun4All.C`.
Thus you need look into the macro to understand the default condition.
You might modify the macro as you need.


## Re-Analysis of Reconstructed Data

The analysis defined in `AnaDimuon` is done together with the reconstruction.
When you need reanalyzed the reconstructed data, you can use `work_ana/`.
