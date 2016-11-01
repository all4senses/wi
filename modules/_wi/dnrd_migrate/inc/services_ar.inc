<?php

/**
 * @file
 * Contains classes for services (arabic) migration.
 */

/**
 * Class for Services (arabic) migrations.
 */
class ServicesArMigrate extends XMLMigration {

  /**
   * Performs services (arabic) migrations.
   */
  public function __construct($arguments = array()) {
    parent::__construct($arguments);

    $this->description = t('XML feed of News from SharePoint.');

    // "fields" from an XML feed, so we pass an explicit list of source fields.
    $fields = array(
      'd:Id' => t('ID'),
      'd:ServiceID' => t('Service ID'),
      'd:ServiceTitleAr' => t('Name'),
      'd:ServiceDescriptionAr' => t('Description'),
      'd:LogoSmall' => t('Image'),
      'd:RequiredDocuments' => t('Require Documents'),
      'd:Procedures' => t('Procedures'),
      'd:Fees' => t('Fees'),
      'd:AdditionalInfo' => t('Additional Info'),
      'd:ProcessingTime' => t('Processing Time'),
      'd:CommunicationInfoTel' => t('Communication Info Tel'),
      'd:CommunicationInfoFax' => t('Communication Info Fax'),
      'd:CommunicationInfoEmail' => t('d:Communication Info Email'),
      'd:CommunicationInfoOthers' => t('d:Communication Info Others'),
      'd:EFormURL' => t('EFormURL'),
      'd:EDnrdURL' => t('EDnrdURL'),
      'd:ASCategoryTitleId' => t('ASCategory TitleId'),
      'd:IsAudianceService' => t('Is Audience Servies'),
      'd:isTopService' => t('Is Top Servies'),
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
    $list_url = 'http://dnrd.ae/_layouts/RestProxy/Query.aspx?html=0&q=Services';

    // Each ID retrieved from the list URL will be plugged into :id in the
    // item URL to fetch the specific objects.
    $item_url = 'http://dnrd.ae/_layouts/RestProxy/Query.aspx?html=0&q=Services(:id)';

    // We use the MigrateSourceList class for any source where we obtain the
    // list of IDs to process separately from the data for each item. The
    // listing and item are represented by separate classes, so for example we
    // could replace the XML listing with a file directory listing, or the XML
    // item with a JSON item.
    $this->source = new MigrateSourceList(new DnrdMigrateListXML($list_url, $xpath),
      new MigrateItemXML($item_url), $fields);
    $this->destination = new MigrateDestinationNode('services');

    // TIP: Note that for XML sources, in addition to the source field passed to
    // addFieldMapping (the name under which it will be saved in the data row
    // passed through the migration process) we specify the Xpath used to retrieve
    // the value from the XML.
    $this->addFieldMapping('title', 'd:ServiceTitleAr')
      ->xpath('//d:ServiceTitleAr');

    $this->addFieldMapping('field_description', 'd:ServiceDescriptionAr')
      ->xpath('//d:ServiceDescription');

    $this->addFieldMapping('field_common_image', 'image_id');

    $this->addFieldMapping('field_common_image:file_class')
      ->defaultValue('MigrateFileFid');

    $this->addFieldMapping('field_required_documents', 'd:RequiredDocumentsAr')
      ->xpath('//d:RequiredDocuments');

    $this->addFieldMapping('field_procedures', 'd:Procedures')
      ->xpath('//d:Procedures');

    $this->addFieldMapping('field_fees', 'd:FeesAr')
      ->xpath('//d:Fees');

    $this->addFieldMapping('field_additional_info', 'd:AdditionalInfoAr')
      ->xpath('//d:AdditionalInfo');

    $this->addFieldMapping('field_processing_time', 'd:ProcessingTimeAr')
      ->xpath('//d:ProcessingTime');

    $this->addFieldMapping('field_communication_infotel', 'd:CommunicationInfoTel')
      ->xpath('//d:CommunicationInfoTel');

    $this->addFieldMapping('field_communication_infofax', 'd:CommunicationInfoFax')
      ->xpath('//d:CommunicationInfoFax');

    $this->addFieldMapping('field_communication_infoemail', 'd:CommunicationInfoEmail')
      ->xpath('//d:CommunicationInfoEmail');

    $this->addFieldMapping('field_communication_infoothers', 'd:CommunicationInfoOthers')
      ->xpath('//d:CommunicationInfoTel');

    $this->addFieldMapping('field_eformurl', 'd:EFormURL')
      ->xpath('//d:EFormURL');

    $this->addFieldMapping('field_ednrdurl', 'd:EDnrdURL')
      ->xpath('//d:EDnrdURL');

    $this->addFieldMapping('field_ascategory_titleid', 'asc_term_id');

    $this->addFieldMapping('field_ascategory_titleid:source_type')
      ->defaultValue('tid');

    $this->addFieldMapping('field_ascategory_titleid:create_term')
      ->defaultValue(FALSE);

    $this->addFieldMapping('field_ascategory_titleid:ignore_case')
      ->defaultValue(TRUE);

    $this->addFieldMapping('field_service_id', 'd:ServiceID')
      ->xpath('//d:Id');

    $this->addFieldMapping('tnid', 't_nid');

    $this->addFieldMapping('status')
      ->defaultValue(1);

    $this->addFieldMapping('promote')
      ->defaultValue(0);

    $this->addFieldMapping('sticky')
      ->defaultValue(0);

    $this->addFieldMapping('language')
      ->defaultValue('en');

    $this->addFieldMapping('field_is_audiance_service', 'is_audience_service');
    $this->addFieldMapping('field_is_top_service', 'is_top_service');
    
    // Declare unmapped source fields.
    $unmapped_sources = array(
      'd:Title',
      'd:ServiceDescription',
      'd:IsAudianceService',
      'd:LogoLarge',
      'd:RequiredDocuments',
      'd:ProceduresAr',
      'd:FeesAr',
      'd:AdditionalInfo',
      'd:ProcessingTime',
      'd:ShowOnMainPage',
      'd:IsTopService',
      'd:Active',
      'd:CreatedMonth',
      'd:CreatedYear',
      'd:ModifiedMonth',
      'd:ModifiedYear',
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
      'nid',
      'uid',
      'created',
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

  /**
   * Adds entries to $row.
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) == FALSE) {
      return FALSE;
    }
    $result = $this->applyXpath($row, '//d:ASCategoryTitleId');
    // Selects term id of audiecne_service_category for mapping.
    $query = db_select('migrate_map_audience_service_cateogry_ar', 'ma')
      ->fields('ma', array('destid1'))
      ->condition('sourceid1', $result);

    $term = $query->execute()->fetchField();
    $row->asc_term_id = $term;

    $result = $this->applyXpath($row, '//d:Id');
    // Select node id for corresponding services(en) node.
    $query = db_select('migrate_map_services', 'ms')
      ->fields('ma', array('destid1'))
      ->condition('sourceid1', $result);
    $destId = $query->execute()->fetchField();
    // Add tnid to services(en) node to current nid of service(ar) node.
    $node = node_load($destId);
    $tnid = $node->nid;
    $row->t_nid = $tnid;
    // Select fid of image attached to service(en) node.
    $query = db_select('file_usage', 'fu')
      ->fields('fu', array('fid'))
      ->condition('type', 'node')
      ->condition('id', $tnid);

    $fid = $query->execute()->fetchField();

    $is_audience_service = $this->applyXpath($row, '//d:IsAudianceService');
    $is_top_service = $this->applyXpath($row, '//d:isTopService');
    // Sets status of field_is_audiance_service.
    if ($is_audience_service == 'true') {
      $row->is_audience_service = '1';
    }
    else {
      $row->is_audience_service = '0';
    }
    // Sets status of field_is_top_service.
    if ($is_top_service == 'true') {
      $row->is_top_service = '1';
    }
    else {
      $row->is_top_service = '0';
    }

    $row->image_id = $fid;
  }

}
