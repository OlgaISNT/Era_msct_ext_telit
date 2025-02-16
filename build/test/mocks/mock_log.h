/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_LOG_H
#define _MOCK_LOG_H

#include "unity.h"
#include "log.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic push
#endif
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void mock_log_Init(void);
void mock_log_Destroy(void);
void mock_log_Verify(void);




#define log_deinit_Ignore() log_deinit_CMockIgnore()
void log_deinit_CMockIgnore(void);
#define log_deinit_StopIgnore() log_deinit_CMockStopIgnore()
void log_deinit_CMockStopIgnore(void);
#define log_deinit_Expect() log_deinit_CMockExpect(__LINE__)
void log_deinit_CMockExpect(UNITY_LINE_TYPE cmock_line);
typedef void (* CMOCK_log_deinit_CALLBACK)(int cmock_num_calls);
void log_deinit_AddCallback(CMOCK_log_deinit_CALLBACK Callback);
void log_deinit_Stub(CMOCK_log_deinit_CALLBACK Callback);
#define log_deinit_StubWithCallback log_deinit_Stub
#define log_init_Ignore() log_init_CMockIgnore()
void log_init_CMockIgnore(void);
#define log_init_StopIgnore() log_init_CMockStopIgnore()
void log_init_CMockStopIgnore(void);
#define log_init_Expect() log_init_CMockExpect(__LINE__)
void log_init_CMockExpect(UNITY_LINE_TYPE cmock_line);
typedef void (* CMOCK_log_init_CALLBACK)(int cmock_num_calls);
void log_init_AddCallback(CMOCK_log_init_CALLBACK Callback);
void log_init_Stub(CMOCK_log_init_CALLBACK Callback);
#define log_init_StubWithCallback log_init_Stub
#define log_c_Ignore() log_c_CMockIgnore()
void log_c_CMockIgnore(void);
#define log_c_StopIgnore() log_c_CMockStopIgnore()
void log_c_CMockStopIgnore(void);
#define log_c_Expect(str) log_c_CMockExpect(__LINE__, str)
void log_c_CMockExpect(UNITY_LINE_TYPE cmock_line, char* str);
typedef void (* CMOCK_log_c_CALLBACK)(char* str, int cmock_num_calls);
void log_c_AddCallback(CMOCK_log_c_CALLBACK Callback);
void log_c_Stub(CMOCK_log_c_CALLBACK Callback);
#define log_c_StubWithCallback log_c_Stub
#define log_e_Ignore() log_e_CMockIgnore()
void log_e_CMockIgnore(void);
#define log_e_StopIgnore() log_e_CMockStopIgnore()
void log_e_CMockStopIgnore(void);
#define log_e_Expect(str) log_e_CMockExpect(__LINE__, str)
void log_e_CMockExpect(UNITY_LINE_TYPE cmock_line, char* str);
typedef void (* CMOCK_log_e_CALLBACK)(char* str, int cmock_num_calls);
void log_e_AddCallback(CMOCK_log_e_CALLBACK Callback);
void log_e_Stub(CMOCK_log_e_CALLBACK Callback);
#define log_e_StubWithCallback log_e_Stub
#define log_w_Ignore() log_w_CMockIgnore()
void log_w_CMockIgnore(void);
#define log_w_StopIgnore() log_w_CMockStopIgnore()
void log_w_CMockStopIgnore(void);
#define log_w_Expect(str) log_w_CMockExpect(__LINE__, str)
void log_w_CMockExpect(UNITY_LINE_TYPE cmock_line, char* str);
typedef void (* CMOCK_log_w_CALLBACK)(char* str, int cmock_num_calls);
void log_w_AddCallback(CMOCK_log_w_CALLBACK Callback);
void log_w_Stub(CMOCK_log_w_CALLBACK Callback);
#define log_w_StubWithCallback log_w_Stub
#define log_i_Ignore() log_i_CMockIgnore()
void log_i_CMockIgnore(void);
#define log_i_StopIgnore() log_i_CMockStopIgnore()
void log_i_CMockStopIgnore(void);
#define log_i_Expect(str) log_i_CMockExpect(__LINE__, str)
void log_i_CMockExpect(UNITY_LINE_TYPE cmock_line, char* str);
typedef void (* CMOCK_log_i_CALLBACK)(char* str, int cmock_num_calls);
void log_i_AddCallback(CMOCK_log_i_CALLBACK Callback);
void log_i_Stub(CMOCK_log_i_CALLBACK Callback);
#define log_i_StubWithCallback log_i_Stub
#define log_t_Ignore() log_t_CMockIgnore()
void log_t_CMockIgnore(void);
#define log_t_StopIgnore() log_t_CMockStopIgnore()
void log_t_CMockStopIgnore(void);
#define log_t_Expect(str) log_t_CMockExpect(__LINE__, str)
void log_t_CMockExpect(UNITY_LINE_TYPE cmock_line, char* str);
typedef void (* CMOCK_log_t_CALLBACK)(char* str, int cmock_num_calls);
void log_t_AddCallback(CMOCK_log_t_CALLBACK Callback);
void log_t_Stub(CMOCK_log_t_CALLBACK Callback);
#define log_t_StubWithCallback log_t_Stub
#define log_hex_Ignore() log_hex_CMockIgnore()
void log_hex_CMockIgnore(void);
#define log_hex_StopIgnore() log_hex_CMockStopIgnore()
void log_hex_CMockStopIgnore(void);
#define log_hex_Expect(d) log_hex_CMockExpect(__LINE__, d)
void log_hex_CMockExpect(UNITY_LINE_TYPE cmock_line, char d);
typedef void (* CMOCK_log_hex_CALLBACK)(char d, int cmock_num_calls);
void log_hex_AddCallback(CMOCK_log_hex_CALLBACK Callback);
void log_hex_Stub(CMOCK_log_hex_CALLBACK Callback);
#define log_hex_StubWithCallback log_hex_Stub
#define log_raw_Ignore() log_raw_CMockIgnore()
void log_raw_CMockIgnore(void);
#define log_raw_StopIgnore() log_raw_CMockStopIgnore()
void log_raw_CMockStopIgnore(void);
#define log_raw_Expect(a) log_raw_CMockExpect(__LINE__, a)
void log_raw_CMockExpect(UNITY_LINE_TYPE cmock_line, char* a);
typedef void (* CMOCK_log_raw_CALLBACK)(char* a, int cmock_num_calls);
void log_raw_AddCallback(CMOCK_log_raw_CALLBACK Callback);
void log_raw_Stub(CMOCK_log_raw_CALLBACK Callback);
#define log_raw_StubWithCallback log_raw_Stub
#define print_hex_Ignore() print_hex_CMockIgnore()
void print_hex_CMockIgnore(void);
#define print_hex_StopIgnore() print_hex_CMockStopIgnore()
void print_hex_CMockStopIgnore(void);
#define print_hex_Expect(caption, m, length) print_hex_CMockExpect(__LINE__, caption, m, length)
void print_hex_CMockExpect(UNITY_LINE_TYPE cmock_line, char* caption, char* m, int length);
typedef void (* CMOCK_print_hex_CALLBACK)(char* caption, char* m, int length, int cmock_num_calls);
void print_hex_AddCallback(CMOCK_print_hex_CALLBACK Callback);
void print_hex_Stub(CMOCK_print_hex_CALLBACK Callback);
#define print_hex_StubWithCallback print_hex_Stub
#define print_date_time_Ignore() print_date_time_CMockIgnore()
void print_date_time_CMockIgnore(void);
#define print_date_time_StopIgnore() print_date_time_CMockStopIgnore()
void print_date_time_CMockStopIgnore(void);
#define print_date_time_Expect() print_date_time_CMockExpect(__LINE__)
void print_date_time_CMockExpect(UNITY_LINE_TYPE cmock_line);
typedef void (* CMOCK_print_date_time_CALLBACK)(int cmock_num_calls);
void print_date_time_AddCallback(CMOCK_print_date_time_CALLBACK Callback);
void print_date_time_Stub(CMOCK_print_date_time_CALLBACK Callback);
#define print_date_time_StubWithCallback print_date_time_Stub

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif
