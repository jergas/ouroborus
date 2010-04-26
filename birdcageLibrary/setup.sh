pushd ../birdcage/
./compile.sh
popd
cp ../birdcage/*.so .
rm kristos*
cp ../birdcage/neighborhood.pxd .
cp ../birdcage/topology.pxd .
cp ../birdcage/rule.pxd .
cp ../birdcage/visual.py .
cp ../birdcage/sound_globals.py .
cp ../birdcage/background_sound.py .
cp ../birdcage/csnd_interface.py .
cp ../birdcage/Csnd_data.py .
cp ../birdcage/Numeric_utils.py .
cp ../birdcage/equal_temper.py .
cp ../birdcage/Csnd_notes.py .
cp ../birdcage/Note_methods.py .
python setup_lib_environment.py build_ext --inplace