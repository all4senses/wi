<?php

/**
 * @file
 * Defines news migration class.
 */

/**
 *
 */
class NewsMigrate extends XMLMigration {

  /**
   * Performs news migration.
   */
  public function __construct($arguments = array()) {
    parent::__construct($arguments);

    $this->description = t('XML feed of News from SharePoint.');

    // "fields" from an XML feed, so we pass an explicit list of source fields.
    $fields = array(
      'd:Id' => t('Service ID'),
      'd:NewsTitleEn' => t('Name'),
      'd:ShortDescriptionEn' => t('Short Description'),
      'd:NewsDetailEn' => t('Description'),
      'd:RollupImage' => t('Image'),
      'd:IsArchive' => t('Is News in Archive Status or Not'),
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
      MigrateDestinationNode::getKeySchema()
    );

    $xpath = '//m:properties/d:Id';

    // Source list URL.
    $list_url = 'http://dnrd.ae/_layouts/RestProxy/Query.aspx?html=0&q=News';

    // Each ID retrieved from the list URL will be plugged into :id in the
    // item URL to fetch the specific objects.
    $item_url = 'http://dnrd.ae/_layouts/RestProxy/Query.aspx?html=0&q=News(:id)';

    // We use the MigrateSourceList class for any source where we obtain the
    // list of IDs to process separately from the data for each item. The
    // listing and item are represented by separate classes, so for example we
    // could replace the XML listing with a file directory listing, or the XML
    // item with a JSON item.
    $this->source = new MigrateSourceList(new DnrdMigrateListXML($list_url, $xpath),
      new MigrateItemXML($item_url), $fields);
    $this->destination = new MigrateDestinationNode('news');

    // TIP: Note that for XML sources, in addition to the source field passed to
    // addFieldMapping (the name under which it will be saved in the data row
    // passed through the migration process) we specify the Xpath used to retrieve
    // the value from the XML.
    $this->addFieldMapping('title', 'title');

    $this->addFieldMapping('field_short_description', 'short_description');

    $this->addFieldMapping('field_description', 'description');

    $this->addFieldMapping('field_common_image', 'image_id');

    $this->addFieldMapping('field_common_image:file_class')
      ->defaultValue('MigrateFileFid');

    $this->addFieldMapping('field_common_image:preserve_files', 'title');

    $this->addFieldMapping('field_common_image:alt', 'title');

    $this->addFieldMapping('field_common_image:title', 'title');

    $this->addFieldMapping('field_is_archive', 'is_archive');

    $this->addFieldMapping('language', 'language');

    $this->addFieldMapping('status')
      ->defaultValue(1);

    $this->addFieldMapping('promote')
      ->defaultValue(0);

    $this->addFieldMapping('sticky')
      ->defaultValue(0);

    // Declare unmapped source fields.
    $unmapped_sources = array(
      'd:NewsTitleAr',
      'd:ShortDescriptionEn',
      'd:ShortDescriptionAr',
      'd:NewsDetailAr',
      'd:IsShowOnMain',
      'd:Active ',
      'd:ShowOnMainPage',
      'd:OLD_ID',
      'd:Id',
      'd:ContentType',
      'd:Modified',
      'd:Created',
      'd:Path',
    );
    $this->addUnmigratedSources($unmapped_sources);

    // Declare unmapped destination fields.
    $unmapped_destinations = array(
      'nid',
      'uid',
      'field_news_category',
      'field_keywords',
      'metatags',
      'redirect',
      'changed',
      'log',
      'tnid',
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

  /**
   * Adds entries in $row.
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) == FALSE) {
      return FALSE;
    }
    $result = $this->applyXpath($row, '//d:LanguageValue');
    $image_url = $this->applyXpath($row, '//d:RollupImage');
    $archive_status = $this->applyXpath($row, '//d:IsArchive');

    // We set title, description on basis of Language.
    if ($result == 'EN') {
      $row->title = $this->applyXpath($row, '//d:NewsTitleEn');
      $row->short_description = $this->applyXpath($row, '//d:ShortDescriptionEn');
      $row->description = $this->applyXpath($row, '//d:NewsDetailEn');
      $row->language = 'en';
    }
    elseif ($result == 'Both') {
      $row->language = 'en';
      $row->title = $this->applyXpath($row, '//d:NewsTitleEn');
      $row->short_description = $this->applyXpath($row, '//d:ShortDescriptionEn');
      $row->description = $this->applyXpath($row, '//d:NewsDetailEn');

      // We create entries in $row for creating a corresponding translated node.
      $row->title_ar = $this->applyXpath($row, '//d:NewsTitleAr');
      $row->short_description_ar = $this->applyXpath($row, '//d:ShortDescriptionAr');
      $row->description_ar = $this->applyXpath($row, '//d:NewsDetailAr');
    }
    else {
      $row->title = $this->applyXpath($row, '//d:NewsTitleAr');
      $row->short_description_ar = $this->applyXpath($row, '//d:ShortDescriptionAr');
      $row->description = $this->applyXpath($row, '//d:NewsDetailAr');
      $row->language = 'ar';
    }
    // Sets status of field is_archive.
    if ($archive_status == 'true') {
      $row->is_archive = '1';
    }
    else {
      $row->is_archive = '0';
    }
    // Image url contains ',' at end of URL from XML so we handle it here.
    if (preg_match('/,/', $image_url)) {
      $url = explode(',', $image_url);
      if (empty($url[count($url) - 1])) {
        unset($url[count($url) - 1]);
      }
      $url = implode('', $url);
    }
    // Retrieves and creates file from URL and returns a file object.
    $file = system_retrieve_file($url, NULL, TRUE);
    $row->image_id = $file->fid;
  }

  /**
   * Creates a new node corresponding to current node depends on
   * if $row->language is set to 'Both'.
   * Also sets tid to current node id.
   */
  public function complete($entity, stdClass $row) {
    if ($row->languge == 'Both') {
      $node = new stdClass();
      $node->type = 'news';
      $node->title = $row->title_ar;
      // Description field.
      $node->field_short_description['und'][0] = array(
        'value_format' => NULL,
        'value' => $row->short_description_ar,
      );
      $node->field_description['und'][0] = array(
        'value_format' => NULL,
        'value' => $this->description_ar,
      );
      // Image field.
      $node->field_common_image = array(
        'fid' => $row->image_id,
        'alt' => $row->title,
        'title' => $row->title,
      );
      $node->field_is_archive = $row->is_archive;
      $node->language = 'ar';
      $node->status = 1;
      $node->promote = 0;
      $node->comment = 0;
      $node->tnid = $entity->nid;
      // Prepare node for saving.
      $node = node_submit($node);
      node_save($node);
    }
  }

}
