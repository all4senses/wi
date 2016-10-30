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
   * Call to SOAP service and return an array of the IDs found within.
   *
   * @return array
   *   Array to be passed on for iteration to MigrateItemSoapXML class.
   *
   * @override
   */
  public function getIdList($target = 'IDs') {
    migrate_instrument_start("Retrieve $target from the $this->soap_service_name SOAP service");
    
    
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
    
    if($ids = $this->getIdList('--Count of IDs--')) {
      return count($ids);
    }
    else {
      return 0;
    }
    
   
  }
  

}


/**
 * Implementation of MigrateItem, for retrieving a parsed XML document given
 * an ID provided by a MigrateList class.
 */
class Gdrfa_MigrateItemSoapXML extends MigrateItem {
  /**
   * A URL pointing to an XML document containing the data for one item to be
   * migrated.
   *
   * @var string
   */
  //protected $itemUrl;
  protected $soap_service_name;

  /**
   * An array of namespaces to explicitly register before Xpath queries.
   *
   * @var array
   */
  protected $namespaces;

  /**
   * {@inheritdoc}
   */
  
    
  public function __construct($soap_service_name, array $namespaces = array()) {
    parent::__construct();
    //$this->itemUrl = $item_url;
    $this->soap_service_name = $soap_service_name;
    $this->namespaces = $namespaces;
    // Suppress errors during parsing, so we can pick them up after.
    libxml_use_internal_errors(TRUE);
  }

  /**
   * Explicitly register namespaces on an XML element.
   *
   * @param SimpleXMLElement $xml
   *   A SimpleXMLElement to register the namespaces on.
   */
  protected function registerNamespaces(SimpleXMLElement &$xml) {
    foreach ($this->namespaces as $prefix => $namespace) {
      $xml->registerXPathNamespace($prefix, $namespace);
    }
  }

  /**
   * {@inheritdoc}
   *
   * Implementors are expected to return an object representing a source item.
   */
  public function getItem($id) {
    // Make sure we actually have an ID.
    if (empty($id)) {
      return NULL;
    }
    
    /*
    $item_url = $this->constructItemUrl($id);
    // And make sure we actually got a URL to fetch.
    if (empty($item_url)) {
      return NULL;
    }
    */
    
    // Get the XML object at the specified URL.
    //$xml = $this->loadXmlUrl($item_url);
    
    $xml = $this->loadXml_from_SOAP($id);
    
    dpm($xml, '$xml 1');
    
    if ($xml !== FALSE) {
      if ($xml) {
        $this->registerNamespaces($xml);
        dpm($xml, '$xml 2');
        $return = new stdclass();
        $return->xml = $xml;
      }
      else {
        $return = NULL;
      }
      return $return;
    }
    else {
      $migration = Migration::currentMigration();
      $message = t('Loading of item !id from SOAP service has failed:', array('!id' => $id));
      foreach (libxml_get_errors() as $error) {
        $message .= "\n" . $error->message;
      }
      $migration->getMap()->saveMessage(
        array($id), $message, MigrationBase::MESSAGE_ERROR);
      libxml_clear_errors();
      return NULL;
    }
  }

  /**
   * Creates a valid URL pointing to current item.
   *
   * The default implementation simply replaces the :id token in the URL with
   * the ID obtained from MigrateListXML. Override if the item URL is not so
   * easily expressed from the ID.
   *
   * @param mixed $id
   *   XML item ID
   *
   * @return string
   *   Formatted string with replaced tokens
   */
  /*
  protected function constructItemUrl($id) {
    return str_replace(':id', $id, $this->itemUrl);
  }
  */

  /**
   * Loads the XML.
   *
   * Default XML loader - just use Simplexml directly. This can be overridden
   * for preprocessing of XML (removal of unwanted elements, caching of XML if
   * the source service is slow, etc.)
   *
   * @param string $item_url
   *   URL to the XML file
   *
   * @return SimpleXMLElement
   *   Loaded XML
   */
  /*
  protected function loadXmlUrl($item_url) {
    return simplexml_load_file($item_url);
  }
  */
  
  /**
   * Loads the XML.
   *
   * Default XML loader - just use Simplexml directly. This can be overridden
   * for preprocessing of XML (removal of unwanted elements, caching of XML if
   * the source service is slow, etc.)
   *
   * @param string $item_url
   *   URL to the XML file
   *
   * @return SimpleXMLElement
   *   Loaded XML
   */
  protected function loadXml_from_SOAP($id) {
    
    $service = wsclient_service_load($this->soap_service_name);
    $soap_results = $service->GetProcedures(array($id));
    dpm($soap_results, '$soap_results 1');
    $xml = simplexml_load_string('<xml>' . $soap_results->GetProceduresResult->any . '</xml>', NULL, NULL, "http://schemas.xmlsoap.org/soap/envelope/");
    dpm($xml, '$xml x1');
    $ids = array();
    foreach ($soap->xpath('//DocumentElement/dummy/Ebeneficiary') as $key => $item) {
    //foreach ($soap->xpath('//dummy[@diffgr:id="dummy1"]')[0]->children() as $key => $item) {
        $ids[(string) $key] =(string) $item;
    }
    dpm($ids,'$ids');



    //return simplexml_load_file($item_url);
    return $xml;
  }
  

  /**
   * Implments MigrateItem::hash().
   */
  public function hash($row) {
    // $row->xml is a SimpleXMLElement. Temporarily set it as an XML string
    // to prevent parent::hash() failing when try to create the hash.
    migrate_instrument_start('MigrateItemSoapXML::hash');
    $hash = md5(serialize($row->xml->asXML()));
    migrate_instrument_stop('MigrateItemSoapXML::hash');
    return $hash;
  }
}
