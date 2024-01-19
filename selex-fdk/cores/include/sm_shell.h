/*
 * shell.h
 *
 *  Created on: Sep 20, 2023
 *      Author: MinhNhan
 */

#ifndef INCLUDE_SHELL_H_
#define INCLUDE_SHELL_H_

#pragma once

#include <stddef.h>

typedef struct ShellCommand {
  const char *command;
  int (*handler)(int argc, char *argv[]);
  const char *help;
} sm_ShellCommand_t;

extern const sm_ShellCommand_t *const g_shell_commands;
extern const size_t g_num_shell_commands;

typedef struct sm_ShellImpl {
  //! Function to call whenever a character needs to be sent out.
  int (*send_char)(char c);
  char (*recv_char)();
} sm_ShellImpl_t;

/**
 * @brief
 * @param impl
 */
void sm_shell_boot(const sm_ShellImpl_t *impl);

/**
 * @brief
 */
void sm_shell_process();
/**
 * @brief
 * @param c
 */
void sm_shell_receive_char(char c);

/**
 * @brief
 * @param argc
 * @param argv
 * @return
 */
int sm_shell_help_handler(int argc, char *argv[]);

/**
 * @brief
 * @param str
 */
void sm_shell_put_line(const char *str);



#endif /* INCLUDE_SHELL_H_ */
