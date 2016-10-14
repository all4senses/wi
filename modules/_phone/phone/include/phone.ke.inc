<?php

define('PHONE_NUMBER_PREFIX', 254);
define('PHONE_NUMBER_LENGTH_MIN', 6);
define('PHONE_NUMBER_LENGTH_MAX', 9);

/**
 * @file
 * CCK Field for Kenya phone numbers.
 */

function phone_ke_metadata() {
  // These strings are translated using t() on output.
  return array(
    'error' => '"%value" is not a valid Kenya phone number!',
  );
}

/**
 * Verifies that $phonenumber is valid
 *
 * @param string $phonenumber
 * @return boolean Returns boolean FALSE if the phone number is not valid.
 */
function valid_ke_phone_number($phonenumber) {
  // define regular expression
  //$regex = "/^(\+254\s+)?\d{2}(\s*|\-)\d{3}(\s*|\-)\d{4}(\s*|\-)$/i";
  // return true if valid, false otherwise
  //return (bool) preg_match($regex, $phonenumber);
  $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);
  if(strlen($phonenumber) >= PHONE_NUMBER_LENGTH_MIN && strlen($phonenumber) <= PHONE_NUMBER_LENGTH_MAX) {
    return true;
  }
  return false;
}

/**
 * Formatting for Kenya Phone Numbers.
 *
 * @param string $phonenumber
 * @return string Returns a string containting the phone number with some formatting.
 */
function format_ke_phone_number($phonenumber, $field) {
   $phonenumber  = str_replace(array(' ','+','(',')','.','-'), '', $phonenumber);

   if(strlen($phonenumber) >= PHONE_NUMBER_LENGTH_MIN && strlen($phonenumber) <= PHONE_NUMBER_LENGTH_MAX)
       $phonenumber = PHONE_NUMBER_PREFIX . $phonenumber;

   return $phonenumber;
}
