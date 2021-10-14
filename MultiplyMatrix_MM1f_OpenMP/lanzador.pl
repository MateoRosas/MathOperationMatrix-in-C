#!/usr/bin/perl
#Fichero de automatización de ejecución por lotes de un ejecutable
#dados parametros de entrada

$repeticiones = 30;
@ejecutables = ("matrices1");
@matrizSize = ("100", "200", "300", "400", "500", "600", "800", "1000", "2000","4000", "6000");
@threadSize = ("1","2","4");
$path = "/home/mateo/Documents/ComputacionParalelayDistribuida/Openmp/OpenmpVersion2/";

foreach $exe (@ejecutables){
	foreach $size (@matrizSize){
		foreach $thread (@threadSize){
			$fichero = "$path"."soluciones2/"."$exe"."-size"."$size"."-thread"."$thread";
			#print("$fichero \n");
			for($i = 0; $i < $repeticiones; $i++){
				#print("$path$exe $size \n");
				system("$path$exe $size $thread >> $fichero");		
			}

		}
	
	}

}

exit(1);
