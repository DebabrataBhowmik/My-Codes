#!/bin/bash
#for (( c=1; c<=5; c+0.1 ))
#for i in {10..2.3}
#rm file_append.txt

LambdaArray=(0.000001 0.000002 0.000003 0.000004 0.000005 0.000006 0.000007 0.000008 0.000009 0.00001)
gDarkArray=(0.5 0.6 0.7 0.8 0.9 )
MchiArray=(0.00000085 0.0000085 0.000085 0.00085 0.0085 0.085 0.85 8.5 85)
MBXArray=(731 7310 73100 731000)
MHSArray=(1090 10900 109000 1090000)

for valueLambda in "${LambdaArray[@]}";
do
    for valuegDark in "${gDarkArray[@]}";
    do
	for valueMchi in "${MchiArray[@]}";
	do
	    for valueMBX in "${MBXArray[@]}";
	    do
		for valueMHS in "${MHSArray[@]}";
		do
		    echo "$valueLambda $valuegDark $valueMchi $valueMBX $valueMHS";
		    sed -e "s/Lambda_val/$valueLambda/g"\
			-e "s/gDark_val/$valuegDark/g"\
			-e "s/Mchi_val/$valueMchi/g"\
			-e "s/MBX_val/$valueMBX/g"\
			-e "s/MHS_val/$valueMHS/g" data_template.par > data_replace.par
		    #	./main data_replace.par
		done
	    done
	done	
    done	    
done


##a[100]

#for value1 in $(seq 1.0 .01 1.1)
#do
#    echo $value1
#    for value2 in $(seq 2.0 .01 2.1)
#    do
#	sed -e "s/REPLACE1/$value1/g"\
#	    -e "s/REPLACE2/$value2/g" mssms_template.par > mssms.par	
##	./main mssms.par
#    done
#done

