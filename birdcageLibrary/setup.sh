pushd ../birdcage/
./compile.sh
popd
cp ../birdcage/*.so .
rm kristos*
cp ../birdcage/neighborhood.pxd .
cp ../birdcage/topology.pxd .
cp ../birdcage/rule.pxd .
python setup_lib_environment.py build_ext --inplace