<?php

/**
 * @file
 * Defines audience taxonomy term migrations.
 */

/**
 *
 */
class AudienceMigrate_Soap extends XMLMigration {

  /**
   * Performs audience taxonomy term migration.
   */
  public function __construct($arguments = array()) {
        
    parent::__construct($arguments);

    $this->description = t('Get Procedure (English) from SOAP service (SharePoint).');

    // "fields" from an XML feed, so we pass an explicit list of source fields.
    $fields = array(
//      'd:Id' => t('ID'),
//      'd:Title' => t('Name'),
//      'd:AudienceDesc' => t('Description'),
      
      'RecordID' => t('Record ID'),
      'ServiceID' => t('Service ID'),
      'AProcedureName' => t('A ProcedureName'),
      'Ebeneficiary' => t('E Beneficiary'),
    );

    // The source ID here is the one retrieved from the XML listing URL, and
    // used to identify the specific item's URL.
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'RecordID' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Record ID',
        ),
      ),
      MigrateDestinationTerm::getKeySchema()
    );

    //$xpath = '//m:properties/d:Id';

    // Source list URL.
    //$list_url = 'http://dnrd.ae/_layouts/RestProxy/Query.aspx?html=0&q=Audiance';
    $soap_service_name = 'test_soap';

    // Each ID retrieved from the list URL will be plugged into :id in the
    // item URL to fetch the specific objects.
    //$item_url = 'http://dnrd.ae/_layouts/RestProxy/Query.aspx?html=0&q=Audiance(:id)';

    // We use the MigrateSourceList class for any source where we obtain the
    // list of IDs to process separately from the data for each item. The
    // listing and item are represented by separate classes, so for example we
    // could replace the XML listing with a file directory listing, or the XML
    // item with a JSON item.
    
//    $this->source = new MigrateSourceList(new DnrdMigrateListXML($list_url, $xpath),
//      new MigrateItemXML($item_url), $fields);
    $this->source = new MigrateSourceList(new Gdrfa_MigrateListSoapXML($soap_service_name),
      new Gdrfa_MigrateItemSoapXML($soap_service_name), $fields);
    
    
    $this->destination = new MigrateDestinationNode('service_soap');
   

    // TIP: Note that for XML sources, in addition to the source field passed to
    // addFieldMapping (the name under which it will be saved in the data row
    // passed through the migration process) we specify the Xpath used to retrieve
    // the value from the XML.
    
    $this->addFieldMapping('title', 'RecordID')->xpath('//RecordID');

    $this->addFieldMapping('field_service_id', 'ServiceID')->xpath('//ServiceID');

    $this->addFieldMapping('field_a_procedure_name', 'AProcedureName')->xpath('//AProcedureName');
    
    $this->addFieldMapping('field_e_beneficiary', 'Ebeneficiary')->xpath('//Ebeneficiary');

    $this->addFieldMapping('status')
      ->defaultValue(1);

    $this->addFieldMapping('promote')
      ->defaultValue(0);

    $this->addFieldMapping('sticky')
      ->defaultValue(0);

    // Declare unmapped source fields.
    $unmapped_sources = array(
      
      'EProcedureName',
      'ADepartment',
      'EDepartment',
      'ECustomerType',
      'ACustomerType',
      'Classification',
      'Status',
      'Estatus',
      'Astatus',

      'Abeneficiary',
      'AFeeRequired',
      'ARequirements',
      'ATools',
      'ANotesforCustomer',
      'ANoteforemployees',
      'ESubmissionPlaces',
      'ASubmissionPlaces',
      'AProcedureDetail',
      'OnLocal',
      'OnLine',
      'Modified',
      'NeedUpdate',
      'UpdateID',
      'Active',

    );
    $this->addUnmigratedSources($unmapped_sources);

    // Declare unmapped destination fields.
    $unmapped_destinations = array(
      'nid',
      'uid',
      'redirect',
      'changed',
      'log',
      'translate',
      'revision',
      'revision_uid',
      'is_new',
      'path',
      'pathauto',
      'comment',
    );
    $this->addUnmigratedDestinations($unmapped_destinations);
    
    
    

  }

}
