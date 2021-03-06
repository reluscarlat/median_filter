Ultima varianta functionala a proiectului este "varianta_cod_functional_22-12-2018".

Mod de implemetare:
	Punctul de plecare a fost un cod serial pe care l-am imbunatatit prin modificarea metodei de citire a imaginii.
	Pentru a evita problema acesarii datelor procesate de catre mai multe threaduri am ales sa ne impartim imaginea procesata in chunk-uri pe care le vom procesa in paralel.
	Am citit imaginea pe n bucati (n - nr de threaduri). Fiecare bucata are incorporata suplimentar date din bucata ce o precede pentru a asigura procesarea granitelor dintre aceste sectiuni ale imaginii.
	Fiecare thread executa filtrul median pe portiunea lui de imagine. Scrierea si citirea fisierului se fac de catre threadul master. Masurarea perfomatelor (timpului de executie) se realizeaza doar pe sectiunea de cod paralela si se exporta intr-un fisier extern pentru a realiza graficele.
	Toate implemetarile (openmp,pthread,mpi) au fost realizate in aceeasi maniera.
	S-a incercat imbunatatirea perfomatelor si lizibilitatea codului pentru fiecare implemetare in parte.
	
	Observatii:
	-openmp are cea mai mare lizibilitate si cea mai usoara metoda de a paraleliza codul rapid si eficient
	-pthread - am "fortat" fiecare thread sa stea pe un procesor separat pentru a imbunatatii perfomatele
	-mpi - mai dificil de implementat si lizibilitatea scazuta 
	
Mod de testare:
	Am verificat integritatea imaginii procesate si am verificat ca imaginea procesata paralel nu difera de cea procesata de programul serial cu ajutorul comenzii diff.
	Am rulat progamele pe imagini de dimensiuni diferite pentru a verifica imbunatatirea adusa de paralelizarea codului
	Am analizat scalabilitatea algoritmului pe o imaginea de 16380 x 16380 cu numar diferit de threaduri.
