#include <sklc_lib/utils/unit_tests.h>
#include <sklc_lib/utils/string.h>
#include <sklc_lib/utils/vector.h>
#include <sklc_lib/utils/console.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void UnitTestHashFunc(string name, UnitTestFunc f) {
	static bool initialized = false;
	static uint64_t seed1 = 0;
	static uint64_t seed2 = 0;
	if(!initialized) {
		initialized = true;
		srand((uint32_t)time(NULL));
		seed1 = rand();
		seed2 = rand();
	}
	return SIP64(name.data, name.len, seed1, seed2);
}

UnitTestGroup* UnitTestHashCopyFunc(UnitTestGroup* group) {
	UnitTestGroup* new_group = malloc(sizeof(UnitTestGroup));
	StringDuplicate(&new_group->name, group->name);
	new_group->tests = group->tests.copy(&group->tests);
	return new_group;
}


void UnitTestHashDestroyFunc(UnitTestGroup* group) {
	StringDestroy(&group->name);
	vector_destroy(&group->tests);	
}

int UnitTestHashCmpFunc(UnitTestGroup* a, UnitTestGroup* b) {
	return StringCompare(a->name, b->name);
}

void UnitTestErrVecDtor(struct _vector* vec, UnitTestError* val) {
	StringDestroy(&val->file);
	StringDestroy(&val->expected);
	StringDestroy(&val->actual);
}

void InitTests(UnitTestHandler* handler) {
	assert(handler != NULL && "handler cannot be null");
	if(handler->tests != NULL) {
		handler->tests->clear(handler->tests);
	} else {
		handler->tests = malloc(sizeof(hashmap));
		hashmap_create(handler->tests,
			UnitTestHashFunc,
			__hashmap_destroy_string,
			UnitTestHashDestroyFunc,
			__hashmap_copy_string,
			UnitTestHashCopyFunc,
			__hashmap_compare_string,
			UnitTestHashCmpFunc
		);
	}
	handler->errors =	_vector_create(1, sizeof(UnitTestError), UnitTestErrVecDtor, __vector_def_val_cpy, __vector_def_cmp);
}

void DestroyTests(UnitTestHandler* handler) {
	assert(handler != NULL && "handler cannot be null");
	if(handler->tests != NULL) {
		hashmap_destroy(handler->tests);
		free(handler->tests);
		handler->tests = NULL;
	}
	vector_destroy(&handler->errors);
}

void AddTest(UnitTestHandler* handler, string group_name, string name, UnitTestFunc test_func) {
	assert(handler != NULL && "handler cannot be null");
	assert(handler->tests != NULL && "UnitTestHandler is not initialized");
	assert(test_func != NULL && "test_func cannot be null");
	UnitTestGroup* group = (UnitTestGroup*)handler->tests->get(handler->tests, &group_name, false);
	if(group == NULL) {
		group = malloc(sizeof(UnitTestGroup));
		*group = (UnitTestGroup){0};
		StringDuplicate(&group->name, group_name);
		vector_create(&group->tests);
		handler->tests->set(handler->tests, &group_name, group);
		group = (UnitTestGroup*)handler->tests->get(handler->tests, &group_name, false);
		string _g = {0}; StringDuplicate(&_g, group_name);
	}

	group->tests.push_back(&group->tests, test_func);
}

void IterateTests(string* name, UnitTestGroup* group, UnitTestHandler* handler) {
	assert(handler != NULL && "handler cannot be null");
	assert(handler->tests != NULL && "UnitTestHandler is NULL");
	assert(name != NULL && "Name cannot be null");
	int errors = 0;
	printf("Test group: \"%s\"\n", name->data);
	for(int i = 0; i < group->tests.length; i++) {
		UnitTestFunc test_func = *(UnitTestFunc*)group->tests.get_at(&group->tests, i);
		assert(test_func != NULL && "INTERNAL ERROR: test_func cannot be null");
		printf("Starting test #%d\n", i + 1, name->data);
		if(!test_func(name, handler)) {
			printf("Test \"%s\" failed\n", name->data);
			printf("======================================\n");
			for(int i = 0; i < handler->errors.length; i++) {
				UnitTestError error = *(UnitTestError*)handler->errors.get_at(&handler->errors, i);
				printf("Error: %s\n", error.file.data);
				printf("Line: %d\n", error.line);
				printf("Expected: \"%s\"\n", error.expected.data);
				printf("Actual: \"%s\"\n", error.actual.data);
				printf("======================================\n");
			}
		} else {
			printf("Test #%d passed...\n", i + 1);
		}
	}
	printf("Test group \"%s\" finished with %d errors\n\n", name->data, errors);
}

void RunAllTests(UnitTestHandler* handler, bool destroy_handler_after_run, char ***argv) {
	assert(handler != NULL && "handler cannot be null");
	assert(handler->tests != NULL && "UnitTestHandler is not initialized");
	ResetConsoleColor();
	printf("\n");
	printf("<Running unit tests...>\n");
	printf("<=====================>\n");
	gc_start(&handler->gc, argv);
	handler->tests->iterate(handler->tests, IterateTests, handler);
	if(destroy_handler_after_run) {
		DestroyTests(handler);
	}
	gc_stop(&handler->gc);
	printf("<=====================>\n");
	printf("<Finished unit tests.>\n");
	ResetConsoleColor();
}
