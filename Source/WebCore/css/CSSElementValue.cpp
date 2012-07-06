/*
 * Copyright (C) 2012 Google Inc.  All rights reserved.
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

#include "config.h"
#include "CSSElementValue.h"

#include "ImageBuffer.h"
#include "RenderObject.h"

namespace WebCore {

CSSElementValue::~CSSElementValue()
{
}

String CSSElementValue::customCssText() const
{
    String result = "-webkit-element(";
    result += m_idSelector  + ")";
    return result;
}

IntSize CSSElementValue::fixedSize(const RenderObject* /*renderer*/)
{
    //if (Element* elt = element(renderer->document()))
    //    return IntSize(elt->width(), elt->height());
    return IntSize();
}

Element* CSSElementValue::element(Document* document)
{
    if (!m_element) {
        m_element = document->getElementById(m_idSelector);
        if (!m_element)
            return 0;
    }
    return m_element;
}

PassRefPtr<Image> CSSElementValue::image(RenderObject* /*renderer*/, const IntSize& /*size*/)
{
    // TODO: Mark the element so it creates a render layer.
    // paint the image on an image buffer

    //ASSERT(clients().contains(renderer));
    //HTMLCanvasElement* elt = element(renderer->document());
    //if (!elt || !elt->buffer())
    //    return 0;
    return NULL;
}

} // namespace WebCore
