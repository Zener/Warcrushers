// xmlInterface.h: interface for the xmlManager class.
//
//////////////////////////////////////////////////////////////////////


class xmlNode;





class xmlInterface
{
	public:
		bool							gDoNamespaces;
		bool							gDoSchema;
		bool							gSchemaFullChecking;
		bool							gDoCreate;
		char*							currentFile;
		xmlNode							*root;

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
