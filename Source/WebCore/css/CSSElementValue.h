/*
 * Copyright (C) 2012 Google Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CSSElementValue_h
#define CSSElementValue_h

#include "CSSImageGeneratorValue.h"
#include "Element.h"

namespace WebCore {

class Document;

class CSSElementValue : public CSSImageGeneratorValue {
public:
    static PassRefPtr<CSSElementValue> create(const String& idSelector) { return adoptRef(new CSSElementValue(idSelector)); }
    ~CSSElementValue();
    
    String customCssText() const;
    
    PassRefPtr<Image> image(RenderObject*, const IntSize&);
    bool isFixedSize() const { return true; }
    IntSize fixedSize(const RenderObject*);
    
    bool isPending() const { return false; }
    void loadSubimages(CachedResourceLoader*) { }
    
private:
    CSSElementValue(const String& idSelector)
    : CSSImageGeneratorValue(ElementClass)
    , m_idSelector(idSelector)
    , m_element(0)
    {
    }
    
    Element* element(Document*);
    
    // The name of the canvas.
    String m_idSelector;
    // The document supplies the element and owns it.
    Element* m_element;
};

} // namespace WebCore

#endif // CSSElementValue_h
