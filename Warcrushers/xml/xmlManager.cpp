// xmlManager.cpp: implementation of the xmlManager class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "xmlManager.h"
/*#include <EPGLDRX.h>
#include <RPC.h>
#include <RPCNDR.h>*/
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

xmlManager::xmlManager()
{
    gValScheme				= XercesDOMParser::Val_Auto;
	gDoNamespaces			= false;
	gDoSchema				= false;
	gSchemaFullChecking		= false;
	gDoCreate				= false;


	XMLPlatformUtils::Initialize();

	parser = new XercesDOMParser;
    parser->setValidationScheme(gValScheme);
    parser->setDoNamespaces(gDoNamespaces);
    parser->setDoSchema(gDoSchema);
    parser->setValidationSchemaFullChecking(gSchemaFullChecking);
    parser->setCreateEntityReferenceNodes(gDoCreate);

}





void xmlManager::save()
{
	static const XMLCh gLS[] = { chLatin_L, chLatin_S, chNull };
	DOMImplementation *impl = 
		DOMImplementationRegistry::getDOMImplementation(gLS);

	DOMNode* aDOMNode = root;

	// construct the DOMWriter
	DOMWriter* myWriter = ((DOMImplementationLS*)impl)->createDOMWriter();

	// construct the LocalFileFormatTarget
	XMLFormatTarget *myFormatTarget = new LocalFileFormatTarget(currentFile);
	
	// set the encoding Windows-1252 ISO-8859-1
	/*XMLCh tempStr[100];
	XMLString::transcode("UTF-8", tempStr, 99);
	myWriter->setEncoding(tempStr);*/



	// serialize a DOMNode to the local file "myXMLFile.xml"
	myWriter->writeNode(myFormatTarget, *aDOMNode);

	// optionally, you can flush the buffer to ensure all contents are written
	myFormatTarget->flush();

	// release the memory
	myWriter->release();
	delete myFormatTarget; 

}







xmlManager::~xmlManager()
{
	XMLPlatformUtils::Terminate();
}



bool xmlManager::loadXml(char* filename)
{
	currentFile = filename;
	parser->parse(currentFile);
	root = (xmlNode *)parser->getDocument();	
	return true;
}


xmlNode* xmlManager::getRoot()
{
	return root;
}


bool xmlManager::validate()
{
	return true;
}


/*void xmlManager::getTagCount(xmlNode *node, char *tag, int *count)
{
	XMLString *s;

	if (node == NULL) return;

	if (strcmp(s->transcode(node->getNodeName()), tag) == 0) *count++;

	xmlNodeList *lst = node->getChildNodes();

	if (lst == NULL) return;

	int i = 0;

	while(i < lst->getLength())
	{
		getTagCount(lst->item(i), tag, count);
		i++;
	}

	return;
}*/


int xmlManager::getTagCount(char *tag)
{
	int count = 0;
	while (getNodeByName(tag, count+1) != NULL) count++;
		
	return count;
	/*DOMDocument *dd;			
	int count = 0;

	dd = (DOMDocument*)getRoot();		  
	
	getTagCount((xmlNode *)(dd->getDocumentElement()), tag, &count);
	return count;*/
}

int xmlManager::getTagCount(xmlNode *node, char *tag)
{
	int count = 0;

	while (getTagCountEx(node, tag, count+1) != NULL) 
		count++;
		
	//exit(1);
	return count;
}


xmlNode *xmlManager::getTagCountEx(xmlNode *node, char *tag, int index)
{
	int idx = index;
	return getNodeByName(node, tag, &idx);		

}









char *xmlManager::getValueByName(xmlNode *node, char *tag, int index)
{
	//ARREGALR
	//El index ha de ir por referenciaaaaaa
	char* result = NULL;
	DOMNode *_node;
	XMLString *s;

	if (node == NULL) return NULL;
	DOMNodeList *lst = node->getChildNodes();

	bool found = false;
	int nfound = 0;
	int i = 0;

	//printf("n: %d", lst->getLength());
	while(!found && i < lst->getLength())
	{
		_node = lst->item(i);
		//printf("s: %s\n", s->transcode(_node->getNodeName()));
		if (strcmp(s->transcode(_node->getNodeName()), tag) == 0)
		{
			nfound++;
			if (nfound == index)	found = true;
		}                                       
		else i++;		
		//if (!found) getValueByName(_node, char *tag, int index)
	}

	if (found) result = s->transcode(_node->getNodeValue());
	

    return result;
}


bool xmlManager::getBoolValue(char *tag)
{
	int idx = 1;
	char *rets;
	bool ret = false;
	char *stop;
	rets = getValueByName(getRoot(), tag, &idx);
	if (rets != NULL) ret = strcmp(rets, "true") == 0;
	return ret;
}


int xmlManager::getIntValue(char *tag)
{
	int idx = 1;
	char *rets;
	int ret = -1;
	char *stop;
	rets = getValueByName(getRoot(), tag, &idx);
	if (rets != NULL) ret = strtol(rets, &stop, 10) ;
	return ret;
}


float xmlManager::getFltValue(char *tag)
{
	int idx = 1;
	char *rets;
	float ret = 0;
	char *stop;
	rets = getValueByName(getRoot(), tag, &idx);
	if (rets != NULL) ret = (float)strtod(rets, &stop) ;
	return ret;
}

char* xmlManager::getStrValue(char *tag)
{
	int idx = 1;
	char *rets;
	rets = getValueByName(getRoot(), tag, &idx);
	return rets;
}




int xmlManager::getIntValue(char *tag, int index)
{
	int idx = index;
	char *rets;
	int ret = -1;
	char *stop;
	rets = getValueByName(getRoot(), tag, &idx);
	if (rets != NULL) ret = strtol(rets, &stop, 10) ;
	return ret;
}


float xmlManager::getFltValue(char *tag, int index)
{
	int idx = index;
	char *rets;
	float ret = 0;
	char *stop;
	rets = getValueByName(getRoot(), tag, &idx);
	if (rets != NULL) ret = (float)strtod(rets, &stop) ;
	return ret;
}



char* xmlManager::getStrValue(char *tag, int index)
{
	int idx = index;
	char *rets;
	rets = getValueByName(getRoot(), tag, &idx);
	return rets;
}


int xmlManager::getIntValue(xmlNode *node, char *tag, int index)
{
	int idx = index;
	char *rets;
	int ret = -1;
	char *stop;
	rets = getValueByName(node, tag, &idx);
	if (rets != NULL) ret = strtol(rets, &stop, 10) ;
	return ret;
}


bool xmlManager::getBoolValue(xmlNode *node, char *tag, int index)
{
	int idx = index;
	char *rets;
	int ret = 0;
	char *stop;
	rets = getValueByName(node, tag, &idx);
	if (rets != NULL) ret = strcmp(rets, "true") == 0;
	return ret;
	
}



//#include <stdio.h>

float xmlManager::getFltValue(xmlNode *node, char *tag, int index)
{
	int idx = index;
	char *rets;
	float ret = 0;
	char *stop;
	rets = getValueByName(node, tag, &idx);
	//printf("HOLA !!!");
	if (rets != NULL) ret = (float)strtod(rets, &stop) ;
	return ret;
}



char* xmlManager::getStrValue(xmlNode *node, char *tag, int index)
{
	int idx = index;
	char *rets = NULL;
	rets = getValueByName(node, tag, &idx);
	return rets;
}


bool xmlManager::getBoolValue(char *supertag, char *tag, int index)
{
	int idx = index;
	char *rets;
	bool ret = false;
	char *stop;
	rets = getValueByName(getNodeByName(supertag), tag, &idx);
	if (rets != NULL) ret = strcmp(rets, "true") == 0;
	return ret;

}


int xmlManager::getIntValue(char *supertag, char *tag, int index)
{
	int idx = index;
	char *rets;
	int ret = -1;
	char *stop;
	rets = getValueByName(getNodeByName(supertag), tag, &idx);
	if (rets != NULL) ret = strtol(rets, &stop, 10) ;
	return ret;

}


float xmlManager::getFltValue(char *supertag, char *tag, int index)
{
	int idx = index;
	char *rets;
	float ret = 0;
	char *stop;
	rets = getValueByName(getNodeByName(supertag), tag, &idx);
	if (rets != NULL) ret = (float)strtod(rets, &stop) ;
	return ret;

}

char* xmlManager::getStrValue(char *supertag, char *tag, int index)
{
	int idx = index;
	char *rets;
	rets = getValueByName(getNodeByName(supertag), tag, &idx);
	return rets;
}




xmlNode *xmlManager::getNodeByName(char *tag)
{
	int idx = 1;
	return getNodeByName(getRoot(), tag, &idx);
}

xmlNode *xmlManager::getNodeByName(char *tag, int index)
{
	int idx = index;
	return getNodeByName(getRoot(), tag, &idx);
}

xmlNode *xmlManager::getNodeByName(xmlNode *node, char *tag, int index)
{
	int idx = index;
	return getNodeByName(node, tag, &idx);
}


char *xmlManager::getValueByName(xmlNode *node, char *tag, int *index)
{
	//XMLString *s;

	//return s->transcode(getNodeByName(node, tag, index)->getFirstChild()->getNodeValue());


	
	char* result = NULL;
	DOMNode *_node;
	XMLString *s;

	if (node == NULL) return NULL;
	DOMNodeList *lst = node->getChildNodes();


	bool found = false;
	int nfound = 0;
	int i = 0;

	DOMNamedNodeMap *attrs = node->getAttributes();
	if (attrs != NULL) 
	{
		int len = attrs->getLength();
		for (int i = 0; i < len; i++) 
		{
				if (strcmp(s->transcode(attrs->item(i)->getNodeName()), tag) == 0)
				{
					nfound++;	
					if (index == NULL || nfound == *index)	
					{
					
						found = true;
						//if (index != NULL) *index --;
						result = s->transcode(attrs->item(i)->getNodeValue());
					}
					else if (index != NULL)
					{
						(*index)--;
						
					}
					
					
				}
		}
	}

	//if (lst == NULL) return NULL;//NUEVO

	while(!found && i < lst->getLength())
	{
		_node = lst->item(i);
		
		
		if (strcmp(s->transcode(_node->getNodeName()), tag) == 0)
		{
			nfound++;
			if (index == NULL || nfound == *index)	
			{
				found = true;
				//if (index != NULL) (*index --;//NO ME ACABA DE GUSTAR
				result = s->transcode(_node->getFirstChild()->getNodeValue());	
			}
			//AQUI FALTA DECREMENTAR INDEX
		}                                       
		i++;		
		//if (index != NULL) *index -= nfound;
		if (!found) 
		{	
			result = getValueByName((xmlNode *)_node, tag, index);
			if (result != NULL) found = true;
		}		
	}
	//NO ME ACABA DE GUSTAR
	if (found && result == NULL) 
	{
		result = s->transcode(_node->getFirstChild()->getNodeValue());	
		printf("*@*");
	}

	return result;
}



xmlNode *xmlManager::getNodeByName(xmlNode *node, char *tag, int *index)
{
	xmlNode * result = NULL;
	DOMNode *_node;
	XMLString *s;

	if (node == NULL) return NULL;
	DOMNodeList *lst = node->getChildNodes();

	bool found = false;
	int nfound = 0;
	int i = 0;

	DOMNamedNodeMap *attrs = node->getAttributes();
	if (attrs != NULL) 
	{
		int len = attrs->getLength();
		for (int i = 0; i < len; i++) 
		{
				if (strcmp(s->transcode(attrs->item(i)->getNodeName()), tag) == 0)
				{
					nfound++;	
					if (index == NULL || nfound == *index)	
					{
						found = true;
						result = (xmlNode *)attrs->item(i);
					}
				}
		}
	}

	
	while(lst != NULL && !found && i < lst->getLength())
	{
		_node = lst->item(i);
		if (strcmp(s->transcode(_node->getNodeName()), tag) == 0)
		{
			nfound++;
			if (index == NULL || nfound == *index)	
			{
				found = true;
				if (index != NULL) *index --;
				result = (xmlNode *)_node;
			}			
		}                                       
		//else 
			i++;				
		if (!found) 
		{	
			result = getNodeByName((xmlNode *)_node, tag, index);
			if (result != NULL) found = true;
		}		
	}

	//if (found && result == NULL) result = _node->getFirstChild();	

	return result;
}



bool	 xmlManager::setBoolValue(char *tag, bool value)
{
	XMLString *s;
	char *strValue = new char[16];
	DOMNode *node;
	//char *s1, *s2;
	

	if (value) 
		sprintf(strValue, "true\0");
	else 
		sprintf(strValue, "false\0");

	node = getNodeByName(tag);
	node->getFirstChild()->setNodeValue(s->transcode(strValue));
	
	//s1 = s->transcode(node->getNodeName());
	//s2 = s->transcode(node->getFirstChild()->getNodeValue());
	//printf("node: %s  value: %s \n", s1, s2);
	
	if (node) return true;
	return false;
}


bool	 xmlManager::setIntValue(char *tag, int value)
{
	XMLString *s;
	char *strValue = new char[256];
	DOMNode *node;
	
	sprintf(strValue, "%d\0", value);
	
	node = getNodeByName(tag);
	node->getFirstChild()->setNodeValue(s->transcode(strValue));
	
	if (node) return true;
	return false;
}



bool	 xmlManager::setFltValue(char *tag, float value)
{
	XMLString *s;
	char *strValue = new char[256];
	DOMNode *node;
	
	sprintf(strValue, "%f\0", value);
	
	node = getNodeByName(tag);
	node->getFirstChild()->setNodeValue(s->transcode(strValue));
	
	if (node) return true;
	return false;
}



bool	 xmlManager::setStrValue(char *tag, char *value)
{
	XMLString *s;
	char *strValue = new char[1024];
	DOMNode *node;
	
	sprintf(strValue, "%s\0", value);
	
	node = getNodeByName(tag);
	node->getFirstChild()->setNodeValue(s->transcode(strValue));
	
	if (node) return true;
	return false;
}








char *xmlManager::getNodeName(xmlNode *node)
{
	char* result = NULL;
	return result;
}


char *xmlManager::getNodeValue(xmlNode *node)
{
	char* result = NULL;
	return result;
}


/*xmlNode *xmlManager::getNodeByName(xmlNode *node, char *tag, int *index)
{
	//ARREGLAR INDEXC NULL
	xmlNode* result = NULL;
	xmlNode *_node;
	XMLString *s;

	if (node == NULL) return NULL;
	xmlNodeList *lst = node->getChildNodes();

	BOOL found = false;
	int nfound = 0;
	int i = 0;

	DOMNamedNodeMap *attrs = node->getAttributes();
	if (attrs != NULL) 
	{
		int len = attrs->getLength();
		for (int i = 0; i < len; i++) 
		{
				if (strcmp(s->transcode(attrs->item(i)->getNodeName()), tag) == 0)
				{
					nfound++;				
					if (nfound == *index)	
					{
						found = true;
						result = attrs->item(i);
					}
				}
		}
	}

	while(!found && i < lst->getLength())
	{
		_node = lst->item(i);
		if (strcmp(s->transcode(_node->getNodeName()), tag) == 0)
		{
			nfound++;
			if (nfound == *index)	found = true;
		}                                       
		else i++;		
		*index -= nfound;
		if (!found) 
		{	
			result = getNodeByName(_node, tag, index);
			if (result != NULL) found = true;
		}		
	}

	if (found && result == NULL) result = _node->getFirstChild();	

	return result;



	return result;
}
*/


void xmlManager::dump(xmlNode *node)
{
	 	/*xmlNodeList *children;
		DOMNamedNodeMap *attrs;
		char * ss;
		XMLString *s;
//		DOMText *dt;

		if (node == NULL) return; // is there anything to do?

		//printf("\n%d\n", node->getNodeType());
		switch (node->getNodeType()) 
		{ 
			case DOCUMENT_NODE: // print document
				//printf("\nDOCUMENT: ");
				DOMDocument *dd;
				dd = (DOMDocument*)node;		  
				dump((xmlNode*)dd->getDocumentElement());				
				break;
	
			case ELEMENT_NODE: //Node.ELEMENT_NODE: 
				// print element with attributes
				//printf("\nELEMENT: ");				
				ss = s->transcode(node->getNodeName());
				//printf(ss);									
				attrs = node->getAttributes();
				if (attrs != NULL) 
				{
					int len = attrs->getLength();
					//printf(" : %d",len);
					for (int i = 0; i < len; i++) dump(attrs->item(i));
				}
				children = node->getChildNodes();
				if (children != NULL) 
				{
					int len = children->getLength();
					//printf(" : %d",len);
					for (int i = 0; i < len; i++) dump(children->item(i));					
				}
				break;

			case ENTITY_REFERENCE_NODE:
				//printf("\nENTITY_REFERENCE_NODE: ");				
				children = node->getChildNodes();
				if (children != NULL) 
				{
					int len = children->getLength();
					for (int i = 0; i < len; i++) dump(children->item(i));
				}
				break;

			case CDATA_SECTION_NODE:
				//printf("\nCDATA_SECTION_NODE: ");				
				break;

			case TEXT_NODE:		
				ss = s->transcode(node->getNodeValue());
				//!!printf("\n      TEXTNODE: ");									
				//!!printf(ss);
				break;
			case ATTRIBUTE_NODE:
				//printf("\n   ATTRIBUTE_NODE: ");
				ss = s->transcode(node->getNodeName());
				//printf(ss);
				//printf(" - ");
				ss = s->transcode(node->getNodeValue());
				//printf(ss);				
				break;
		}		*/
  }
