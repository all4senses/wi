<?php
/**
 * @file
 * Class DnrdMigrateListXML.
 *
 * Overrides MigrateListXML functions to accommodate for handling the data
 * returned by DNRD Sharepoint Web API.
 */

/**
 * Custom MigrateListXML needed for the xml structure provided by Web API.
 *
 * The struct doesn't fit in what Migrate module provides out of the box.
 */
class DnrdMigrateListXML extends MigrateListXML {
  /**
   * A URL pointing to an XML document containing a list of IDs to be processed.
   *
   * @var string
   */
  protected $listUrl;

  /**
   * Xpath for the list of content to be migrated.
   *
   * @var string
   */
  protected $xpath;

  /**
   * Customization required to pass in xpath.
   *
   * @override
   */
  public function __construct($list_url, $xpath) {
    parent::__construct($list_url);
    $this->xpath = $xpath;
  }

  /**
   * Load the XML at the given URL, and return an array of the IDs found within.
   *
   * @return array
   *   Array to be passed on for iteration to MigrateItemXML class.
   *
   * @override
   */
  public function getIdList() {
    migrate_instrument_start("Retrieve $this->listUrl");
    $context = stream_context_create(array(
      'http' => array('header' => 'Accept: application/xml'),
    ));
    $xml = file_get_contents($this->listUrl, FALSE, $context);
    $xml = simplexml_load_string($xml);
    migrate_instrument_stop("Retrieve $this->listUrl");
    if ($xml !== FALSE) {
      return $this->getIDsFromXML($xml);
    }
    else {
      Migration::displayMessage(t(
        'Loading of !listUrl failed:',
        array('!listUrl' => $this->listUrl)
      ));
      foreach (libxml_get_errors() as $error) {
        Migration::displayMessage(MigrateItemsXML::parseLibXMLError($error));
      }
      return NULL;
    }
  }

  /**
   * Overrides to fetch the id of elements that need to be migrated.
   *
   * @param SimpleXMLElement $xml
   *   An instance of SimpleXMLElement class allowing us to fetch XML content.
   *
   * @return array
   *   Array of item ids that need to be migrated sorted by modified.
   *
   * @override
   */
  protected function getIDsFromXML(SimpleXMLElement $xml) {
    $ids = array();
    $result = $xml->xpath($this->xpath);

    foreach ($result as $element) {
      $ids[] = (string) $element;
    }
    // Additionally, if there are any namespaces registered, try to parse
    // elements with namespaces as well.
    if ($namespaces = $xml->getNamespaces()) {
      foreach ($namespaces as $prefix => $url) {
        foreach ($xml->children($url) as $element) {
          $ids[] = (string) $element;
        }
      }
    }
    return array_unique($ids);
  }

}
