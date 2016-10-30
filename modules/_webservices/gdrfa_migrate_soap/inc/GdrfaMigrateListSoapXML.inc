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
class Gdrfa_MigrateListSoapXML extends MigrateListXML {
  /**
   * A URL pointing to an XML document containing a list of IDs to be processed.
   *
   * @var string
   */
  //protected $listUrl;

  /**
   * Xpath for the list of content to be migrated.
   *
   * @var string
   */
  //protected $xpath;
  
  
  
  /**
   * SOAP service name, created in WSClient.
   *
   * @var string
   */
  protected $soap_service_name;

  /**
   * Customization required to pass in xpath.
   *
   * @override
   */
  public function __construct($soap_service_name) {
    //parent::__construct($list_url);
    $this->soap_service_name = $soap_service_name;
  }

  
  /**
   * {@inheritdoc}
   *
   * Our public face is the SOAP Service we're getting items from
   */
  public function __toString() {
    return $this->soap_service_name;
  }
  
  /**
   * Load the XML at the given URL, and return an array of the IDs found within.
   *
   * @return array
   *   Array to be passed on for iteration to MigrateItemXML class.
   *
   * @override
   */
  public function getIdList($target = 'IDs') {
    migrate_instrument_start("Retrieve $target from the $this->soap_service_name SOAP service");
    
    /*
    $context = stream_context_create(array(
      'http' => array('header' => 'Accept: application/xml'),
    ));
    $xml = file_get_contents($this->listUrl, FALSE, $context);
    $xml = simplexml_load_string($xml);
    */
    
    if($service = wsclient_service_load($this->soap_service_name)) {
      
      if($soap_results = $service->GetPendingRecordIds()) {
        if (!empty($soap_results->GetPendingRecordIdsResult->long)) {
          return array_unique($soap_results->GetPendingRecordIdsResult->long);
        }
        else {
          return NULL;
        }
      }
      else {
        Migration::displayMessage(t(
          "Calling a !soap_service_name SOAP service\'s function GetPendingRecordIds() for $target has failed",
          array('!soap_service_name' => $this->soap_service_name)
        ));
      }
      
    }
    else {
      Migration::displayMessage(t(
        "Accessing service !soap_service_name for $target has failed",
        array('!soap_service_name' => $this->soap_service_name)
      ));
    }
    
    migrate_instrument_stop("Retrieve $target from the $this->soap_service_name SOAP service");
    
    /*
    if ($xml !== FALSE) {
      return array_unique($ids);
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
    */
  }

  /**
   * {@inheritdoc}
   *
   * Return a count of all available IDs from the source listing.
   * The default implementation assumes the count of top-level elements
   * reflects the number of IDs available - in many cases, you will need
   * to override this to reflect your particular XML structure.
   */
  public function computeCount() {
    
    if($ids = getIdList('--Count of IDs--')) {
      return count($ids);
    }
    else {
      return 0;
    }
    
    
    /*
    $xml = simplexml_load_file($this->listUrl);
    $this->registerNamespaces($xml);
    // Number of sourceid elements beneath the top-level element.
    $count = count($xml);
    // Additionally, if there are any namespaces registered, try to count
    // elements with namespaces as well.
    if ($namespaces = $xml->getNamespaces()) {
      foreach ($namespaces as $prefix => $url) {
        $count += count($xml->children($url));
      }
    }
    
    return $count;
    */
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
  /*
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
*/  

}
