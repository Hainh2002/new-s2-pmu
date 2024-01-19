/*
 * shell_command.c
 *
 *  Created on: Sep 20, 2023
 *      Author: MinhNhan
 */
#include "sm_shell.h"

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define FILE_SYS 0

const char passwork[32] = "selex.vn";
extern char SHELL_PROMPT[128];
extern bool login;

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
/**
 *
 * @param argc
 * @param argv
 * @return
 */
static int shell_login(int argc, char *argv[]){
	sm_shell_put_line("Login success");
	login = true;
	return 0;
}

#if FILE_SYS
#include <dirent.h>


char shell_buff[64];
static void clear_buff();
static void clear_buff(){
	memset(shell_buff,0,64);
}

static int print_working_directory(int argc, char *argv[]){
	sm_shell_put_line("home/");
	return 0;
}

static int change_directory(int argc, char *argv[]){
	if(argc == 1){
		DIR *dir = opendir(argv[1]);
		if(dir != NULL){

		}
		else{

		}
	}
	return 0;
}

static int make_dir(int argc, char *argv[]){
	return 0;
}

static int list(int argc, char *argv[]){
	return 0;
}

static int move(int argc, char *argv[]){
	return 0;
}


static int remove_file(int argc, char *argv[]){
	return 0;
}

static int remove_directory(int argc, char *argv[]){
	return 0;
}

static int concatenate(int argc, char *argv[]){
	return 0;
}
#endif

static const sm_ShellCommand_t s_shell_commands[] = {
  { passwork, shell_login,"passwork" },
  { "help", sm_shell_help_handler, "Lists all commands" },
#if FILE_SYS
  {"pwd",print_working_directory,"Print working directory"},
  {"cd",change_directory,"Change directory"},
  {"mkdir",make_dir,"make directory"},
  {"ls",list,"List"},
  {"mv",move,"Move"},
  {"rm",remove_file,"Remove file"},
  {"rmdir",remove_directory,"Remove_directory"},
  {"cat",concatenate,"Concatenate"}
#endif
};

const sm_ShellCommand_t *const g_shell_commands = s_shell_commands;
const size_t g_num_shell_commands = ARRAY_SIZE(s_shell_commands);
