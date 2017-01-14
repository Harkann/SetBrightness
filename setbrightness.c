#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char current_brightness_path[] = "/sys/class/backlight/intel_backlight/actual_brightness";
char max_brightness_path[] = "/sys/class/backlight/intel_backlight/max_brightness";
char edit_brightness_path[] =  "/sys/class/backlight/intel_backlight/brightness";

int help (char *cmd){
	printf("usage : %s [OPTION] {VALUE}\n",cmd);
	printf("OPTIONS :\n\t");
	printf("--inc or + {VALUE} : substract VALUE to the current brightness\n\t");
	printf("--dec or - {VALUE} : add VALUE to the current brightness\n\t");
	printf("--get : display current_brightness/max_brightness\n\t");
	printf("--help or -h : display this help\n");
	return 0;
}

int getbrightness(char file_path[]){
	int brightness;
	FILE * bright_file;
	bright_file = fopen(file_path, "r");
	fscanf(bright_file, "%d", &brightness);
	fclose(bright_file);
	return brightness;
}

int setbrightness(char file_path[], int arg, int value){
	int current_brightness ;
	int max_brightness ;
	current_brightness = getbrightness(current_brightness_path);
	max_brightness = getbrightness(max_brightness_path);
	FILE * bright_file;
	bright_file = fopen(file_path, "w");
	if (arg == 0){
		if (value > max_brightness){
			printf("%d", max_brightness);
			fprintf(bright_file, "%d", max_brightness);
			printf("value too high : set to max brightness\n");
		}
		else if (value >= 10) {
			printf("%d", value);
			fprintf(bright_file, "%d", value);	
		}
		else {
			printf("value too low, must be over 10");
		}
	}
	else if (arg == 1){
		if (current_brightness+value > max_brightness){
			printf("%d", max_brightness);
			fprintf(bright_file, "%d", max_brightness);
			printf("value too high : set to max brightness\n");
		}
		else {
			printf("%d", current_brightness+value);
			fprintf(bright_file, "%d", current_brightness+value);	
		}
	}
	else if (arg == -1){
		if (current_brightness-value < 10){
			printf("%d", 10);
			fprintf(bright_file, "%d", 10);
			printf("value too low : set to 10\n");
		}
		else {
			printf("%d", current_brightness-value);
			fprintf(bright_file, "%d", current_brightness-value);	
		}
	}
	return 0;
}

int main (int argc, char *argv[]){
	int current_brightness ;
	int max_brightness ;
	if (argc == 2){
		if (strcmp(argv[1], "--get") ==0 ){
			current_brightness = getbrightness(current_brightness_path);
			max_brightness = getbrightness(max_brightness_path);
			printf("%d/%d\n", current_brightness, max_brightness);
		}
		else {
			help(argv[0]);
		}
	}
	else if (argc > 2){
		if (strcmp(argv[1], "--inc") ==0 || strcmp(argv[1], "+") == 0){
			setbrightness(edit_brightness_path, 1, atoi(argv[2]));
		}
		else if (strcmp(argv[1], "--dec") ==0 || strcmp(argv[1], "-") == 0){
			setbrightness(edit_brightness_path, -1, atoi(argv[2]));
		}
		else if (strcmp(argv[1], "--set") ==0){
			setbrightness(edit_brightness_path, 0, atoi(argv[2]));
		}
		else {
			help(argv[0]);
		}	
	}
	else {
		help(argv[0]);
	}
	return 0;

}

