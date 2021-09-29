cp param_card.dat.template param_card3.dat.template
cat relic.txt |while read valueLambda valuegDark valueMchi valueMBX valueMHS valueOmega; do
#    echo "$valueLambda $valuegDark $valueMchi $valueMBX $valueMHS "
    sed -e "s/] #Lambda/$valueLambda, ] #Lambda/g"\
	-e "s/] #gdark/$valuegDark, ] #gdark/g"\
	-e "s/] #Mchi/$valueMchi, ] #Mchi/g"\
	-e "s/] #MBX/$valueMBX, ] #MBX/g"\
	-e "s/] #MHS/$valueMHS, ] #MHS/g" param_card3.dat.template > param_card2.dat.template
    #done < "input.txt"
    mv param_card2.dat.template param_card3.dat.template
done
    sed -e "s/, ] #Lambda/ ] #Lambda/g"\
        -e "s/, ] #gdark/ ] #gdark/g"\
        -e "s/, ] #Mchi/ ] #Mchi/g"\
        -e "s/, ] #MBX/ ] #MBX/g"\
        -e "s/, ] #MHS/ ] #MHS/g" param_card3.dat.template > param_card.dat
rm param_card3.dat.template
