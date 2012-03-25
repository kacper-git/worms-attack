//////////////////////////////////////////////////////////
/*********************************************************
 *
 * Triggerconf XML wrapper for the XercesC library
 *
 * This version of Triggerconf works with XercesC v3.x.x
 *
 *********************************************************/
//////////////////////////////////////////////////////////


//
// these articles really help, as there is not too much docu/articles for xerces around ..
// http://www-128.ibm.com/developerworks/xml/library/x-serial.html
// http://www-128.ibm.com/developerworks/xml/library/x-xercc2/
// http://www-128.ibm.com/developerworks/xml/library/x-xercc/
//

#ifndef __TRIGGERCONF_H
#define __TRIGGERCONF_H

#ifdef WIN32
	// deprecated unsecure function from MS Visual Studio 8 on
	#pragma warning (disable : 4996) 
	// xercesc conversion warning
	#pragma warning (disable : 4244)
	// to prevent the inclusion of windows.h
	// (	which will include ole2.h -> objbase.h -> urlmon.h -> msxml.h
	//		and msxml.h defines DOMDocument ... and we have a redefinition 
	//		problem with xerces ...
	//	)
	#define WIN32_LEAN_AND_MEAN
#endif

#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstdio>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/PlatformUtils.hpp>

using std::map;
using std::string;
using std::vector;
using std::pair;
XERCES_CPP_NAMESPACE_USE

#define 	ROOT_NAME			"triggerconf"
#define 	ELEMENT_MODULE_NAME		"module"
#define 	ELEMENT_SUBMODULE_NAME		"submodule"
#define 	ELEMENT_CONFIGITEM_NAME		"configitem"
#define 	ATTRIBUTE_NAME			"name"
#define		PATH_DELIMITER			'/'

/// \brief	The Triggerconf class.
///
/// The Triggerconf class enables easy hierarchical access to config
/// elements and config attributes. It hides the complexity of the
/// XML library and gives easy to use manipulators for creating, reading 
/// and editing XML configuration files. 
/// The hierarchy consists of modules, submodules and configelements. 
/// Modules and submodules have unique names such that it is always 
/// possible to build a path that uniquely identifies a module, submodule 
/// or configelement. Modules and submodules just have names and no other values
/// or attributes. Configelements have a name and value. Additionally configelements
/// can have a arbitrary number of attributes which are made up of a name and value.
/// All function which access/manipulate modules/submodules/configelements/configattributes
/// can be accessed either through single parameters for each hierarchy or a path.
/// Triggerconf uses the XercesC XML DOM library.
class Triggerconf {
public:

	///
	/// \brief Constructor for a Triggerconf object.
	///
	/// The given configuration file will be parsed with an 
	/// XML DOM Parser. If the file does not exist, it will be created.
	///
	/// \param filename The name of the xml file to open or create.
	/// \param autocreateitems Chooses the autocreate mode which means 
	/// that you don't have to create configelements/attributs or any 
	/// of its parents when setting a value. All elements and parents 
	/// are automatically created.
	/// \param mustexist Specify true if you don't want triggerconf to 
	/// create the file if it does not exist. If the file does not exist 
	/// an error will be set. Use isGood to test if the file has been found.
	///
	Triggerconf( string _filename, bool _autocreateitems = false, bool _mustexist = false, bool _savechanges = true );

	///
	/// \brief Destruct and save the configuration file.
	///
	/// The destructor will save the current configuration
	/// to the file and savely terminate the XML library.
	///
	~Triggerconf();
	
	///
	/// \brief Check if an error occured?
	///
	/// None of the functions in triggerconf returns status
	/// codes or errors. To check wether an error occured during
	/// execution of the last function call this function.
	///
	/// \return True if no error occured, false if an error occured.
	/// \see getError
	///
	bool isGood();

	///
	/// \brief Get the error message of the last error.
	///
	/// Returns the error message of the last error that occured. 
	/// Use in conjunection with isGood.
	///
	/// \return Error string of the last error.
	/// \see isGood
	///
	string getError();

	///
	/// \brief Get the value of a configelement.
	///
	/// Returns the config value of a configelement. If the element
	/// does not exist The returned string will be empty. Use isGood
	/// to check for errors.
	///
	/// \param module The module which the configelement belongs to.
	/// \param submodule The submodule which the configelement belongs to.
	/// \param configname The name of the configelement.
	/// \return The value for the configelement.
	/// \see getConfigValue(string)
	///
	string getConfigValue( string module, string submodule, string configname );

	///
	/// \brief Get the value of a configelement through its path.
	///
	/// Get the value of a configelement through a path in the form 
	/// module/submodule/configelement.
	///
	/// \see getConfigValue(string, string, string)
	///
	string getConfigValue( string path );

	///
	/// \brief Get the value of an attribute from a configelement.
	///
	/// Retrieve the value of an attribute in the specified module/submodule
	/// which belongs to the given configelement.
	///
	/// \param module The module to which the configelement belongs.
	/// \param submodule The submodule to which the configelement belongs.
	/// \param configname The configelement which owns the attribute.
	/// \param attributename The name of the attribute for which to get the value.
	/// \return The value of the attribute.
	/// \see getConfigAttributeValue(string)
	///
	string getConfigAttributeValue( string module, string submodule, string configname, string attributename );
	
	///
	/// \brief Get the value of an attribute from a configelement through its path.
	/// 
	/// The path must be in the form
	/// module/submodule/configelement/attributename
	///
	/// \see getConfigAttributeValue(string, string, string, string)
	///
	string getConfigAttributeValue( string path );

	
	///
	/// \brief Get the value of an attribute from a submodule.
	///
	/// Retrieve the value of an attribute in the specified module
	/// which belongs to the given submodule.
	///
	/// \param module The module to which the submodule belongs.
	/// \param submodule The submodule which has the attribute
	/// \param attributename The name of the attribute for which to get the value.
	/// \return The value of the attribute.
	/// \see getSubmoduleAttributeValue(string)
	///
	string getSubmoduleAttributeValue( string module, string submodule, string attributename );
	
	///
	/// \brief Check if a module exists.
	///
	/// Checks if the module with the given name exists.
	///
	/// \param module The name of the module.
	/// \return True if the module exists, false if it does not exist.
	///
	bool existsModule( string module );

	///
	/// \brief Check if a submodule exists.
	///
	/// Checks if the submodule exists in the given module.
	///
	/// \param module The name of the module.
	/// \param submodule The name of the submodule.
	/// \return True if the submodule exists, false if it does not exist or the module does not exist.
	/// \see existsSubmodule(string)
	bool existsSubmodule( string module, string submodule );

	///
	/// \brief Check if a submodule exists.
	///
	/// Checks if the submodule with the given path exists. The path
	/// must be in the form module/submodule.
	///
	/// \param path The path to the submodule.
	/// \return True if the submodule exists, false if it does not exist or the module does not exist.
	/// \see existsSubmodule(string, string)
	bool existsSubmodule( string path );

	///
	/// \brief Check if a configelement exists
	///
	/// Checks if the configelement in the given module and submodule exists
	///
	/// \param module The module to which the configelement belongs.
	/// \param submodule The module to which the configelement belongs.
	/// \param configname The name of the configelement.
	/// \return True if the configelement exists, else false.
	/// \see existsConfigElement(string)
	///
	bool existsConfigElement( string module, string submodule, string configname );

	///
	/// \brief Check if a configelement exists
	///
	/// Checks if the configelement in the given module and submodule exists.
	/// The path must be in the form module/submodule/configelement.
	///
	/// \param path The path to the configelement in the form module/submodule/configelement.
	/// \return True if the configelement exists, else false.
	/// \see existsConfigElement(string, string, string)
	///
	bool existsConfigElement( string path );

	///
	/// \brief Check if a configattribute exists
	///
	/// Checks if the configattribute in the given module, submodule and configelement exists.
	///
	/// \param module The module in which the configattribute is.
	/// \param submodule The submodule in which the configattribute is.
	/// \param configname The configelement in which the configattribute is.
	/// \param attributename The name of the attribute.
	/// \return True if the configattribute exists, else false.
	/// \see existsConfigAttribute(string)
	///
	bool existsConfigAttribute( string module, string submodule, string configname, string attributename );
	
	///
	/// \brief Check if a configattribute exists
	///
	/// Checks if the configattribute in the given path exists.
	///
	/// \param path The path to the configattribute in the form module/submodule/configelement/attributename.
	/// \return True if the configattribute exists, else false.
	/// \see existsConfigAttribute(string, string, string, string)
	///
	bool existsConfigAttribute( string path );

	///
	/// \brief Create a new module.
	///
	/// Create a new module with the given name. If the 
	/// module already exists an error will occur. Use isGood to check for errors.
	///
	/// \param module The name for the new module.
	///
	void createModule( string module );

	///
	/// \brief Create a new submodule.
	///
	/// Create a new submodule with the given name in the given modle. If the 
	/// submodule already exists or the module does not exist an error will occur. 
	/// Use isGood to check for errors.
	///
	/// \param module The name of an existing module where to put the new submodule in.
	/// \param submodule The name for the new submodule.
	/// \see createSubmodule(string)
	///
	void createSubmodule( string module, string submodule );

	///
	/// \brief Create a new submodule.
	///
	/// Create a new submodule with the given name in the given modle. If the 
	/// submodule already exists or the module does not exist an error will occur. 
	/// Use isGood to check for errors.
	///
	/// \param path The path to the new submodule in the form module/submodule.
	/// \see createSubmodule(string, string)
	///
	void createSubmodule( string path );

	///
	/// \brief Create a new configelement.
	///
	/// Create a new configelement in the given module, submodule and the given name.
	/// Use isGood to check for errors.
	///
	/// \param module The module in which to create the configelement.
	/// \param submodule The submodule in which to create the configelement.
	/// \param configname The name for the new configelement.
	/// \see createConfigElement(string)
	///
	void createConfigElement( string module, string submodule, string configname );

	///
	/// \brief Create a new configelement.
	///
	/// Create a new configelement in the given module, submodule and the given name.
	/// Use isGood to check for errors.
	///
	/// \param path Path to the new configelement in the form module/submodule/configname.
	/// \see createConfigElement(string)
	///
	void createConfigElement( string path );

	///
	/// \brief Create a configattribute.
	///
	/// Create a new configattribute in the given module, submodule, configelement with the given name.
	///
	/// \param module The module in which to create the new configattribute.
	/// \param submodule The submodule in which to create the new configattribute.
	/// \param configname The configelement in which to create the new configattribute.
	/// \param attributename The name for the new configattribute.
	/// \see createConfigAttribute(string)
	///
	void createConfigAttribute( string module, string submodule, string configname, string attributename );

	///
	/// \brief Create a configattribute.
	///
	/// Create a new configattribute in the given module, submodule, 
	/// configelement with the given name.
	///
	/// \param path The path for the new configattribute in the form module/submodule/configelement/attributename.
	/// \see createConfigAttribute(string, string, string, string)
	///
	void createConfigAttribute( string path );

	///
	/// \brief Set the value of a configelement. 
	///
	/// Set the value of a configelement. If in autocreate mode and the configelement 
	/// or any of its parents does not exist, they will be created.
	///
	/// \param module The module of the configelement.
	/// \param submodule The submodule of the configelement.
	/// \param configname The name of the configelement.
	/// \param value The value to set for the configelement.
	/// \see setConfigValue(string, string)
	///
	void setConfigValue( string module, string submodule, string configname, string value );
	
	///
	/// \brief Set the value of a configelement. 
	///
	/// Set the value of a configelement. If in autocreate mode and the configelement 
	/// or any of its parents does not exist, they will be created.
	///
	/// \param path The path to the configelement in the form module/submodule/configelement.
	/// \param value The value to set for the configelement.
	/// \see setConfigValue(string, string)
	///
	void setConfigValue( string path, string value );
	
	///
	/// \brief Set the value of a configattribute
	///
	/// Set the value for a configattribute. If in autocreate mode and any of the parents
	/// or the configelement does not exist it will be created.
	///
	/// \param module The module in which the configelement is.
	/// \param submodule The submodule in which the configelement is.
	/// \param configname The name of the configelement.
	/// \param attributename The name of the configattribute.
	/// \param value The value to set.
	/// \see setConfigAttributeValue(string, string)
	/// 
	void setConfigAttributeValue( string module, string submodule, string configname, string attributename, string value );
	
	///
	/// \brief Set the value of a configattribute
	///
	/// Set the value for a configattribute. If in autocreate mode and any of the parents
	/// or the configelement does not exist it will be created.
	///
	/// \param path The path to the configattribute in the form module/submodule/configelement/configattribute
	/// \param value The value to set.
	/// \see setConfigAttributeValue(string, string, string, string, string)
	/// 
	void setConfigAttributeValue( string path, string value );
	
	///
	/// \brief Delete all modules.
	///
	/// Delete all available modules.
	///
	/// \see deleteModule(string)
	///
	void deleteAllModules( );
	
	///
	/// \brief Delete a module.
	///
	/// Delete the module with the specified name.
	///
	/// \see deleteAllModules
	///
	void deleteModule( string module );
	
	///
	/// \brief Delete a submodule.
	///
	/// Delete a submodule in the specified module.
	///
	/// \param module The module which contains the submodule.
	/// \param submodule The submodule to delete.
	/// \see deleteSubmodule(string)
	///
	void deleteSubmodule( string module, string submodule );
	
	///
	/// \brief Delete a submodule.
	///
	/// Delete a submodule in the specified module.
	///
	/// \param path The path to the submodule in the form module/submodule.
	/// \see deleteSubmodule(string, string)
	///
	void deleteSubmodule( string path );
	
	///
	/// \brief Delete a config element.
	///
	/// Delete a configelement in the given module and submodule.
	///
	/// \param module The module which contains the configelement.
	/// \param submodule The submodule which contains the configelement.
	/// \param configname The name of the configelement.
	/// \see deleteConfigElement(string)
	///
	void deleteConfigElement( string module, string submodule, string configname );
	
	///
	/// \brief Delete a config element.
	///
	/// Delete a configelement in the given module and submodule.
	///
	/// \param path The path to the configelement in the form module/submodule/configname.
	/// \see deleteConfigElement(string, string, string)
	///
	void deleteConfigElement( string path );
	
	///
	/// \brief Delete a configattribute
	///
	/// Delete a configattribute specified by its module, submodule, 
	/// configelement and the name of the configattribute
	///
	/// \param module The module which contains the configattribute.
	/// \param submodule The submodule which contains the configattribute.
	/// \param configname The name of the configelement which contains the configattribute.
	/// \param attributename The name of the attribute to delete.
	/// \see deleteConfigAttribute(string)
	///
	void deleteConfigAttribute( string module, string submodule, string configname, string attributename );
	
	///
	/// \brief Delete a configattribute
	///
	/// Delete a configattribute specified by its module, submodule, 
	/// configelement and the name of the configattribute
	///
	/// \param path The path to the configattribute in the form module/submodule/configname/attributename.
	/// \see deleteConfigAttribute(string, string, string, string)
	///
	void deleteConfigAttribute( string path );
	
	/// A list of strings
	typedef vector<string> STRING_LIST;
	
	/// Iterator to a list of strings
	typedef STRING_LIST::iterator STRING_LIST_ITERATOR;
	
	///
	/// \brief Get the names of all available modules.
	/// \return The list of module names.
	///
	STRING_LIST getModuleNames( );
	
	///
	/// \brief Get the names of all available submodules.
	///
	/// Get the names of all available submodules in the given module.
	///
	/// \param module The name of the module from which to retrieve the submodules.
	/// \return The name of the submodules in the given module.
	///
	STRING_LIST getSubmoduleNames( string module );
	
	///
	/// \brief Get the names of all available configelements.
	///
	/// Gets the names of all available configelements in the given module/submodule.
	///
	/// \param module The module from which to retrieve all configelements.
	/// \param submodule The submodule from which to retrieve all configelements.
	/// \return The names of the configelements.
	/// \see getConfigItemNames(string)
	///
	STRING_LIST getConfigItemNames( string module, string submodule );
	
	///
	/// \brief Get the names of all available configelements.
	///
	/// Gets the names of all available configelements in the given module/submodule.
	///
	/// \param path The path to the submodule from which to retrieve the configelements in the form module/submodule.
	/// \return The names of the configelements.
	/// \see getConfigItemNames(string, string)
	///
	STRING_LIST getConfigItemNames( string path );
	
	///
	/// \brief Get the names of available configattributes.
	///
	/// Get the names of available configattributes from the 
	/// selected module, submodule, configelement.
	///
	/// \param module The name of the module.
	/// \param submodule The name of the submodule.
	/// \param configname The name of the configelement from which to retrieve all attributes.
	/// \return The names of the configattributes.
	///
	STRING_LIST getConfigAttributeNames( string module, string submodule, string configname );
	
	///
	/// \brief Get the names of available configattributes.
	///
	/// Get the names of available configattributes from the 
	/// selected module, submodule, configelement.
	///
	/// \param path The path to the configelement from which to 
	/// retrieve all attribute names in the form module/submodule/configelement.
	/// \return The names of the configattributes.
	///
	STRING_LIST getConfigAttributeNames( string path );
	
	/// a map to store name-value attribute mappings
	typedef map<string, string> ATTRIBUTE_MAP;
	
	/// an iterator to a ATTRIBUTE_MAP
	typedef ATTRIBUTE_MAP::iterator ATTRIBUTE_MAP_ITERATOR; 
	
	/// a string-string pair
	typedef pair<string,string> ATTRIBUTE_PAIR;
	
	///
	/// \brief get all attributes with the specified configitem
	///
	/// Retrieve all attributes that are attached to the specified
	/// configitem. The returned attributes are stored in a
	/// map with key and value type string.
	///
	/// \param module The module in which the configitem is.
	/// \param submodule The submodule where the configitem is.
	/// \param configitem The configitem from which to get attributes.
	/// \return The map with names and values.
	///
	ATTRIBUTE_MAP getConfigItemAttributes( string module, string submodule, string configitem );
	
	///
	/// \brief get all attributes with the specified configitem
	///
	/// See getConfigItemAttributes(string, string, string)
	///
	/// \param path The path to the configitem in the form
	/// module/submodule/configitem.
	///
	ATTRIBUTE_MAP getConfigItemAttributes( string path );
	
	private:
	
	/// The current state of the Triggerconf object.
	bool goodstate;
	
	/// The last error string that occured.
	string lasterror;
	
	/// Autocreate modus. If true, items will be created automatically if they are needed but do not exist.
	volatile bool autocreate;

	/// save changes made to the DOM when the triggerconf is destroyed.
	bool savechanges;
	
	/// The name of the file which contains the xml.
	string file;
	
	/// The DOM Parser.
	XercesDOMParser* parser;
	
	/// The ErrorHandler for the DOM Parser.
	ErrorHandler* errhandler;
	
	/// The root node. This is not the document node but the triggerconf node.
	DOMNode* rootnode;
	
	///
	/// \brief Get child of a specified node type.
	///
	/// Gets the child or the given root node which is of given type. 
	/// 
	/// \param root The root node.
	/// \param type The type of which the child node must be( see DOMNode::).
	/// \param index You can specify which child that matches the condition should be returned( first, second, ...).
	/// \return The child that matches all contitions of NULL if no child was found that matches.
	///
	DOMNode* getChildOfType( DOMNode* root, short type, unsigned int index = 0 ); 
	
	///
	/// \brief Get the value of an attribute from the given node.
	///
	/// Return the value from the specified attribute from the given node.
	///
	/// \param element The element from which to retrieve the attribute value.
	/// \param attributename the name of the attribute.
	/// \return the value of the attribute.
	///
	string getAttributeValue( DOMNode* element, string attributename );
	
	///
	/// \brief Reset the error.
	///
	/// Reset the error state and last error message.
	///
	void resetError( );
	
	///
	/// \brief Set an error.
	///
	/// Set the current state to errornous and set the error message.
	///
	/// \param err The error message.
	///
	void setError( string err ); 
	
	///
	/// \brief Select a module.
	///
	/// Get a module by its name. If it does not exist and in autocreate mode
	/// it will be created.
	/// 
	/// \param modulename The name of the module to get.
	/// \return The found node or NULL if the node was not found( and not in autocreate mode).
	///
	DOMNode* selectModule( string modulename );
	
	///
	/// \brief Select a submodule.
	///
	/// Get a submodule by its name. If it does not exist and in autocreate mode
	/// it will be created.
	/// 
	/// \param modulename The name of the module which contains the submodule.
	/// \param submodulename The name of the submodule to get.
	/// \return The found node or NULL if the node was not found( and not in autocreate mode).
	///
	DOMNode* selectSubmodule( string modulename, string submodulename );
	
	///
	/// \brief Select a configelement.
	///
	/// Get a configelement by its name. If it does not exist and in autocreate mode
	/// it will be created.
	/// 
	/// \param modulename The name of the module which contains the configelement.
	/// \param submodulename The name of the submodule which contains the configelement.
	/// \param configname The name of the configelement to get.
	/// \return The found node or NULL if the node was not found( and not in autocreate mode).
	///
	DOMNode* selectConfigElement( string modulename, string submodulename, string configname );
	
	///
	/// \brief Split a string.
	///
	/// Split a string into pieces using '/' as delimiter.
	///
	/// \param path The string to split.
	/// \return The pieces that were split apart.
	/// \see untokenize
	///
	STRING_LIST tokenize( string path );
	
	///
	/// \brief Concat a list of strings.
	/// 
	/// concat a list of strings using '/' as delimiter.
	///
	/// \param path The list of strings to concat.
	/// \return The concatenated pieces as one string.
	/// \see tokenize
	///
	string untokenize( STRING_LIST path );
	
	///
	/// \brief Check for correct pieces.
	///
	/// Check that the given string list contains the given count of items.
	/// If this is not the case the error state is set.
	///
	/// \param path The list of strings.
	/// \param items The number to check against.
	/// \return True if path contains items elements, else false.
	/// \see checkItemCount(string, unsigned int)
	///
	bool checkItemCount( STRING_LIST path, unsigned int items );
	
	///
	/// \brief Check for correct pieces.
	///
	/// Check that the given string list contains the given count of items.
	/// If this is not the case the error state is set. The given string will 
	/// be split apart using the '/' delimiter.
	///
	/// \param path The string to split and check element count.
	/// \param items The number of items to check against.
	/// \return True if path contains items elements, else false.
	/// \see checkItemCount(STRING_LISTS, unsigned int)
	///
	bool checkItemCount( string path, unsigned int items );
	
	///
	/// \brief Get all the values of childs.
	///
	/// Walk the childs of the root node and select each node that has the specified 
	/// xml element name of nodename. From these nodes the attribute with the given name
	/// is selected and the values of these attributes are returned.
	///
	/// \param root The root node whose children will be walked.
	/// \param nodename The xml node names to select.
	/// \param attribute The attribute names to get the values.
	/// \return The list of attribute values.
	///
	STRING_LIST getChildsAttribute( DOMNode* root, string nodename, string attribute ); 

};

#endif // __TRIGGERCONF_H
