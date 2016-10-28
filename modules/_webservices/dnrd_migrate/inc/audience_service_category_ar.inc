<?php

/**
 * @file
 * Defines audience_service_category (arabic) taxonomy term migrations.
 */

/**
 *
 */
class AudienceServiceCategoryArMigrate extends XMLMigration {

  /**
   * Performs audience_service_category (arabic) taxonomy term migrations.
   */
  public function __construct($arguments = array()) {
    parent::__construct($arguments);

    $this->description = t('XML feed of News from SharePoint.');

    // "fields" from an XML feed, so we pass an explicit list of source fields.
    $fields = array(
      'd:Id' => t('ID'),
      'd:ASCategoryTitleAr' => t('Name'),
      'd:CategoryDescriptionAr' => t('Description'),
      'd:AudianceTypeId' => t('AudienceType'),
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
    $list_url = 'http://dnrd.ae/_layouts/RestProxy/Query.aspx?html=0&q=AudianceServiceCategory';

    // Each ID retrieved from the list URL will be plugged into :id in the
    // item URL to fetch the specific objects.
    $item_url = 'http://dnrd.ae/_layouts/RestProxy/Query.aspx?html=0&q=AudianceServiceCategory(:id)';

    // We use the MigrateSourceList class for any source where we obtain the
    // list of IDs to process separately from the data for each item. The
    // listing and item are represented by separate classes, so for example we
    // could replace the XML listing with a file directory listing, or the XML
    // item with a JSON item.
    $this->source = new MigrateSourceList(new DnrdMigrateListXML($list_url, $xpath),
      new MigrateItemXML($item_url), $fields);
    $this->destination = new MigrateDestinationTerm('audience_service_category');

    // TIP: Note that for XML sources, in addition to the source field passed to
    // addFieldMapping (the name under which it will be saved in the data row
    // passed through the migration process) we specify the Xpath used to retrieve
    // the value from the XML.
    $this->addFieldMapping('name', 'd:ASCategoryTitleAr')
      ->xpath('//d:ASCategoryTitleAr');

    $this->addFieldMapping('description', 'd:CategoryDescriptionAr')
      ->xpath('//d:CategoryDescription');

    $this->addFieldMapping('field_audience_type', 'term_id');
    $this->addFieldMapping('field_audience_type:source_type')
      ->defaultValue('tid');

    $this->addFieldMapping('field_audience_type:create_term')
      ->defaultValue(FALSE);
    $this->addFieldMapping('field_audience_type:ignore_case')
      ->defaultValue(TRUE);

    $this->addFieldMapping('weight')
      ->defaultValue(0);

    // Declare unmapped source fields.
    $unmapped_sources = array(
      'd:Title',
      'd:ASCategoryTitleEn',
      'd:CategoryDescriptionEn',
      'd:Active',
      'd:ServiceID',
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

  /**
   * Adds entry in $row for term id of audience to be mapped
   * to audience_type reference field.
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) == FALSE) {
      return FALSE;
    }
    $result = $this->applyXpath($row, '//d:AudianceTypeId');
    // Select term id of audience (arabic).
    $query = db_select('migrate_map_audience_ar', 'ma')
      ->fields('ma', array('destid1'))
      ->condition('sourceid1', $result);

    $term = $query->execute()->fetchField();
    $row->term_id = $term;
    return TRUE;
  }

}
