cd ../birdcage/
pwd
sudo su -c "python setup.py install"
cd ../worldish/
pwd
python setup_code.py build_ext --inplace
mkdir creatures