/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * raptor.h - Redland Parser Toolkit for RDF (Raptor) - public API
 *
 * Copyright (C) 2000-2010, David Beckett http://www.dajobe.org/
 * Copyright (C) 2000-2005, University of Bristol, UK http://www.bristol.ac.uk/
 * 
 * This package is Free Software and part of Redland http://librdf.org/
 * 
 * It is licensed under the following three licenses as alternatives:
 *   1. GNU Lesser General Public License (LGPL) V2.1 or any newer version
 *   2. GNU General Public License (GPL) V2 or any newer version
 *   3. Apache License, V2.0 or any newer version
 * 
 * You may not use this file except in compliance with at least one of
 * the above three licenses.
 * 
 * See LICENSE.html or LICENSE.txt at the top of this package for the
 * complete terms and further detail along with the license texts for
 * the licenses in COPYING.LIB, COPYING and LICENSE-2.0.txt respectively.
 * 
 * 
 */



#ifndef RAPTOR_H
#define RAPTOR_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

/* Required for va_list in raptor_vsnprintf */
#include <stdarg.h>


/**
 * RAPTOR_V2_AVAILABLE
 *
 * Flag for marking raptor2 API availability.
 */
#define RAPTOR_V2_AVAILABLE 1


/**
 * RAPTOR_API:
 *
 * Macro for wrapping API function call declarations.
 *
 */
#ifndef RAPTOR_API
#  ifdef WIN32
#    ifdef __GNUC__
#      undef _declspec
#      define _declspec(x) __declspec(x)
#    endif
#    ifdef RAPTOR_STATIC
#      define RAPTOR_API
#    else
#      ifdef RAPTOR_INTERNAL
#        define RAPTOR_API _declspec(dllexport)
#      else
#        define RAPTOR_API _declspec(dllimport)
#      endif
#    endif
#  else
#    define RAPTOR_API
#  endif
#endif

/* Use gcc 3.1+ feature to allow marking of deprecated API calls.
 * This gives a warning during compiling.
 */
#if( __GNUC__ == 3 && __GNUC_MINOR__ > 0 ) || __GNUC__ > 3
#ifdef __APPLE_CC__
/* OSX gcc cpp-precomp is broken */
#define RAPTOR_DEPRECATED
#else
#define RAPTOR_DEPRECATED __attribute__((deprecated))
#endif
#else
#define RAPTOR_DEPRECATED
#endif

/**
 * RAPTOR_PRINTF_FORMAT:
 * @string_index: ignore me
 * @first_to_check_index: ignore me
 *
 * Internal macro
 */
#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 4)
#define RAPTOR_PRINTF_FORMAT(string_index, first_to_check_index) \
  __attribute__((__format__(__printf__, string_index, first_to_check_index)))
#else
#define RAPTOR_PRINTF_FORMAT(string_index, first_to_check_index)
#endif

/**
 * raptor_uri:
 *
 * Raptor URI Class.
 */
typedef struct raptor_uri_s raptor_uri;


/* Public statics */
RAPTOR_API
extern const char * const raptor_short_copyright_string;
RAPTOR_API
extern const char * const raptor_copyright_string;
RAPTOR_API
extern const char * const raptor_version_string;
RAPTOR_API
extern const unsigned int raptor_version_major;
RAPTOR_API
extern const unsigned int raptor_version_minor;
RAPTOR_API
extern const unsigned int raptor_version_release;
RAPTOR_API
extern const unsigned int raptor_version_decimal;
RAPTOR_API
extern const char * const raptor_license_string;
RAPTOR_API
extern const char * const raptor_home_url_string;

RAPTOR_API
extern const unsigned char * const raptor_xml_namespace_uri;
RAPTOR_API
extern const unsigned char * const raptor_rdf_namespace_uri;
RAPTOR_API
extern const unsigned char * const raptor_rdf_schema_namespace_uri;
RAPTOR_API
extern const unsigned char * const raptor_xmlschema_datatypes_namespace_uri;
RAPTOR_API
extern const unsigned char * const raptor_owl_namespace_uri;

/**
 * raptor_rdf_namespace_uri_len:
 *
 * Length of #raptor_rdf_namespace_uri string
 */
RAPTOR_API
extern const unsigned int raptor_rdf_namespace_uri_len;

RAPTOR_API
extern const unsigned char * const raptor_xml_literal_datatype_uri_string;

/**
 * raptor_xml_literal_datatype_uri_string_len:
 *
 * Length of #raptor_xml_literal_datatype_uri_string
 */
RAPTOR_API
extern const unsigned int raptor_xml_literal_datatype_uri_string_len;


/* Public structure */
/**
 * raptor_world:
 *
 * Raptor world class.
 */
typedef struct raptor_world_s raptor_world;
/**
 * raptor_parser:
 *
 * Raptor Parser class
 */
typedef struct raptor_parser_s raptor_parser;
/**
 * raptor_serializer:
 *
 * Raptor Serializer class
 */
typedef struct raptor_serializer_s raptor_serializer;

/**
 * raptor_www:
 *
 * Raptor WWW class
 */
typedef struct raptor_www_s raptor_www;
/**
 * raptor_iostream:
 *
 * Raptor I/O Stream class
 */
typedef struct raptor_iostream_s raptor_iostream;
/**
 * raptor_xml_element:
 *
 * Raptor XML Element class
 */
typedef struct raptor_xml_element_s raptor_xml_element;
/**
 * raptor_xml_writer:
 *
 * Raptor XML Writer class
 */
typedef struct raptor_xml_writer_s raptor_xml_writer;
/**
 * raptor_qname:
 *
 * Raptor XML qname class
 */
typedef struct raptor_qname_s raptor_qname;
/**
 * raptor_namespace:
 *
 * Raptor XML Namespace class
 */
typedef struct raptor_namespace_s raptor_namespace;
/**
 * raptor_namespace_stack:
 *
 * Raptor XML Namespace Stack class
 */
typedef struct raptor_namespace_stack_s raptor_namespace_stack;

/**
 * raptor_sax2:
 *
 * Raptor SAX2 class
 */
typedef struct raptor_sax2_s raptor_sax2;


/**
 * raptor_term_type:
 * @RAPTOR_TERM_TYPE_URI: RDF URI
 * @RAPTOR_TERM_TYPE_BLANK: RDF blank node
 * @RAPTOR_TERM_TYPE_LITERAL: RDF literal
 * @RAPTOR_TERM_TYPE_UNKNOWN: Internal
 *
 * Type of term in a #raptor_statement
 *
 */
typedef enum {
  RAPTOR_TERM_TYPE_UNKNOWN,
  RAPTOR_TERM_TYPE_URI,
  RAPTOR_TERM_TYPE_BLANK,
  RAPTOR_TERM_TYPE_LITERAL
} raptor_term_type;


/**
 * raptor_locator:
 * @uri: URI of location (or NULL)
 * @file: Filename of location (or NULL)
 * @line: Line number of location (or <0 for no line)
 * @column: Column number of location (or <0 for no column)
 * @byte: Byte number of location (or <0 for no byte)
 *
 * Location information for an error, warning or information message.
 */
typedef struct {
  raptor_uri *uri;
  const char *file;
  int line;
  int column;
  int byte;  
} raptor_locator;

/**
 * raptor_option:
 * @RAPTOR_OPTION_SCANNING: If true (default false), the RDF/XML
 *   parser will look for embedded rdf:RDF elements inside the XML
 *   content, and not require that the XML start with an rdf:RDF root
 *   element.
 * @RAPTOR_OPTION_ALLOW_NON_NS_ATTRIBUTES: If true (default true)
 *   then the RDF/XML parser will allow non-XML namespaced attributes
 *   to be accepted as well as rdf: namespaced ones.  For example,
 *   'about' and 'ID' will be interpreted as if they were rdf:about
 *   and rdf:ID respectively.
 * @RAPTOR_OPTION_ALLOW_OTHER_PARSETYPES: If true (default true)
 *   then the RDF/XML parser will allow unknown parsetypes to be
 *   present and will pass them on to the user.  Unimplemented at
 *   present.
 * @RAPTOR_OPTION_ALLOW_BAGID: If true (default true) then the
 *   RDF/XML parser will support the rdf:bagID attribute that was
 *   removed from the RDF/XML language when it was revised.  This
 *   support may be removed in future.
 * @RAPTOR_OPTION_ALLOW_RDF_TYPE_RDF_LIST: If true (default false)
 *   then the RDF/XML parser will generate the idList rdf:type
 *   rdf:List triple in the handling of rdf:parseType="Collection".
 *   This triple was removed during the revising of RDF/XML after
 *   collections were initially added.
 * @RAPTOR_OPTION_NORMALIZE_LANGUAGE: If true (default true) then
 *   XML language values such as from xml:lang will be normalized to
 *   lowercase.
 * @RAPTOR_OPTION_NON_NFC_FATAL: If true (default false) then
 *  illegal Unicode Normal Form C in literals will give a fatal
 *  error, otherwise just a warning.
 * @RAPTOR_OPTION_WARN_OTHER_PARSETYPES: If true (default true) then 
 *   the RDF/XML parser will warn about unknown rdf:parseType values.
 * @RAPTOR_OPTION_CHECK_RDF_ID: If true (default true) then the
 *   RDF/XML will check rdf:ID attribute values for duplicates and
 *   cause an error if any are found.
 * @RAPTOR_OPTION_RELATIVE_URIS: If true (default true) then
 *   relative URIs will be used wherever possible when serializing.
 * @RAPTOR_OPTION_WRITER_AUTO_INDENT: Automatically indent elements when
 *   seriailizing.
 * @RAPTOR_OPTION_WRITER_AUTO_EMPTY: Automatically detect and
 *   abbreviate empty elements when serializing.
 * @RAPTOR_OPTION_WRITER_INDENT_WIDTH: Integer number of spaces to use
 *   for each indent level when serializing with auto indent.
 * @RAPTOR_OPTION_WRITER_XML_VERSION: Integer XML version XML 1.0 (10) or XML 1.1 (11)
 * @RAPTOR_OPTION_WRITER_XML_DECLARATION: Write XML 1.0 or 1.1 declaration.
 * @RAPTOR_OPTION_NO_NET: Deny network requests.
 * @RAPTOR_OPTION_RESOURCE_BORDER: Border color of resource
 *   nodes for GraphViz DOT serializer.
 * @RAPTOR_OPTION_LITERAL_BORDER: Border color of literal nodes
 *   for GraphViz DOT serializer.
 * @RAPTOR_OPTION_BNODE_BORDER: Border color of blank nodes for
 *   GraphViz DOT serializer.
 * @RAPTOR_OPTION_RESOURCE_FILL: Fill color of resource nodes
 *   for GraphViz DOT serializer.
 * @RAPTOR_OPTION_LITERAL_FILL: Fill color of literal nodes for
 *   GraphViz DOT serializer.
 * @RAPTOR_OPTION_BNODE_FILL: Fill color of blank nodes for
 *   GraphViz DOT serializer.
 * @RAPTOR_OPTION_HTML_TAG_SOUP: Use a lax HTML parser if an XML parser
 *   fails when read HTML for GRDDL parser.
 * @RAPTOR_OPTION_MICROFORMATS: Look for microformats for GRDDL parser.
 * @RAPTOR_OPTION_HTML_LINK: Look for head &lt;link&gt; to type rdf/xml
 *   for GRDDL parser.
 * @RAPTOR_OPTION_WWW_TIMEOUT: Set timeout for internal WWW URI requests
 *   for GRDDL parser.
 * @RAPTOR_OPTION_WRITE_BASE_URI: Write @base directive for Turtle/N3.
 * @RAPTOR_OPTION_WWW_HTTP_CACHE_CONTROL: HTTP Cache-Control: header
 * @RAPTOR_OPTION_WWW_HTTP_USER_AGENT: HTTP User-Agent: header
 * @RAPTOR_OPTION_JSON_CALLBACK: JSON serializer callback function.
 * @RAPTOR_OPTION_JSON_EXTRA_DATA: JSON serializer extra top-level data
 * @RAPTOR_OPTION_RSS_TRIPLES: Atom/RSS serializer writes extra RDF triples it finds (none, rdf-xml, atom-triples)
 * @RAPTOR_OPTION_ATOM_ENTRY_URI: Atom entry URI.  If given, generate an Atom Entry Document with the item having the given URI, otherwise generate an Atom Feed Document with any items found.
 * @RAPTOR_OPTION_PREFIX_ELEMENTS: Integer. If set, generate Atom/RSS1.0 documents with prefixed elements, otherwise unprefixed.
 * @RAPTOR_OPTION_LAST: Internal
 *
 * Raptor parser, serializer or XML writer options.
 */
typedef enum {
  RAPTOR_OPTION_SCANNING,
  RAPTOR_OPTION_ALLOW_NON_NS_ATTRIBUTES,
  RAPTOR_OPTION_ALLOW_OTHER_PARSETYPES,
  RAPTOR_OPTION_ALLOW_BAGID,
  RAPTOR_OPTION_ALLOW_RDF_TYPE_RDF_LIST,
  RAPTOR_OPTION_NORMALIZE_LANGUAGE,
  RAPTOR_OPTION_NON_NFC_FATAL,
  RAPTOR_OPTION_WARN_OTHER_PARSETYPES,
  RAPTOR_OPTION_CHECK_RDF_ID,
  RAPTOR_OPTION_RELATIVE_URIS,
  RAPTOR_OPTION_WRITER_AUTO_INDENT,
  RAPTOR_OPTION_WRITER_AUTO_EMPTY,
  RAPTOR_OPTION_WRITER_INDENT_WIDTH,
  RAPTOR_OPTION_WRITER_XML_VERSION,
  RAPTOR_OPTION_WRITER_XML_DECLARATION,
  RAPTOR_OPTION_NO_NET,
  RAPTOR_OPTION_RESOURCE_BORDER,
  RAPTOR_OPTION_LITERAL_BORDER,
  RAPTOR_OPTION_BNODE_BORDER,
  RAPTOR_OPTION_RESOURCE_FILL,
  RAPTOR_OPTION_LITERAL_FILL,
  RAPTOR_OPTION_BNODE_FILL,
  RAPTOR_OPTION_HTML_TAG_SOUP,
  RAPTOR_OPTION_MICROFORMATS,
  RAPTOR_OPTION_HTML_LINK,
  RAPTOR_OPTION_WWW_TIMEOUT,
  RAPTOR_OPTION_WRITE_BASE_URI,
  RAPTOR_OPTION_WWW_HTTP_CACHE_CONTROL,
  RAPTOR_OPTION_WWW_HTTP_USER_AGENT,
  RAPTOR_OPTION_JSON_CALLBACK,
  RAPTOR_OPTION_JSON_EXTRA_DATA,
  RAPTOR_OPTION_RSS_TRIPLES,
  RAPTOR_OPTION_ATOM_ENTRY_URI,
  RAPTOR_OPTION_PREFIX_ELEMENTS,
  RAPTOR_OPTION_LAST = RAPTOR_OPTION_PREFIX_ELEMENTS
} raptor_option;


/**
 * raptor_genid_type:
 * @RAPTOR_GENID_TYPE_BNODEID: Generated ID is for a blank node
 * @RAPTOR_GENID_TYPE_BAGID: Generated ID is for rdf:bagID
 *
 * Intended type for a generated identifier asked for by the handler
 * registered with raptor_parser_set_generate_id_handler().
 */
typedef enum {
  RAPTOR_GENID_TYPE_BNODEID,
  RAPTOR_GENID_TYPE_BAGID
} raptor_genid_type;


/**
 * raptor_term:
 * @world: world
 * @usage: usage reference count (if >0)
 * @type: term type
 * @value: term values per type
 *
 * An RDF statement term
 *
 */
typedef struct {
  raptor_world* world;

  int usage;

  raptor_term_type type;

  union {
    /* RAPTOR_TERM_TYPE_URI */
    raptor_uri *uri;

    /* RAPTOR_TERM_TYPE_LITERAL */
    struct {
      unsigned char *string;
      raptor_uri *datatype;
      unsigned char *language;
    } literal;

    /* RAPTOR_TERM_TYPE_BLANK */
    unsigned char *blank;
  } value;

} raptor_term;


/**
 * raptor_statement:
 * @world: world pointer
 * @usage: usage count
 * @subject: statement subject
 * @predicate: statement predicate
 * @object: statement object
 *
 * An RDF triple with graph
 *
 * See #raptor_term for a description of how the fields may be used.
 * As returned by a parser statement_handler.
 */
typedef struct {
  raptor_world* world;
  int usage;
  raptor_term* subject;
  raptor_term* predicate;
  raptor_term* object;
} raptor_statement;


/**
 * raptor_message_handler:
 * @user_data: user data
 * @locator: location associated with message or NULL
 * @message: message to report
 *
 * Message with location handler function.
 *
 * Used during parsing and serializing for errors and warnings that
 * may include location information. Multiple handlers may be set for
 * parsers and serializers by raptor_world_set_fatal_error_handler(),
 * raptor_world_set_error_handler(), raptor_world_set_warning_handler().
 *
 */
typedef void (*raptor_message_handler)(void *user_data, raptor_locator* locator, const char *message);


/**
 * raptor_message_handler_closure:
 * @user_data: user data for handler invocation
 * @handler: handler function
 *
 * The combination of a message handler and the user data to send to it.
 */
typedef struct {
  void *user_data;
  raptor_message_handler handler;
} raptor_message_handler_closure;


/**
 * raptor_statement_handler:
 * @user_data: user data
 * @statement: statement to report
 *
 * Statement (triple) reporting handler function.
 */
typedef void (*raptor_statement_handler)(void *user_data, raptor_statement *statement);

/**
 * raptor_graph_handler:
 * @user_data: user data
 * @graph: graph to report, 0 for the default graph
 *
 * Named graph reporting handler function. Due to historic reasons the named graph
 * API is separated from the statement handler. A graph is reported after all its 
 * statements.
 */
typedef void (*raptor_graph_handler)(void *user_data, raptor_uri *graph);

/**
 * raptor_generate_id_handler:
 * @user_data: user data
 * @type: type of ID to create
 * @user_bnodeid: a user-specified ID or NULL if none available.
 *
 * Generate an identifier handler function.
 *
 * Return value: new ID to use
 */
typedef unsigned char* (*raptor_generate_id_handler)(void *user_data, raptor_genid_type type, unsigned char* user_bnodeid);

/**
 * raptor_namespace_handler:
 * @user_data: user data
 * @nspace: #raptor_namespace declared
 *
 * XML Namespace declaration reporting handler set by 
 * raptor_parser_set_namespace_handler().
 */
typedef void (*raptor_namespace_handler)(void* user_data, raptor_namespace *nspace);

/**
 * raptor_www_write_bytes_handler:
 * @www: WWW object
 * @userdata: user data
 * @ptr: data pointer
 * @size: size of individual item
 * @nmemb: number of items
 *
 * Receiving bytes of data from WWW retrieval handler.
 *
 * Set by raptor_www_set_write_bytes_handler().
 */
typedef void (*raptor_www_write_bytes_handler)(raptor_www* www, void *userdata, const void *ptr, size_t size, size_t nmemb);

/**
 * raptor_www_content_type_handler:
 * @www: WWW object
 * @userdata: user data
 * @content_type: content type seen
 *
 * Receiving Content-Type: header from WWW retrieval handler.
 *
 * Set by raptor_www_set_content_type_handler().
 */
typedef void (*raptor_www_content_type_handler)(raptor_www* www, void *userdata, const char *content_type);

/**
 * raptor_www_final_uri_handler:
 * @www: WWW object
 * @userdata: user data
 * @final_uri: final URI seen
 *
 * Receiving the final resolved URI from a WWW retrieval
 *
 * Set by raptor_www_set_final_uri_handler().
 */
typedef void (*raptor_www_final_uri_handler)(raptor_www* www, void *userdata, raptor_uri *final_uri);

/**
 * raptor_uri_filter_func:
 * @user_data: user data
 * @uri: #raptor_uri URI to check
 *
 * Callback function for #raptor_www_set_uri_filter
 *
 * Return value: non-0 to filter the URI
 */
typedef int (*raptor_uri_filter_func)(void *user_data, raptor_uri* uri);


/**
 * raptor_libxml_flags:
 * @RAPTOR_LIBXML_FLAGS_GENERIC_ERROR_SAVE: if set - save/restore the libxml generic error handler when raptor library initializes (default set)
 * @RAPTOR_LIBXML_FLAGS_STRUCTURED_ERROR_SAVE: if set - save/restore the libxml structured error handler when raptor library terminates (default set)
 *
 * libxml library flags
 *
 * These are used by raptor_world_set_libxml_flags() to control
 * common libxml features.
 *
 * If any handler saving/restoring is enabled, any existing handler
 * and context is saved before parsing and restored afterwards.
 * Otherwise, no saving/restoring is performed.
 *
 */
typedef enum {
  RAPTOR_LIBXML_FLAGS_GENERIC_ERROR_SAVE    = 1,
  RAPTOR_LIBXML_FLAGS_STRUCTURED_ERROR_SAVE = 2
} raptor_libxml_flags;


typedef int (*raptor_data_compare_function)(const void* data1, const void* data2);
typedef void (*raptor_data_free_function)(void* data);


/* Public functions */

RAPTOR_API
raptor_world* raptor_new_world(void);
RAPTOR_API
int raptor_world_open(raptor_world* world);
RAPTOR_API
void raptor_free_world(raptor_world* world);
RAPTOR_API
void raptor_world_set_libxslt_security_preferences(raptor_world *world, void *security_preferences);
RAPTOR_API
void raptor_world_set_libxml_flags(raptor_world *world,  int flags);
RAPTOR_API
void raptor_world_set_fatal_error_handler(raptor_world *world, void *user_data, raptor_message_handler handler);
RAPTOR_API
void raptor_world_set_error_handler(raptor_world *world, void *user_data, raptor_message_handler handler);
RAPTOR_API
void raptor_world_set_warning_handler(raptor_world *world, void *user_data, raptor_message_handler handler);

/* Parser names */
RAPTOR_API
int raptor_world_enumerate_parsers(raptor_world* world, const unsigned int counter, const char **name, const char **label, const char **mime_type, const unsigned char **uri_string);
RAPTOR_API
int raptor_world_is_parser_name(raptor_world* world, const char *name);
RAPTOR_API
const char* raptor_world_guess_parser_name(raptor_world* world, raptor_uri *uri, const char *mime_type, const unsigned char *buffer, size_t len, const unsigned char *identifier);
RAPTOR_API
int raptor_world_enumerate_parser_options(raptor_world* world, const raptor_option option, const char **name, raptor_uri **uri, const char **label);
RAPTOR_API
int raptor_world_enumerate_serializers(raptor_world* world, const unsigned int counter, const char **name, const char **label, const char **mime_type, const unsigned char **uri_string);
RAPTOR_API
int raptor_world_enumerate_sax2_options(raptor_world* world, const raptor_option option, const char **name,  raptor_uri **uri, const char **label);
RAPTOR_API
int raptor_world_is_serializer_name(raptor_world* world, const char *name);
RAPTOR_API
raptor_option raptor_world_get_option_from_uri(raptor_world* world, raptor_uri *uri);


/* Term Class */
RAPTOR_API
raptor_term* raptor_new_term_from_uri(raptor_world* world, raptor_uri* uri);
RAPTOR_API
raptor_term* raptor_new_term_from_literal(raptor_world* world, const unsigned char* literal, raptor_uri* datatype, const unsigned char* language);
RAPTOR_API
raptor_term* raptor_new_term_from_blank(raptor_world* world, const unsigned char* blank);
RAPTOR_API
void raptor_free_term(raptor_term *term);

RAPTOR_API
unsigned char* raptor_term_as_counted_string(raptor_term *term, size_t* len_p);
RAPTOR_API
unsigned char* raptor_term_as_string(raptor_term *term);
RAPTOR_API
int raptor_term_ntriples_write(const raptor_term *term, raptor_iostream* iostr);


/* Statement Class */
RAPTOR_API
void raptor_statement_init(raptor_statement *statement, raptor_world *world);
RAPTOR_API
void raptor_free_statement(raptor_statement *statement);
RAPTOR_API
int raptor_statement_print(const raptor_statement * statement, FILE *stream);
RAPTOR_API
int raptor_statement_print_as_ntriples(const raptor_statement * statement, FILE *stream);
RAPTOR_API
int raptor_statement_compare(const raptor_statement *s1, const raptor_statement *s2);


/* Parser Class */
RAPTOR_API
raptor_parser* raptor_new_parser(raptor_world* world, const char *name);
RAPTOR_API
raptor_parser* raptor_new_parser_for_content(raptor_world* world, raptor_uri *uri, const char *mime_type, const unsigned char *buffer, size_t len, const unsigned char *identifier);
RAPTOR_API
void raptor_free_parser(raptor_parser* parser);

/* methods */

/* Handlers */
RAPTOR_API
void raptor_parser_set_statement_handler(raptor_parser* parser, void *user_data, raptor_statement_handler handler);
RAPTOR_API
void raptor_parser_set_graph_handler(raptor_parser* parser, void *user_data, raptor_graph_handler handler);
RAPTOR_API
void raptor_parser_set_generate_id_handler(raptor_parser* parser, void *user_data, raptor_generate_id_handler handler);
RAPTOR_API
void raptor_parser_set_namespace_handler(raptor_parser* parser, void *user_data, raptor_namespace_handler handler);
RAPTOR_API
void raptor_parser_set_uri_filter(raptor_parser* parser, raptor_uri_filter_func filter, void* user_data);
RAPTOR_API
raptor_locator* raptor_parser_get_locator(raptor_parser* rdf_parser);
RAPTOR_API
void raptor_parser_set_default_generate_id_parameters(raptor_parser* rdf_parser, char *prefix, int base);


/* Parsing functions */
RAPTOR_API
int raptor_parser_parse_start(raptor_parser *rdf_parser, raptor_uri *uri);
RAPTOR_API
int raptor_parser_parse_chunk(raptor_parser* rdf_parser, const unsigned char *buffer, size_t len, int is_end);
RAPTOR_API
int raptor_parser_parse_file_stream(raptor_parser* rdf_parser, FILE *stream, const char *filename, raptor_uri *base_uri);
RAPTOR_API
int raptor_parser_parse_file(raptor_parser* rdf_parser, raptor_uri *uri, raptor_uri *base_uri);
RAPTOR_API
int raptor_parser_parse_uri(raptor_parser* rdf_parser, raptor_uri *uri, raptor_uri *base_uri);
RAPTOR_API
int raptor_parser_parse_uri_with_connection(raptor_parser* rdf_parser, raptor_uri *uri, raptor_uri *base_uri, void *connection);
RAPTOR_API
void raptor_parser_parse_abort(raptor_parser* rdf_parser);
RAPTOR_API
const char* raptor_parser_get_name(raptor_parser *rdf_parser);
RAPTOR_API
const char* raptor_parser_get_label(raptor_parser *rdf_parser);
RAPTOR_API
const char* raptor_parser_get_mime_type(raptor_parser *rdf_parser);
RAPTOR_API
int raptor_parser_get_need_base_uri(raptor_parser *rdf_parser);

/* parser option methods */
RAPTOR_API
int raptor_parser_set_option(raptor_parser *parser, raptor_option option, int value);
RAPTOR_API
int raptor_parser_set_option_string(raptor_parser *parser, raptor_option option, const unsigned char *value);
RAPTOR_API
int raptor_parser_get_option(raptor_parser *parser, raptor_option option);
RAPTOR_API
const unsigned char* raptor_parser_get_option_string(raptor_parser *parser, raptor_option option);
RAPTOR_API
unsigned int raptor_parser_get_option_count(void);

/* parser utility methods */
RAPTOR_API
void raptor_parser_set_strict(raptor_parser* rdf_parser, int is_strict);
RAPTOR_API
const char* raptor_parser_get_accept_header(raptor_parser* rdf_parser);
RAPTOR_API
unsigned char* raptor_parser_get_new_generated_id(raptor_parser *rdf_parser, raptor_genid_type type);
RAPTOR_API
raptor_world* raptor_parser_get_world(raptor_parser* rdf_parser);


/* Locator Class */
/* methods */
RAPTOR_API
void raptor_locator_print(raptor_locator* locator, FILE *stream);
RAPTOR_API
int raptor_locator_format(char *buffer, size_t length, raptor_locator* locator);
RAPTOR_API
int raptor_locator_line(raptor_locator *locator);
RAPTOR_API
int raptor_locator_column(raptor_locator *locator);
RAPTOR_API
int raptor_locator_byte(raptor_locator *locator);
RAPTOR_API
const char* raptor_locator_file(raptor_locator *locator);
RAPTOR_API
const char* raptor_locator_uri_string(raptor_locator *locator);


/* Serializer Class */
RAPTOR_API
raptor_serializer* raptor_new_serializer(raptor_world* world, const char *name);
RAPTOR_API
void raptor_free_serializer(raptor_serializer* rdf_serializer);

/* methods */
RAPTOR_API
int raptor_serializer_start_to_iostream(raptor_serializer *rdf_serializer, raptor_uri *uri, raptor_iostream *iostream);
RAPTOR_API
int raptor_serializer_start_to_filename(raptor_serializer *rdf_serializer, const char *filename);
RAPTOR_API
int raptor_serializer_start_to_string(raptor_serializer *rdf_serializer, raptor_uri *uri, void **string_p, size_t *length_p);
RAPTOR_API
int raptor_serializer_start_to_file_handle(raptor_serializer *rdf_serializer, raptor_uri *uri, FILE *fh);
RAPTOR_API
int raptor_serializer_set_namespace(raptor_serializer* rdf_serializer, raptor_uri *uri, const unsigned char *prefix);
RAPTOR_API
int raptor_serializer_set_namespace_from_namespace(raptor_serializer* rdf_serializer, raptor_namespace *nspace);
RAPTOR_API
int raptor_serializer_serialize_statement(raptor_serializer* rdf_serializer, raptor_statement *statement);
RAPTOR_API
int raptor_serializer_serialize_end(raptor_serializer *rdf_serializer);
RAPTOR_API
raptor_iostream* raptor_serializer_get_iostream(raptor_serializer *serializer);
RAPTOR_API
raptor_locator* raptor_serializer_get_locator(raptor_serializer *rdf_serializer);

/* serializer option methods */
RAPTOR_API
int raptor_world_enumerate_serializer_options(raptor_world* world, const raptor_option option, const char **name,  raptor_uri **uri, const char **label);
RAPTOR_API
int raptor_serializer_set_option(raptor_serializer *serializer, raptor_option option, int value);
RAPTOR_API
int raptor_serializer_set_option_string(raptor_serializer *serializer, raptor_option option, const unsigned char *value);
RAPTOR_API
int raptor_serializer_get_option(raptor_serializer *serializer, raptor_option option);
RAPTOR_API
const unsigned char *raptor_serializer_get_option_string(raptor_serializer *serializer, raptor_option option);

/* utility methods */
RAPTOR_API
raptor_world* raptor_serializer_get_world(raptor_serializer* rdf_serializer);


/* memory functions */
RAPTOR_API
void raptor_free_memory(void *ptr);
RAPTOR_API
void* raptor_alloc_memory(size_t size);
RAPTOR_API
void* raptor_calloc_memory(size_t nmemb, size_t size);


/* URI Class */
RAPTOR_API
raptor_uri* raptor_new_uri_from_counted_string(raptor_world* world, const unsigned char *uri_string, size_t length);
RAPTOR_API
raptor_uri* raptor_new_uri(raptor_world* world, const unsigned char *uri_string);
RAPTOR_API
raptor_uri* raptor_new_uri_from_uri_local_name(raptor_world* world, raptor_uri *uri, const unsigned char *local_name);
RAPTOR_API
raptor_uri* raptor_new_uri_relative_to_base(raptor_world* world, raptor_uri *base_uri, const unsigned char *uri_string);
RAPTOR_API
raptor_uri* raptor_new_uri_from_id(raptor_world* world, raptor_uri *base_uri, const unsigned char *id);
RAPTOR_API
raptor_uri* raptor_new_uri_for_rdf_concept(raptor_world* world, const unsigned char *name);
RAPTOR_API
raptor_uri* raptor_new_uri_for_xmlbase(raptor_uri* old_uri);
RAPTOR_API
raptor_uri* raptor_new_uri_for_retrieval(raptor_uri* old_uri);
RAPTOR_API
void raptor_free_uri(raptor_uri *uri);

/* methods */
RAPTOR_API
int raptor_uri_equals(raptor_uri* uri1, raptor_uri* uri2);
RAPTOR_API
int raptor_uri_compare(raptor_uri* uri1, raptor_uri* uri2);
RAPTOR_API
raptor_uri* raptor_uri_copy(raptor_uri *uri);
RAPTOR_API
unsigned char* raptor_uri_as_string(raptor_uri *uri);
RAPTOR_API
unsigned char* raptor_uri_as_counted_string(raptor_uri *uri, size_t* len_p);
RAPTOR_API
unsigned char* raptor_uri_to_relative_counted_uri_string(raptor_uri *base_uri, raptor_uri *reference_uri, size_t *length_p);
RAPTOR_API
unsigned char* raptor_uri_to_relative_uri_string(raptor_uri *base_uri,  raptor_uri *reference_uri);
RAPTOR_API
int raptor_uri_print(const raptor_uri* uri, FILE *stream);
RAPTOR_API
unsigned char* raptor_uri_to_counted_string(raptor_uri *uri, size_t *len_p);
RAPTOR_API
unsigned char* raptor_uri_to_string(raptor_uri *uri);
RAPTOR_API
raptor_world* raptor_uri_get_world(raptor_uri *uri);


/* XML utility functions */
RAPTOR_API
int raptor_xml_any_escape_string(raptor_world* world, const unsigned char *string, size_t len, unsigned char *buffer, size_t length, char quote, int xml_version);
RAPTOR_API
int raptor_xml_any_escaped_string_write(const unsigned char *string, size_t len, char quote, int xml_version, raptor_iostream* iostr);
RAPTOR_API
int raptor_xml_escape_string(raptor_world *world, const unsigned char *string, size_t len, unsigned char *buffer, size_t length, char quote);
RAPTOR_API
int raptor_xml_escaped_string_write(const unsigned char *string, size_t len, char quote, raptor_iostream* iostr);
RAPTOR_API
int raptor_xml_name_check(const unsigned char *string, size_t length, int xml_version);


/* portable vsnprintf utility function */
RAPTOR_API
char* raptor_vsnprintf(const char *message, va_list arguments) RAPTOR_PRINTF_FORMAT(1, 0);

/* RFC2396 URI resolving functions */
RAPTOR_API
size_t raptor_uri_resolve_uri_reference(const unsigned char *base_uri, const unsigned char *reference_uri, unsigned char* buffer, size_t length);

/* URI String utility functions */
RAPTOR_API
unsigned char *raptor_uri_filename_to_uri_string(const char *filename);
RAPTOR_API
char *raptor_uri_uri_string_to_filename(const unsigned char *uri_string);
RAPTOR_API
char *raptor_uri_uri_string_to_filename_fragment(const unsigned char *uri_string, unsigned char **fragment_p);
RAPTOR_API
int raptor_uri_uri_string_is_file_uri(const unsigned char* uri_string);



/**
 * RAPTOR_RDF_MS_URI:
 *
 * RDF Namespace URI (rdf:).
 *
 * Copy with raptor_uri_copy() to use.
 */
#define RAPTOR_RDF_MS_URI raptor_rdf_namespace_uri

/**
 * RAPTOR_RDF_SCHEMA_URI:
 *
 * RDF Schema Namespace URI (rdfs:).
 *
 * Copy with raptor_uri_copy() to use.
 */
#define RAPTOR_RDF_SCHEMA_URI raptor_rdf_schema_namespace_uri

/**
 * RAPTOR_XMLSCHEMA_DATATYPES_URI:
 *
 * XML Schema Datatypes URI (xsd:).
 *
 * Copy with raptor_uri_copy() to use.
 */
#define RAPTOR_XMLSCHEMA_DATATYPES_URI raptor_xmlschema_datatypes_namespace_uri

/**
 * RAPTOR_OWL_URI:
 *
 * OWL Namespace URI (owl:).
 *
 * Copy with raptor_uri_copy() to use.
 */
#define RAPTOR_OWL_URI raptor_owl_namespace_uri


/* raptor_www */
RAPTOR_API
void raptor_world_set_www_flags(raptor_world* world, int flags);


RAPTOR_API
raptor_www *raptor_new_www(raptor_world* world);
RAPTOR_API
raptor_www *raptor_new_www_with_connection(raptor_world* world, void* connection);
RAPTOR_API
void raptor_free_www(raptor_www *www);
RAPTOR_API
void raptor_www_set_user_agent(raptor_www *www, const char *user_agent);
RAPTOR_API
void raptor_www_set_proxy(raptor_www *www, const char *proxy);
RAPTOR_API
void raptor_www_set_http_accept(raptor_www *www, const char *value);
RAPTOR_API
void raptor_www_set_write_bytes_handler(raptor_www *www, raptor_www_write_bytes_handler handler, void *user_data);
RAPTOR_API
void raptor_www_set_content_type_handler(raptor_www *www, raptor_www_content_type_handler handler, void *user_data);
RAPTOR_API
void raptor_www_set_final_uri_handler(raptor_www* www, raptor_www_final_uri_handler handler, void *user_data);
RAPTOR_API
void raptor_www_set_uri_filter(raptor_www* www, raptor_uri_filter_func filter, void* user_data);
RAPTOR_API
void raptor_www_set_connection_timeout(raptor_www* www, int timeout);
RAPTOR_API
int raptor_www_set_http_cache_control(raptor_www* www, const char* cache_control);
RAPTOR_API
int raptor_www_fetch(raptor_www *www, raptor_uri *uri);
RAPTOR_API
int raptor_www_fetch_to_string(raptor_www *www, raptor_uri *uri, void **string_p, size_t *length_p, void *(*malloc_handler)(size_t size));
RAPTOR_API
void* raptor_www_get_connection(raptor_www *www);
RAPTOR_API
void raptor_www_abort(raptor_www *www, const char *reason);
RAPTOR_API
raptor_uri* raptor_www_get_final_uri(raptor_www* www);


/* XML QNames Class */
RAPTOR_API
raptor_qname* raptor_new_qname(raptor_namespace_stack *nstack, const unsigned char *name, const unsigned char *value);
RAPTOR_API
raptor_qname* raptor_new_qname_from_namespace_local_name(raptor_world* world, raptor_namespace *ns, const unsigned char *local_name, const unsigned char *value);

/* methods */
RAPTOR_API
raptor_qname* raptor_qname_copy(raptor_qname *qname);
RAPTOR_API
void raptor_free_qname(raptor_qname* name);
RAPTOR_API
int raptor_qname_equal(raptor_qname *name1, raptor_qname *name2);
RAPTOR_API
unsigned char* raptor_qname_to_counted_name(raptor_qname *qname, size_t* length_p);
RAPTOR_API
const raptor_namespace* raptor_qname_get_namespace(raptor_qname* name);
RAPTOR_API
const unsigned char* raptor_qname_get_local_name(raptor_qname* name);
RAPTOR_API
const unsigned char* raptor_qname_get_value(raptor_qname* name);
RAPTOR_API
const unsigned char* raptor_qname_get_counted_value(raptor_qname* name, size_t* length_p);
RAPTOR_API
int raptor_qname_write(raptor_qname *qname, raptor_iostream* iostr);

/* QName String utility functions */
RAPTOR_API
raptor_uri* raptor_qname_string_to_uri(raptor_namespace_stack *nstack,  const unsigned char *name, size_t name_len);

/* XML Namespaces Stack class */
RAPTOR_API
raptor_namespace* raptor_new_namespace_from_uri(raptor_namespace_stack *nstack, const unsigned char *prefix,  raptor_uri* ns_uri, int depth);
RAPTOR_API
raptor_namespace_stack* raptor_new_namespaces(raptor_world* world, int defaults);
RAPTOR_API
int raptor_namespaces_init(raptor_world* world, raptor_namespace_stack *nstack, int defaults);
RAPTOR_API
void raptor_namespaces_clear(raptor_namespace_stack *nstack);
RAPTOR_API
void raptor_free_namespaces(raptor_namespace_stack *nstack);

/* methods */
RAPTOR_API
void raptor_namespaces_start_namespace(raptor_namespace_stack *nstack, raptor_namespace *nspace);
RAPTOR_API
int raptor_namespaces_start_namespace_full(raptor_namespace_stack *nstack, const unsigned char *prefix, const unsigned char *ns_uri_string, int depth);
RAPTOR_API
void raptor_namespaces_end_for_depth(raptor_namespace_stack *nstack, int depth);
RAPTOR_API
raptor_namespace* raptor_namespaces_get_default_namespace(raptor_namespace_stack *nstack);
RAPTOR_API
raptor_namespace *raptor_namespaces_find_namespace(raptor_namespace_stack *nstack, const unsigned char *prefix, int prefix_length);
RAPTOR_API
raptor_namespace* raptor_namespaces_find_namespace_by_uri(raptor_namespace_stack *nstack, raptor_uri *ns_uri);
RAPTOR_API
int raptor_namespaces_namespace_in_scope(raptor_namespace_stack *nstack, const raptor_namespace *nspace);
RAPTOR_API
raptor_qname* raptor_namespaces_qname_from_uri(raptor_namespace_stack *nstack,  raptor_uri *uri, int xml_version);


/* XML Namespace Class */
RAPTOR_API
raptor_namespace* raptor_new_namespace(raptor_namespace_stack *nstack, const unsigned char *prefix, const unsigned char *ns_uri_string, int depth);
RAPTOR_API
void raptor_free_namespace(raptor_namespace *ns);
RAPTOR_API
int raptor_namespace_copy(raptor_namespace_stack *nstack, raptor_namespace *ns, int new_depth);
RAPTOR_API
raptor_uri* raptor_namespace_get_uri(const raptor_namespace *ns);
RAPTOR_API
const unsigned char* raptor_namespace_get_prefix(const raptor_namespace *ns);
RAPTOR_API
const unsigned char* raptor_namespace_get_counted_prefix(const raptor_namespace *ns, size_t *length_p);
RAPTOR_API
unsigned char *raptor_namespace_format_as_xml(const raptor_namespace *ns, size_t *length_p);
RAPTOR_API
int raptor_namespace_write(raptor_namespace *ns, raptor_iostream* iostr);

/* namespace string utility function */
RAPTOR_API
int raptor_xml_namespace_string_parse(const unsigned char *string, unsigned char **prefix, unsigned char **uri_string);

/**
 * raptor_stringbuffer:
 *
 * Raptor string buffer class
 */
typedef struct raptor_stringbuffer_s raptor_stringbuffer;

/* Sequence class */
/**
 * raptor_sequence:
 *
 * Raptor sequence class
 */
typedef struct raptor_sequence_s raptor_sequence;

/**
 * raptor_sequence_free_handler:
 * @object: object to free
 *
 * Handler function for freeing a sequence item.
 *
 * Set by raptor_new_sequence().
*/
typedef void (raptor_data_free_handler)(void* object);

/**
 * raptor_data_context_free_handler:
 * @context: context data for the free handler
 * @object: object to free
 *
 * Handler function for freeing a sequence item with a contextual pointer.
 *
 * Set by raptor_new_sequence_with_context().
*/
typedef void (raptor_data_context_free_handler)(void* context, void* object);

/**
 * raptor_data_print_handler:
 * @object: object to print
 * @fh: FILE* to print to
 *
 * Handler function for printing an object to a stream.
 *
 * Set by raptor_new_sequence()
 */
typedef int (raptor_data_print_handler)(void *object, FILE *fh);

/**
 * raptor_data_context_print_handler:
 * @context: context data for the print handler
 * @object: object to print
 * @fh: FILE* to print to
 *
 * Handler function for printing an object with data context to a stream.
 *
 * Set by raptor_new_sequence_with_context()
 */
typedef int (raptor_data_context_print_handler)(void *context, void *object, FILE *fh);


/* Sequence Clsas */
RAPTOR_API
raptor_sequence* raptor_new_sequence(raptor_data_free_handler* free_handler, raptor_data_print_handler* print_handler);
RAPTOR_API
raptor_sequence* raptor_new_sequence_with_context(raptor_data_context_free_handler* free_handler, raptor_data_context_print_handler* print_handler, void* handler_context);
RAPTOR_API
void raptor_free_sequence(raptor_sequence* seq);

/* methods */
RAPTOR_API
int raptor_sequence_size(raptor_sequence* seq);
RAPTOR_API
int raptor_sequence_set_at(raptor_sequence* seq, int idx, void *data);
RAPTOR_API
int raptor_sequence_push(raptor_sequence* seq, void *data);
RAPTOR_API
int raptor_sequence_shift(raptor_sequence* seq, void *data);
RAPTOR_API
void* raptor_sequence_get_at(raptor_sequence* seq, int idx);
RAPTOR_API
void* raptor_sequence_pop(raptor_sequence* seq);
RAPTOR_API
void* raptor_sequence_unshift(raptor_sequence* seq);
RAPTOR_API
void* raptor_sequence_delete_at(raptor_sequence* seq, int idx);

RAPTOR_API
void raptor_sequence_sort(raptor_sequence* seq, raptor_data_compare_function compare);

/* helper for printing sequences of strings */ 
RAPTOR_API
int raptor_sequence_print(raptor_sequence* seq, FILE* fh);
RAPTOR_API
int raptor_sequence_join(raptor_sequence* dest, raptor_sequence *src);


/* Unicode and UTF8 */

/**
 * raptor_unichar:
 *
 * raptor Unicode codepoint
 */
typedef unsigned long raptor_unichar;
RAPTOR_API
int raptor_unicode_char_to_utf8(raptor_unichar c, unsigned char *output);
RAPTOR_API
int raptor_utf8_to_unicode_char(raptor_unichar *output, const unsigned char *input, int length);
RAPTOR_API
int raptor_unicode_is_xml11_namestartchar(raptor_unichar c);
RAPTOR_API
int raptor_unicode_is_xml10_namestartchar(raptor_unichar c);
RAPTOR_API
int raptor_unicode_is_xml11_namechar(raptor_unichar c);
RAPTOR_API
int raptor_unicode_is_xml10_namechar(raptor_unichar c);
RAPTOR_API
int raptor_utf8_check(const unsigned char *string, size_t length);


/* Stringbuffer Class */
RAPTOR_API
raptor_stringbuffer* raptor_new_stringbuffer(void);
RAPTOR_API
void raptor_free_stringbuffer(raptor_stringbuffer *stringbuffer);

/* methods */
RAPTOR_API
int raptor_stringbuffer_append_counted_string(raptor_stringbuffer* stringbuffer, const unsigned char *string, size_t length, int do_copy);
RAPTOR_API
int raptor_stringbuffer_append_string(raptor_stringbuffer* stringbuffer, const unsigned char *string, int do_copy);
RAPTOR_API
int raptor_stringbuffer_append_decimal(raptor_stringbuffer* stringbuffer, int integer);
RAPTOR_API
int raptor_stringbuffer_append_stringbuffer(raptor_stringbuffer* stringbuffer, raptor_stringbuffer* append);
RAPTOR_API
int raptor_stringbuffer_prepend_counted_string(raptor_stringbuffer* stringbuffer, const unsigned char *string, size_t length, int do_copy);
RAPTOR_API
int raptor_stringbuffer_prepend_string(raptor_stringbuffer* stringbuffer, const unsigned char *string, int do_copy);
RAPTOR_API
unsigned char* raptor_stringbuffer_as_string(raptor_stringbuffer* stringbuffer);
RAPTOR_API
size_t raptor_stringbuffer_length(raptor_stringbuffer* stringbuffer);
RAPTOR_API
int raptor_stringbuffer_copy_to_string(raptor_stringbuffer* stringbuffer, unsigned char *string, size_t length);

/**
 * raptor_iostream_init_func:
 * @context: stream context data
 *
 * Handler function for #raptor_iostream initialising.
 *
 * Return value: non-0 on failure.
 */
typedef int (*raptor_iostream_init_func) (void *context);

/**
 * raptor_iostream_finish_func:
 * @context: stream context data
 *
 * Handler function for #raptor_iostream terminating.
 *
 */
typedef void (*raptor_iostream_finish_func) (void *context);

/**
 * raptor_iostream_write_byte_func
 * @context: stream context data
 * @byte: byte to write
 *
 * Handler function for implementing raptor_iostream_write_byte().
 *
 * Return value: non-0 on failure.
 */
typedef int (*raptor_iostream_write_byte_func) (void *context, const int byte);

/**
 * raptor_iostream_write_bytes_func:
 * @context: stream context data
 * @ptr: pointer to bytes to write
 * @size: size of item
 * @nmemb: number of items
 *
 * Handler function for implementing raptor_iostream_write_bytes().
 *
 * Return value: non-0 on failure.
 */
typedef int (*raptor_iostream_write_bytes_func) (void *context, const void *ptr, size_t size, size_t nmemb);

/**
 * raptor_iostream_write_end_func:
 * @context: stream context data
 *
 * Handler function for implementing raptor_iostream_write_end().
 *
 */
typedef int (*raptor_iostream_write_end_func) (void *context);

/**
 * raptor_iostream_read_bytes_func:
 * @context: stream context data
 * @ptr: pointer to buffer to read into
 * @size: size of buffer
 * @nmemb: number of items
 *
 * Handler function for implementing raptor_iostream_read_bytes().
 *
 * Return value: number of items read, 0 or < @size on EOF, <0 on failure
 */
typedef int (*raptor_iostream_read_bytes_func) (void *context, void *ptr, size_t size, size_t nmemb);

/**
 * raptor_iostream_read_eof_func:
 * @context: stream context data
 *
 * Handler function for implementing raptor_iostream_read_eof().
 *
 * Return value: non-0 if EOF
 */
typedef int (*raptor_iostream_read_eof_func) (void *context);

/**
 * raptor_iostream_handler:
 * @version: interface version.  Presently 1 or 2.
 * @init:  initialisation handler - optional, called at most once (V1)
 * @finish: finishing handler -  optional, called at most once (V1)
 * @write_byte: write byte handler - required (for writing) (V1)
 * @write_bytes: write bytes handler - required (for writing) (V1)
 * @write_end: write end handler - optional (for writing), called at most once (V1)
 * @read_bytes: read bytes handler - required (for reading) (V2)
 * @read_eof: read EOF handler - required (for reading) (V2)
 *
 * I/O stream implementation handler structure.
 * 
 */
typedef struct {
  int version;

  /* V1 functions */
  raptor_iostream_init_func         init;
  raptor_iostream_finish_func       finish;
  raptor_iostream_write_byte_func   write_byte;
  raptor_iostream_write_bytes_func  write_bytes;
  raptor_iostream_write_end_func    write_end;

  /* V2 functions */
  raptor_iostream_read_bytes_func   read_bytes;
  raptor_iostream_read_eof_func     read_eof;
} raptor_iostream_handler;


/* I/O Stream Class */
RAPTOR_API
raptor_iostream* raptor_new_iostream_from_handler(raptor_world* world, void *user_data, const raptor_iostream_handler* const handler);
RAPTOR_API
raptor_iostream* raptor_new_iostream_to_sink(raptor_world* world);
RAPTOR_API
raptor_iostream* raptor_new_iostream_to_filename(raptor_world* world, const char *filename);
RAPTOR_API
raptor_iostream* raptor_new_iostream_to_file_handle(raptor_world* world, FILE *handle);
RAPTOR_API
raptor_iostream* raptor_new_iostream_to_string(raptor_world* world, void **string_p, size_t *length_p, void *(*malloc_handler)(size_t size));
RAPTOR_API
raptor_iostream* raptor_new_iostream_from_sink(raptor_world* world);
RAPTOR_API
raptor_iostream* raptor_new_iostream_from_filename(raptor_world* world, const char *filename);
RAPTOR_API
raptor_iostream* raptor_new_iostream_from_file_handle(raptor_world* world, FILE *handle);
RAPTOR_API
raptor_iostream* raptor_new_iostream_from_string(raptor_world* world, void *string, size_t length);
RAPTOR_API
void raptor_free_iostream(raptor_iostream *iostr);

RAPTOR_API
int raptor_iostream_write_bytes(raptor_iostream *iostr, const void *ptr, size_t size, size_t nmemb);
RAPTOR_API
int raptor_iostream_write_byte(raptor_iostream *iostr, const int byte);
RAPTOR_API
int raptor_iostream_write_end(raptor_iostream *iostr);
RAPTOR_API
int raptor_iostream_write_string(raptor_iostream *iostr, const void *string);
RAPTOR_API
int raptor_iostream_write_counted_string(raptor_iostream *iostr, const void *string, size_t len);
RAPTOR_API
unsigned long raptor_iostream_tell(raptor_iostream *iostr);
RAPTOR_API
int raptor_iostream_write_decimal(raptor_iostream* iostr, int integer);
RAPTOR_API
int raptor_iostream_format_hexadecimal(raptor_iostream* iostr, unsigned int integer, int width);
RAPTOR_API
int raptor_iostream_write_stringbuffer(raptor_iostream* iostr, raptor_stringbuffer *sb);
RAPTOR_API
int raptor_iostream_write_uri(raptor_iostream *iostr,  raptor_uri *uri);
RAPTOR_API
int raptor_iostream_read_bytes(raptor_iostream* iostr, void *ptr, size_t size, size_t nmemb);
RAPTOR_API
int raptor_iostream_read_eof(raptor_iostream *iostr);

/* I/O Stream utility functions */
RAPTOR_API
int raptor_string_ntriples_write(const unsigned char *string, size_t len, const char delim, raptor_iostream *iostr);
RAPTOR_API
int raptor_string_python_write(const unsigned char *string, size_t len, const char delim, int flags, raptor_iostream *iostr);
RAPTOR_API
int raptor_statement_ntriples_write(const raptor_statement *statement, raptor_iostream* iostr);



/* Parser and Serializer options */

/**
 * raptor_option_value_type:
 * @RAPTOR_OPTION_VALUE_TYPE_BOOL: Boolean integer value. Non-0 is true
 * @RAPTOR_OPTION_VALUE_TYPE_INT: Decimal integer value
 * @RAPTOR_OPTION_VALUE_TYPE_STRING: String value
 * @RAPTOR_OPTION_VALUE_TYPE_URI: URI String value.
 * @RAPTOR_OPTION_VALUE_TYPE_LAST: internal
 *
 * Option value types.
 */
typedef enum {
  RAPTOR_OPTION_VALUE_TYPE_BOOL,
  RAPTOR_OPTION_VALUE_TYPE_INT,
  RAPTOR_OPTION_VALUE_TYPE_STRING,
  RAPTOR_OPTION_VALUE_TYPE_URI,
  RAPTOR_OPTION_VALUE_TYPE_LAST = RAPTOR_OPTION_VALUE_TYPE_URI
} raptor_option_value_type;

RAPTOR_API
raptor_option_value_type raptor_option_get_value_type(const raptor_option option);
RAPTOR_API
const char* raptor_option_get_value_type_label(const raptor_option_value_type type);


/* SAX2 element Class (raptor_xml_element) */
RAPTOR_API
raptor_xml_element* raptor_new_xml_element(raptor_qname* name, const unsigned char* xml_language, raptor_uri* xml_base);
RAPTOR_API
raptor_xml_element* raptor_new_xml_element_from_namespace_local_name(raptor_namespace *ns, const unsigned char *name, const unsigned char *xml_language, raptor_uri *xml_base);
RAPTOR_API
void raptor_free_xml_element(raptor_xml_element *element);

/* methods */
RAPTOR_API
raptor_qname* raptor_xml_element_get_name(raptor_xml_element *xml_element);
RAPTOR_API
void raptor_xml_element_set_attributes(raptor_xml_element* xml_element, raptor_qname **attributes, int count);
RAPTOR_API
raptor_qname** raptor_xml_element_get_attributes(raptor_xml_element* xml_element);
RAPTOR_API
int raptor_xml_element_get_attributes_count(raptor_xml_element* xml_element);
RAPTOR_API
int raptor_xml_element_declare_namespace(raptor_xml_element* xml_element, raptor_namespace *nspace);
RAPTOR_API
int raptor_iostream_write_xml_element(raptor_iostream *iostr, raptor_xml_element *element, raptor_namespace_stack *nstack, int is_empty, int is_end, int depth);
RAPTOR_API
int raptor_xml_element_is_empty(raptor_xml_element* xml_element);
RAPTOR_API
const unsigned char* raptor_xml_element_get_language(raptor_xml_element* xml_element);


/* XML Writer Class (raptor_xml_writer) */
RAPTOR_API
raptor_xml_writer* raptor_new_xml_writer(raptor_world* world, raptor_namespace_stack *nstack, raptor_iostream* iostr);
RAPTOR_API
void raptor_free_xml_writer(raptor_xml_writer* xml_writer);

/* methods */
RAPTOR_API
void raptor_xml_writer_empty_element(raptor_xml_writer* xml_writer, raptor_xml_element *element);
RAPTOR_API
void raptor_xml_writer_start_element(raptor_xml_writer* xml_writer, raptor_xml_element *element);
RAPTOR_API
void raptor_xml_writer_end_element(raptor_xml_writer* xml_writer, raptor_xml_element *element);
RAPTOR_API
void raptor_xml_writer_newline(raptor_xml_writer* xml_writer);
RAPTOR_API
void raptor_xml_writer_cdata(raptor_xml_writer* xml_writer, const unsigned char *s);
RAPTOR_API
void raptor_xml_writer_cdata_counted(raptor_xml_writer* xml_writer, const unsigned char *s, unsigned int len);
RAPTOR_API
void raptor_xml_writer_raw(raptor_xml_writer* xml_writer, const unsigned char *s);
RAPTOR_API
void raptor_xml_writer_raw_counted(raptor_xml_writer* xml_writer, const unsigned char *s, unsigned int len);
RAPTOR_API
void raptor_xml_writer_comment(raptor_xml_writer* xml_writer, const unsigned char *s);
RAPTOR_API
void raptor_xml_writer_comment_counted(raptor_xml_writer* xml_writer, const unsigned char *s, unsigned int len);
RAPTOR_API
void raptor_xml_writer_flush(raptor_xml_writer* xml_writer);
RAPTOR_API
int raptor_world_enumerate_xml_writer_options(raptor_world* world, const raptor_option option, const char **name,  raptor_uri **uri, const char **label);
RAPTOR_API
int raptor_xml_writer_set_option(raptor_xml_writer *xml_writer, raptor_option option, int value);
RAPTOR_API
int raptor_xml_writer_set_option_string(raptor_xml_writer *xml_writer, raptor_option option, const unsigned char *value);
RAPTOR_API
int raptor_xml_writer_get_option(raptor_xml_writer *xml_writer, raptor_option option);
RAPTOR_API
const unsigned char *raptor_xml_writer_get_option_string(raptor_xml_writer *xml_writer, raptor_option option);
RAPTOR_API
int raptor_xml_writer_get_depth(raptor_xml_writer *xml_writer);

/**
 * raptor_sax2_start_element_handler:
 * @user_data: user data
 * @xml_element: XML element
 *
 * SAX2 start element handler
 */
typedef void (*raptor_sax2_start_element_handler)(void *user_data, raptor_xml_element *xml_element);

/**
 * raptor_sax2_end_element_handler:
 * @user_data: user data
 * @xml_element: XML element
 *
 * SAX2 end element handler
 */
typedef void (*raptor_sax2_end_element_handler)(void *user_data, raptor_xml_element* xml_element);

/**
 * raptor_sax2_characters_handler:
 * @user_data: user data
 * @xml_element: XML element
 * @s: string
 * @len: string len
 *
 * SAX2 characters handler
 */
typedef void (*raptor_sax2_characters_handler)(void *user_data, raptor_xml_element* xml_element, const unsigned char *s, int len);

/**
 * raptor_sax2_cdata_handler:
 * @user_data: user data
 * @xml_element: XML element
 * @s: string
 * @len: string len

 * SAX2 CDATA section handler
 */
typedef void (*raptor_sax2_cdata_handler)(void *user_data, raptor_xml_element* xml_element, const unsigned char *s, int len);

/**
 * raptor_sax2_comment_handler:
 * @user_data: user data
 * @xml_element: XML element
 * @s: string
 *
 * SAX2 XML comment handler
 */
typedef void (*raptor_sax2_comment_handler)(void *user_data, raptor_xml_element* xml_element, const unsigned char *s);

/**
 * raptor_sax2_unparsed_entity_decl_handler:
 * @user_data: user data
 * @entityName: entity name
 * @base: base URI
 * @systemId: system ID
 * @publicId: public ID
 * @notationName: notation name
 *
 * SAX2 unparsed entity (NDATA) handler
 */
typedef void (*raptor_sax2_unparsed_entity_decl_handler)(void *user_data, const unsigned char* entityName, const unsigned char* base, const unsigned char* systemId, const unsigned char* publicId, const unsigned char* notationName);

/**
 * raptor_sax2_external_entity_ref_handler:
 * @user_data: user data
 * @context: context
 * @base: base URI
 * @systemId: system ID
 * @publicId: public ID
 *
 * SAX2 external entity reference handler
 * 
 * Return value: 0 if processing should not continue because of a
 * fatal error in the handling of the external entity.
 */
typedef int (*raptor_sax2_external_entity_ref_handler)(void *user_data, const unsigned char* context, const unsigned char* base, const unsigned char* systemId, const unsigned char* publicId);


/**
 * raptor_log_level:
 * @RAPTOR_LOG_LEVEL_NONE: Internal
 * @RAPTOR_LOG_LEVEL_TRACE: very fine-grained tracing messages information
 * @RAPTOR_LOG_LEVEL_DEBUG: fine-grained tracing messages suitable for debugging
 * @RAPTOR_LOG_LEVEL_INFO: coarse-grained information messages
 * @RAPTOR_LOG_LEVEL_WARN: warning messages of potentially harmful problems
 * @RAPTOR_LOG_LEVEL_ERROR: error messages where the application can continue
 * @RAPTOR_LOG_LEVEL_FATAL: fatal error message where the application will likely abort
 * @RAPTOR_LOG_LEVEL_LAST: Internal
 *
 * Log levels
 */
typedef enum {
  RAPTOR_LOG_LEVEL_NONE,
  RAPTOR_LOG_LEVEL_TRACE,
  RAPTOR_LOG_LEVEL_DEBUG,
  RAPTOR_LOG_LEVEL_INFO,
  RAPTOR_LOG_LEVEL_WARN,
  RAPTOR_LOG_LEVEL_ERROR,
  RAPTOR_LOG_LEVEL_FATAL,
  RAPTOR_LOG_LEVEL_LAST = RAPTOR_LOG_LEVEL_FATAL
} raptor_log_level;


/**
 * raptor_error_handlers:
 * @magic: magic value - must use raptor_error_handlers_init() to set this
 * @world: raptor_world object
 * @locator: raptor locator of the error
 * @last_log_level: number of log levels; size of @handlers arrays
 * @handlers: user handlers per log level
 *
 * Error handlers structure
 */
typedef struct {
  unsigned int magic;

  raptor_world *world;

  raptor_locator* locator;

  /* size of handlers array */
  raptor_log_level last_log_level;

  /* this must be at the end of the structure to allow handlers array to grow */
  raptor_message_handler_closure handlers[RAPTOR_LOG_LEVEL_LAST+1];
} raptor_error_handlers;

RAPTOR_API
void raptor_error_handlers_init(raptor_world* world, raptor_error_handlers* error_handlers);


/* SAX2 API */
RAPTOR_API
raptor_sax2* raptor_new_sax2(raptor_world *world, raptor_locator *locator, void* user_data);
RAPTOR_API
void raptor_free_sax2(raptor_sax2 *sax2);

/* methods */
RAPTOR_API
void raptor_sax2_set_start_element_handler(raptor_sax2* sax2, raptor_sax2_start_element_handler handler);
RAPTOR_API
void raptor_sax2_set_end_element_handler(raptor_sax2* sax2, raptor_sax2_end_element_handler handler);
RAPTOR_API
void raptor_sax2_set_characters_handler(raptor_sax2* sax2, raptor_sax2_characters_handler handler);
RAPTOR_API
void raptor_sax2_set_cdata_handler(raptor_sax2* sax2, raptor_sax2_cdata_handler handler);
RAPTOR_API
void raptor_sax2_set_comment_handler(raptor_sax2* sax2, raptor_sax2_comment_handler handler);
RAPTOR_API
void raptor_sax2_set_unparsed_entity_decl_handler(raptor_sax2* sax2, raptor_sax2_unparsed_entity_decl_handler handler);
RAPTOR_API
void raptor_sax2_set_external_entity_ref_handler(raptor_sax2* sax2, raptor_sax2_external_entity_ref_handler handler);
RAPTOR_API
void raptor_sax2_set_namespace_handler(raptor_sax2* sax2, raptor_namespace_handler handler);
RAPTOR_API
void raptor_sax2_parse_start(raptor_sax2 *sax2, raptor_uri *base_uri);
RAPTOR_API
int raptor_sax2_parse_chunk(raptor_sax2* sax2, const unsigned char *buffer, size_t len, int is_end);
RAPTOR_API
const unsigned char* raptor_sax2_inscope_xml_language(raptor_sax2* sax2);
RAPTOR_API
raptor_uri* raptor_sax2_inscope_base_uri(raptor_sax2* sax2);



/* AVL Trees */
typedef struct raptor_avltree_s raptor_avltree;
typedef struct raptor_avltree_iterator_s raptor_avltree_iterator;

typedef int (*raptor_avltree_visit_function)(int depth, void* data, void *user_data);

#define RAPTOR_AVLTREE_FLAG_REPLACE_DUPLICATES 1

RAPTOR_API
raptor_avltree* raptor_new_avltree(raptor_world* world, raptor_data_compare_function compare_fn, raptor_data_free_function free_fn, unsigned int flags);
RAPTOR_API
void raptor_free_avltree(raptor_avltree* tree);

/* methods */
RAPTOR_API
int raptor_avltree_add(raptor_avltree* tree, void* p_user);
RAPTOR_API
void* raptor_avltree_remove(raptor_avltree* tree, void* p_data);
RAPTOR_API
int raptor_avltree_delete(raptor_avltree* tree, void* p_user);
RAPTOR_API
void* raptor_avltree_search(raptor_avltree* tree, const void* p_user);
RAPTOR_API
int raptor_avltree_visit(raptor_avltree* tree, raptor_avltree_visit_function visit_fn, void* user_data);
RAPTOR_API
int raptor_avltree_size(raptor_avltree* tree);
RAPTOR_API
void raptor_avltree_set_print_handler(raptor_avltree* tree, raptor_data_print_handler print_fn);
RAPTOR_API
void raptor_avltree_print(raptor_avltree* tree, FILE* stream);

#ifdef RAPTOR_DEBUG
int raptor_avltree_dump(raptor_avltree* tree, FILE* stream);
void raptor_avltree_check(raptor_avltree* tree);
#endif

RAPTOR_API
raptor_avltree_iterator* raptor_new_avltree_iterator(raptor_avltree* tree, void* range,  raptor_data_free_function range_free_fn, int direction);
RAPTOR_API
void raptor_free_avltree_iterator(raptor_avltree_iterator* iterator);

RAPTOR_API
int raptor_avltree_iterator_is_end(raptor_avltree_iterator* iterator);
RAPTOR_API
int raptor_avltree_iterator_next(raptor_avltree_iterator* iterator);
RAPTOR_API
void* raptor_avltree_iterator_get(raptor_avltree_iterator* iterator);


#ifdef __cplusplus
}
#endif

#endif
