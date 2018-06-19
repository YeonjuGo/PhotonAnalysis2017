# PhotonAnalysis2017

This repository works combined with **ElectroWeak-Jet-Track-Analyses**(*https://github.com/CmsHI/ElectroWeak-Jet-Track-Analyses*) repository. 
You will have to clone **ElectroWeak-Jet-Track-Analyses** repository in this repository before you run any codes in here. 

## Analysis structure

The basic analysis workflow is

1. Using the code in the **ElectroWeak-Jet-Track-Analyses/ForestSkimmers** folder, take an input HiForest file and make a *skim* of photon RAA.
2. Use the code in the **efficiency** folder to make photon efficiency. Reconstruction and isolation efficiencies will be obtained seperately from each macros. 
3. Use the code in the **purity** folder to obtain photon purity.
4. Use the code in the **results** folder to make the physics observables root files: RAA and dN/dpT.
5. Use the code in the **systematics** folder to calculate total systematics. You can draw systematic summary plots here. 
5. Use the code in the **plotting** folder to produce the final publish-quality plots from the root files. 

All cuts applied at every step come from files in the **phoRaaCuts** folder. 
