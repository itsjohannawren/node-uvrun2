#include <node.h>
#include <v8.h>
#include <uv.h>

namespace uvrun2 {
	using v8::FunctionCallbackInfo;
	using v8::Handle;
	using v8::Object;
	using v8::Value;

	void run (const FunctionCallbackInfo<Value>& args) {
		 uv_run (uv_default_loop (), UV_RUN_NOWAIT);
	}

	void init (Handle<Object> target) {
		NODE_SET_METHOD (target, "run", run);
	}

	NODE_MODULE (uvrun2, init);
}
