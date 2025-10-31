#include <stdio.h>
#include <unity.h>

int main_app() {
    printf("Unit testing options\n");
    printf("- Run specific test by its index: type the number and press ENTER.\n");
    printf("- Run a group of tests with a certain tag: type the tag, including square brackets, and press ENTER.\n");
    printf("- Run all tests except the ones with a certain tag : press !, then type the tag, including the square brackets, then press ENTER.\n");
    printf("- Run test with a specific name : type the name of the test, including quotes, and press ENTER.\n");
    printf("- Run all the tests : press * and then ENTER.\n");

    unity_run_menu();  // Open the test menu
}