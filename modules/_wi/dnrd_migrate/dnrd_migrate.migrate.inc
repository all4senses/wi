<?php

/**
 * @file
 * Contains group of migration to register.
 */

/**
 * Implements hook_migrate_api().
 */
function dnrd_migrate_migrate_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'sharepoint' => array(
        'title' => t('SharePoint (English)'),
      ),
      'sharepoint_ar' => array(
        'title' => t('SharePoint (Arabic)'),
      ),
      'news' => array(
        'title' => t('News'),
      ),
    ),
    'migrations' => array(
      'audience' => array(
        'class_name' => 'AudienceMigrate',
        'group_name' => 'sharepoint',
      ),
      'audience_service_cateogry' => array(
        'class_name' => 'AudienceServiceCategoryMigrate',
        'group_name' => 'sharepoint',
      ),
      'services' => array(
        'class_name' => 'ServicesMigrate',
        'group_name' => 'sharepoint',
      ),
      'audience_ar' => array(
        'class_name' => 'AudienceArMigrate',
        'group_name' => 'sharepoint_ar',
      ),
      'audience_service_cateogry_ar' => array(
        'class_name' => 'AudienceServiceCategoryArMigrate',
        'group_name' => 'sharepoint_ar',
      ),
      'services_ar' => array(
        'class_name' => 'ServicesArMigrate',
        'group_name' => 'sharepoint_ar',
      ),
      'news' => array(
        'class_name' => 'NewsMigrate',
        'group_name' => 'news',
      ),
    ),
  );
  return $api;
}
