//
// Created by vnbk on 19/04/2023.
//
#include <sm_datetime.h>
#include <time.h>
#include <stdio.h>

int32_t sm_get_timestamp(){
    return (int32_t)time(NULL);
}


const char* sm_get_timestamp_string(){
    static char timestamp_string[20];
    int len = sprintf(timestamp_string, "%ld", time(NULL));
    timestamp_string[len] = '\0';

    return timestamp_string;
}

const char* sm_get_current_time(){
    static char current_time_string[30];
    time_t raw_time;

    time ( &raw_time );

    int len = sprintf(current_time_string, "%s", ctime(&raw_time));
    current_time_string[len] = '\0';

    return current_time_string;
}
