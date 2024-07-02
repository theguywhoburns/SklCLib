#pragma once

#include <sklc_lib/defines.h>
#include <sklc_lib/utils/function.h>
#include <sklc_lib/utils/string.h>
#include <sklc_lib/utils/vector.h>
#include <sklc_lib/utils/function.h>
#include <sklc_lib/utils/gc.h>

#define CREATE_UNIT_TEST(name) bool (name)(struct UnitTestHandler* handler)

#define ASSERT_TRUE(statement)  if(!statement) { \
	UnitTestError error = {0}; 				\
	error.e = ERR_TRUE;\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_FALSE(statement) if(statement) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_FALSE;	\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_IF(statement) if(!statement) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_IF;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_EQ_INT(a, b) if(a != b) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_EQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	IntToString(&error.expected, a);	\
	IntToString(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_EQ_FLOAT(a, b) if(a != b) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_EQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	FloatToString(&error.expected, a);	\
	FloatToString(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_EQ_CSTR(a, b) if(StringCompare(STRING_VIEW_(a, StringLength(a)), STRING_VIEW_(b, StringLength(b))) != 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_EQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_EQ_STR(a, b) if(!StringEquals(a, b)) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_EQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringDuplicate(&error.expected, a);	\
	StringDuplicate(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_NEQ_INT(a, b) if(a == b) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_NEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	IntToString(&error.expected, a);	\
	IntToString(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_NEQ_FLOAT(a, b) if(a == b) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_NEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	FloatToString(&error.expected, a);	\
	FloatToString(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_NEQ_CSTR(a, b) if(StringCompare(STRING_VIEW_(a, StringLength(a)), STRING_VIEW_(b, StringLength(b))) == 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_NEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_NEQ_STR(a, b) if(StringEquals(a, b)) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_NEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringDuplicate(&error.expected, a);	\
	StringDuplicate(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_GT_INT(a, b) if(a <= b) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_GT;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	IntToString(&error.expected, a);	\
	IntToString(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_GT_FLOAT(a, b) if(a <= b) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_GT;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	FloatToString(&error.expected, a);	\
	FloatToString(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_GT_CSTR(a, b) if(StringCompare(STRING_VIEW_(a, StringLength(a)), STRING_VIEW_(b, StringLength(b))) <= 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_GT;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_GT_STR(a, b) if(StringCompare(a, b) <= 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_GT;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringDuplicate(&error.expected, a);	\
	StringDuplicate(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_LT_INT(a, b) if(a >= b) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_LT;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	IntToString(&error.expected, a);	\
	IntToString(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_LT_FLOAT(a, b) if(a >= b) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_LT;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	FloatToString(&error.expected, a);	\
	FloatToString(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_LT_CSTR(a, b) if(StringCompare(STRING_VIEW_(a, StringLength(a)), STRING_VIEW_(b, StringLength(b))) >= 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_LT;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_LT_STR(a, b) if(StringCompare(a, b) >= 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_LT;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringDuplicate(&error.expected, a);	\
	StringDuplicate(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_GTEQ_INT(a, b) if(a < b) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_GTEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	IntToString(&error.expected, a);	\
	IntToString(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_GTEQ_FLOAT(a, b) if(a < b) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_GTEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	FloatToString(&error.expected, a);	\
	FloatToString(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_GTEQ_CSTR(a, b) if(StringCompare(STRING_VIEW_(a, StringLength(a)), STRING_VIEW_(b, StringLength(b))) < 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_GTEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_GTEQ_STR(a, b) if(StringCompare(a, b) < 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_GTEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringDuplicate(&error.expected, a);	\
	StringDuplicate(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_LTEQ_INT(a, b) if(a > b) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_LTEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	IntToString(&error.expected, a);	\
	IntToString(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_LTEQ_FLOAT(a, b) if(a > b) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_LTEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	FloatToString(&error.expected, a);	\
	FloatToString(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_LTEQ_CSTR(a, b) if(StringCompare(STRING_VIEW_(a, StringLength(a)), STRING_VIEW_(b, StringLength(b))) > 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_LTEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_LTEQ_STR(a, b) if(StringCompare(a, b) > 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_LTEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringDuplicate(&error.expected, a);	\
	StringDuplicate(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_EQ_INT(a, b) if(a != b) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_EQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	IntToString(&error.expected, a);	\
	IntToString(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_EQ_FLOAT(a, b) if(a != b) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_EQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	FloatToString(&error.expected, a);	\
	FloatToString(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_EQ_CSTR(a, b) if(StringCompare(STRING_VIEW_(a, StringLength(a)), STRING_VIEW_(b, StringLength(b))) != 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_EQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_NEQ_INT(a, b) if(a == b) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_NEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	IntToString(&error.expected, a);	\
	IntToString(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_NEQ_FLOAT(a, b) if(a == b) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_NEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	FloatToString(&error.expected, a);	\
	FloatToString(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define ASSERT_NEQ_CSTR(a, b) if(StringCompare(STRING_VIEW_(a, StringLength(a)), STRING_VIEW_(b, StringLength(b))) == 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_NEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringCreate(&error.expected, a);	\
	StringCreate(&error.actual, b);		\
	handler->errors.push_back(&handler->errors, &error); \
	return false; 				\
}

#define EXPECT_TRUE(x) if(!(x)) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_TRUE;	\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_FALSE(x) if(x) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_FALSE;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_IF(x) if(!x) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_IF;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_EQ_INT(x, y) if(x != y) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_EQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	IntToString(&error.expected, x);	\
	IntToString(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_EQ_FLOAT(x, y) if(x != y) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_EQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	FloatToString(&error.expected, x);	\
	FloatToString(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_EQ_CSTR(x, y) if(StringCompare(STRING_VIEW_(x, StringLength(x)), STRING_VIEW_(y, StringLength(y))) != 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_EQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringCreate(&error.expected, x);	\
	StringCreate(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_EQ_STR(x, y) if(StringCompare(x, y) != 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_EQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringDuplicate(&error.expected, x);	\
	StringDuplicate(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_NEQ_INT(x, y) if(x == y) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_NEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	IntToString(&error.expected, x);	\
	IntToString(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_NEQ_FLOAT(x, y) if(x == y) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_NEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	FloatToString(&error.expected, x);	\
	FloatToString(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_NEQ_CSTR(x, y) if(StringCompare(STRING_VIEW_(x, StringLength(x)), STRING_VIEW_(y, StringLength(y))) == 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_NEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringCreate(&error.expected, x);	\
	StringCreate(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_NEQ_STR(x, y) if(StringCompare(x, y) == 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_NEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringDuplicate(&error.expected, x);	\
	StringDuplicate(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_GT_INT(x, y) if(x <= y) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_GT;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	IntToString(&error.expected, x);	\
	IntToString(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}	

#define EXPECT_GT_FLOAT(x, y) if(x <= y) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_GT;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	FloatToString(&error.expected, x);	\
	FloatToString(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_GT_CSTR(x, y) if(StringCompare(STRING_VIEW_(x, StringLength(x)), STRING_VIEW_(y, StringLength(y))) <= 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_GT;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringCreate(&error.expected, x);	\
	StringCreate(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_GT_STR(x, y) if(StringCompare(x, y) <= 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_GT;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringDuplicate(&error.expected, x);	\
	StringDuplicate(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_GTEQ_INT(x, y) if(x < y) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_GTEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	IntToString(&error.expected, x);	\
	IntToString(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_GTEQ_FLOAT(x, y) if(x < y) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_GTEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	FloatToString(&error.expected, x);	\
	FloatToString(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_GTEQ_CSTR(x, y) if(StringCompare(STRING_VIEW_(x, StringLength(x)), STRING_VIEW_(y, StringLength(y))) < 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_GTEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringCreate(&error.expected, x);	\
	StringCreate(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_GTEQ_STR(x, y) if(StringCompare(x, y) < 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_GTEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringDuplicate(&error.expected, x);	\
	StringDuplicate(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_LT_INT(x, y) if(x >= y) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_LT;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	IntToString(&error.expected, x);	\
	IntToString(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_LT_FLOAT(x, y) if(x >= y) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_LT;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	FloatToString(&error.expected, x);	\
	FloatToString(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_LT_CSTR(x, y) if(StringCompare(STRING_VIEW_(x, StringLength(x)), STRING_VIEW_(y, StringLength(y))) >= 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_LT;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringCreate(&error.expected, x);	\
	StringCreate(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_LT_STR(x, y) if(StringCompare(x, y) >= 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_LT;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringDuplicate(&error.expected, x);	\
	StringDuplicate(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_LTEQ_INT(x, y) if(x > y) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_LTEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	IntToString(&error.expected, x);	\
	IntToString(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_LTEQ_FLOAT(x, y) if(x > y) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_LTEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	FloatToString(&error.expected, x);	\
	FloatToString(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_LTEQ_CSTR(x, y) if(StringCompare(STRING_VIEW_(x, StringLength(x)), STRING_VIEW_(y, StringLength(y))) > 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_LTEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringCreate(&error.expected, x);	\
	StringCreate(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

#define EXPECT_LTEQ_STR(x, y) if(StringCompare(x, y) > 0) { \
	UnitTestError error = {0}; 					\
	error.e = ERR_LTEQ;		\
	error.line = __LINE__; 	\
	StringCreate(&error.file, __FILE__);	\
	StringDuplicate(&error.expected, x);	\
	StringDuplicate(&error.actual, y);		\
	handler->errors.push_back(&handler->errors, &error); \
}

typedef struct UnitTestGroup {
	string name;
	vector tests;
	vector names;
	bool success;
} UnitTestGroup;

struct UnitTestError {
	enum ErrorType {
		ERR_TRUE,  // true
		ERR_FALSE, // false
		ERR_IF,    // if
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
	vector   groups;// Save all groups in a vector
	vector   errors;// Errors for current UnitTestGroup
	GarbageCollector gc;
} UnitTestHandler;

CREATE_FUNCTION_TYPE(UnitTestFunc, bool, struct UnitTestHandler*);

typedef struct UnitTestError UnitTestError;

#define TEST_ALLOC(size) gc_malloc(handler.gc, size);
#define TEST_FREE(ptr)   gc_free(handler.gc, ptr);

void TestHandlerCreate(UnitTestHandler* handler, char* argv[]);
void TestHandlerDestroy(UnitTestHandler* handler);

void __AddTest(UnitTestHandler* handler, string group, string name, UnitTestFunc f);
#define AddTest(handler, group, func) __AddTest(handler, STRING_VIEW_(#group, StringLength(#group)), STRING_VIEW_(#func, StringLength(#func)), func)

void RunTests(UnitTestHandler* handler);