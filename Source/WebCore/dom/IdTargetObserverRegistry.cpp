/*
 * Copyright (C) 2012 Google Inc. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "IdTargetObserverRegistry.h"

#include "IdTargetObserver.h"

namespace WebCore {

void IdTargetObserverRegistry::addObserver(const AtomicString& id, IdTargetObserver* observer)
{
    if (id.isEmpty())
        return;

    HashSet<IdTargetObserver*>* set = m_registry.get(id.impl());
    if (!set) {
        set = new HashSet<IdTargetObserver*>();
        m_registry.add(id.impl(), set);
    }

    set->add(observer);
}

void IdTargetObserverRegistry::removeObserver(const AtomicString& id, IdTargetObserver* observer)
{
    if (id.isEmpty() || m_registry.isEmpty())
        return;

    HashSet<IdTargetObserver*>* set = m_registry.get(id.impl());
    if (!set)
        return;

    set->remove(observer);
    if (set->isEmpty())
        m_registry.remove(id.impl());
}

void IdTargetObserverRegistry::removeObserver(IdTargetObserver* observer)
{
    if (m_registry.isEmpty())
        return;

    for (HashMap<AtomicStringImpl*, HashSet<IdTargetObserver*>* >::const_iterator it = m_registry.begin(); it != m_registry.end(); ++it) {
        HashSet<IdTargetObserver*>* set = it->second;
        set->remove(observer);
        if (set->isEmpty())
            m_registry.remove(it->first);
    }
}

void IdTargetObserverRegistry::notifyObservers(const AtomicString& id)
{
    if (id.isEmpty() || m_registry.isEmpty())
        return;

    HashSet<IdTargetObserver*>* set = m_registry.get(id.impl());
    if (!set)
        return;

    for (HashSet<IdTargetObserver*>::const_iterator it = set->begin(); it != set->end(); ++it)
        (*it)->idRefChanged(id);
}

void IdTargetObserverRegistry::notifyAllObservers()
{
    if (m_registry.isEmpty())
        return;

    for (HashMap<AtomicStringImpl*, HashSet<IdTargetObserver*>* >::const_iterator it = m_registry.begin(); it != m_registry.end(); ++it)
            notifyObservers(it->first);
}

} // namespace WebCore
