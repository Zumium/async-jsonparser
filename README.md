# async-jsonparser
Asynchronous json parser written in C++ for Node.js

## Overview
__async-jsonparser__ provides you a __C++ written, libuv-worker-thread-based JSON parser__ for Node.js, in order to release the V8 
engine from parsing json string. 

## What's going on under the surface ?
When the function gets called, it converts the string into a tree structure firstly. This work is done by one of the worker threads
of the libuv, so V8 engine doesn't have to spend time on this. This helps increasing the performance of Node (compares to V8's 
JSON.parse function).<br><br>
After the converting process completed, the function will convert the tree structure into a JavaScript object, in the event loop
thread. When this final work is completed, the result will be passed to js code as an argument of callback function.

## Other Things
Specially thanks to __@lloyd__. This project embeds YAJL as the actual json-parsing library, which saves me a lot of time from writing
parsing code by myself! Thanks!

##License

The MIT License (MIT)<br>
Copyright (c) 2016 Zumium <martin007323@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
