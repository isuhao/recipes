// excerpts from http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (giantchen at gmail dot com)

#ifndef MUDUO_BASE_THREAD_H
#define MUDUO_BASE_THREAD_H

#include "Atomic.h"

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <pthread.h>

namespace muduo
{

class Thread : boost::noncopyable
{
 public:
  typedef boost::function<void ()> ThreadFunc;

  Thread(const ThreadFunc&, const std::string& name = std::string());
  ~Thread();

  void start();
  void join();

  bool started() const { return started_; }
  // pthread_t pthreadId() const { return pthreadId_; }
  pid_t tid() const { return tid_; }
  const std::string& name() const { return name_; }

  static int numCreated() { return numCreated_.get(); }

 private:
  static void* startThread(void* thread);
  void runInThread();

  bool        started_;
  pthread_t   pthreadId_;
  pid_t       tid_;
  ThreadFunc  func_;
  std::string name_;

  static AtomicInt32 numCreated_;
};

namespace CurrentThread
{
  pid_t tid();
  const char* name();
  bool isMainThread();
}

}

#endif