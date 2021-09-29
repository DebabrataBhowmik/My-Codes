#!/bin/bash
#for (( c=1; c<=5; c+0.1 ))
#for i in {10..2.3}
#rm file_append.txt

LambdaArray=(0.00000001 0.00001)
#gDarkArray=(0.5 0.6 0.7 0.8 0.9 )
MchiArray=(0.00000085 0.0000085 0.000085 0.00085 0.0085 0.085 0.85 8.5 85)
MBXArray=(500 1000)
MHSArray=(1090 10900 109000 1090000)

mnu=0.00000000001
vev=246.21965
ynu=0.000001


for valueLambda in "${LambdaArray[@]}";
do
    #    for valuegDark in "${gDarkArray[@]}";
    #    do
    for valueMBX in "${MBXArray[@]}";
    do
	vs=`echo 2*$mnu / $ynu / $vev / $valueLambda | bc -l`
	valuegDark=`echo $valueMBX / $vs | bc -l`
	if (( $(echo "$valuegDark > 10.0" | bc -l) )); then
	    continue
	fi
	for valueMchi in "${MchiArray[@]}";
	do
	    ychi=`echo "sqrt(2)"* $valueMchi / $vs | bc -l`	    
	    if (( $(echo "$ychi > 10.0" | bc -l) )); then
		continue
	    fi  
	    for valueMHS in "${MHSArray[@]}";
	    do
		lams=`echo $valueMHS*$valueMHS / 2 / $vs / $vs | bc -l`
		if (( $(echo "$lams > 10.0" | bc -l) )); then
		    continue
		fi
		echo "$valueLambda $valuegDark $valueMchi $valueMBX $valueMHS";
		sed -e "s/Lambda_val/$valueLambda/g"\
		    -e "s/gDark_val/$valuegDark/g"\
		    -e "s/Mchi_val/$valueMchi/g"\
		    -e "s/MBX_val/$valueMBX/g"\
		    -e "s/MHS_val/$valueMHS/g" data_template.par > data_replace.par
		./main data_replace.par
	    done
	done
    done	
    #done	    
done


##a[100]

#for value1 in $(#seq 1.0 .01 1.1)
#do
#    echo $value1
#    for value2 in $(#seq 2.0 .01 2.1)
#    do
#	sed -e "s/REPLACE1/$value1/g"\
#	    -e "s/REPLACE2/$value2/g" mssms_template.par > mssms.par	
##	./main mssms.par
#    done
#done

