#include <nan.h>
#include <node.h>
#include "yajl_gen.h"
#include "yajl_parse.h"

void Parse(const Nan::FunctionCallbackInfo<v8:Value> &info){
  
}

void Stringify(const Nan::FunctionCallbackInfo<v8:Value> &info){

}

void Init(v8::Local<v8::Object> exports){
  exports->Set(Nan::New("parse").toLocalChecked(),Nan::New<v8::FunctionTemplate>(Parse)->GetFunction());
  exports->Set(Nan::New("stringify").toLocalChecked(),Nan::New<v8::FunctionTemplate>(Stringify)->GetFunction());
}

NODE_MODULE(jsonasync,Init)
