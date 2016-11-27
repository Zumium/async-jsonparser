#include <nan.h>
#include "jsonparse.hpp"

NAN_METHOD(parse){
  if(info.Length() != 2){
    Nan::ThrowTypeError("parse function requires exactly two paramters");
    return;
  }
  if(!info[0]->IsString() || !info[1]->IsFunction()){
    Nan::ThrowTypeError("parse function requires a string to parse and a callback function to invoke");
    return;
  }

  char* json_str=*Nan::Utf8String(info[0]);
  Nan::Callback* callback=new Nan::Callback(info[1].As<v8::Function>());
  Nan::AsyncQueueWorker(new JsonParseWork(callback,json_str));
}

/*
temporarily disable this for conveniently testing parse

NAN_METHOD(stringify){
  if(info.Length() != 2){
    Nan::ThrowTypeError("stringify function requires exactly two paramters");
    return;
  }
  if(!info[0]->IsObject() || !info[1]->IsFunction()){
    Nan::ThrowTypeError("stringify function requires an object and a callback function to invoke");
    return;
  }

}
*/

NAN_MODULE_INIT(Init){
  NAN_EXPORT(target,parse);
  //NAN_EXPORT(target,stringify);
}

NODE_MODULE(jsonasync,Init)
