<?php
/**
 * This file is automatically @generated by {@link BuildMetadataPHPFromXml}.
 * Please don't modify it directly.
 */


return array (
  'generalDesc' => 
  array (
    'NationalNumberPattern' => '[1-9]\\d{6,7}',
    'PossibleNumberPattern' => '\\d{7,8}',
  ),
  'fixedLine' => 
  array (
    'NationalNumberPattern' => '
          (?:
            1(?:
              0[0-8]|
              1[49]|
              2[37]|
              3[0137]|
              4[147]|
              5[05]|
              6[58]|
              7[0167]|
              8[58]|
              9[139]
            )|
            2(?:
              [0235679]\\d|
              1[0-7]|
              4[04-9]|
              8[028]
            )|
            3(?:
              [09]\\d|
              1[014-7]|
              2[0-3]|
              3[03]|
              4[03-57]|
              55|
              6[068]|
              7[06-8]|
              8[06-9]
            )|
            4(?:
              3[013-69]|
              4\\d|
              7[0-589]
            )|
            5(?:
              [01]\\d|
              2[0-7]|
              [56]0|
              79
            )|
            7(?:
              0[09]|
              2[0-267]|
              3[06]|
              [469]0|
              5[06-9]|
              7[0-24-79]|
              8[7-9]
            )|
            8(?:
              09|
              [34]\\d|
              5[0134]|
              8[02]
            )|
            9(?:
              0[6-9]|
              1[016-8]|
              2[036-8]|
              3[3679]|
              40|
              5[0489]|
              6[06-9]|
              7[046-9]|
              8[36-8]|
              9[1-9]
            )
          )\\d{4}
        ',
    'PossibleNumberPattern' => '\\d{7}',
    'ExampleNumber' => '2001234',
  ),
  'mobile' => 
  array (
    'NationalNumberPattern' => '
          (?:
            1[16]1|
            21[89]|
            8(?:
              1[01]|
              7[23]
            )
          )\\d{4}|
          6(?:
            [024-9]\\d|
            1[0-5]|
            3[0-24-9]
          )\\d{5}
        ',
    'PossibleNumberPattern' => '\\d{7,8}',
    'ExampleNumber' => '60012345',
  ),
  'tollFree' => 
  array (
    'NationalNumberPattern' => '80[09]\\d{4}',
    'PossibleNumberPattern' => '\\d{7}',
    'ExampleNumber' => '8001234',
  ),
  'premiumRate' => 
  array (
    'NationalNumberPattern' => '
          (?:
            779|
            8(?:
              55|
              60|
              7[78]
            )|
            9(?:
              00|
              81
            )
          )\\d{4}
        ',
    'PossibleNumberPattern' => '\\d{7}',
    'ExampleNumber' => '8601234',
  ),
  'sharedCost' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'personalNumber' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'voip' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'pager' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'uan' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'emergency' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'voicemail' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'shortCode' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'standardRate' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'carrierSpecific' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'noInternationalDialling' => 
  array (
    'NationalNumberPattern' => 'NA',
    'PossibleNumberPattern' => 'NA',
  ),
  'id' => 'PA',
  'countryCode' => 507,
  'internationalPrefix' => '00',
  'sameMobileAndFixedLinePattern' => false,
  'numberFormat' => 
  array (
    0 => 
    array (
      'pattern' => '(\\d{3})(\\d{4})',
      'format' => '$1-$2',
      'leadingDigitsPatterns' => 
      array (
        0 => '[1-57-9]',
      ),
      'nationalPrefixFormattingRule' => '',
      'domesticCarrierCodeFormattingRule' => '',
    ),
    1 => 
    array (
      'pattern' => '(\\d{4})(\\d{4})',
      'format' => '$1-$2',
      'leadingDigitsPatterns' => 
      array (
        0 => '6',
      ),
      'nationalPrefixFormattingRule' => '',
      'domesticCarrierCodeFormattingRule' => '',
    ),
  ),
  'intlNumberFormat' => 
  array (
  ),
  'mainCountryForCode' => false,
  'leadingZeroPossible' => false,
  'mobileNumberPortableRegion' => true,
);
