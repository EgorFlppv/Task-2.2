/*
test_app.c - модуль проверки программы.
ФИО: Филиппов Егор Ильич
Группа: МК-102
*/
#include "unity.h"
#include "hexdump_lib.h"

void setUp(void) {
}

void tearDown(void) {
}

void TestHexdumpNullFile(void) {
    DumpOptions opts = { .offset = 0, .size = 0, .chunk_size = 1, .chunks_per_line = 16 };
    TEST_ASSERT_EQUAL_INT(-1, dump_file(NULL, &opts));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(TestHexdumpNullFile);
    return UNITY_END();
}