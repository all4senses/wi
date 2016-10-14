<?php

/**
 * @file
 * CCK Field for Senegalese phone numbers.
 */

//define('PHONE_SN_REGEX', '/((\+221|00221)?)((7[7608][0-9]{7}$)|(3[03][98][0-9]{6}$))/');

function phone_sn_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Senegalese phone number',
  );
}

/**
 * Verification for Senegalese Phone Numbers.
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_sn_phone_number($phonenumber) {
  // define regular expression
  $regex = "/^(\+221\s+)?\d{2}(\s*|\-)\d{3}(\s*|\-)\d{4}(\s*|\-)$/i";
  // return true if valid, false otherwise
  return (bool) preg_match($regex, $phonenumber);
}

/**
 * Formatting for Senegalese Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns the phone number as string.
 */
function format_sn_phone_number($phonenumber, $field = FALSE) {
  $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);

   if(strlen($phonenumber) < 9)
       $phonenumber = '221' . $phonenumber;

   return $phonenumber;
}

