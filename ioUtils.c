#include <stdio.h>

#include "ioUtils.h"



int setLayout ( struct layout* myLayout, int size)
{
	int howMany=2;
	
	
	(*myLayout).photo[0].dim.x=300;
	(*myLayout).photo[0].dim.y=200;
	(*myLayout).photo[1].dim.x=300;
	(*myLayout).photo[1].dim.y=200;
 
	(*myLayout).photo[0].pos.x=10;
	(*myLayout).photo[0].dim.y=10;
	(*myLayout).photo[1].dim.x=320;
	(*myLayout).photo[1].dim.y=10;
	
	(*myLayout).layoutDim.x = 630;
	(*myLayout).layoutDim.y = 220;
	
	(*myLayout).col.r=200;
	(*myLayout).col.g=20;
	(*myLayout).col.b=0;
	
	
	return 1;
}

int evaluateNumPhoto(int numPhoto)
{
	printf ("\e[35mevluateNumPhoto ancora da fare!!\e[0m\n\n", numPhoto);
}

int printASCIIArt(int numPhoto)
{
	switch (numPhoto)
	{
		case 2:
			printf("\nA):\e[34m\n\t\t _____________\n\t\t|      |      |\n\t\t|      |      |\n\t\t|      |      |\n\t\t|      |      |\n\t\t|      |      |\n\t\t|______|______|\n\n\e[0m");
			printf("\nB):\e[34m\n\t\t _____________\n\t\t|             |\n\t\t|             |\n\t\t|             |\n\t\t|_____________|\n\t\t|             |\n\t\t|             |\n\t\t|             |\n\t\t|_____________|\n\n\e[0m");
			printf("\nC):\e[34m\n\t\t _________________\n\t\t| ______   ______ |\n\t\t||      | |      ||\n\t\t||      | |      ||\n\t\t||      | |      ||\n\t\t||      | |      ||\n\t\t||      | |      ||\n\t\t||______| |______||\n\t\t|_________________|\n\n\e[0m");
			printf("\nC):\e[34m\n\t\t ______________\n\t\t| ____________ |\n\t\t||            ||\n\t\t||            ||\n\t\t||            ||\n\t\t||____________||\n\t\t| ____________ |\n\t\t||            ||\n\t\t||            ||\n\t\t||            ||\n\t\t||____________||\n\t\t|______________|\n\n\e[0m");
			
			break;
		case 3:
			printf ("\e[35mError: ASCII art for %i not found\e[0m\n\n", numPhoto);
			
			
			break;
		case 4:
			printf ("\e[35mError: ASCII art for %i not found\e[0m\n\n", numPhoto);
			
			
			break;
		case 5:
			
			printf ("\e[35mError: ASCII art for %i not found\e[0m\n\n", numPhoto);
			
			break;
		case 6:
			
			
			printf ("\e[35mError: ASCII art for %i not found\e[0m\n\n", numPhoto);
			
			break;
		default:
			printf ("\e[31mError in retrieving ASCII art", numPhoto);
			return -1;
	
	}
	return 1;
}

int retrieveInput(struct layout* myLayout, int size)
{
	int ret;
	int numPhoto;
	
	numPhoto=0;
	printf ("\e[36m\nBenvenuto in collage maker\e[0m\n\n");
	
	while (1) {
		printf("inserire il numero di foto che si desidera comporre e premere invio:");
		scanf ("%i", &numPhoto);
		ret = evaluateNumPhoto(numPhoto);
		if (numPhoto<=MAX_NUM_PHOTO && numPhoto>=MIN_NUM_PHOTO & ret>0)
			break;
		
		if (ret<1)
			printf("i caratteri immessi non sono validi\n\n");
		else if (numPhoto>=MAX_NUM_PHOTO)
			printf("Non � possibile inserire pi� di 6 foto\n\n");
		else
			printf("Non � possibile inserire meno di 2 foto\n\n");
	};
	
	(*myLayout).number= numPhoto;
	printf("\nQuesti sono i layout disponibili:\n");
	ret = printASCIIArt(numPhoto);
	if (ret<0)
	{
		printf ("\e[31mError: ASCII art not found\e[0m\n\n");
	}


	printf ("\e[35mAttenzione!!\n\nBisogna finire di implementare ancora tutta la parte di raccolta proferenze dall'utente!!\e[0m\n\n");
	
	ret= setLayout(myLayout, size);
	if (ret<0)
	{
		printf("Error!");
		return -1;
	}
}


int createOutputImage(gdImagePtr im){
	FILE *pngout, *jpegout;
	
	/* Open a file for writing. "wb" means "write binary", important
    under MSDOS, harmless under Unix. */
	pngout = fopen("test.png", "wb");

	/* Do the same for a JPEG-format file. */
	jpegout = fopen("test.jpg", "wb");

	/* Output the image to the disk file in PNG format. */
	gdImagePng(im, pngout);

	/* Output the same image in JPEG format, using the default
    JPEG quality setting. */
	gdImageJpeg(im, jpegout, -1);

	/* Close the files. */
	fclose(pngout);
	fclose(jpegout);

	/* Destroy the image in memory. */
	gdImageDestroy(im);
	
	return 1;
}