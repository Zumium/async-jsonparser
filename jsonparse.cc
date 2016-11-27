#include "jsonparse.hpp"
#include <cstring>
#include <cstdlib>

JsonParseWork::JsonParseWork(Nan::Callback* cb,char* json) : AsyncWorker(cb) {
  jsonStr=(char*)malloc(strlen(json)+1);
  strcpy(jsonStr,json);
}

JsonParseWork::~JsonParseWork() {
  yajl_tree_free(jsonTree);
  free(jsonStr);
}

void JsonParseWork::Execute() {
  char errorBuf[1024]={0};
  jsonTree=yajl_tree_parse((const char*)jsonStr,errorBuf,1024);
  if(jsonTree == NULL){
    //error occurded
    SetErrorMessage((const char*)errorBuf);
  }
}

void JsonParseWork::HandleOKCallback() {
  Nan::HandleScope scope;
  //turn tree into js object here
  v8::Local<v8::Value> argv[]={Nan::Null(),TreeNodeToObject(jsonTree)};
  //invoke callback
  callback->Call(2,argv);
}

v8::Local<v8::Value> TreeNodeToObject(yajl_val treeNode){
  //This function is to convert a tree node to v8 object
    if (YAJL_IS_STRING(treeNode)) {
      //String value
      return Nan::New(YAJL_GET_STRING(treeNode)).ToLocalChecked().As<v8::Value>();
    }
    else if (YAJL_IS_NUMBER(treeNode)) {
      //Number type
      if(YAJL_IS_INTEGER(treeNode))
        return Nan::New(static_cast<double>(YAJL_GET_INTEGER(treeNode))).As<v8::Value>();
      else if(YAJL_IS_DOUBLE(treeNode))
        return Nan::New(YAJL_GET_DOUBLE(treeNode)).As<v8::Value>();
      else
        //In this situation we need to convert string to double
        return Nan::New(atof(YAJL_GET_NUMBER(treeNode))).As<v8::Value>();
    }
    else if (YAJL_IS_OBJECT(treeNode)) {
      //Object type
      //First create a new object
      v8::Local<v8::Object> newObj=Nan::New<v8::Object>();
      //pointers that point to inner keys and values
      const char** keys=YAJL_GET_OBJECT(treeNode)->keys;
      yajl_val* values=YAJL_GET_OBJECT(treeNode)->values;
      //iterating through and convert
      for(unsigned long i=0;i<YAJL_GET_OBJECT(treeNode)->len;i++)
        Nan::Set(newObj,Nan::New(keys[i]).ToLocalChecked().As<v8::Value>(),TreeNodeToObject(values[i]));
      //return the object
      return newObj.As<v8::Value>();
    }
    else if (YAJL_IS_ARRAY(treeNode)) {
      //Array type
      //Make a blanke array with right size
      v8::Local<v8::Array> newArray=Nan::New<v8::Array>(YAJL_GET_ARRAY(treeNode)->len);
      //Create a pointer that points to the inner array
      yajl_val* values=YAJL_GET_ARRAY(treeNode)->values;
      //convert and fill the array
      for(unsigned long i=0;i<YAJL_GET_ARRAY(treeNode)->len;i++)
        Nan::Set(newArray,i,TreeNodeToObject(values[i]));
      //return the array
      return newArray.As<v8::Value>();
    }
    else if (YAJL_IS_TRUE(treeNode)) {
      //Boolean type -- true
      return Nan::True().As<v8::Value>();
    }
    else if (YAJL_IS_FALSE(treeNode)) {
      //Boolean type -- false
      return Nan::False().As<v8::Value>();
    }
    else if (YAJL_IS_NULL(treeNode)) {
      //Null type
      return Nan::Null().As<v8::Value>();
    }
  //the default return value is a NULL
  //This shouldn't happen in normal condition
  return Nan::Null().As<v8::Value>();
}
