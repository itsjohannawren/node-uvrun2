#include <node.h>
#include <v8.h>
#include <uv.h>

namespace uvrun2 {
	using namespace v8;

	void RunOnce (const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = Isolate::GetCurrent ();
		int result;
		uv_run_mode mode;

		// No arguments?
		if (args.Length () == 0) {
			// No args so use the blocking mode
			mode = UV_RUN_ONCE;
		// Has some arguments, but is the first one boolean?
		} else if (args [0]->IsBoolean ()) {
			// Sure enough, is it true?
			if (args [0]->BooleanValue (isolate)) {
				// Yup! Non-blocking it is
				mode = UV_RUN_NOWAIT;
			} else {
				// Nope, blocking mode
				mode = UV_RUN_ONCE;
			}
		// Has some arguments, but the first one is not a boolean
		} else {
			// Throw our hands up
			isolate->ThrowException (Exception::TypeError (String::NewFromUtf8 (isolate, "Argument must be a boolean value", v8::NewStringType::kInternalized).ToLocalChecked ()));
			return;
		}

		// Run the main loop for one event, or possibly none
		result = uv_run (uv_default_loop (), mode);
		// Return the uv_run() return value
		args.GetReturnValue ().Set (Number::New (isolate, result));
	}

	void init (Local<Object> target) {
		NODE_SET_METHOD (target, "runOnce", RunOnce);
	}

	NODE_MODULE (uvrun2, init);
}
