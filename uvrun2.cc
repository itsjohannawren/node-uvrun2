#include <node.h>
#include <v8.h>
#include <uv.h>
#include <stdio.h>

namespace uvrun2 {
	using namespace v8;

#if (UV_VERSION_MAJOR == 0) && (UV_VERSION_MINOR < 11)

	Handle<Value> Run (const Arguments& args) {
		HandleScope scope;
#	if (UV_VERSION_MAJOR == 0) && (UV_VERSION_MINOR < 9)
		uv_run (uv_default_loop ());
#	else
		uv_run (uv_default_loop (), UV_RUN_DEFAULT);
#	endif
		return (scope.Close (Null ()));
	}

	Handle<Value> RunOnce (const Arguments& args) {
		HandleScope scope;
		int result;
#	if ! (UV_VERSION_MAJOR == 0) && (UV_VERSION_MINOR < 9)
		uv_run_mode mode;
#	endif
		if (args.Length () == 0) {
#	if ! (UV_VERSION_MAJOR == 0) && (UV_VERSION_MINOR < 9)
			mode = UV_RUN_ONCE;
#	endif
		} else if (args [0]->IsBoolean ()) {
			if (args [0]->BooleanValue ()) {
#	if ! (UV_VERSION_MAJOR == 0) && (UV_VERSION_MINOR < 9)
				mode = UV_RUN_NOWAIT;
#	else
#		warning "libuv is too old to support UV_RUN_NOWAIT"
				Isolate::GetCurrent ()->ThrowException (Exception::TypeError (String::NewFromUtf8 (Isolate::GetCurrent (), "Argument not valid in this version of libuv")));
#	endif
			}
#	if ! (UV_VERSION_MAJOR == 0) && (UV_VERSION_MINOR < 9)
			else {
				mode = UV_RUN_ONCE;
			}
#	endif
		} else {
			Isolate::GetCurrent ()->ThrowException (Exception::TypeError (String::NewFromUtf8 (Isolate::GetCurrent (), "Argument must be a boolean value")));
		}

#	if (UV_VERSION_MAJOR == 0) && (UV_VERSION_MINOR < 9)
		result = uv_run_once (uv_default_loop ());
#	else
		result = uv_run (uv_default_loop (), mode);
#	endif
		return (scope.Close (Number::New (result)));
	}

#else
	void Run (const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = Isolate::GetCurrent ();
		int result;

		result = uv_run (uv_default_loop (), UV_RUN_DEFAULT);
		args.GetReturnValue ().Set (Number::New (isolate, result));
	}

	void RunOnce (const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = Isolate::GetCurrent ();
		int result;
		uv_run_mode mode;

		if (args.Length () == 0) {
			mode = UV_RUN_ONCE;
		} else if (args [0]->IsBoolean ()) {
			if (args [0]->BooleanValue ()) {
				mode = UV_RUN_NOWAIT;
			} else {
				mode = UV_RUN_ONCE;
			}
		} else {
			isolate->ThrowException (Exception::TypeError (String::NewFromUtf8 (isolate, "Argument must be a boolean value")));
			return;
		}

		result = uv_run (uv_default_loop (), mode);
		args.GetReturnValue ().Set (Number::New (isolate, result));
	}

#endif

	void init (Handle<Object> target) {
		NODE_SET_METHOD (target, "run", Run);
		NODE_SET_METHOD (target, "runOnce", RunOnce);
	}

	NODE_MODULE (uvrun2, init);
}
