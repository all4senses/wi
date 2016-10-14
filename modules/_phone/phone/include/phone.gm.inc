<?php

define('PHONE_NUMBER_PREFIX', 220);
define('PHONE_NUMBER_LENGTH', 7);

/**
 * @file
 * CCK Field for Gambia phone numbers.
 */

function phone_gm_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Gambia phone number!',
  );
}

/**
 * Verifies that $phonenumber is valid
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_gm_phone_number($phonenumber) {
  // define regular expression
  //$regex = "/^(\+220\s+)?\d{3}(\s*|\-)\d{4}(\s*|\-)$/i";
  // return true if valid, false otherwise
  //return (bool) preg_match($regex, $phonenumber);
  $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);
  if(strlen($phonenumber) == PHONE_NUMBER_LENGTH) {
    return true;
  }
  return false;
}

/**
 * Formatting for Gambia Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_gm_phone_number($phonenumber, $field) {
   $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);

   if(strlen($phonenumber) == PHONE_NUMBER_LENGTH)
       $phonenumber = PHONE_NUMBER_PREFIX . $phonenumber;

   return $phonenumber;
}
