#define UNITY_SUPPORT_TEST_CASES
#include <stdio.h>
#include <esp_task_wdt.h>
#include "unity_test_runner.h"
#include "unity.h"

TEST_CASE("test_case 1", "[mainTests]") {
    // printf("Hello World\n");
    TEST_ASSERT_EQUAL(1, -2);
}

TEST_CASE("test 2", "[mainTests]") {
    // printf("Hello\n");
    TEST_ASSERT_EQUAL(2, 2);
}

TEST_CASE("test 3", "[mainTests]") {
    // printf("Hello\n");
    TEST_ASSERT_EQUAL(2, 2);
}


void app_main(void) {
    // printf("Unit testing options\n");
    // printf("- Run specific test by its index: type the number and press ENTER.\n");
    // printf("- Run a group of tests with a certain tag: type the tag, including square brackets, and press ENTER.\n");
    // printf("- Run all tests except the ones with a certain tag : press !, then type the tag, including the square brackets, then press ENTER.\n");
    // printf("- Run test with a specific name : type the name of the test, including quotes, and press ENTER.\n");
    // printf("- Run all the tests : press * and then ENTER.\n");
    esp_task_wdt_deinit();
    unity_run_all_tests();
    unity_run_menu();
}