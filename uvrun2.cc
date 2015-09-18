#include <node.h>
#include <v8.h>
#include <uv.h>
#include <stdio.h>

namespace uvrun2 {
	using namespace v8;

	void Run (const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = Isolate::GetCurrent ();
		int result;

		// Run the main loop until there are no active handles
		result = uv_run (uv_default_loop (), UV_RUN_DEFAULT);
		// Return the uv_run() return value
		args.GetReturnValue ().Set (Number::New (isolate, result));
	}

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
			if (args [0]->BooleanValue ()) {
				// Yup! Non-blocking it is
				mode = UV_RUN_NOWAIT;
			} else {
				// Nope, blocking mode
				mode = UV_RUN_ONCE;
			}
		// Has some arguments, but the first one is not a boolean
		} else {
			// Throw our hands up
			isolate->ThrowException (Exception::TypeError (String::NewFromUtf8 (isolate, "Argument must be a boolean value")));
			return;
		}

		// Run the main loop for one event, or possibly none
		result = uv_run (uv_default_loop (), mode);
		// Return the uv_run() return value
		args.GetReturnValue ().Set (Number::New (isolate, result));
	}

	void LoopSize (const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = Isolate::GetCurrent ();
		int count;
		uv_loop_t* loop;

		// Get the default loop, but just once
		loop = uv_default_loop ();

		// Do we have an argument?
		if (args.Length () == 1) {
			// Yes. Is it a number?
			if (! args [0]->IsNumber ()) {
				// Nope. Hands go up
				isolate->ThrowException (Exception::TypeError (String::NewFromUtf8 (isolate, "Argument must be an integer value")));
				return;
			}

			// Convert the argument to proper C integer
			count = args [0]->ToInteger ()->IntegerValue ();

			// Will the adjustment bring the number of active handles below 0?
			if ((int) loop->active_handles + count < 0) {
				// Looks that way so just set it to 0
				loop->active_handles = 0;
			} else {
				// Nah, add them in
				loop->active_handles += count;
			}
		}

		// Return the number of active handles
		args.GetReturnValue ().Set (Number::New (isolate, loop->active_handles));
	}

	void init (Handle<Object> target) {
		NODE_SET_METHOD (target, "run", Run);
		NODE_SET_METHOD (target, "runOnce", RunOnce);
		NODE_SET_METHOD (target, "loopSize", LoopSize);
	}

	NODE_MODULE (uvrun2, init);
}
