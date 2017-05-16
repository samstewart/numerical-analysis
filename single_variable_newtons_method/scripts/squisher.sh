#!/bin/bash

# simple script that runs my approximator on a list of test files provided by jeff and output the results
TESTDIR=test_files
OUTPUTDIR=output_files
COMBINEDFILE=results.txt

echo "Compiling my program...."

cd ../
make clean

make

cd scripts

echo "Cleaning up old output files...."
rm $OUTPUTDIR/*.output

echo "Running my approximator on the test files...."

for FILE in $TESTDIR/*.test;
do
	echo "Running on $FILE and placing output in $OUTPUTDIR/$FILE.output..."
	../newtons_method < $FILE > $FILE.output &
	
	sleep 2
done

echo "Moving result files.."
mv $TESTDIR/*.output $OUTPUTDIR/

echo "Combining results...."
cat $OUTPUTDIR/*.output > $COMBINEDFILE

echo "Sending to printer..."

# TODO: need to send this to the printer
