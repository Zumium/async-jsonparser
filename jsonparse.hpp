#ifndef __JSONPARSE_H
#define __JSONPARSE_H

#include <nan.h>
#include "yajl_tree.h"

class JsonParseWork : public Nan::AsyncWorker {
private:
  char* jsonStr;
  yajl_val jsonTree;

  v8::Local<v8::Value> TreeNodeToObject(yajl_val treeNode);
public:
  JsonParseWork(Nan::Callback* cb,char* json);
  ~JsonParseWork();
  void Execute();
protected:
  void HandleOKCallback();
};

#endif
