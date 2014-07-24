#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
int main(){
	typedef enum { false, true } bool;
	int opc;
	int file=-1;	
	char content[20];
	char c[1];
	char input[20];
	char inp2[20];
	char newline[1] = {'\n'};
	char dot[2]={'.','/'};
	char nam[20];//nombre del archivo
	MENU:
	printf("----------MENU----------\n1. Abrir Archivo\n2. Escribir Archivo\n3. Buscar\n4. Listar\n5. Cerrar Archivo\nIngrese una opción:\n");
	scanf("%d", &opc);//validar bla bla
	//memset(&nam[0], 0, sizeof(nam));
	//memset(&inp2[0], 0, sizeof(inp2));
	

	switch(opc){
		case 1:		
			printf("Ingrese el nombre del archivo: (Ejemplo: myFile.txt, no es necesario el prefijo \"./\")\n");
			scanf("%s", nam);
			int i=0, s = strlen(nam);
			char buff[20];
			while(i<s){
				buff[i]=nam[i];
				i++;
			}
			i=0;
			while(i<strlen(nam)){
				nam[i+2]=buff[i];
				i++;
			}
			nam[0]=dot[0];
			nam[1]=dot[1];
			nam[s+2]='\0';
			//concatenate_string(fi, nam);
			if((file = open(nam,O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH,0666))==-1){
				perror ("Ocurrió el siguiente error:");
			}
			goto MENU;
		break;
		case 2:
			if(file!=-1){
				printf("Ingrese contenido\n");
				memset(&content[0], 0, sizeof(content));
				scanf("%s", content);
				int ss = strlen(content);
				strcat(content, newline);
				content[ss+1]='\0';//...
				write(file, content, strlen(content));
				//write(file, newline, strlen(newline));
				//close(file);
			}else{
				printf("No se ha especificado ningún archivo.\n");
			}
			goto MENU;
		break;
		case 3:
			if(file!=-1){
				close(file);
				if((file = open(nam,O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH,0666))==-1){
					perror ("Ocurrió el siguiente error:");
				}
			printf("Ingrese el nombre que desea buscar:\n");
			scanf("%s", input);
			int inpsize = strlen(input);
			int j=0,i=0;
			bool stop = false;
			int ignore =-1;
			struct stat st;
			stat(nam, &st);
			int size = st.st_size;
			bool found = false;
			while(i<size){//size of file<0
			while(read(file, c, 1)>0){
				if(c[0]==input[0]&&j>ignore&&!stop){
					ignore = j;
					stop=true;
				}
				if(ignore>-1){
					inp2[j-ignore]=c[0];
				}
				j++;
				if(ignore>=0){
					if(j-ignore==inpsize){
						break;
					}
				}
			}
			inp2[inpsize]='\0';
			if(strcmp(input,inp2)==0){
				printf("Se encontró cadena en la posición ");
				printf("%d", ignore);
				printf("\n");
				found = true;
				break;
			}else{
				stop=false;
			}
			i++;
			}
			if(!found)
				printf("No se encontró.\n");
			}else{
				printf("No se ha especificado ningún archivo.\n");
			}
			
    		goto MENU;
		break;
		case 4:
			if(file!=-1){
				close(file);
				if((file = open(nam,O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH,0666))==-1){
					perror ("Ocurrió el siguiente error:");
				}
				while(read(file, c, 20)>0)
					printf("%s", c);
			}else{
				printf("No se ha especificado ningún archivo.\n");
			}
    		goto MENU;
		break;
		case 5:
			if(file!=-1){
				close(file);
			}
		break;
		default:
		//an error occurs!
		break;
	}
}