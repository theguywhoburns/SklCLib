#include <sklc_lib/utils/unit_tests.h>
#include <sklc_lib/utils/string.h>
#include <sklc_lib/utils/vector.h>
#include <sklc_lib/utils/console.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void TestHandlerCreate(UnitTestHandler* handler, char* argv[]) {
	handler->groups = vector_create(UnitTestGroup);
	gc_start(&handler->gc, argv);
}

void TestHandlerDestroy(UnitTestHandler* handler) {
	for(uint64_t i = 0; i < handler->groups.length; i++) {
		UnitTestGroup* g = handler->groups.get_at(&handler->groups, i);
		for(uint64_t j = 0; j < g->names.length; j++) {
			StringDestroy(g->names.get_at(&g->names, j));
		}
		vector_destroy(&g->names);
		vector_destroy(&g->tests);
	}
	vector_destroy(&handler->groups);
	gc_stop(&handler->gc);
}

void __AddTest(UnitTestHandler* handler, string group, string name, UnitTestFunc f) {
	printf("Adding test %s.%s\n", group.data, name.data);
	for(uint64_t i = 0; i < handler->groups.length; i++) {
		UnitTestGroup* g = handler->groups.get_at(&handler->groups, i);
		if(StringEquals(g->name, group)) {
			string name_cpy = {0};
			StringDuplicate(&name_cpy, name);
			g->names.push_back(&g->tests, &name_cpy);
			g->tests.push_back(&g->tests, &(function){(void*)f});
			return;
		}
	}
	printf("Group %s not found, creating it\n", group.data);
	UnitTestGroup g = {0};
	string name_cpy = {0};
	StringDuplicate(&name_cpy, name);
	StringDuplicate(&g.name, group);
	g.names = vector_create(string);
	g.tests = vector_create(UnitTestFunc);
	g.names.push_back(&g.names, &name_cpy);
	g.tests.push_back(&g.tests, &(function){(void*)f});
	g.success = true;
	handler->groups.push_back(&handler->groups, &g);
}

string ErrTypeToString(enum ErrorType e) {
	string ret = {0};
	switch(e) {
		case ERR_TRUE:
			StringCreate(&ret, "true");
			break;
		case ERR_FALSE:
			StringCreate(&ret, "false");
			break;
		case ERR_IF:
			StringCreate(&ret, "if");
			break;
		case ERR_EQ:
			StringCreate(&ret, "==");
			break;
		case ERR_NEQ:
			StringCreate(&ret, "!=");
			break;
		case ERR_GT:
			StringCreate(&ret, ">");
			break;
		case ERR_LT:
			StringCreate(&ret, "<");
			break;
		case ERR_GTEQ:
			StringCreate(&ret, ">=");
			break;
		case ERR_LTEQ:
			StringCreate(&ret, "<=");
			break;
		default:
			assert(false && "Unknown error type");
	}
	return ret;
}

void RunTests(UnitTestHandler* handler) {
	for(uint64_t i = 0; i < handler->groups.length; i++) {
		UnitTestGroup* g = handler->groups.get_at(&handler->groups, i);
		for(uint64_t j = 0; j < g->names.length; j++) {
			printf("Running test: %s.%s\n", g->name.data, ((string*)g->names.get_at(&g->names, j))->data);
			UnitTestFunc* _f = g->tests.get_at(&g->tests, j);
			UnitTestFunc f = *_f;
			handler->errors = vector_create(UnitTestError);
			if(!f(handler) || handler->errors.length > 0) {
				printf("Test %s with #%llu errors...\n", g->success ? "passed" : "failed", handler->errors.length);
				for(uint64_t k = 0; k < handler->errors.length; k++) {
					UnitTestError* error = handler->errors.get_at(&handler->errors, k);
					string err_type = ErrTypeToString(error->e);
					printf("Type: %s File: %s - Line: %d\n", err_type.data, error->file.data, error->line);
					StringDestroy(&err_type);
					if(error->expected.len > 0) {
						printf("Expected: %s\n", error->expected.data);
					}
					if(error->actual.len > 0) {
						printf("Actual: %s\n", error->actual.data);
					}
					StringDestroy(&error->expected);
					StringDestroy(&error->actual);
					StringDestroy(&error->file);
				}
				vector_destroy(&handler->errors);
				g->success = false;
				return;
			} else {
				printf("Test passed\n");
			}
			vector_destroy(&handler->errors);
		}
	}
}