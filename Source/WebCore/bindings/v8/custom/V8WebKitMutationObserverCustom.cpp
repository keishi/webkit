/*
 * Copyright (C) 2011 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"

#if ENABLE(MUTATION_OBSERVERS)

#include "V8WebKitMutationObserver.h"

#include "V8Binding.h"
#include "V8BindingMacros.h"
#include "V8DOMWrapper.h"
#include "V8MutationCallback.h"
#include "V8Proxy.h"
#include "V8Utilities.h"
#include "WebKitMutationObserver.h"

namespace WebCore {

v8::Handle<v8::Value> V8WebKitMutationObserver::constructorCallback(const v8::Arguments& args)
{
    INC_STATS("DOM.WebKitMutationObserver.Constructor");

    if (!args.IsConstructCall())
        return V8Proxy::throwTypeError("DOM object constructor cannot be called as a function.", args.GetIsolate());

    if (ConstructorMode::current() == ConstructorMode::WrapExistingObject)
        return args.Holder();

    if (args.Length() < 1)
        return V8Proxy::throwNotEnoughArgumentsError(args.GetIsolate());

    v8::Local<v8::Value> arg = args[0];
    if (!arg->IsObject())
        return throwError(TYPE_MISMATCH_ERR, args.GetIsolate());

    ScriptExecutionContext* context = getScriptExecutionContext();
    if (!context)
        return V8Proxy::throwError(V8Proxy::ReferenceError, "WebKitMutationObserver constructor's associated frame unavailable", args.GetIsolate());

    RefPtr<MutationCallback> callback = V8MutationCallback::create(arg, context);
    RefPtr<WebKitMutationObserver> observer = WebKitMutationObserver::create(callback.release());

    V8DOMWrapper::setDOMWrapper(args.Holder(), &info, observer.get());
    V8DOMWrapper::setJSWrapperForDOMObject(observer.release(), v8::Persistent<v8::Object>::New(args.Holder()));
    return args.Holder();
}

} // namespace WebCore

#endif // ENABLE(MUTATION_OBSERVERS)
