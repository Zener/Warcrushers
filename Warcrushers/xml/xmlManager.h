// xmlManager.h: interface for the xmlManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLMANAGER_H__453A96E8_7657_4BCB_919C_78C1958BA430__INCLUDED_)
#define AFX_XMLMANAGER_H__453A96E8_7657_4BCB_919C_78C1958BA430__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <windows.h>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMWriter.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/dom/DOMWriterFilter.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/util/XMLString.hpp>
#include "../xmlInterface.hpp"


#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif

XERCES_CPP_NAMESPACE_USE
#define xmlNode DOMNode



 enum NodeType {
        ELEMENT_NODE                = 1,
        ATTRIBUTE_NODE              = 2,
        TEXT_NODE                   = 3,
        CDATA_SECTION_NODE          = 4,
        ENTITY_REFERENCE_NODE       = 5,
        ENTITY_NODE                 = 6,
        PROCESSING_INSTRUCTION_NODE = 7,
        COMMENT_NODE                = 8,
        DOCUMENT_NODE               = 9,
        DOCUMENT_TYPE_NODE          = 10,
        DOCUMENT_FRAGMENT_NODE      = 11,
        NOTATION_NODE               = 12
    };



class xmlManager  : public xmlInterface
{
	public:
		XercesDOMParser					*parser;
		XercesDOMParser::ValSchemes		gValScheme;
		bool							gDoNamespaces;
		bool							gDoSchema;
		bool							gSchemaFullChecking;
		bool							gDoCreate;
		char*							currentFile;
		xmlNode							*root;

		xmlManager();
		virtual ~xmlManager();
		bool loadXml(char* filename);
		xmlNode *getRoot();
		bool validate();
		char *getNodeName(xmlNode *node);
		char *getNodeValue(xmlNode *node);
		int getTagCount(char *tag);
		int getTagCount(xmlNode *node, char *tag);
		

		xmlNode *getNodeByName(char *tag);		
		
		bool	 getBoolValue(char *tag);		
		int		 getIntValue(char *tag);
		float	 getFltValue(char *tag);		
		char	*getStrValue(char *tag);

		xmlNode *getNodeByName(char *tag, int index);		
		
		bool	 getBoolValue(char *tag, int index);
		int		 getIntValue(char *tag, int index);
		float	 getFltValue(char *tag, int index);
		char	*getStrValue(char *tag, int index);
		
		xmlNode *getNodeByName(xmlNode *node, char *tag, int index);		
		bool	 getBoolValue(xmlNode *node, char *tag, int index);
		int		 getIntValue(xmlNode *node, char *tag, int index);
		float	 getFltValue(xmlNode *node, char *tag, int index);
		char	*getStrValue(xmlNode *node, char *tag, int index);
		
		xmlNode *getNodeByName(char *supertag, char *tag, int index);		
		bool	 getBoolValue(char *supertag, char *tag, int index);		
		int		 getIntValue(char *supertag, char *tag, int index);
		float	 getFltValue(char *supertag, char *tag, int index);
		char	*getStrValue(char *supertag, char *tag, int index);
		

		//SET
		bool	 setBoolValue(char *tag, bool value);		
		bool	 setIntValue(char *tag, int value);
		bool	 setFltValue(char *tag, float value);		
		bool	 setStrValue(char *tag, char *value);

		
		void save();



		void dump(xmlNode *node);

	private:
		char *getValueByName(xmlNode *node, char* tag, int index);
		char *getValueByName(xmlNode *node, char *tag, int *index);
		xmlNode *getNodeByName(xmlNode *node, char *tag, int *index);
		void getTagCount(xmlNode *node, char *tag, int *count);
		xmlNode *getTagCountEx(xmlNode *node, char *tag, int index);
		
};

#endif // !defined(AFX_XMLMANAGER_H__453A96E8_7657_4BCB_919C_78C1958BA430__INCLUDED_)
