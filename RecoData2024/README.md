# e1039-analysis/RecoData2024

A sample program to analyze the officially-reconstructed commissioning data.
It can also carry out the reconstruction with customizable configurations.
It analyzes the good runs and spills listed in `work/list_run_spill.txt`, which were defined in [DocDB 10854-v2](https://seaquest-docdb.fnal.gov/cgi-bin/sso/ShowDocument?docid=10854&version=2).


## Shell Environment and Source Code

This program depends on the E1039 software.
You need source `setup.sh` every time you open a new text terminal to use the program.
A sub-directory, `src/`, contains a SubsysReco module for analysis.
It should be built via two commands, `cmake-this` and `make-this`, which are defined in `setup.sh`.
They can be executed at any directory.

```
cd /path/to/your/e1039-analysis/RecoData2024
source setup.sh
cmake-this
make-this
```


## Analysis of Officially-Reconstructed Data

The officially-reconstructed data are stored under `/pnfs/e1039/persistent/users/spinquestpro/commisioning_recodata/`.
A set of scripts/macros for analysis is prepared under `work_ana/`.
Its usage is described in `work_ana/README.md`.


## Reconstruction of Data

A set of scripts/macros to reconstruct the commissioning data is prepared under `work_reco/`.
Its usage is described in `work_reco/README.md`.
It reads the spill-level data files stored in `/pnfs/e1039/persistent/users/kenichi/dst`.


## Contact

Kenichi Naknao <knakano0524@gmail.com>
