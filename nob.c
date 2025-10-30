#include <errno.h>
#define NOB_IMPLEMENTATION
#define NOB_WARN_DEPRECATED
#define NOB_EXPERIMENTAL_DELETE_OLD
// #define NOB_NO_ECHO
#include "nob.h"

/////////////////////////////////////////////////////////////////////////////////
//                              MACRO DEFINITION                              //
///////////////////////////////////////////////////////////////////////////////
#define ARRAY_LEN(array) sizeof(array)/sizeof(array[0])
#define ifeq(command, com) if(strcmp(command, com) == 0)


/////////////////////////////////////////////////////////////////////////////////
//                             STRUCT DEFINITION                              //
///////////////////////////////////////////////////////////////////////////////
typedef struct __unit_test{
    const char* type;
    const char* name;
}Unit_Test;

/////////////////////////////////////////////////////////////////////////////////
//                            FUNCTION DEFINITION                             //
///////////////////////////////////////////////////////////////////////////////
char* shift(int* argc, char*** argv){
    if((*argc) == 0) return NULL;
    (*argc)--;
    return (*argv)++[0];
}


/////////////////////////////////////////////////////////////////////////////////
//                              GLOBAL VARIABLES                              //
///////////////////////////////////////////////////////////////////////////////
const Unit_Test test_files[] = {
    { .type = "absolute", .name = "simple" },
    { .type = "absolute", .name = "absolute_path" },
    { .type = "absolute", .name = "unix_relative_base" },
    { .type = "absolute", .name = "windows_relative_base" },
    { .type = "absolute", .name = "mixed" },
    { .type = "absolute", .name = "normalization" },
    { .type = "absolute", .name = "too_far" },
    { .type = "absolute", .name = "check" },
    { .type = "absolute", .name = "buffer_reuse" },
    { .type = "basename", .name = "simple" },
    { .type = "basename", .name = "empty" },
    { .type = "basename", .name = "trailing_separator" },
    { .type = "basename", .name = "trailing_separators" },
    { .type = "basename", .name = "no_separators" },
    { .type = "basename", .name = "special_directories" },
    { .type = "basename", .name = "root" },
    { .type = "basename", .name = "windows" },
    { .type = "basename", .name = "change_simple" },
    { .type = "basename", .name = "change_empty_path" },
    { .type = "basename", .name = "change_only_root" },
    { .type = "basename", .name = "change_empty_basename" },
    { .type = "basename", .name = "change_relative" },
    { .type = "basename", .name = "change_trim" },
    { .type = "basename", .name = "change_trim_only_root" },
    { .type = "dirname", .name = "simple" },
    { .type = "dirname", .name = "empty" },
    { .type = "dirname", .name = "trailing_separator" },
    { .type = "dirname", .name = "trailing_separators" },
    { .type = "dirname", .name = "no_separators" },
    { .type = "dirname", .name = "special_directories" },
    { .type = "dirname", .name = "root" },
    { .type = "dirname", .name = "three_segments" },
    { .type = "dirname", .name = "relative" },
    { .type = "extension", .name = "get_simple" },
    { .type = "extension", .name = "get_without" },
    { .type = "extension", .name = "get_first" },
    { .type = "extension", .name = "get_last" },
    { .type = "extension", .name = "get_multiple" },
    { .type = "extension", .name = "check_simple" },
    { .type = "extension", .name = "check_empty" },
    { .type = "extension", .name = "check_without" },
    { .type = "extension", .name = "change_simple" },
    { .type = "extension", .name = "change_no_basename" },
    { .type = "extension", .name = "change_no_extension" },
    { .type = "extension", .name = "change_with_dot" },
    { .type = "extension", .name = "change_overlap" },
    { .type = "extension", .name = "change_overlap_long" },
    { .type = "extension", .name = "change_hidden_file" },
    { .type = "extension", .name = "change_with_trailing_slash" },
    { .type = "guess", .name = "empty_string" },
    { .type = "guess", .name = "windows_root" },
    { .type = "guess", .name = "unix_root" },
    { .type = "guess", .name = "windows_separator" },
    { .type = "guess", .name = "unix_separator" },
    { .type = "guess", .name = "hidden_file" },
    { .type = "guess", .name = "extension" },
    { .type = "guess", .name = "unguessable" },
    { .type = "intersection", .name = "simple" },
    { .type = "intersection", .name = "trailing_separator" },
    { .type = "intersection", .name = "double_separator" },
    { .type = "intersection", .name = "empty" },
    { .type = "intersection", .name = "unequal_roots" },
    { .type = "intersection", .name = "relative_absolute_mix" },
    { .type = "intersection", .name = "same_roots" },
    { .type = "intersection", .name = "one_root_only" },
    { .type = "intersection", .name = "relative_base" },
    { .type = "intersection", .name = "relative_other" },
    { .type = "intersection", .name = "skipped_end" },
    { .type = "is_absolute", .name = "absolute" },
    { .type = "is_absolute", .name = "unc" },
    { .type = "is_absolute", .name = "device_unc" },
    { .type = "is_absolute", .name = "device_dot" },
    { .type = "is_absolute", .name = "device_question_mark" },
    { .type = "is_absolute", .name = "relative" },
    { .type = "is_absolute", .name = "windows_backslash" },
    { .type = "is_absolute", .name = "windows_slash" },
    { .type = "is_absolute", .name = "unix_backslash" },
    { .type = "is_absolute", .name = "unix_drive" },
    { .type = "is_absolute", .name = "absolute_drive" },
    { .type = "is_absolute", .name = "relative_drive" },
    { .type = "is_absolute", .name = "relative_windows" },
    { .type = "is_absolute", .name = "root" },
    { .type = "is_absolute", .name = "dir" },
    { .type = "is_relative", .name = "absolute" },
    { .type = "is_relative", .name = "unc" },
    { .type = "is_relative", .name = "device_unc" },
    { .type = "is_relative", .name = "device_dot" },
    { .type = "is_relative", .name = "device_question_mark" },
    { .type = "is_relative", .name = "relative" },
    { .type = "is_relative", .name = "windows_backslash" },
    { .type = "is_relative", .name = "windows_slash" },
    { .type = "is_relative", .name = "unix_backslash" },
    { .type = "is_relative", .name = "unix_drive" },
    { .type = "is_relative", .name = "absolute_drive" },
    { .type = "is_relative", .name = "relative_drive" },
    { .type = "is_relative", .name = "relative_windows" },
    { .type = "join", .name = "simple" },
    { .type = "join", .name = "navigate_back" },
    { .type = "join", .name = "empty" },
    { .type = "join", .name = "two_absolute" },
    { .type = "join", .name = "two_unc" },
    { .type = "join", .name = "with_two_roots" },
    { .type = "join", .name = "back_after_root" },
    { .type = "join", .name = "relative_back_after_root" },
    { .type = "join", .name = "multiple" },
    { .type = "normalize", .name = "do_nothing" },
    { .type = "normalize", .name = "navigate_back" },
    { .type = "normalize", .name = "relative_too_far" },
    { .type = "normalize", .name = "absolute_too_far" },
    { .type = "normalize", .name = "terminated" },
    { .type = "normalize", .name = "double_separator" },
    { .type = "normalize", .name = "remove_current" },
    { .type = "normalize", .name = "mixed" },
    { .type = "normalize", .name = "overlap" },
    { .type = "normalize", .name = "empty" },
    { .type = "normalize", .name = "only_separators" },
    { .type = "normalize", .name = "back_after_root" },
    { .type = "normalize", .name = "forward_slashes" },
    { .type = "relative", .name = "simple" },
    { .type = "relative", .name = "relative" },
    { .type = "relative", .name = "long_base" },
    { .type = "relative", .name = "long_target" },
    { .type = "relative", .name = "equal" },
    { .type = "relative", .name = "same_base" },
    { .type = "relative", .name = "base_skipped_end" },
    { .type = "relative", .name = "target_skipped_end" },
    { .type = "relative", .name = "base_div_skipped_end" },
    { .type = "relative", .name = "target_div_skipped_end" },
    { .type = "relative", .name = "skip_all" },
    { .type = "relative", .name = "different_roots" },
    { .type = "relative", .name = "relative_and_absolute" },
    { .type = "relative", .name = "check" },
    { .type = "relative", .name = "root_path_unix" },
    { .type = "relative", .name = "root_path_windows" },
    { .type = "relative", .name = "root_forward_slashes" },
    { .type = "root", .name = "absolute" },
    { .type = "root", .name = "unc" },
    { .type = "root", .name = "device_unc" },
    { .type = "root", .name = "device_dot" },
    { .type = "root", .name = "device_question_mark" },
    { .type = "root", .name = "relative" },
    { .type = "root", .name = "windows_backslash" },
    { .type = "root", .name = "windows_slash" },
    { .type = "root", .name = "unix_backslash" },
    { .type = "root", .name = "unix_drive" },
    { .type = "root", .name = "absolute_drive" },
    { .type = "root", .name = "relative_drive" },
    { .type = "root", .name = "relative_windows" },
    { .type = "root", .name = "change_simple" },
    { .type = "root", .name = "change_empty" },
    { .type = "root", .name = "change_separators" },
    { .type = "root", .name = "change_overlapping" },
    { .type = "root", .name = "change_without_root" },
    { .type = "segment", .name = "first" },
    { .type = "segment", .name = "last" },
    { .type = "segment", .name = "next" },
    { .type = "segment", .name = "next_too_far" },
    { .type = "segment", .name = "previous_absolute" },
    { .type = "segment", .name = "previous_relative" },
    { .type = "segment", .name = "previous_absolute_one_char_first" },
    { .type = "segment", .name = "previous_relative_one_char_first" },
    { .type = "segment", .name = "previous_too_far" },
    { .type = "segment", .name = "previous_too_far_root" },
    { .type = "segment", .name = "type" },
    { .type = "segment", .name = "back_with_root" },
    { .type = "segment", .name = "change_simple" },
    { .type = "segment", .name = "change_first" },
    { .type = "segment", .name = "change_last" },
    { .type = "segment", .name = "change_trim" },
    { .type = "segment", .name = "change_empty" },
    { .type = "segment", .name = "change_with_separator" },
    { .type = "segment", .name = "change_overlap" },
    { .type = "windows", .name = "change_style" },
    { .type = "windows", .name = "get_root" },
    { .type = "windows", .name = "get_unc_root" },
    { .type = "windows", .name = "get_root_separator" },
    { .type = "windows", .name = "get_root_relative" },
    { .type = "windows", .name = "intersection_case" },
    { .type = "windows", .name = "root_backslash" },
    { .type = "windows", .name = "root_empty" },
};


Nob_Cmd cmd  = {0};

int main(int _argc, char** _argv) {
    NOB_GO_REBUILD_URSELF(_argc, _argv);

    int argc = _argc;
    char** argv = _argv;

    // the first argument is the executable (./nob in this case)
    char* prog_name = shift(&argc, &argv);

    // We ensure the existence of commond dirs
    if(!nob_mkdir_if_not_exists(".build")) return 1;

    const char* tests_h_path = "test/tests.h";
    FILE* tests_h = fopen(tests_h_path, "w");
    if(tests_h == NULL){
        nob_log(NOB_ERROR, "could not open %s:%s", tests_h_path, strerror(errno));
        return 1;
    }

    fprintf(tests_h, "#define UNIT_TESTS(XX)");
    for(int i = 0; i < ARRAY_LEN(test_files); ++i){
        fprintf(tests_h, "\\\n    XX(%s,%s)", test_files[i].type, test_files[i].name);
    }
    fprintf(tests_h, "\n\n");

    nob_log(NOB_ERROR, "testing functionality is still not implemented!");

    return 1;

    nob_cmd_append(&cmd, "clang");
    nob_cmd_append(&cmd, "-E");
    nob_cmd_append(&cmd, "-P");
    nob_cmd_append(&cmd, "test/main.c");
    nob_cmd_append(&cmd, "-Wno-unterminated-macro");
    // nob_cmd_append(&cmd, "-o");
    // nob_cmd_append(&cmd, "test/main");

    if(!nob_cmd_run(&cmd)) return 1;

    return 0;
}
