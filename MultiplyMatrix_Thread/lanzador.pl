#!/usr/bin/perl
#Fichero de automatización de ejecución por lotes de un ejecutable
#dados parametros de entrada

$repeticiones = 30;
@ejecutables = ("matrices1");
@matrizSize = ("4000");
@threadSize = ("2");
$path = "/home/mateo/Documents/version_3/";

foreach $exe (@ejecutables){
	foreach $size (@matrizSize){
		foreach $thread (@threadSize){
			$fichero = "$path"."soluciones/"."$exe"."-size"."$size"."-thread"."$thread";
			#print("$fichero \n");
			for($i = 0; $i < $repeticiones; $i++){
				#print("$path$exe $size \n");
				system("$path$exe $size $thread >> $fichero");		
			}

		}
	
	}

}

exit(1);
