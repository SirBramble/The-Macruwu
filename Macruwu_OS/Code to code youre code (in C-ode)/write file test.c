#include <stdio.h>

int main(void){
	FILE * fp;
   	fp = fopen ("Mapping.h", "w+");
	fprintf(fp, "%cifndef MAPPING_H_\n%cdefine MAPPING_H_\n\n", '#', '#');
	fprintf(fp, "%cinclude <stdbool.h>\n", '#');
	fprintf(fp, "%cinclude <stdint.h>\n", '#');
	fprintf(fp, "%cinclude <Arduino.h>\n", '#');
	fprintf(fp, "%cinclude <Wire.h>\n", '#');
	fprintf(fp, "%cifdef USE_TINYUSB\n", '#');
	fprintf(fp, "%cinclude <Adafruit_TinyUSB.h>\n", '#');
	fprintf(fp, "%cendif\n\n", '#');
   	for(int i = 0; i < 32; i++){
		fprintf(fp, "void button%d();\n",i+1);
		}
	fprintf(fp, "void action(uint8_t button);\n");
	fprintf(fp, "#endif");
	fprintf(fp, "%c* MAPPING_H_ *%c", '/', '/');
   	fclose(fp);
   	//char c = '"';
	fp = fopen("Mapping.cpp", "w+");
	fprintf(fp, "%cinclude %cMapping%ch%c\n\n", '#','"', '.', '"');
   	for(int i = 0; i < 32; i++){
		fprintf(fp, "void button%d(){\n",i+1);
		fprintf(fp, "\t\n");
		fprintf(fp, "\tSerial.println(%cButton%d%c);\n",'"',i+1, '"');
		fprintf(fp, "}\n\n");
		}
	fprintf(fp, "void action(uint8_t button){\n");
	fprintf(fp, "\tbutton++;\n");
	fprintf(fp, "\tswitch(button){\n");
	for(int i = 0; i < 32; i++){
		fprintf(fp, "\t\tcase %d:\n", i+1);
		fprintf(fp, "\t\t\tbutton%d();\n", i+1);
		fprintf(fp, "\t\tbreak;\n\n");
		}
	fprintf(fp, "\t}\n");
	fprintf(fp, "}");
   	fclose(fp);
   	return(0);
	

}