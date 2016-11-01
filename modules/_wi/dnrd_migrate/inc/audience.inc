<?php

/**
 * @file
 * Defines audience taxonomy term migrations.
 */

/**
 *
 */
class AudienceMigrate extends XMLMigration {

  /**
   * Performs audience taxonomy term migration.
   */
  public function __construct($arguments = array()) {
    parent::__construct($arguments);

    $this->description = t('XML feed of Audience (English) from SharePoint.');

    // "fields" from an XML feed, so we pass an explicit list of source fields.
    $fields = array(
      'd:Id' => t('ID'),
      'd:Title' => t('Name'),
      'd:AudienceDesc' => t('Description'),
    );

    // The source ID here is the one retrieved from the XML listing URL, and
    // used to identify the specific item's URL.
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'd:Id' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Source ID',
        ),
      ),
      MigrateDestinationTerm::getKeySchema()
    );

    $xpath = '//m:properties/d:Id';

    // Source list URL.
    $list_url = 'http://dnrd.ae/_layouts/RestProxy/Query.aspx?html=0&q=Audiance';

    // Each ID retrieved from the list URL will be plugged into :id in the
    // item URL to fetch the specific objects.
    $item_url = 'http://dnrd.ae/_layouts/RestProxy/Query.aspx?html=0&q=Audiance(:id)';

    // We use the MigrateSourceList class for any source where we obtain the
    // list of IDs to process separately from the data for each item. The
    // listing and item are represented by separate classes, so for example we
    // could replace the XML listing with a file directory listing, or the XML
    // item with a JSON item.
    $this->source = new MigrateSourceList(new DnrdMigrateListXML($list_url, $xpath),
      new MigrateItemXML($item_url), $fields);
    $this->destination = new MigrateDestinationTerm('audience');

    // TIP: Note that for XML sources, in addition to the source field passed to
    // addFieldMapping (the name under which it will be saved in the data row
    // passed through the migration process) we specify the Xpath used to retrieve
    // the value from the XML.
    $this->addFieldMapping('name', 'd:Title')
      ->xpath('//d:Title');

    $this->addFieldMapping('description', 'd:AudienceDesc')
      ->xpath('//d:AudienceDesc');

    $this->addFieldMapping('weight', 'd:Order')
      ->defaultValue(0)
      ->xpath('//d:Order');

    // Declare unmapped source fields.
    $unmapped_sources = array(
      'd:AudianceTypeAr',
      'd:AudianceURLAr',
      'd:AudienceDescAr',
      'd:Id',
      'd:ContentType',
      'd:Modified',
      'd:Created',
      'd:Path',
    );
    $this->addUnmigratedSources($unmapped_sources);

    // Declare unmapped destination fields.
    $unmapped_destinations = array(
      'format',
      'parent',
      'parent_name',
      'path',
      'pathauto',
    );
    $this->addUnmigratedDestinations($unmapped_destinations);

  }

}
