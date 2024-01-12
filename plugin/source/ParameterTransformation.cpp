
#include "ParameterTransformation.h"

#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>

int main() {
    // Initialize the libraries
    xmlInitParser();
    xmlXPathInit();
    xsltInit();

    // Parse the XML and XSLT documents
    xmlDocPtr xml = xmlParseFile("input.xml");
    xmlDocPtr xsl = xmlParseFile("transform.xsl");

    // Create an XSLT stylesheet object from the XSLT document
    xsltStylesheetPtr stylesheet = xsltParseStylesheetDoc(xsl);

    // Apply the transformation
    xmlDocPtr result = xsltApplyStylesheet(stylesheet, xml, NULL);

    // Save the result to a file
    FILE* output = fopen("output.xml", "w");
    xsltSaveResultToFile(output, result, stylesheet);
    fclose(output);

    // Clean up
    xsltFreeStylesheet(stylesheet);
    xmlFreeDoc(result);
    xmlFreeDoc(xml);

    // Shutdown the libraries
    xsltCleanupGlobals();
    xmlCleanupParser();

    return 0;
}