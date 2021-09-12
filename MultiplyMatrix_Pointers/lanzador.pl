#!/usr/bin/perl
#Fichero de automatización de ejecución por lotes de un ejecutable
#dados parametros de entrada

$repeticiones = 24;
@ejecutables = ("matrices1");
@matrizSize = ("4000");
$path = "/home/ubuntu/Documents/version3/";

foreach $exe (@ejecutables){
	foreach $size (@matrizSize){
		$fichero = "$path"."soluciones/"."$exe"."-size"."$size";
		#print("$fichero \n");
		for($i = 0; $i < $repeticiones; $i++){
			#print("$path$exe $size \n");

			system("$path$exe $size >> $fichero");		

		}

	
	}

}

exit(1);
