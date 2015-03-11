#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "cbor.h"
#include <inttypes.h>


unsigned char buffer[512];

static void test_embedded_negint8(void **state) {
	assert_int_equal(1, cbor_encode_negint8(14, buffer, 512));
	assert_memory_equal(buffer, (unsigned char[]){ 0x2E }, 1);
}

static void test_negint8(void **state) {
	assert_int_equal(0, cbor_encode_negint8(180, buffer, 1));
	assert_int_equal(2, cbor_encode_negint8(255, buffer, 512));
	assert_memory_equal(buffer, ((unsigned char[]){ 0x38, 0xFF }), 2);
}

static void test_negint16(void **state) {
	assert_int_equal(0, cbor_encode_negint16(1000, buffer, 2));
	assert_int_equal(3, cbor_encode_negint16(1000, buffer, 512));
	assert_memory_equal(buffer, ((unsigned char[]){ 0x39, 0x03, 0xE8 }), 3);
}

static void test_negint32(void **state) {
	assert_int_equal(0, cbor_encode_negint32(1000000, buffer, 4));
	assert_int_equal(5, cbor_encode_negint32(1000000, buffer, 512));
	assert_memory_equal(buffer, ((unsigned char[]){ 0x3A, 0x00, 0x0F, 0x42, 0x40 }), 5);
}

static void test_negint64(void **state) {
	assert_int_equal(0, cbor_encode_negint64(18446744073709551615ULL, buffer, 8));
	assert_int_equal(9, cbor_encode_negint64(18446744073709551615ULL, buffer, 512));
	assert_memory_equal(buffer, ((unsigned char[]){ 0x3B, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }), 9);
}

static void test_unspecified(void **state) {
	assert_int_equal(9, cbor_encode_negint(18446744073709551615ULL, buffer, 512));
	assert_memory_equal(buffer, ((unsigned char[]){ 0x3B, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }), 9);
	assert_int_equal(5, cbor_encode_negint(1000000, buffer, 512));
	assert_memory_equal(buffer, ((unsigned char[]){ 0x3A, 0x00, 0x0F, 0x42, 0x40 }), 5);
	assert_int_equal(3, cbor_encode_negint(1000, buffer, 512));
	assert_memory_equal(buffer, ((unsigned char[]){ 0x39, 0x03, 0xE8 }), 3);
	assert_int_equal(2, cbor_encode_negint(255, buffer, 512));
	assert_memory_equal(buffer, ((unsigned char[]){ 0x38, 0xFF }), 2);
}

int main(void) {
	const UnitTest tests[] = {
		unit_test(test_embedded_negint8),
		unit_test(test_negint8),
		unit_test(test_negint16),
		unit_test(test_negint32),
		unit_test(test_negint64),
		unit_test(test_unspecified)
	};
	return run_tests(tests);
}