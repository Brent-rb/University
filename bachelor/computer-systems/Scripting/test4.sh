if [ $# -eq 0 ]
	#Als het aantal parameters gelijk (-eq equals) is aan nul dan:
	then
	#Print deze shit
	echo "Argument(s) not supplied "
	#En deze shit ook printen
	echo "Usage: program.sh argument(s)"
#Anders doen we dit:
else
	#Deze shit printen
	echo "\033[1mINPUT \t\t OUTPUT\033[0m"
	#Zolang het aantal parameters verschillend (-ne not equals) is van 0 doen we:
	while [ $# -ne 0 ]
	do
		var1=$1 		#var1 = eerste argument (geen spatie tussen variabele naam en toekenning is belangrijk)
		var2= 			#var2 wordt gedeclareerd als leeg
		var3=$var1		#var3 = var1 = eerste argument
		#Zolang var1 verschillend is van 0 doen we:
		while [ $var1 -ne 0 ]
		do
			var4=$(expr $var1 % 2)  	#var4 = var1 % 2
			var2=$var4$var2				#Beschouw dit als een string (in java): var2 = var4 + var2
			var1=$(expr $var1 / 2)		#var1 = var1 / 2
		done
		echo "$var3 \t\t $var2"
		#Parameters naar links verschuiven --> aantal parameters -1 
		#voorbeeld: 	 0de iteratie: 1 4 3 2    	$# = 4
		#				1ste iteratie: 4 3 2		$# = 3
		#				 2de iteratie: 3 2  		$# = 2
		#				 3de iteratie: 2   			$# = 1
		#				 4de iteratie: 				$# = 0
		shift
		#reset van var 2 
		unset var2
	done
fi