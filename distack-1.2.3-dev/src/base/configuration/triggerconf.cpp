//////////////////////////////////////////////////////////
/*********************************************************
 *
 * Triggerconf XML wrapper for the XercesC library
 *
 * This version of Triggerconf works with XercesC v3.x.x
 *
 *********************************************************/
//////////////////////////////////////////////////////////

#include "triggerconf.h"

Triggerconf::Triggerconf(string _filename, bool _autocreateitems, bool _mustexist, bool _savechanges)
	: file( _filename ), autocreate( _autocreateitems ), savechanges( _savechanges ) {

	rootnode	= NULL;
	goodstate	= true;
	lasterror	= "";
    
	try {

		XMLPlatformUtils::Initialize();

		//
		// if the file does not exists we create it with the root node
		// but only if the constructor parameter is fine with this
		//

		FileHandle filehandle = XMLPlatformUtils::openFile (file.c_str ());
		
		if (filehandle == NULL && _mustexist == false) {

			static const XMLCh	gLS []	= {chLatin_L, chLatin_S, chNull};
			DOMImplementation*	impl	= DOMImplementationRegistry::getDOMImplementation(gLS);
			
			XMLCh*			xroot	= XMLString::transcode( ROOT_NAME );
			DOMDocument*		doc	= impl->createDocument( 0, xroot, 0 );
			DOMElement*		elemrt	= doc->getDocumentElement();
			DOMLSSerializer* 	writer  = ((DOMImplementationLS*)impl)->createLSSerializer();
			
			XMLString::release (&xroot);

			if (writer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true))
				writer->getDomConfig()->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);

			if (writer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTBOM, true))
				writer->getDomConfig()->setParameter(XMLUni::fgDOMWRTBOM, true);

			XMLFormatTarget* target	= new LocalFileFormatTarget (file.c_str ());
			target->flush();

			DOMLSOutput* output = ((DOMImplementationLS*)impl)->createLSOutput();
        		output->setByteStream( target );
            		writer->write( elemrt, output );

			writer->release();
			doc->release();

			delete output;
			delete target;

		} else if (filehandle == NULL && _mustexist == true) {

			setError ("file " + file + " does not exist");
			return;

		} else {

			XMLPlatformUtils::closeFile (filehandle);

		}

		//
		// parse the file
		//

		parser		= new XercesDOMParser ();
		errhandler	= (ErrorHandler*) new HandlerBase ();

		parser->setErrorHandler	(errhandler);
		parser->parse		(file.c_str ());
		rootnode		= getChildOfType (parser->getDocument (), DOMNode::ELEMENT_NODE);

		if (rootnode != NULL) {
		
			char* xmlstring = XMLString::transcode (rootnode->getNodeName ());

			if (((string) ROOT_NAME).compare (xmlstring) == 0)
				resetError();
			else
				setError("invalid root item in file " + file);
		
			XMLString::release (&xmlstring);

		} else
			setError("parsing xml file " + file + " failed");	

	} catch (const XMLException& toCatch) {
		char* message = XMLString::transcode (toCatch.getMessage());
		setError ("failed parsing file " + file + ": " + message);
		XMLString::release(&message);
	}
	catch (const DOMException& toCatch) {
		char* message = XMLString::transcode (toCatch.msg);
		setError ("failed parsing file " + file + ": " + message);
		XMLString::release(&message);
	}
	catch (...) {
		setError( "failed parsing file " + file );
	}

}

Triggerconf::~Triggerconf ()
{
	if( savechanges ){
	
		//
		// save file
		//
	
		static const XMLCh	gLS []	= {chLatin_L, chLatin_S, chNull};
		DOMImplementation*	impl	= DOMImplementationRegistry::getDOMImplementation(gLS);
		DOMLSSerializer*	writer	= ((DOMImplementationLS*)impl)->createLSSerializer();
	
		if (writer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true))
			writer->getDomConfig()->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
	
		if (writer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTBOM, true))
			writer->getDomConfig()->setParameter(XMLUni::fgDOMWRTBOM, true);
	
		XMLFormatTarget* target	= new LocalFileFormatTarget (file.c_str ());
		target->flush();
	
		DOMLSOutput* output = ((DOMImplementationLS*)impl)->createLSOutput();
		output->setByteStream( target );
		writer->write( rootnode , output );
		
		writer->release();
		delete target;
		delete output;

	} // if( savechanges )

	//
	// delete all stuff here
	//

	delete parser;
	delete errhandler;

	//
	// now we can safely terminate xerces
	//

	XMLPlatformUtils::Terminate();
}

bool Triggerconf::isGood () 
{ 
	return goodstate;
}

string Triggerconf::getError ()
{ 
	return lasterror;
}

DOMNode* Triggerconf::selectModule (string modulename)
{
	if(rootnode == NULL) {
		setError ("invalid root node");	
		return NULL;
	}

	DOMNodeList* childs = rootnode->getChildNodes ();
	
	if (childs == NULL) {

		if (autocreate == false) {
			setError ("module " + modulename + " not found");
			return NULL;
		} else {
			resetError ();
			createModule (modulename);
			return selectModule (modulename);
		}

	} // if (childs == NULL) 
		
	for (unsigned int i=0; i<childs->getLength (); i++) {
		
		DOMNode* node = childs->item (i);
		if (node == NULL || node->getNodeType () != DOMNode::ELEMENT_NODE) continue;
		
		char* xmlstring = XMLString::transcode (node->getNodeName ());
		
		if (((string) ELEMENT_MODULE_NAME).compare (xmlstring) != 0) {
			XMLString::release (&xmlstring);
			continue;
		}
		
		XMLString::release (&xmlstring);

		if ((getAttributeValue (node, ATTRIBUTE_NAME)).compare (modulename) == 0) {
			resetError ();		
			return node;
		}

	} // for (unsigned int i=0; i<childs->getLength (); i++)

	if (autocreate == false) {
		setError ("module " + modulename + " not found");
		return NULL;
	} else {
		resetError ();
		createModule (modulename);
		return selectModule (modulename);
	}
}

void Triggerconf::resetError ()
{
	goodstate = true;
	lasterror = "";
}

void Triggerconf::setError (string err)
{
	goodstate = false; 
	lasterror = err;
}

DOMNode* Triggerconf::selectSubmodule (string modulename, string submodulename)
{
	DOMNode* currentModule = selectModule (modulename);

	if (currentModule == NULL) {
		setError ("invalid module: " + modulename);
		return NULL;
	}

	DOMNodeList* childs = currentModule->getChildNodes ();
	
	if (childs == NULL) {

		if (autocreate == false) {
			setError ("submodule " + modulename + " not found");
			return NULL; 
		} else {
			resetError ();
			createSubmodule (modulename, submodulename);
			return selectSubmodule (modulename, submodulename);
		}

	} // if (childs == NULL) 

	for (unsigned int i=0; i<childs->getLength (); i++) {
		
		DOMNode* node = childs->item (i);
		if (node == NULL || node->getNodeType () != DOMNode::ELEMENT_NODE) continue;
		
		char* xmlstring = XMLString::transcode (node->getNodeName ());

		if (((string) ELEMENT_SUBMODULE_NAME).compare (xmlstring) != 0) {
			XMLString::release (&xmlstring);
			continue;
		}

		XMLString::release (&xmlstring);

		if ((getAttributeValue (node, ATTRIBUTE_NAME)).compare (submodulename) == 0) {		
			resetError ();		
			return node;
		}

	} // for (unsigned int i=0; i<childs->getLength (); i++)

	if (autocreate == false) {
		setError ("submodule " + submodulename + " not found");
		return NULL;
	} else {
		resetError ();
		createSubmodule (modulename, submodulename);
		return selectSubmodule (modulename, submodulename);
	}
}

DOMNode* Triggerconf::selectConfigElement (string modulename, string submodulename, string configname)
{
	DOMNode* currentSubmodule = selectSubmodule (modulename, submodulename);
	if (currentSubmodule == NULL) {
		setError ("invalid submodule " + submodulename + " in module " + modulename);
		return NULL;
	}

	DOMNodeList* childs = currentSubmodule->getChildNodes ();
	if (childs == NULL) {
		setError ("submodule " + submodulename + " in module " + modulename + " not found");
		return NULL;
	}

	for (unsigned int i=0; i<childs->getLength (); i++) {
		
		DOMNode* child = childs->item (i);
		if (child == NULL || child->getNodeType () != DOMNode::ELEMENT_NODE) continue;

		char* xmlstring = XMLString::transcode (child->getNodeName ());

		if (((string) ELEMENT_CONFIGITEM_NAME).compare (xmlstring) != 0) {
			XMLString::release (&xmlstring);		
			continue;
		}

		XMLString::release (&xmlstring);		

		if ((getAttributeValue (child, ATTRIBUTE_NAME)).compare (configname) == 0) {		
			resetError ();		
			return child;
		}

	} // for (unsigned int i=0; i<childs->getLength (); i++) 

	if (autocreate == false) {
		setError ("configelement " + configname + " not found");
		return NULL; 
	} else {
		resetError ();
		createConfigElement (modulename, submodulename, configname);
		return selectConfigElement (modulename, submodulename, configname);
	}
}

string Triggerconf::getAttributeValue (DOMNode* element, string attributename)
{
	if (element == NULL) return "";
	if (element->getNodeType () != DOMNode::ELEMENT_NODE) return "";

	DOMElement*  	domelem		= (DOMElement*) element;
	XMLCh*		xattrname	= XMLString::transcode	(attributename.c_str ());
	const XMLCh*	xattrval	= domelem->getAttribute (xattrname);
	char*		charval		= XMLString::transcode	(xattrval);
	string		ret		= charval;
	
	XMLString::release	(&xattrname);
	//XMLString::release	(&xattrval);
	XMLString::release	(&charval);

	return ret;
}

string Triggerconf::getConfigValue (string module, string submodule, string configname)
{
	if (existsConfigElement (module, submodule, configname) == false) {
		setError ("invalid config element");	
		return "";
	}

	DOMNode* node = selectConfigElement (module, submodule, configname);
	if (node == NULL) return "";

	const XMLCh* xval	= node->getTextContent ();
	char*	charstring	= XMLString::transcode (xval);
	string	ret		= charstring;
	XMLString::release	(&charstring);

	resetError ();

	return ret;
}

string Triggerconf::getConfigValue (string path)
{
	if (! checkItemCount (path, 3)) return "";

	STRING_LIST items = tokenize (path);
	return getConfigValue (items [0], items [1], items [2]);
}

string Triggerconf::getConfigAttributeValue(string module, string submodule, string configname, string attributename)
{
	if (! existsConfigElement (module, submodule, configname)) {
		setError ("invalid config element");
		return "";
	}

	DOMNode* node = selectConfigElement (module, submodule, configname);
	assert (node->getNodeType () == DOMNode::ELEMENT_NODE);
	DOMElement* elem = (DOMElement*) node;
	
	XMLCh*	xattrname	= XMLString::transcode (attributename.c_str ());
	const XMLCh* xattrval	= elem->getAttribute (xattrname);
	char*	charstring	= XMLString::transcode (xattrval);
	string	ret		= charstring;

	XMLString::release	(&xattrname);
	XMLString::release	(&charstring);

	resetError		();

	return ret;
}

string Triggerconf::getConfigAttributeValue (string path)
{
	if (! checkItemCount (path, 4)) return "";
	
	STRING_LIST items = tokenize (path);
	return getConfigAttributeValue (items [0], items [1], items [2], items [3]);
}

string Triggerconf::getSubmoduleAttributeValue (string module, string submodule, string attributename)
{
	if (! existsSubmodule (module, submodule)) {
		setError ("invalid submodule");
		return "";
	}

	DOMNode* node = selectSubmodule (module, submodule);
	assert (node->getNodeType () == DOMNode::ELEMENT_NODE);
	DOMElement* elem = (DOMElement*) node;
	
	XMLCh*	xattrname	= XMLString::transcode (attributename.c_str ());
	const XMLCh* xattrval	= elem->getAttribute (xattrname);
	char*	charstring	= XMLString::transcode (xattrval);
	string	ret		= charstring;

	XMLString::release	(&xattrname);
	XMLString::release	(&charstring);

	resetError		();

	return ret;
}

Triggerconf::STRING_LIST Triggerconf::tokenize (string path)
{
	STRING_LIST ret;
	
	int first = 0;
	int last = 0; 

	while (true) {

		last = (int) path.find (PATH_DELIMITER, first);
		
		if (last == (int)string::npos) {
			if (path.length () - first >= 1)
				ret.push_back (path.substr (first, path.length () - first));			
			break;
		}
		
		if (last-first >= 1)
			ret.push_back (path.substr (first, last-first));

		first = last + 1;
	}

	return ret;
}

string Triggerconf::untokenize (STRING_LIST path)
{
	STRING_LIST::iterator begin = path.begin();
	STRING_LIST::iterator end = path.end();
	string ret;

	for ( ; begin != end; begin++) {
		
		if (ret.length () == 0)
			ret += *begin;
		else
			ret += (PATH_DELIMITER + *begin);

	}

	return ret;
}

DOMNode* Triggerconf::getChildOfType (DOMNode* root, short type, unsigned int index)
{
	if (root == NULL) return NULL;
	if (! root->hasChildNodes ()) return NULL;

	DOMNodeList* childs = root->getChildNodes ();
	if (childs == NULL) return NULL;

	unsigned int idx = 0;

	for (unsigned int i=0; i<childs->getLength (); i++) {
		DOMNode* child = childs->item (i);

		if (child->getNodeType () == type) {
			if (idx == index)
				return child;
			else
				idx++;
		}
	} // for (unsigned int i=0; i<childs->getLength (); i++)

	return NULL;
}

void Triggerconf::createModule (string module)
{
	if (rootnode == NULL) return;
	
	if (existsModule (module)) {
		resetError ();	
		return;
	}

	XMLCh* xmodulename	= XMLString::transcode (ELEMENT_MODULE_NAME);
	DOMElement* node	= rootnode->getOwnerDocument ()->createElement	(xmodulename);
	XMLString::release	(&xmodulename);

	XMLCh* xattrname	= XMLString::transcode (ATTRIBUTE_NAME);
	XMLCh* xmodule		= XMLString::transcode (module.c_str ());
	node->setAttribute	(xattrname, xmodule);

	XMLString::release	(&xattrname);
	XMLString::release	(&xmodule);

	rootnode->appendChild (node);

	resetError ();
}

void Triggerconf::createSubmodule (string module, string submodule)
{
	if (rootnode == NULL) return;
	
	if (existsSubmodule (module, submodule)) {
		resetError ();	
		return;
	}

	DOMNode* currentModule	= selectModule (module);
	if (currentModule == NULL) return;
	
	XMLCh* xsubmodule	= XMLString::transcode (ELEMENT_SUBMODULE_NAME);
	DOMElement* node	= rootnode->getOwnerDocument ()->createElement	(xsubmodule);
	XMLString::release	(&xsubmodule);

	XMLCh* xattrname	= XMLString::transcode (ATTRIBUTE_NAME);
	XMLCh* xsubmodulename	= XMLString::transcode (submodule.c_str ());
	node->setAttribute	(xattrname, xsubmodulename);
	XMLString::release	(&xattrname);
	XMLString::release	(&xsubmodulename);

	currentModule->appendChild (node);

	resetError ();
}

void Triggerconf::createSubmodule (string path)
{
	if (! checkItemCount (path, 2)) return;
	
	STRING_LIST items = tokenize (path);
	createSubmodule (items [0], items [1]);
}

void Triggerconf::createConfigElement (string module, string submodule, string configname)
{
	if (rootnode == NULL) return;
	
	if (existsConfigElement (module, submodule, configname)) {
		resetError ();	
		return;
	}

	DOMNode* currentSubmodule = selectSubmodule (module, submodule);
	if (currentSubmodule == NULL) return;

	XMLCh* xitemname	= XMLString::transcode (ELEMENT_CONFIGITEM_NAME);
	DOMElement* node	= rootnode->getOwnerDocument ()->createElement	(xitemname);
	XMLString::release	(&xitemname);

	XMLCh* xattrname	= XMLString::transcode (ATTRIBUTE_NAME);
	XMLCh* xconfigname	= XMLString::transcode (configname.c_str ());
	node->setAttribute	(xattrname, xconfigname);
	XMLString::release	(&xattrname);
	XMLString::release	(&xconfigname);

	currentSubmodule->appendChild (node);

	resetError ();
}

void Triggerconf::createConfigElement (string path)
{
	if (! checkItemCount (path, 3))	return;

	STRING_LIST items = tokenize (path);
	createConfigElement (items [0], items [1], items [2]);
}

void Triggerconf::createConfigAttribute	(string module, string submodule, string configname, string attributename)
{
	//
	// attributes are always created, no matter if they exists or not
	// dublication is prevented by xercesc
	//

	DOMNode* currentConfigElement = selectConfigElement (module, submodule, configname);
	if (currentConfigElement == NULL) return;
	
	assert (currentConfigElement->getNodeType () == DOMNode::ELEMENT_NODE);
	DOMElement* elem = (DOMElement*) currentConfigElement;

	XMLCh* xattrname	= XMLString::transcode (attributename.c_str ());
	XMLCh* xempty		= XMLString::transcode ("");
	elem->setAttribute	(xattrname, xempty);
	XMLString::release	(&xattrname);
	XMLString::release	(&xempty);

	resetError ();
}

void Triggerconf::createConfigAttribute (string path)
{
	if (! checkItemCount (path, 4)) return;

	STRING_LIST items = tokenize (path);
	createConfigAttribute (items [0], items [1], items [2], items [3]); 
}

void Triggerconf::setConfigValue (string module, string submodule, string configname, string value)
{
	DOMNode* currentConfigElement = selectConfigElement (module, submodule, configname);
	if (currentConfigElement == NULL) return;
	
	assert (currentConfigElement->getNodeType () == DOMNode::ELEMENT_NODE);
	DOMElement* elem = (DOMElement*) currentConfigElement;
	
	XMLCh* xval		= XMLString::transcode (value.c_str ());
	elem->setTextContent	(xval);
	XMLString::release	(&xval);

	resetError ();
}

void Triggerconf::setConfigValue (string path, string value)
{
	if (! checkItemCount (path, 3)) return;

	STRING_LIST items = tokenize (path);
	setConfigValue (items[0], items[1], items[2], value);
}	

void Triggerconf::setConfigAttributeValue (string module, string submodule, string configname, string attributename, string value)
{
	DOMNode* currentConfigElement = selectConfigElement (module, submodule, configname);
	if (currentConfigElement == NULL) return;

	assert (currentConfigElement->getNodeType () == DOMNode::ELEMENT_NODE);
	DOMElement* elem = (DOMElement*) currentConfigElement;

	XMLCh* xattrname	= XMLString::transcode (attributename.c_str ());
	XMLCh* xval		= XMLString::transcode (value.c_str ());

	elem->setAttribute (xattrname, xval);

	XMLString::release (&xattrname);
	XMLString::release (&xval);

	resetError ();
}

void Triggerconf::setConfigAttributeValue (string path, string value)
{
	if (! checkItemCount (path, 4)) return;

	STRING_LIST items = tokenize (path);
	setConfigAttributeValue (items [0], items [1], items [2], items [3], value);
}

void Triggerconf::deleteModule (string module)
{
	if (! existsModule (module)) return;

	DOMNode* currentModule = selectModule (module);
	if (currentModule == NULL)	return;
	
	rootnode->removeChild (currentModule);
	currentModule = NULL;

	resetError ();
}

void Triggerconf::deleteAllModules ()
{
	//
	// removed all modules. have to iterate over and over again
	// if we removed an item because the nodes reflect live changes
	// and removing an element changes the child count
	//
	
	if (rootnode == NULL) return;	
	resetError ();

	DOMNodeList* childs = rootnode->getChildNodes ();
	if (childs == NULL) return;

	bool removed;

	do {
		removed = false;

		for (unsigned int i=0; i<childs->getLength (); i++) {
			
			DOMNode* child = childs->item (i);
			if (child == NULL) continue;
			
			if (child->getNodeType () == DOMNode::ELEMENT_NODE || 
					child->getNodeType () == DOMNode::TEXT_NODE) {
	
				rootnode->removeChild (child);
				removed = true;
				break;
			}
	
		} // for (unsigned int i=0; i<childs->getLength (); i++)

	} while (removed); 

	assert (getModuleNames().size() == 0);
}

void Triggerconf::deleteSubmodule (string module, string submodule)
{
	if (! existsSubmodule (module, submodule)) return;

	DOMNode* currentModule = selectModule (module);
	if (currentModule == NULL) return;

	DOMNode* currentSubmodule = selectSubmodule (module, submodule);
	if (currentSubmodule == NULL) return;

	currentModule->removeChild (currentSubmodule);
	currentSubmodule = NULL;

	resetError ();
}

void Triggerconf::deleteSubmodule (string path)
{
	if (! checkItemCount (path, 2)) return;

	STRING_LIST items = tokenize (path);
	deleteSubmodule (items [0], items [1]);
}

void Triggerconf::deleteConfigElement (string module, string submodule, string configname)
{
	if (! existsConfigElement (module, submodule, configname)) return;

	DOMNode* currentSubmodule = selectSubmodule (module, submodule);
	if (currentSubmodule == NULL) return;

	DOMNode* currentConfigElement = selectConfigElement (module, submodule, configname);
	if (currentConfigElement == NULL) return;

	currentSubmodule->removeChild (currentConfigElement);
	currentConfigElement = NULL;

	resetError ();
}

void Triggerconf::deleteConfigElement (string path)
{
	if (! checkItemCount (path, 3)) return;
	
	STRING_LIST items = tokenize (path);
	deleteConfigElement (items [0], items [1], items [2]); 
}

void Triggerconf::deleteConfigAttribute (string module, string submodule, string configname, string attributename)
{
	if (! existsConfigElement (module, submodule, configname)) return;

	DOMNode* currentConfigElement = selectConfigElement (module, submodule, configname);
	if (currentConfigElement == NULL) return;

	assert (currentConfigElement->getNodeType () == DOMNode::ELEMENT_NODE);
	DOMElement* elem = (DOMElement*) currentConfigElement;

	XMLCh* xattrname	= XMLString::transcode (attributename.c_str ());
	elem->removeAttribute	(xattrname);
	XMLString::release	(&xattrname);

	resetError ();
}

void Triggerconf::deleteConfigAttribute (string path)
{
	if (! checkItemCount (path, 4)) return;

	STRING_LIST items = tokenize (path);
	deleteConfigAttribute (items [0], items [1], items [2], items [3]);
}


bool Triggerconf::checkItemCount (STRING_LIST path, unsigned int items)
{
	if (path.size () != items) {
		
		char buf [16];

#ifdef WIN32
		ultoa (items, buf, 10);
#else
		snprintf (buf, 10, "%d", items);
#endif
		
		setError ("path " + untokenize (path) + " does not contain " + string(buf) + " items");
		return false;
	
	} else
		return true;
}

bool Triggerconf::checkItemCount (string path, unsigned int items)
{
	return checkItemCount (tokenize (path), items);
}

bool Triggerconf::existsModule (string module)
{
	bool autoval	= autocreate;
	autocreate	= false;
	bool exists	= selectModule (module) != NULL;
	autocreate	= autoval;

	return exists;
}

bool Triggerconf::existsSubmodule (string module, string submodule)
{
	bool autoval	= autocreate;
	autocreate	= false;
	bool exists	= selectSubmodule (module, submodule) != NULL;
	autocreate	= autoval;

	return exists;
}

bool Triggerconf::existsSubmodule (string path)
{
	if (! checkItemCount (path, 2)) return false;

	STRING_LIST items = tokenize (path);
	return existsSubmodule (items [0], items [1]);
}

bool Triggerconf::existsConfigElement (string module, string submodule, string configname)
{
	bool autoval	= autocreate;
	autocreate	= false;
	bool exists	= selectConfigElement (module, submodule, configname) != NULL;
	autocreate	= autoval;

	return exists;
}

bool Triggerconf::existsConfigElement (string path)
{
	if (! checkItemCount (path, 3)) return false;

	STRING_LIST items = tokenize (path);
	return existsConfigElement (items [0], items [1], items [2]);
}

bool Triggerconf::existsConfigAttribute (string module, string submodule, string configname, string attributename)
{
	bool autoval	= autocreate;
	autocreate	= false;
	
	DOMNode* currentConfigElement = selectConfigElement (module, submodule, configname);
	autocreate = autoval;
	if (currentConfigElement == NULL) return false;

	assert (currentConfigElement->getNodeType () == DOMNode::ELEMENT_NODE);
	DOMElement* elem = (DOMElement*) currentConfigElement;

	XMLCh* xattrname	= XMLString::transcode (attributename.c_str ());
	bool hasattr		= elem->getAttributeNode (xattrname) != NULL;
	XMLString::release	(&xattrname);

	return hasattr;
}

bool Triggerconf::existsConfigAttribute	(string path)
{
	if (! checkItemCount (path, 4)) return false;

	STRING_LIST items = tokenize (path);
	return existsConfigAttribute (items [0], items [1], items [2], items [3]);
}

Triggerconf::STRING_LIST Triggerconf::getChildsAttribute (DOMNode* root, string nodename, string attribute)
{
	STRING_LIST ret;
	
	if (root == NULL) {
		setError ("invalid root node");	
		return ret;
	}

	DOMNodeList* childs = root->getChildNodes ();
	if (childs == NULL) return ret;

	for (unsigned int i=0; i<childs->getLength (); i++) {
		
		DOMNode* child = childs->item (i);
		if (child == NULL || child->getNodeType () != DOMNode::ELEMENT_NODE) continue;

		const XMLCh* xnodename = child->getNodeName ();
		char* charname = XMLString::transcode (xnodename);
		
		if (nodename.compare (charname) == 0)
			ret.push_back (getAttributeValue (child, attribute));

		XMLString::release (&charname);

	} // for (unsigned int i=0; i<childs->getLength (); i++) 

	return ret;
}

Triggerconf::STRING_LIST Triggerconf::getModuleNames ()
{
	return getChildsAttribute (rootnode, ELEMENT_MODULE_NAME, ATTRIBUTE_NAME);
}

Triggerconf::STRING_LIST Triggerconf::getSubmoduleNames (string module)
{
	if (! existsModule (module)) return STRING_LIST ();
	DOMNode* root = selectModule (module);

	return getChildsAttribute (root, ELEMENT_SUBMODULE_NAME, ATTRIBUTE_NAME);
}

Triggerconf::STRING_LIST Triggerconf::getConfigItemNames (string module, string submodule)
{
	if (! existsSubmodule (module, submodule)) return STRING_LIST ();
	DOMNode* root = selectSubmodule (module, submodule);
	return getChildsAttribute (root, ELEMENT_CONFIGITEM_NAME, ATTRIBUTE_NAME);
}

Triggerconf::STRING_LIST Triggerconf::getConfigItemNames (string path)
{
	if (! checkItemCount (path, 2)) return STRING_LIST ();
	STRING_LIST items = tokenize (path);
	return getConfigItemNames (items [0], items [1]);
}

Triggerconf::STRING_LIST Triggerconf::getConfigAttributeNames (string module, string submodule, string configname)
{
	STRING_LIST ret;

	if (! existsConfigElement (module, submodule, configname)) return ret;

	DOMNode* node = selectConfigElement (module, submodule, configname);
	if (node == NULL || node->getNodeType () != DOMNode::ELEMENT_NODE) return ret;

	DOMElement* elem = (DOMElement*) node;
	DOMNamedNodeMap* attributes = elem->getAttributes ();

	for (unsigned int i=0; i<attributes->getLength (); i++) {
		DOMNode* attr = attributes->item (i);
		const XMLCh* xname = attr->getNodeName ();	
		char* cname = XMLString::transcode (xname);

		ret.push_back (cname);	
		XMLString::release (&cname);
	}

	return ret;
}

Triggerconf::STRING_LIST Triggerconf::getConfigAttributeNames (string path)
{
	if (! checkItemCount (path, 3)) return STRING_LIST ();
	
	STRING_LIST items = tokenize (path);
	return getConfigAttributeNames (items [0], items [1], items [2]);
}

Triggerconf::ATTRIBUTE_MAP Triggerconf::getConfigItemAttributes (string module, string submodule, string configitem)
{
	ATTRIBUTE_MAP ret;	
	STRING_LIST names = getConfigAttributeNames (module, submodule, configitem);

	STRING_LIST_ITERATOR	begin	= names.begin();
	STRING_LIST_ITERATOR	end	= names.end();

	for ( ; begin != end; begin++) {
		
		string value	= getConfigAttributeValue (module, submodule, configitem, *begin);
		ret.insert	(ATTRIBUTE_PAIR (*begin, value));

	} // for ( ; begin != end; begin++) 

	return ret;
}

Triggerconf::ATTRIBUTE_MAP Triggerconf::getConfigItemAttributes (string path)
{
	if (! checkItemCount (path, 3)) return ATTRIBUTE_MAP ();

	STRING_LIST items = tokenize (path);
	return getConfigItemAttributes (items [0], items [1], items [2]);
}
