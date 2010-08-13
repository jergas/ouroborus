pushd ../birdcage/
sudo python setup.py install
popd

pushd ../worldish/
./compile.sh
popd

rm heru*

cp ../worldish/code.so .
cp ../worldish/GOD.py .
cp ../worldish/visual.py .
cp ../worldish/sound.py .
cp ../worldish/sound_globals.py .
cp ../worldish/background_sound.py .
cp ../worldish/csnd_interface.py .
cp ../worldish/Csnd_data.py .
cp ../worldish/Numeric_utils.py .
cp ../worldish/equal_temper.py .
cp ../worldish/Csnd_notes.py .
cp ../worldish/Note_methods.py .

cp ../birdcage/topology.pxd .
cp ../birdcage/neighborhood.pxd .
cp ../birdcage/rule.pxd .

python2.5 setup_lib_environment.py build_ext --inplace
