/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2003 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xerces" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache\@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation, and was
 * originally based on software copyright (c) 1999, International
 * Business Machines, Inc., http://www.ibm.com .  For more information
 * on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

/*
 * $Log: XSAttributeUse.hpp,v $
 * Revision 1.5  2003/11/21 17:19:30  knoaman
 * PSVI update.
 *
 * Revision 1.4  2003/11/14 22:47:53  neilg
 * fix bogus log message from previous commit...
 *
 * Revision 1.3  2003/11/14 22:33:30  neilg
 * Second phase of schema component model implementation.  
 * Implement XSModel, XSNamespaceItem, and the plumbing necessary
 * to connect them to the other components.
 * Thanks to David Cargill.
 *
 * Revision 1.2  2003/11/06 15:30:04  neilg
 * first part of PSVI/schema component model implementation, thanks to David Cargill.  This covers setting the PSVIHandler on parser objects, as well as implementing XSNotation, XSSimpleTypeDefinition, XSIDCDefinition, and most of XSWildcard, XSComplexTypeDefinition, XSElementDeclaration, XSAttributeDeclaration and XSAttributeUse.
 *
 * Revision 1.1  2003/09/16 14:33:36  neilg
 * PSVI/schema component model classes, with Makefile/configuration changes necessary to build them
 *
 */

#if !defined(XSATTRIBUTEUSE_HPP)
#define XSATTRIBUTEUSE_HPP

#include <xercesc/framework/psvi/XSObject.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
 * This class describes all properties of a Schema Attribute
 * Use component.
 * This is *always* owned by the validator /parser object from which
 * it is obtained.  
 */

// forward declarations
class XSAttributeDeclaration;

class XMLPARSER_EXPORT XSAttributeUse : public XSObject
{
public:

    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    /** @name Constructors */
    //@{

    /**
      * The default constructor 
      *
      * @param  manager     The configurable memory manager
      */
    XSAttributeUse
    (
        XSAttributeDeclaration* const xsAttDecl,
        XSModel* const xsModel,
        MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    //@};

    /** @name Destructor */
    //@{
    ~XSAttributeUse();
    //@}

    //---------------------
    /** @name XSAttributeUse methods /

    //@{

    /**
     * [required]: determines whether this use of an attribute declaration 
     * requires an appropriate attribute information item to be present, or 
     * merely allows it. 
     */
    bool getRequired() const;

    /**
     * [attribute declaration]: provides the attribute declaration itself, 
     * which will in turn determine the simple type definition used. 
     */
    XSAttributeDeclaration *getAttrDeclaration() const;

    /**
     * Value Constraint: one of default, fixed. 
     */
    XSConstants::VALUE_CONSTRAINT getConstraintType() const;

    /**
     * Value Constraint: The actual value. 
     */
    const XMLCh *getConstraintValue();

    //@}

    //----------------------------------
    /** methods needed by implementation */

    //@{

    //@}

private:

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XSAttributeUse(const XSAttributeUse&);
    XSAttributeUse & operator=(const XSAttributeUse &);

protected:

    // -----------------------------------------------------------------------
    //  data members
    // -----------------------------------------------------------------------
    XSAttributeDeclaration* fXSAttributeDeclaration;
};

inline XSAttributeDeclaration *XSAttributeUse::getAttrDeclaration() const
{
    return fXSAttributeDeclaration;
}


XERCES_CPP_NAMESPACE_END

#endif
