#pragma once

#include <sklc_lib/defines.h>
#include <sklc_lib/utils/function.h>
#include <sklc_lib/utils/string.h>
#include <sklc_lib/utils/vector.h>
#include <sklc_lib/utils/hashmap.h>
#include <sklc_lib/utils/function.h>
#include <sklc_lib/utils/gc.h>

CREATE_FUNCTION_TYPE(UnitTestFunc, bool, struct UnitTestHandler*);

typedef struct UnitTestError UnitTestError;

#define CREATE_UNIT_TEST(name) bool (name)(struct UnitTestHandler* handler)

#define ASSERT_TRUE(statement)  if(!statement) { \
	UnitTestError error = {0}; 				\
	error.e = UnitTestError::ERR_TRUE;\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_FALSE(statement) if(statement) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_FALSE;	\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_EQ_INT(a, b) if(a != b) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_EQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	IntToString(&error.expected, a);	\
	IntToString(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_EQ_FLOAT(a, b) if(a != b) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_EQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	FloatToString(&error.expected, a);	\
	FloatToString(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_EQ_CSTR(a, b) if(StringCompare(STRING_VIEW(a, StringLength(a)), STRING_VIEW(b, StringLength(b))) != 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_EQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_EQ_STR(a, b) if(!StringEquals(a, b)) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_EQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_NEQ_INT(a, b) if(a == b) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_NEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	IntToString(&error.expected, a);	\
	IntToString(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_NEQ_FLOAT(a, b) if(a == b) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_NEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	FloatToString(&error.expected, a);	\
	FloatToString(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_NEQ_CSTR(a, b) if(StringCompare(STRING_VIEW(a, StringLength(a)), STRING_VIEW(b, StringLength(b))) == 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_NEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_NEQ_STR(a, b) if(StringEquals(a, b)) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_NEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_GT_INT(a, b) if(a <= b) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_GT;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	IntToString(&error.expected, a);	\
	IntToString(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_GT_FLOAT(a, b) if(a <= b) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_GT;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	FloatToString(&error.expected, a);	\
	FloatToString(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_GT_CSTR(a, b) if(StringCompare(STRING_VIEW(a, StringLength(a)), STRING_VIEW(b, StringLength(b))) <= 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_GT;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_GT_STR(a, b) if(StringCompare(a, b) <= 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_GT;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_LT_INT(a, b) if(a >= b) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_LT;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	IntToString(&error.expected, a);	\
	IntToString(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_LT_FLOAT(a, b) if(a >= b) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_LT;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	FloatToString(&error.expected, a);	\
	FloatToString(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_LT_CSTR(a, b) if(StringCompare(STRING_VIEW(a, StringLength(a)), STRING_VIEW(b, StringLength(b))) >= 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_LT;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_LT_STR(a, b) if(StringCompare(a, b) >= 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_LT;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_GTEQ_INT(a, b) if(a < b) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_GTEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	IntToString(&error.expected, a);	\
	IntToString(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_GTEQ_FLOAT(a, b) if(a < b) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_GTEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	FloatToString(&error.expected, a);	\
	FloatToString(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_GTEQ_CSTR(a, b) if(StringCompare(STRING_VIEW(a, StringLength(a)), STRING_VIEW(b, StringLength(b))) < 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_GTEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_GTEQ_STR(a, b) if(StringCompare(a, b) < 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_GTEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_LTEQ_INT(a, b) if(a > b) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_LTEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	IntToString(&error.expected, a);	\
	IntToString(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_LTEQ_FLOAT(a, b) if(a > b) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_LTEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	FloatToString(&error.expected, a);	\
	FloatToString(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_LTEQ_CSTR(a, b) if(StringCompare(STRING_VIEW(a, StringLength(a)), STRING_VIEW(b, StringLength(b))) > 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_LTEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_LTEQ_STR(a, b) if(StringCompare(a, b) > 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_LTEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_EQ_INT(a, b) if(a != b) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_EQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	IntToString(&error.expected, a);	\
	IntToString(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_EQ_FLOAT(a, b) if(a != b) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_EQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	FloatToString(&error.expected, a);	\
	FloatToString(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_EQ_CSTR(a, b) if(StringCompare(STRING_VIEW(a, StringLength(a)), STRING_VIEW(b, StringLength(b))) != 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_EQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_EQ_STR(a, b) if(StringCompare(a, b) != 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_EQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_NEQ_INT(a, b) if(a == b) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_NEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	IntToString(&error.expected, a);	\
	IntToString(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_NEQ_FLOAT(a, b) if(a == b) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_NEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	FloatToString(&error.expected, a);	\
	FloatToString(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_NEQ_CSTR(a, b) if(StringCompare(STRING_VIEW(a, StringLength(a)), STRING_VIEW(b, StringLength(b))) == 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_NEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define ASSERT_NEQ_STR(a, b) if(StringCompare(a, b) == 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_NEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler.tests.push_back(handler.tests, error); \
	return false; 				\
}

#define EXPECT_TRUE(x) if(!(x)) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_TRUE;	\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_FALSE(x) if(x) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_FALSE;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_EQ_INT(x, y) if(x != y) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_EQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	IntToString(&error.expected, x);	\
	IntToString(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_EQ_FLOAT(x, y) if(x != y) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_EQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	FloatToString(&error.expected, x);	\
	FloatToString(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_EQ_CSTR(x, y) if(StringCompare(STRING_VIEW(x, StringLength(x)), STRING_VIEW(y, StringLength(y))) != 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_EQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, x);	\
	StringCreate(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_EQ_STR(x, y) if(StringCompare(x, y) != 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_EQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, x);	\
	StringCreate(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_NEQ_INT(x, y) if(x == y) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_NEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	IntToString(&error.expected, x);	\
	IntToString(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_NEQ_FLOAT(x, y) if(x == y) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_NEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	FloatToString(&error.expected, x);	\
	FloatToString(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_NEQ_CSTR(x, y) if(StringCompare(STRING_VIEW(x, StringLength(x)), STRING_VIEW(y, StringLength(y))) == 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_NEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, x);	\
	StringCreate(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_NEQ_STR(x, y) if(StringCompare(x, y) == 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_NEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, x);	\
	StringCreate(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_GT_INT(x, y) if(x <= y) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_GT;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	IntToString(&error.expected, x);	\
	IntToString(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}	

#define EXPECT_GT_FLOAT(x, y) if(x <= y) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_GT;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	FloatToString(&error.expected, x);	\
	FloatToString(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_GT_CSTR(x, y) if(StringCompare(STRING_VIEW(x, StringLength(x)), STRING_VIEW(y, StringLength(y))) <= 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_GT;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, x);	\
	StringCreate(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_GT_STR(x, y) if(StringCompare(x, y) <= 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_GT;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, x);	\
	StringCreate(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_GTEQ_INT(x, y) if(x < y) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_GTEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	IntToString(&error.expected, x);	\
	IntToString(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_GTEQ_FLOAT(x, y) if(x < y) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_GTEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	FloatToString(&error.expected, x);	\
	FloatToString(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_GTEQ_CSTR(x, y) if(StringCompare(STRING_VIEW(x, StringLength(x)), STRING_VIEW(y, StringLength(y))) < 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_GTEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, x);	\
	StringCreate(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_GTEQ_STR(x, y) if(StringCompare(x, y) < 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_GTEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, x);	\
	StringCreate(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_LTEQ_INT(x, y) if(x > y) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_LTEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	IntToString(&error.expected, x);	\
	IntToString(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_LTEQ_FLOAT(x, y) if(x > y) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_LTEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	FloatToString(&error.expected, x);	\
	FloatToString(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_LTEQ_CSTR(x, y) if(StringCompare(STRING_VIEW(x, StringLength(x)), STRING_VIEW(y, StringLength(y))) > 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_LTEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, x);	\
	StringCreate(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

#define EXPECT_LTEQ_STR(x, y) if(StringCompare(x, y) > 0) { \
	UnitTestError error = {0}; 					\
	error.e = UnitTestError::ERR_LTEQ;		\
	err.line = __LINE__; 	\
	StringCreate(&err.file, __FILE__);	\
	StringCreate(&error.expected, x);	\
	StringCreate(&error.actual, y);		\
	handler.tests.push_back(handler.tests, error); \
}

typedef struct UnitTestGroup {
	string name;
	vector tests;
} UnitTestGroup;

struct UnitTestError {
	enum ErrorType {
		ERR_TRUE,  // true
		ERR_FALSE, // false
		ERR_EQ,    // ==
		ERR_NEQ,   // !=
		ERR_GT,    // >
		ERR_LT,    // <
		ERR_GTEQ,  // >=
		ERR_LTEQ   // <=
	} e;
	int line;
	string file;
	string expected;
	string actual;
};

typedef struct UnitTestHandler {
	hashmap* tests; // HashMap for UnitTestGroup	
	vector   groups;// Save all groups in a vector
	vector   errors;// Errors for current UnitTestGroup
	GarbageCollector gc;
} UnitTestHandler;

void InitTests  (UnitTestHandler* handler);
void AddTest    (UnitTestHandler* handler, string group_name, string name, UnitTestFunc test_func);
void RunAllTests(UnitTestHandler* handler, bool destroy_after_run);

#define TEST_ALLOC(size) gc_malloc(handler.gc, size);
#define TEST_FREE(ptr)   gc_free(handler.gc, ptr);