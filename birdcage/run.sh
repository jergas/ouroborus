cat messages/0.txt >> log.txt
cat messages/1.txt >> log.txt
export OPCODEDIR64=/usr/lib/csound/plugins64
cat messages/2.txt >> log.txt
echo $OPCODEDIR64 >> log.txt
cat messages/3.txt >> log.txt
python main_sequence.py build_ext --inplace 2>> log.txt
