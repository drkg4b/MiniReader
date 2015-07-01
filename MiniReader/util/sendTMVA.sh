#!/bin/bash
# usage: ssh -t gbert@bublx28.fysik.su.se 'bash -is' < sendTMVA.sh

cd /data/gbert/MonoJetAnalysis/MiniReader/
setupATLAS
rcSetup

cd TMVAStudies

# Check if there are already files in the dir
if [ "ls -A ." ]; then

    mkdir -p backup

    # Moving existing files:
    find . -maxdepth 0 -type f -exec mv '{}' backup \;
fi

# Note: to have the process fork and quit the ssh session it is needed to close
# all the files descriptors thus the < /dev/null (never wait for any input) >
# out.log and 2>&1 (redirect the stderr to stdout).

bkg_samples=()

bkg_samples+=(../outDir-TMVA/hist-ttbarSamples.root)
bkg_samples+=(../outDir-TMVA/hist-WenuSamples.root)
bkg_samples+=(../outDir-TMVA/hist-WmunuSamples.root)
bkg_samples+=(../outDir-TMVA/hist-WtaunuSamples.root)
bkg_samples+=(../outDir-TMVA/hist-ZeeSamples.root)
bkg_samples+=(../outDir-TMVA/hist-ZmumuSamples.root)
bkg_samples+=(../outDir-TMVA/hist-ZnunuSamples.root)
bkg_samples+=(../outDir-TMVA/hist-ZtautauSamples.root)

# Compressed spectra:
runSensitivityTMVA ../outDir-TMVA/hist-Compressed_450_435.root ${bkg_samples[@]} n_jet30 < /dev/null > Compressed_450_435_n_jet30.log 2>&1 &
runSensitivityTMVA ../outDir-TMVA/hist-Compressed_450_435.root ${bkg_samples[@]} n_jet40 < /dev/null > Compressed_450_435_n_jet40.log 2>&1 &
runSensitivityTMVA ../outDir-TMVA/hist-Compressed_450_435.root ${bkg_samples[@]} n_jet50 < /dev/null > Compressed_450_435_n_jet50.log 2>&1 &

runSensitivityTMVA ../outDir-TMVA/hist-Compressed_450_425.root ${bkg_samples[@]} n_jet30 < /dev/null > Compressed_450_425_n_jet30.log 2>&1 &
runSensitivityTMVA ../outDir-TMVA/hist-Compressed_450_425.root ${bkg_samples[@]} n_jet40 < /dev/null > Compressed_450_425_n_jet40.log 2>&1 &
runSensitivityTMVA ../outDir-TMVA/hist-Compressed_450_425.root ${bkg_samples[@]} n_jet50 < /dev/null > Compressed_450_425_n_jet50.log 2>&1 &

# D5
# runSensitivityTMVA ../outDir-TMVA/hist-D5.root ../outDir-TMVA/hist-all_bkg.root n_jet30 < /dev/null > D5_n_jet30.log 2>&1 &
# runSensitivityTMVA ../outDir-TMVA/hist-D5.root ../outDir-TMVA/hist-all_bkg.root n_jet40 < /dev/null > D5_n_jet40.log 2>&1 &
# runSensitivityTMVA ../outDir-TMVA/hist-D5.root ../outDir-TMVA/hist-all_bkg.root n_jet50 < /dev/null > D5_n_jet50.log 2>&1 &

exit
